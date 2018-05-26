/**
 * This class controlls the playback behaviour of the mpd server.
 */

#ifndef ANOTHR_PLAYBACK_CONTROLLER_H
#define ANOTHR_PLAYBACK_CONTROLLER_H

namespace anothr
{

class PlaybackController
{
public:
  void addSongToPlaylistWithTitle(const char *songTitle);
  void changeVolume(const double volume);
  void nextSong();
  void pauseMpd();
  void playMpd();
  void previousSong();
  void removeSongFromPlaylistAtPosition(int position);
  void stopMpd();
};
} // namespace anothr

#endif