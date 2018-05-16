#include <iostream>
#include <mpd/client.h>
#include <string>

namespace Othr
{

class SignalHandler
{
public:
  SignalHandler();
  void addSongToPlaylistWithTitle(const char *songTitle);
  void changeVolume(const double volume);
  void nextSong();
  void pauseMpd();
  void playMpd();
  void previousSong();
  void removeSongFromPlaylistAtPosition(int position);
  void stopMpd();
};
}