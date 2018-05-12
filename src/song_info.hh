#include <gtkmm.h>

namespace Othr
{

/**
 * An MVC Model used to store all relevant information of a song.
 */
class SongInfo
{
public:
  SongInfo(const char *songUri, unsigned int songPosition, unsigned int songId);
  SongInfo(Glib::ustring songUri, unsigned int songPosition, unsigned int songId);
  Glib::ustring uri;
  unsigned int position;
  unsigned int id;
};
}