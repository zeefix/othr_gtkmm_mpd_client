#include <gtkmm.h>
#include <vector>
#include <iostream>
#include "../controllers/signal_handler.hh"
#include "../controllers/libmpd_helper.hh"
#include "songlist_columns.hh"

namespace Othr {

/**
 * The Viewmodel for the music player.
 * Contains all widgets that are needed for basic playback controls.
 */
    class GraphicalUserInterface {
    private:
        Gtk::Window *mainWindow;
        Gtk::Button *buttonAddToPlaylist;
        Gtk::ToggleButton *buttonMicrophone;
        Gtk::Button *buttonNext;
        Gtk::Button *buttonPause;
        Gtk::Button *buttonPlay;
        Gtk::Button *buttonPrevious;
        Gtk::Button *buttonRemoveFromPlaylist;
        Gtk::Button *buttonStop;
        Gtk::VolumeButton *buttonVolume;
        Gtk::ProgressBar *progressBar;
        Gtk::TreeView *treeviewPlaylist;
        Gtk::TreeView *treeviewLibrary;

        SonglistColumns playlistModel;
        SonglistColumns libraryModel;

        Glib::RefPtr<Gtk::ListStore> liststorePlaylist;
        Glib::RefPtr<Gtk::ListStore> liststoreLibrary;

    public:
        GraphicalUserInterface(Glib::RefPtr<Gtk::Builder> refBuilder, SignalHandler signalHandler);

        void addSelectedSongFromLibraryToPlaylist();

        void bindGladeWidgetsToVariables(Glib::RefPtr<Gtk::Builder> refBuilder);

        void bindWidgetSignalsToHandlers(SignalHandler signalHandler);

        void createUnbindableWidgets();

        void microphoneClicked();

        void refreshDisplayedLibrary();

        void refreshDisplayedPlaylist();

        void removeSelectedSongFromPlaylist();
    };
}