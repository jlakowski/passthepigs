/* Make a statistical simulation of the best game
Pass the Pigs the probabilities come from here
http://passpigs.tripod.com/index.html
http://www.amstat.org/publications/jse/v14n3/datasets.kern.html

TODO add a turn score feature
*/
#include <stdio.h>
#include <stdlib.h>

//create a method (function) which rolls a pig
int roll()
{
  int p;
  int n;
  
  n = rand() % 1000;
  if ( n > 0 && n < 341){
    p = 0; //pink
   }else if ( n >= 341 && n< 670){
    p = 1; //dot
   }else if ( n >= 670 && n< 865){
    p = 2; // Razorback
  }else if (n>= 865 && n<957){
    p = 3; //Trotter
  }else if (n>= 957 && n <992){
    p = 4; //Snouter
  } else {
    p = 5; //Leaning Jowler 
  }
  return p;
}

// the strategy for player 0
int strat0(score, turnscore)
{
  int action;
  action = 0;
  if( turnscore > 50){
    action = 1;
  }else {
    action = 0;
  }
  return action;
}

// the strategy for player 1
int strat1(score, turnscore)
{
  int action;
  if( turnscore > 5){
    action = 1;
  }else{
    action = 0;
  }
  return action;
}


// play a round of pass the pigs
int playround()
{
  //set up the things
  int np = 2;
  
  int i = 0;
  int scoret[6][6] = {{ 1, 0, 5, 5,10,15},
		      { 0, 1, 5, 5,10,15},
		      { 5, 5,20,10,15,20},
		      { 5, 5,10,20,15,20},
		      {10,10,15,15,40,25},
		      {15,15,20,20,25,60}};
  
  //^^this is the table which has the scores for the rolls^^

  // can poss put all this in a start up function !

  //Begin game play
  int ps[] = {0,0};
  int turn = 0;
  int done = 0;
  int pup, p1,p2,score,action,winner,turnscore;
  while(done == 0){
    //which player is up
    pup = turn % np;

    p1 = roll();
    p2 = roll();
    score = scoret[p1][p2];
    if (score == 0){
      
      turn ++;
      turnscore = 0;
    }else {
      turnscore += score; 
      if( ps[pup] + turnscore >= 100){
	done = 1;
	winner = pup;
	break;
      }
      
      if( pup == 0){
	action = strat0(score,turnscore);
      } else if (pup == 1 ){
	action = strat1(score, turnscore);
      }
      if(action == 1){
	ps[pup] += turnscore;
	turnscore = 0;
      }
      
      turn += action;
    }
  } 

  //printf("Player %d won in %d turns", winner,turn);
  
  return(winner);

}

int main()
{
  //set up the things
  time_t t;
  srand((unsigned) time(&t));

  int i = 0;
  int numwins[] = {0,0};
  int winner;
  for (i=0; i<100000; i++){
    winner = playround();
    numwins[winner] ++;
  }
  printf("Player 0 won %d times\n", numwins[0]);
  printf("Player 1 won %d times\n", numwins[1]);
 
  return 0;
}

      
