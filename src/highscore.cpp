#include <iostream>
#include <fstream>
#include <string>
#include "highscore.h"
using namespace std;




void theScore(int yourScore){

int Highscore; // Int to hold the variable inside the txt file.
ifstream score("assets/score.txt");//bring in the file

 if(score.is_open()) // if the file has been opened 
 {
     score >> Highscore; // add the line of score.txt to the Highscore variable
    	
          
// If your the score held in text file is less than your score, you have achived a new higherscore
                 if ( Highscore < yourScore){
		         cout << "******************Congratulations on finishing the game******************"<< endl;
			 cout << "**************************************************************************" << endl;
			 cout << "******************You score was : "<< yourScore << "*********************" << endl;
		         cout << "*** YOU HAVE ACHIVED A NEW HIGHSCORE IT HAS BEEN PERMENTANTLY SAVED" << endl;
                         ofstream myfile("assets/score.txt");//prepare file to write to
	                 myfile<< yourScore << endl; //Write your new high score the the first line in the text file
                         myfile.close(); //close the file once the new int has been stored
                  }

//Checking if the users current score the same as score in the txt folder. If so then the user will be informed they are joint top with the max score.
                 else if(yourScore == 1000 && yourScore == Highscore){
		         cout << "******************Congratulations on finishing the game******************"<< endl;
			 cout << "**************************************************************************" << endl;
			 cout << "******************You score was : "<< yourScore << "*********************" << endl;
		         cout << " ***************You are now joint top of the scoreboard***************" << endl;

              }

                // user has died, print current score and message
                 else if (yourScore < Highscore){
                    cout<<    "******************You have died please try again******************"<< endl;
		 cout << "**************************************************************************" << endl;
		 cout << "******************You score was : "<< yourScore << "*********************" << endl;
                 cout << "*** you have not beat the high score please try again*******" << endl;
		 

                } 


	  
           score.close(); // close the file
           exit(0); // exit the game on completion or death
          }
          
      }



