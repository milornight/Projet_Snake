/*
* ------------------------ *
|                          |
|   << deplace.h >>        |
|                          |
|                          |
* ------------------------ *

Authors: JIN

*/

#ifndef __DEPLACE__
#define __DEPLACE__


typedef struct{
  int posx;
  int posy;
}t_position;

t_move deplace();
t_move deplace_aut();
void position(t_position position);

#endif
