#include "SFApp.h"
#include "sound.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "SFEvent.h"
#include <iostream>
#include <fstream>
#include <string>
#include "highscore.h"




//sound functions for laser shot/coin collection from sound.h
void theScore(int highScore);
void laser();//Laser sound
void coin();//Coin collection sound.
void GetLastCode();
//Score for total aliens killed.
 int totalKilled = 0;



SFApp::SFApp() : fire(0), is_running(true) {
  
float alienPos = 500;

  surface = SDL_GetVideoSurface();
  app_box = make_shared<SFBoundingBox>(Vector2(surface->w/2, surface->h/2), surface->w/2, surface->h/2);
  player  = make_shared<SFAsset>(SFASSET_PLAYER);
  auto player_pos = Point2(surface->w/2, 100.0f);
  player->SetPosition(player_pos);
////////////////////////////////////////////////////////////////////////////////////////////////////////
  const int number_of_aliens = 8; // new number of aliens i picked

  int row = 1; // To place the aliens on the map i will check where the
  int y = 150; // where the alien will be placed
  int width = 0;
  for(int i=0; i<number_of_aliens; i++) {
	if(row % 2 == 1){//using modulus to get remainder
	 alienPos = y; // set current position to y, if row is odd number
	 width = 50;
	} 
        else if( row % 2 == 0){// set position of alien to , if row is even number
	 alienPos = y;
	 width = 600;
           }
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2(width, alienPos);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  row++;//adding to row for next check of odd or even
  y = y + 50;//add to y to position the next row

  }

const int COIN = 10;


srand(time(0));// call to randomise spawn
for(int c = 0; c < COIN; c++){

int coinWidth = rand()% 600;//random spawn for coin
int coinHeight =rand()% 451;//random spawn for coin
  auto coin = make_shared<SFAsset>(SFASSET_COIN);
  auto pos  = Point2(coinWidth, coinHeight);
  coin->SetPosition(pos);
  coins.push_back(coin);
}


const int numberHouse = 2;
int blockWidth = 100;
int blockHeight= 300;
for(int j=0; j<numberHouse;j++){

auto house1 = make_shared<SFAsset>(SFASSET_HOUSE);
auto pos = Point2(blockWidth,blockHeight);
house1->SetPosition(pos);
house.push_back(house1);
blockWidth = blockWidth + 400;} 
}



SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
int lastCode;
int up = 1;
int west = 2;
int east = 3;
int south = 4;
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWestFast();
    lastCode = west;
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEastFast();
    lastCode = east;
    break;
  case SFEVENT_PLAYER_UP:
    lastCode = up;
    player->GoNorthFast();
    break; 
   case SFEVENT_PLAYER_DOWN:
    lastCode = south;
    player->GoSouthFast();
    break;

  case SFEVENT_FIRE:
/////////////////////////////////////////////////////////////////////////
    laser();//Laser SFX
    fire ++;
    std::stringstream sstm;
    sstm << "Lasers fired: " << fire;
    SDL_WM_SetCaption(sstm.str().c_str(),  sstm.str().c_str());
    FireProjectile();
   ///////////////////////////////////////////////////////////////// 
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app

  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {

    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}


void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
   p->GoNorthFast();
   }
  for(auto c: coins) {
   // c->GoSouth();
  }
  // Update enemy positions

bool isEven = true;//Bool to check if row is even for moving the aliens left or right.


for(auto a : aliens) {
     isEven = !isEven; // set even to the opposite, AKA false
	    if(isEven){ // if the row is even the go west
	     a->GoWestSlow();
	   } 
	    else {//else if it is not even then aliens must go east
	     a->GoEastSlow();
	}
 }


for(auto c : coins){
  if(c->CollidesWith(player)){
   c->HandleCollision();//if collisionbetween player and coins this will happen
   totalKilled = totalKilled + 100;//adding to the main high score
  //add coin sound here///
 }
}




   //Blockades 
for(auto h : house){
 if(h->CollidesWith(player))
{
  switch(lastCode){
  case 1:
  player->GoSouthFast();
  break;
  case 2:
  player->GoEastFast();
  break;
  case 3:
  player->GoWestFast();
  break;
  case 4:
  player->GoNorthFast();
  break;

}
 }    
  }

       for(auto a : aliens) {
         int hitCount = 0;
           for(auto p : projectiles ) {
                     if(p->CollidesWith(a)) {
                        p->HandleCollision();
			a->HandleCollision();
                        totalKilled = totalKilled + 100;//Adding to the high score
                      }
 		}
       }  
       
    
//Collision between House/Aliens if true game is ended !
 


for(auto p : projectiles) {
    for(auto c : coins) {
      if(p->CollidesWith(c)){  
        p->HandleCollision();
        c->HandleCollision();  

        //coin();// Add a sound here for the coin collection <=========**********************************
      }
    }
  }
/*
////Bots used for the higher score////
int bot1 = 100;
int bot2 = 200;
int bot3 = 300;
////////////////////////////////////////

std::stringstream gameOver;
gameOver << "Game Over your total Score was: " << totalKilled;
string userName; // String holding the users name Will display score and name.*/

for( auto a : aliens){

if(player->CollidesWith(a)){

theScore(totalKilled);

/*cout<<gameOver.str().c_str()<<endl;//end game message
cout<< "*********High Scores*****************"<< endl <<"************************** " << endl;
printf("%-25s%-20s%\n", "Name", "Score"); 

// Each printf is used to justify the tables left to make it look neat when printing out the text.
if(totalKilled > bot3){
printf("%-25s%-20d%\n", "YourScore", totalKilled);//Prints out highscores based on position on the table
printf("%-25s%-20d%\n", "bot3", bot3);// each printf justifys to the left
printf("%-25s%-20d%\n", "bot2", bot2);
printf("%-25s%-20d%\n", "bot1", bot1);}

else if (totalKilled < bot2 || totalKilled > bot3){//Prints out highscores based on position on the table
printf("%-25s%-20d%\n", "Darren", bot3);
printf("%-25s%-20d%\n", "YourScore", totalKilled);
printf("%-25s%-20d%\n", "Bob", bot2);
printf("%-25s%-20d%\n", "Randal", bot1);
}

else if(totalKilled > bot1 || totalKilled > bot2){//Prints out highscores based on position on the table
printf("%-25s%-20d%\n", "Darren", bot3);
printf("%-25s%-20d%\n", "Bob", bot2);
printf("%-25s%-20d%\n", "Randal", bot1);
printf("%-25s%-20d%\n", "YourScore", totalKilled);//Prints out highscores based on position on the table
}
*/
exit(0);//exit the game once the endgame message/high score has been shown.
 }
}






list<shared_ptr<SFAsset>> tmp2;
for(auto p : projectiles)
{
 if(p->IsAlive()){
tmp2.push_back(p);
}

}
  
projectiles.clear();
projectiles = list<shared_ptr<SFAsset>>(tmp2);

//delete the houses on coll
list<shared_ptr<SFAsset>> tmp3;
for(auto h : house){
 if(h->IsAlive()){

tmp3.push_back(h);
}
}
house.clear();
house = list<shared_ptr<SFAsset>>(tmp3);


list<shared_ptr<SFAsset>> tempC;
for(auto c : coins){
 if(c->IsAlive()){
 tempC.push_back(c);
}
}
coins.clear();
coins = list<shared_ptr<SFAsset>>(tempC);




  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);




}

bool initTTF()
{
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }
    
 
    
    //If everything initialized fine
    return true;
}











SDL_Surface *message = NULL;
SDL_Surface *image;
SDL_Surface *temp;


void SFApp::OnRender() {
SDL_Surface* background = NULL;
background = SDL_LoadBMP("assets/background.bmp");
SDL_BlitSurface(background,NULL, surface, NULL);



SDL_Color backgroundColor = { 0, 0, 0 };
temp = SDL_LoadBMP("assets/background.bmp");
image = SDL_DisplayFormat(temp);
SDL_Rect textLocation = { 0, 0, 0, 0 };
TTF_Font* font = TTF_OpenFont("assets/FreeSans.ttf", 20);
SDL_Color foregroundColor = {255,255, 255};

std::stringstream totalScore;
totalScore << "Score: " << totalKilled; // display for the total score using strign stream to create a string from varible + string



SDL_Surface* textSurface = TTF_RenderText_Shaded(font, totalScore.str().c_str() , foregroundColor, backgroundColor);
SDL_BlitSurface(textSurface, NULL, surface, &textLocation);
SDL_FreeSurface(temp);


SDL_FreeSurface(textSurface);
 TTF_CloseFont(font);


    player->OnRender(surface);
    





  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender(surface);}
  }



  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender(surface);}
  }


  for(auto c: coins) {
    if(c->IsAlive()) {c->OnRender(surface);}
  }

  for(auto h: house){
  if(h->IsAlive()) {h->OnRender(surface);}
}

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
