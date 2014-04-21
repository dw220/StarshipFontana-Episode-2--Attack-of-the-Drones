#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <memory>
#include <iostream>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFBoundingBox.h"

class sound {
public:
sound();
void laser();
void coin();
void clearAudio();
private:

};

#endif
