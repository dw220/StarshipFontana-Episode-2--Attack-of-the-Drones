#include <iostream>
#include <fstream>
#include <string>
#include "highscore.h"
using namespace std;

//int yourScore = 123201;


void theScore(int yourScore){

int Highscore; // Int to hold the variable inside the txt file.
ifstream score("assets/score.txt");//bring in the file

 if(score.is_open()) // if the file has been opened 
 {
     score >> Highscore; // add the line of score.txt to the Highscore variable
    	if(yourScore > Highscore){ // if current score is greater than score held in score.txt
	   ofstream myfile("score.txt");//file to output, in this case score.txt 
	   myfile<< yourScore << endl; // write to "my file", add your current score
	   myfile.close(); //close the file
          
           // Print out the higher score using count, displays on the terminal window //
           cout<< "****************************************"<<endl;
	   cout<< "******New HighScore achived: " << yourScore <<"******" <<endl;
           cout <<"*****************************************" <<endl;
           cout<<"Your score has been permenantly saved" << endl;
    }
  score.close(); // close score.txt file
  }

else cout << "unable to open."; // if score.txt doesn't open let us know on terminal.


}
