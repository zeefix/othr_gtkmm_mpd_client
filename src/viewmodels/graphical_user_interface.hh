/**
 * The Viewmodel for the music player.
 * Contains all widgets and methods used to interact with them.
 */

#include <gtkmm.h>

#include "../controllers/playback_controller.hh"
#include "../controllers/refresh_controller.hh"
#include "../controllers/voice_controller.hh"

#include "songlist_columns.hh"

#ifndef ANOTHR_GRAPHICAL_USER_INTERFACE_H
#define ANOTHR_GRAPHICAL_USER_INTERFACE_H

namespace anothr
{

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

  PlaybackController playbackController;
  RefreshController refreshController;
  VoiceController voiceController;

public:
  GraphicalUserInterface(
      Glib::RefPtr<Gtk::Builder> refBuilder,
      PlaybackController playbackController,
      RefreshController refreshController,
      VoiceController voiceController);

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
} // namespace anothr

#endif