#include <iostream>
#include <vector>
#include <string>

#include <mpd/client.h>

#include "../models/song_info.hh"

namespace Othr
{

/**
 * Collection of methods calling the libmpdclient library in a more complex way than just "fire and forget".
 */
class RefreshController
{
public:
  std::vector<SongInfo> getCurrentPlaylist();
  std::vector<SongInfo> getMusicDirectoryContents();
  SongInfo getCurrentSong();
};
}