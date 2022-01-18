/*
* ------------------------ *
|                          |
|   << deplace >>          |
|                          |
|                          |
* ------------------------ *

Authors: JIN

*/

#include <stdio.h>
#include <stdlib.h>
#include "clientAPI.h"
#include "snakeAPI.h"
#include <time.h>
#include "deplace.h"

char dir[4]={'0','1','2','3'};

t_move deplace(){ //deplacement manuelle
  t_move move;
  char direction;
  scanf("%s",&direction);
  switch(direction){
    case '0':
      move=NORTH;
      break;
    case '1':
      move=EAST;
      break;
    case '2':
      move=SOUTH;
      break;
    case '3':
      move=WEST;
      break;
  }
  return move;
}

t_move deplace_aut(){ //deplacement automatique
  t_move move;
  char direction;
  srand((unsigned)time(NULL));
  direction=dir[rand()%3];
  switch(direction){
    case '0':
      move=NORTH;
      break;
    case '1':
      move=EAST;
      break;
    case '2':
      move=SOUTH;
      break;
    case '3':
      move=WEST;
      break;
  }
  return move;
}

void position(t_position pos){
  char direction;
  switch(direction){
    case '0':
    pos.posy=-1;
    break;
    case '1':
    pos.posx=+1;
    break;
    case '2':
    pos.posy=+1;
    break;
    case '3':
    pos.posx=-1;
    break;
  }
}
