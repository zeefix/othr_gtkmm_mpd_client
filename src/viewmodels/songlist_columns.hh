/**
 * Defines the columns for the Treeviews containing song information, i.e. the library and the playlist.
 * Each member variable needs to be added (add(<memberVar>)) in the constructor.
 * An instance of this class can then be passed to ListStore::create(<instance>) or TreeStore::create(<instance>).
 * The SonglistColumns can then be used with the Gtk::TreeRow::operator[]() to specify the column you're interested in. For example:
 * row[playlistColumns.songPosition].
 */

#include <gtkmm.h>

#ifndef ANOTHR_SONGLIST_COLUMNS_H
#define ANOTHR_SONGLIST_COLUMNS_H

namespace anothr
{

class SonglistColumns : public Gtk::TreeModelColumnRecord
{
public:
  SonglistColumns();
  Gtk::TreeModelColumn<int> songPosition;
  Gtk::TreeModelColumn<int> songId;
  Gtk::TreeModelColumn<Glib::ustring> songTitle;
};
} // namespace anothr

#endif