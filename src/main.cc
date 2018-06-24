#include <iostream>

#include <gtkmm.h>
#include <mpd/client.h>

#include "controllers/playback_controller.hh"
#include "controllers/refresh_controller.hh"
#include "controllers/voice_controller.hh"
#include "viewmodels/graphical_user_interface.hh"

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("player.glade");
    }
    catch (const Glib::FileError &ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Glib::MarkupError &ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Gtk::BuilderError &ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    anothr::PlaybackController playbackController;
    anothr::RefreshController refreshController;
    anothr::VoiceController voiceController;
    anothr::GraphicalUserInterface gui(refBuilder, playbackController, refreshController, voiceController);

    app->run(*gui.getMainWindow());
}
