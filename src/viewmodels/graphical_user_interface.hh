#include <gtkmm.h>
#include <vector>
#include <iostream>
#include "../controllers/signal_handler.hh"
#include "../controllers/libmpd_helper.hh"
#include "../controllers/voice_controller.hh"
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

  Gtk::Button *buttonAddToPlaylist;
  Gtk::Button *buttonMicrophone;
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

  SignalHandler signalHandler;
  LibmpdHelper libmpdHelper;
  VoiceController voice;

public:
  GraphicalUserInterface(Glib::RefPtr<Gtk::Builder> refBuilder, SignalHandler signalHandler, LibmpdHelper libmpdHelper, VoiceController voice);

  void addSelectedSongFromLibraryToPlaylist();

  void bindGladeWidgetsToVariables(Glib::RefPtr<Gtk::Builder> refBuilder);

  void bindWidgetSignalsToHandlers();

  void createUnbindableWidgets();

  void displayCurrentSongInWindowTitle();

  void microphoneClicked();

  void nextSong();

  void playMpd();

  void previousSong();

  void refreshDisplayedLibrary();

  void refreshDisplayedPlaylist();

  void removeSelectedSongFromPlaylist();

  void stopMpd();
};
} // namespace Othr