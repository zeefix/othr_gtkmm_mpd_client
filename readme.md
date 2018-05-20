# Music Player Daemon Client made with gtkmm  

## About

A graphical client for the [music player daemon](https://www.musicpd.org "mpd homepage") with basic playback functionality.
Also contains an experimental natural language interface, which was forked from https://github.com/bierschi/speech_processing (as of 2018.05.20).

## Installation

### Dependencies

* libmpdclient 
    * Easy: get the `libmpdclient-dev` package (from April 2017) with the packagemanager of your choice
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/libmpdclient/ "mpd libmpdclient download section")
* gtkmm:
    * download the `libgtkmm-3.0-dev` package with the package manager of your choice
    * or follow the instructions on the [gtkmm.org website](https://www.gtkmm.org/en/download.html "gtkmm download section")
* mpd (or else this client would be pretty useless):
    * Easy: get the `mpd` package with the package manager of your choice
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/mpd/ "mpd download section")
* python3 (NOT python!)
* all dependencies listed in [project_root]/src/other_modules/speech_processing/README.md

### Steps

If you have a good IDE (e.g. [CLion](https://www.jetbrains.com/clion/ "JetBrains CLion Website")): let cmake and make do their magic

If you're building via the terminal:

1. Create the directory `[project_root]/debug` and `cd` into it
2. The voice control feature requires a [Microsoft Cognitive Services Speech to Text](https://azure.microsoft.com/en-us/services/cognitive-services/directory/speech/ "MS Cognitive Services STT Webpage") API Key, so create a `[project_root]/src/other_modules/speech_processing/configs/configuration.json` with the following structure:
    {
        "Bing_Key": "[your_api_key]"
    }
3. Write `cmake -DCMAKE_BUILD_TYPE=Debug ..`
4. Write `make`
5. `cd` into `[project_root]/debug/src/speech_processing/MPD_NLP/service`
6. Write `export FLASK_ENV=development`
7. Write `export FLASK_APP=parse.py`
8. Write `flask run`
9. Make sure mpd runs on `localhost:6600`
10. Execute the executable `out` from `[project_root]/debug/src`