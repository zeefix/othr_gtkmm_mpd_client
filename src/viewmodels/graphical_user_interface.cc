#include "graphical_user_interface.hh"

namespace Othr
{

GraphicalUserInterface::GraphicalUserInterface(Glib::RefPtr<Gtk::Builder> refBuilder, SignalHandler signalHandler, LibmpdHelper libmpdHelper, VoiceController voice)
    : signalHandler(signalHandler), libmpdHelper(libmpdHelper), voice(voice)
{
    refBuilder->add_from_file("player.glade");
    bindGladeWidgetsToVariables(refBuilder);
    createUnbindableWidgets();

    refreshDisplayedPlaylist();
    refreshDisplayedLibrary();

    bindWidgetSignalsToHandlers();

    displayCurrentSongInWindowTitle();
}

/**
 * Get the selected row from the library Treeview, and add the appropriate song via its title to the playlist.
 */
void GraphicalUserInterface::addSelectedSongFromLibraryToPlaylist()
{
    Glib::RefPtr<Gtk::TreeSelection> selection = treeviewLibrary->get_selection();
    Gtk::TreeModel::iterator selectedIterator = selection->get_selected();

    if (selectedIterator) //If anything is selected
    {
        Gtk::TreeModel::Row row = *selectedIterator;

        // Conversion of songtitle via two "="-statements is necessary, because
        // row[playlistModel.songTitle] is of type "Gtk::TreeValueProxy<Glib::ustring>", and therefore does not contain a method c_str().
        Glib::ustring songTitleUstring = row[playlistModel.songTitle];
        const char *SongTitleCharpointer = songTitleUstring.c_str();

        SignalHandler handler;
        handler.addSongToPlaylistWithTitle(SongTitleCharpointer);
        refreshDisplayedPlaylist();
    }
    else
    {
        std::cout << "Nothing selected in Library." << std::endl;
    }
}

/**
 * Binds the widgets to variables via the ids you declared in the .glade file.
 * refBuilder->get_widget(yourWidgetId, theVariableYouWantToBindItTo); 
 */
void GraphicalUserInterface::bindGladeWidgetsToVariables(Glib::RefPtr<Gtk::Builder> refBuilder)
{
    refBuilder->get_widget("window_main", mainWindow);
    refBuilder->get_widget("button_add-to-playlist", buttonAddToPlaylist);
    refBuilder->get_widget("button_microphone", buttonMicrophone);
    refBuilder->get_widget("button_next", buttonNext);
    refBuilder->get_widget("button_pause", buttonPause);
    refBuilder->get_widget("button_play", buttonPlay);
    refBuilder->get_widget("button_previous", buttonPrevious);
    refBuilder->get_widget("button_remove-from-playlist", buttonRemoveFromPlaylist);
    refBuilder->get_widget("button_stop", buttonStop);
    refBuilder->get_widget("button_volume", buttonVolume);
    refBuilder->get_widget("treeview_playlist", treeviewPlaylist);
    refBuilder->get_widget("treeview_library", treeviewLibrary);
}

/**
 * Binds the user's interactions with the GUI to their appropriate methods, both inside the class and outside.
 * E.g.: when the stop button (buttonStop) is being clicked (signal_clicked), 
 * the member function (mem_fun) "stopMpd" of the object "signalHandler" will be called (with no parameters).
 */
void GraphicalUserInterface::bindWidgetSignalsToHandlers()
{
    buttonStop->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::stopMpd));
    buttonPlay->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::playMpd));
    buttonPause->signal_clicked().connect(sigc::mem_fun(signalHandler, &SignalHandler::pauseMpd));
    buttonPrevious->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::previousSong));
    buttonNext->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::nextSong));

    buttonMicrophone->signal_clicked().connect(sigc::mem_fun(voice, &VoiceController::listen));
    buttonRemoveFromPlaylist->signal_clicked().connect(
        sigc::mem_fun(this, &GraphicalUserInterface::removeSelectedSongFromPlaylist));
    buttonAddToPlaylist->signal_clicked().connect(
        sigc::mem_fun(this, &GraphicalUserInterface::addSelectedSongFromLibraryToPlaylist));

    // Volume parameter muss nicht explizit in mem_fun oder bind angegeben werden, da er in signal_value_changed implizit mituebergeben wird.
    // Er kann in der angegebenen Methode einfach als const double angenommen werden.
    buttonVolume->signal_value_changed().connect(sigc::mem_fun(signalHandler, &SignalHandler::changeVolume));
}

/**
 * Binds those widgets that cannot be defined in Glade when using Gtkmm. 
 * For example the C (as used in Glade) and C++ types are just too different, 
 * and the statically-typed C++ API can't know about your glade file's TreeModel definition at compile time.
 * See: https://stackoverflow.com/questions/28200839/glade-constructed-treeview-with-gtkmm
 */
void GraphicalUserInterface::createUnbindableWidgets()
{
    liststorePlaylist = Gtk::ListStore::create(playlistModel);
    liststoreLibrary = Gtk::ListStore::create(libraryModel);

    treeviewPlaylist->set_model(liststorePlaylist);
    treeviewLibrary->set_model(liststoreLibrary);

    // If you are accessing a property of an object or object reference, use . If you are accessing a property of an object through a pointer, use ->
    treeviewPlaylist->append_column("Position", playlistModel.songPosition);
    treeviewPlaylist->append_column("Id", playlistModel.songId);
    treeviewPlaylist->append_column("Title", playlistModel.songTitle);

    treeviewLibrary->append_column("Position", libraryModel.songPosition);
    treeviewLibrary->append_column("Id", libraryModel.songId);
    treeviewLibrary->append_column("Title", libraryModel.songTitle);
}

void GraphicalUserInterface::displayCurrentSongInWindowTitle()
{
    SongInfo currentSong = libmpdHelper.getCurrentSong();

    Glib::ustring songTitle = Glib::ustring(currentSong.uri);
    mainWindow->set_title(songTitle + "[Othr Gtkmm Player]");
}

void GraphicalUserInterface::nextSong()
{
    signalHandler.nextSong();
    displayCurrentSongInWindowTitle();
}

void GraphicalUserInterface::playMpd()
{
    signalHandler.playMpd();
    displayCurrentSongInWindowTitle();
}

void GraphicalUserInterface::previousSong()
{
    signalHandler.previousSong();
    displayCurrentSongInWindowTitle();
}

/**
 * Clears the displayed song library in the client, fetches the songs which are currently in the mpd music directory, and refills it.
 */
void GraphicalUserInterface::refreshDisplayedLibrary()
{
    auto librarySongs = libmpdHelper.getMusicDirectoryContents();

    std::cout << librarySongs.size() << std::endl;
    for (int i = 0; i < librarySongs.size(); i++)
    {
        Gtk::TreeModel::iterator iter = liststoreLibrary->append();
        auto row = *iter;

        // Benutze die TreeModelColumn<entsprechenderTyp> mit dem . Operator
        row[libraryModel.songTitle] = librarySongs[i].uri;
        row[libraryModel.songId] = librarySongs[i].id;
        row[libraryModel.songPosition] = librarySongs[i].position;
    }
}

/**
 * Clears the displayed playlist, fetches the current playlist from mpd, and refills it.
 */
void GraphicalUserInterface::refreshDisplayedPlaylist()
{
    liststorePlaylist->clear();
    auto songsInfo = libmpdHelper.getCurrentPlaylist();

    for (int i = 0; i < songsInfo.size(); i++)
    {
        Gtk::TreeModel::iterator iter = liststorePlaylist->append();
        auto row = *iter;

        // Use the TreeModelColumn<appropriateType> with the "."-operator
        row[playlistModel.songTitle] = songsInfo[i].uri;
        row[playlistModel.songId] = songsInfo[i].id;
        row[playlistModel.songPosition] = songsInfo[i].position;
    }
}

/**
 * Removes the currently selected song from the playlist by getting its position from the Gtk::TreeSelection, and sending it to the mpd server.
 */
void GraphicalUserInterface::removeSelectedSongFromPlaylist()
{
    Glib::RefPtr<Gtk::TreeSelection> selection = treeviewPlaylist->get_selection();

    Gtk::TreeModel::iterator selectedIterator = selection->get_selected();

    if (selectedIterator) //If anything is selected
    {
        Gtk::TreeModel::Row row = *selectedIterator;

        SignalHandler handler;
        handler.removeSongFromPlaylistAtPosition(row[playlistModel.songPosition]);
        refreshDisplayedPlaylist();
        displayCurrentSongInWindowTitle();
    }
    else
    {
        std::cout << "Nothing selected in Playlist." << std::endl;
    }
}

void GraphicalUserInterface::stopMpd()
{
    signalHandler.stopMpd();
    displayCurrentSongInWindowTitle();
}

} // namespace Othr