# Anothr - an mpd client made with gtkmm  

## About

A graphical client for the [music player daemon](https://www.musicpd.org "mpd homepage") with basic playback functionality.
It contains https://github.com/bierschi/speech_processing as a submodule, which is an experimental natural language interface.


## Installation

### Dependencies

* libmpdclient 
    * Easy: get the `libmpdclient-dev` package (last updated in April 2017, but good enough for this client) with the packagemanager of your choice
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/libmpdclient/ "mpd libmpdclient download section")
* gtkmm:
    * download the `libgtkmm-3.0-dev` package with the package manager of your choice
    * or follow the instructions on the [gtkmm.org website](https://www.gtkmm.org/en/download.html "gtkmm download section")
* mpd (or else this client would be pretty useless):
    * Easy: get the `mpd` package with the package manager of your choice
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/mpd/ "mpd download section")
* python: download and install the `python3` and `python3-dev` packages
* flask: download and install Flask with Python's package manager: `pip3 install flask`
* all dependencies listed in `<project_root>/src/other_modules/speech_processing/README.md`

### Steps

1. Adjust `<project_root>/src/configs/mpd_config.hh` to match your mpd setup
2. Create the directory `<project_root>/debug/` and `cd` into it
3. Run `cmake ..`
4. Run `make`
5. `cd` into `<project_root>/debug/src/speech_processing/`
5. Run `sudo python3 setup.py install` 


## Running the Client

1. `cd` into `<project_root>/debug/src/speech_processing/`
2. Run `export FLASK_APP=parse_server.py`
3. Run `flask run`
4. Open a new terminal and `cd` into `<project_root>/debug/src/`
5. Run the executable `sudo ./anothrclient` 


## The Natural Language Interface

To use it, add the desired songs to the playlist via the GUI. Then click the "mic"-Button and wait for the terminal to say "Please say something...". Speak loudly and clearly into your microphone, e.g. "Please play '[your_song_title]'".

Then the playback starts. Enjoy!