#include "signal_handler.hh"

namespace Othr
{

SignalHandler::SignalHandler() {}

void SignalHandler::addSongToPlaylistWithTitle(const char *songTitle)
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
    bool success = false;

    if (success = mpd_run_add(connection, songTitle))
    {
        std::cout << "Mpd Add: " << std::string(songTitle) << std::endl;
    }
    else
    {
        std::cout << "Mpd Connection Error: " << mpd_connection_get_error(connection) << std::endl;
    }

    mpd_connection_free(connection);
    //std::cout << "in addSongToPlaylistWithTitle(" + std::string(songTitle) + ")" << std::endl;
}

void SignalHandler::changeVolume(const double volume)
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::nextSong()
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::pauseMpd()
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::playMpd()
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::previousSong()
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::removeSongFromPlaylistAtPosition(int position)
{
    std::cout << position << std::endl;
    auto connection = mpd_connection_new("localhost", 6600, 0);
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

void SignalHandler::stopMpd()
{
    auto connection = mpd_connection_new("localhost", 6600, 0);
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
}