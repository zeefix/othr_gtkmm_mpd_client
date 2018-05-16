#include "song_info.hh"
#include <iostream>
namespace Othr
{

SongInfo::SongInfo(const char *songUri, unsigned int songPosition, unsigned int songId)
{
  uri = songUri;
  position = songPosition;
  id = songId;
}

SongInfo::SongInfo(Glib::ustring songUri, unsigned int songPosition, unsigned int songId)
{
  uri = songUri;
  position = songPosition;
  id = songId;
}
}