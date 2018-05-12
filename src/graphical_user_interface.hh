#include <gtkmm.h>
#include <vector>
#include <iostream>
#include "signal_handler.hh"
#include "songlist_columns.hh"

namespace Othr
{

/**
 * The Viewmodel for the music player.
 * Contains all widgets that are needed for basic playback controls.
 */
class GraphicalUserInterface
{
private:
  Gtk::Window *mainWindow;
  Gtk::Button *buttonStop;
  Gtk::Button *buttonPlay;
  Gtk::Button *buttonPause;
  Gtk::Button *buttonPrevious;
  Gtk::Button *buttonNext;
  Gtk::VolumeButton *buttonVolume;
  Gtk::Button *buttonAddToPlaylist;
  Gtk::Button *buttonRemoveFromPlaylist;
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
  void refreshDisplayedLibrary();
  void refreshDisplayedPlaylist();
  void removeSelectedSongFromPlaylist();
};
}