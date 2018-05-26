/**
 * This class is concerned with receiving information from the mpd server.
 * That information may be used to for example update the View.
 */

#include <vector>

#include <mpd/client.h>

#include "../models/song_info.hh"

#ifndef ANOTHR_REFRESH_CONTROLLER_H
#define ANOTHR_REFRESH_CONTROLLER_H

namespace anothr
{

class RefreshController
{
public:
  std::vector<SongInfo> getCurrentPlaylist();
  std::vector<SongInfo> getMusicDirectoryContents();
  SongInfo getCurrentSong();
};
} // namespace anothr

#endif