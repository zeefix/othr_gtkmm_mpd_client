# Music Player Daemon Client made with gtkmm  

## About

A graphical client for the [music player daemon](https://www.musicpd.org "mpd homepage") with basic playback functionality.
Also contains an experimental natural language interface, which was forked from https://github.com/bierschi/speech_processing (as of 2018.05.20).


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
* all dependencies listed in `[project_root]/src/other_modules/speech_processing/README.md`

### Steps

If you have a good IDE (e.g. [CLion](https://www.jetbrains.com/clion/ "JetBrains CLion Website")): let cmake and make do their magic

If you're building via the terminal:

1. Create the directory `[project_root]/debug` and `cd` into it
2. The voice control feature requires a [Microsoft Cognitive Services Speech to Text](https://azure.microsoft.com/en-us/services/cognitive-services/directory/speech/ "MS Cognitive Services STT Webpage") API Key, so create a `[project_root]/src/other_modules/natural_language_interface/configs/configuration.json` with the following structure: `{ "Bing_Key": "[your_api_key]" }`
3. Adjust `[project_root]/src/configs/mpd_config.hh` to match your mpd setups
4. Run `cmake -DCMAKE_BUILD_TYPE=Debug ..`
5. Run `make`


## Running the Client

1. `cd` into `[project_root]/debug/src/natural_language_interface/MPD_NLP/service`
2. Run `export FLASK_ENV=development`
3. Run `export FLASK_APP=parse.py`
4. Run `flask run`
5. `cd` into `[project_root]/debug/src`
6. Run the executable `./out` 


## The Natural Language Interface

is currently pretty buggy. 

To use it, add the desired songs to the playlist via the GUI. Then click the "mic"-Button and wait for the terminal to say "Please say something...". Speak loudly and clearly into your microphone, e.g. "Please play '[your_song_title]'".

If your Flask server throws an error or shuts itself down for some reason, restart your computer. 
If you were understood correctly, this is where the bugs happen. Sometimes your whole library will be added to the playlist, including your desired song TWICE.

Then the playback starts. Enjoy!