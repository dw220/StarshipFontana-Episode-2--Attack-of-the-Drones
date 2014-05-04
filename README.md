# Starship Fontana Episode 2#
This was a C++ application written using the SDL librarys and C++
With added highscore feature which permenantly saves the players score.
Using the SDL_mixer library for sound. Please enjoy playing the game
and email me for any questions at dw220@brighton.ac.uk.

## Story ##
The second part to the thrilling StarshipFontana series, With the emperors troops patroling 
the ground, can you find all of the resources before they find you?

## Installation ##
You will have to have the SDL development libraries installed on
your system.  
To install the librarys needed the following command will work
`$ sudo yum install SDL*`
The easiest way to compile is to use a command-line
in the directory run the following commands to compile and start 
the game

`$ g++ -c -std=c++11 src/*.cpp`
`$ g++ -o StarshipFontana *.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf`

which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$./StarshipFontana`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites were taken from http://www.lostgarden.com/search/label/free%20game%20graphics
All the sounds where created by the developer, "Darren Ward"

The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
