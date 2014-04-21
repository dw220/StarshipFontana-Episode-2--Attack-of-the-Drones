#include <SDL/SDL.h>  // Pull in the SDL definitions
#include <SDL/SDL_mixer.h>
#include "sound.h"
using namespace std;
sound::sound()
{
  /// open the sound for the file
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,2,4096);   
  //Stores the music in a Mix varible
  Mix_Music* music;
  //loading the music to the game
  music=Mix_LoadMUS("assets/music.wav");
  //loops the music
  Mix_PlayMusic(music, -1);

}


void laser()
{

    Mix_Chunk* shot;
    shot = Mix_LoadWAV("assets/shot.WAV");
    Mix_PlayChannel( -1, shot, 0);

}


void coin()
{
    Mix_Chunk* shot;
    shot = Mix_LoadWAV("assets/shot.WAV");
    Mix_PlayChannel( -1, shot, 0);
}


void clearAudio()
{
   Mix_CloseAudio();//Close all the of th audio componeents opena
}

