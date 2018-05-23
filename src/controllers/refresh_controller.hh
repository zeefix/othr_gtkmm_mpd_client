#include <vector>

#include <mpd/client.h>

#include "../models/song_info.hh"

namespace anothr
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