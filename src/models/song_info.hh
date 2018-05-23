#include <gtkmm.h>

#ifndef ANOTHR_SONG_INFO_H
#define ANOTHR_SONG_INFO_H

namespace anothr
{

/**
 * An MVC Model used to store all relevant information of a song.
 */
class SongInfo
{
public:
  SongInfo();
  SongInfo(const char *songUri, unsigned int songPosition, unsigned int songId);
  SongInfo(Glib::ustring songUri, unsigned int songPosition, unsigned int songId);
  bool isEmpty();

  Glib::ustring uri;
  unsigned int position;
  unsigned int id;
};
} // namespace anothr

#endif