#include <iostream>

#include "graphical_user_interface.hh"

namespace anothr
{

GraphicalUserInterface::GraphicalUserInterface(Glib::RefPtr<Gtk::Builder> refBuilder, PlaybackController playbackController, RefreshController refreshController, VoiceController voiceController)
    : playbackController(playbackController), refreshController(refreshController), voiceController(voiceController)
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

        playbackController.addSongToPlaylistViaTitle(SongTitleCharpointer);
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
 * the member function (mem_fun) "stopMpd" of the object "playbackController" will be called (with no parameters).
 */
void GraphicalUserInterface::bindWidgetSignalsToHandlers()
{
    buttonStop->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::stopMpd));
    buttonPlay->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::playMpd));
    buttonPause->signal_clicked().connect(sigc::mem_fun(playbackController, &PlaybackController::pauseMpd));
    buttonPrevious->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::previousSong));
    buttonNext->signal_clicked().connect(sigc::mem_fun(this, &GraphicalUserInterface::nextSong));

    buttonMicrophone->signal_clicked().connect(sigc::mem_fun(voiceController, &VoiceController::runVoiceRecognition));
    buttonRemoveFromPlaylist->signal_clicked().connect(
        sigc::mem_fun(this, &GraphicalUserInterface::removeSelectedSongFromPlaylist));
    buttonAddToPlaylist->signal_clicked().connect(
        sigc::mem_fun(this, &GraphicalUserInterface::addSelectedSongFromLibraryToPlaylist));

    // Volume parameter does not have to be explicitly written in mem_fun/bind.
    // It will be implicitly passed in signal_value_changed.
    buttonVolume->signal_value_changed().connect(sigc::mem_fun(playbackController, &PlaybackController::changeVolume));

    //Glib::signal_timeout().connect( sigc::mem_fun(this, &GraphicalUserInterface::updateProgressbar), 2000);
}

/**
 * Binds those widgets that cannot be defined in Glade when using Gtkmm. 
 * For example the C (as used in Glade) and C++ types are too different. 
 * The statically-typed C++ API can't know about the .glade file's TreeModel definition at compile time.
 * See: https://stackoverflow.com/questions/28200839/glade-constructed-treeview-with-gtkmm
 */
void GraphicalUserInterface::createUnbindableWidgets()
{
    liststorePlaylist = Gtk::ListStore::create(playlistModel);
    liststoreLibrary = Gtk::ListStore::create(libraryModel);

    treeviewPlaylist->set_model(liststorePlaylist);
    treeviewLibrary->set_model(liststoreLibrary);

    treeviewPlaylist->append_column("Position", playlistModel.songPosition);
    treeviewPlaylist->append_column("Id", playlistModel.songId);
    treeviewPlaylist->append_column("Title", playlistModel.songTitle);

    treeviewLibrary->append_column("Position", libraryModel.songPosition);
    treeviewLibrary->append_column("Id", libraryModel.songId);
    treeviewLibrary->append_column("Title", libraryModel.songTitle);
}

void GraphicalUserInterface::displayCurrentSongInWindowTitle()
{
    SongInfo currentSong = refreshController.getCurrentSong();

    Glib::ustring songTitle = Glib::ustring(currentSong.uri);
    mainWindow->set_title(songTitle + " [Anothr]");
}

void GraphicalUserInterface::nextSong()
{
    playbackController.nextSong();
    displayCurrentSongInWindowTitle();
}

void GraphicalUserInterface::playMpd()
{
    playbackController.playMpd();
    displayCurrentSongInWindowTitle();
}

void GraphicalUserInterface::previousSong()
{
    playbackController.previousSong();
    displayCurrentSongInWindowTitle();
}

void GraphicalUserInterface::refreshDisplayedLibrary()
{
    auto librarySongs = refreshController.getSongsInLibrary();

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

void GraphicalUserInterface::refreshDisplayedPlaylist()
{
    liststorePlaylist->clear();
    auto songsInfo = refreshController.getSongsInPlaylist();

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

void GraphicalUserInterface::removeSelectedSongFromPlaylist()
{
    Glib::RefPtr<Gtk::TreeSelection> selection = treeviewPlaylist->get_selection();

    Gtk::TreeModel::iterator selectedIterator = selection->get_selected();

    if (selectedIterator) //If anything is selected
    {
        Gtk::TreeModel::Row row = *selectedIterator;

        playbackController.removeSongFromPlaylistAtPosition(row[playlistModel.songPosition]);
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
    playbackController.stopMpd();
    displayCurrentSongInWindowTitle();
}

bool GraphicalUserInterface::updateProgressbar()
{
    //double elapsed = refreshController.getElapsedSongTimeFraction();
    double elapsed = 0.0;
    progressBar->set_fraction(elapsed);

    return true;
}

} // namespace anothr