#include "songlist_columns.hh"

namespace Othr
{

SonglistColumns::SonglistColumns()
{
    //A ColumnRecord instance, such as an instance of MyModelColumns should then be passed to ListStore::create() or TreeStore::create().
    //The TreeModelColumns, such as the members filename, description and thumbnail can then be used with Gtk::TreeRow::operator[]() to specify the column you're interested in.
    add(songId);
    add(songTitle);
    add(songPosition);
}
}