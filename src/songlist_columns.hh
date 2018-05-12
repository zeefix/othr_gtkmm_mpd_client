#include <gtkmm.h>
#include "libmpd_helper.hh"

namespace Othr
{

/**
 * Defines the columns for the Treeviews "treeviewPlaylist" and "treeviewLibrary".
 * Each member variable need to be added (add(memberVar)) in the constructor.
 * A ColumnRecord instance, such as an instance of this class should then be passed to ListStore::create(<here>) or TreeStore::create(<here>).
 * The TreeModelColumns, can then be used with Gtk::TreeRow::operator[]() to specify the column you're interested in. E.g.: row[playlistColumns.songPosition]
 */
class SonglistColumns : public Gtk::TreeModelColumnRecord
{
public:
  SonglistColumns();
  Gtk::TreeModelColumn<int> songPosition;
  Gtk::TreeModelColumn<int> songId;
  Gtk::TreeModelColumn<Glib::ustring> songTitle;
};
}