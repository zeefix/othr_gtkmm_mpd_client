#include <iostream>

#include "../configs/mpd_config.hh"

#include "refresh_controller.hh"

namespace anothr
{

SongInfo RefreshController::getCurrentSong()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);

    SongInfo currentSongInfo;

    if (auto currentMpdSong = mpd_run_current_song(connection))
    {
        currentSongInfo.uri = mpd_song_get_uri(currentMpdSong);
        currentSongInfo.position = mpd_song_get_pos(currentMpdSong);
        currentSongInfo.id = mpd_song_get_id(currentMpdSong);

        mpd_song_free(currentMpdSong);
    }

    mpd_response_finish(connection);
    mpd_connection_free(connection);

    return currentSongInfo;
}

std::vector<SongInfo> RefreshController::getSongsInLibrary()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    std::vector<SongInfo> songsInfo;

    if (mpd_send_list_all(connection, ""))
    {

        mpd_entity *entity;

        while ((entity = mpd_recv_entity(connection)) != NULL)
        {
            const char *uri;
            unsigned int id;
            unsigned int position;
            if (mpd_entity_get_type(entity) == MPD_ENTITY_TYPE_SONG)
            {
                const mpd_song *mpdSong = mpd_entity_get_song(entity);
                uri = mpd_song_get_uri(mpdSong);
                id = mpd_song_get_id(mpdSong);
                position = mpd_song_get_pos(mpdSong);
            }
            else
            {
                std::cout << "Entity not of type Song." << std::endl;
            }
            SongInfo songInfo(uri, position, id);
            songsInfo.push_back(songInfo);
            mpd_entity_free(entity);
        }

        mpd_response_finish(connection);
        mpd_connection_free(connection);
    }
    else
    {
        std::cout << "Error in getMusicDirectoryContents" << std::endl;
    }

    return songsInfo;
}

std::vector<SongInfo> RefreshController::getSongsInPlaylist()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);

    std::vector<SongInfo> songsInfo;

    if (mpd_send_list_queue_meta(connection))
    {
        mpd_song *song;

        while ((song = mpd_recv_song(connection)) != NULL)
        {
            auto uri = mpd_song_get_uri(song);
            auto position = mpd_song_get_pos(song);
            auto id = mpd_song_get_id(song);

            std::cout << uri << std::endl;

            SongInfo songInfo(uri, position, id);
            songsInfo.push_back(songInfo);

            mpd_song_free(song);
        }
    }
    else
    {
        std::cout << "Error in getCurrentPlaylist" << std::endl;
    }

    mpd_response_finish(connection);
    mpd_connection_free(connection);

    return songsInfo;
}
} // namespace anothr