#include <vector>

#include <mpd/client.h>

#include "../models/song_info.hh"

#ifndef ANOTHR_REFRESH_CONTROLLER_H
#define ANOTHR_REFRESH_CONTROLLER_H

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
} // namespace anothr

#endif