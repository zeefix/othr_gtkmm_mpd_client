#include <iostream>
#include <mpd/client.h>

#include "../configs/mpd_config.hh"

#include "playback_controller.hh"

namespace Othr
{

void PlaybackController::addSongToPlaylistWithTitle(const char *songTitle)
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_add(connection, songTitle))
    {
        std::cout << "Mpd Add: " << songTitle << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::changeVolume(const double volume)
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_set_volume(connection, (volume * 100)))
    {
        std::cout << "Mpd Volume changed: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::nextSong()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_next(connection))
    {
        std::cout << "Mpd Next: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::pauseMpd()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_pause(connection, true))
    {
        std::cout << "Mpd Pause: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::playMpd()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_play(connection))
    {
        std::cout << "Mpd Play: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::previousSong()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_previous(connection))
    {
        std::cout << "Mpd Previous: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::removeSongFromPlaylistAtPosition(int position)
{
    std::cout << position << std::endl;
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_send_delete(connection, position))
    {
        std::cout << "Deleted Song at Position: " << position << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}

void PlaybackController::stopMpd()
{
    auto connection = mpd_connection_new(MpdConfig::mpd_address, MpdConfig::mpd_port, 0);
    bool success = false;

    if (success = mpd_run_stop(connection))
    {
        std::cout << "Mpd Stop: " << connection << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
}
} // namespace Othr