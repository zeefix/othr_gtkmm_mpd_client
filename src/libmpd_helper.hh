#include <iostream>
#include <vector>
#include <string>

#include <mpd/client.h>

#include "song_info.hh"

namespace Othr
{

/**
 * Collection of methods calling the libmpdclient library in a more complex way than just "fire and forget".
 */
class LibmpdHelper
{
public:
  std::vector<SongInfo> getCurrentPlaylist();
  std::vector<SongInfo> getMusicDirectoryContents();
};
}