# Music Player Daemon Client made with GTKmm  

## Installation

### Dependencies

* libmpdclient 
    * Easy: get the libmpdclient-dev package, which is from April 2017
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/libmpdclient/ "mpd libmpdclient download section")
* gtkmm:
    * download the libgtkmm-3.0-dev package with the package manager of your choice
    * or follow the instructions on the [gtkmm.org website](https://www.gtkmm.org/en/download.html "gtkmm download section")
* mpd (or else this client would be pretty useless):
    * Easy: get the mpd package with the package manager of your choice
    * Hard: download and build the source files from the [musicpd.org website](https://www.musicpd.org/download/mpd/ "mpd download section")

### Steps

If you have a good IDE: let cmake and make do their magic

If you're building via the terminal:

1. Create a directory "debug" in the project directory
2. Write `cmake -DCMAKE_BUILD_TYPE=Debug ..`
3. Write `make`
4. The executable is in [project]/debug/src
