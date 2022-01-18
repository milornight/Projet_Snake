/*
* ------------------------ *
|                          |
|   << main >>             |
|                          |
|                          |
* ------------------------ *

Authors: JIN

*/


#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "clientAPI.h"
#include "deplace.h"

int main(int argc, char* argv[]){

  char* serverName = /*"localhost";"li2051-215.members.linode.com";*/ "polydev.cia-polytech-sorbonne.fr";
  //int port=8080;//1234;
  int port=strtol(argv[2],NULL,10);
  char name[20] = "MILOR";
  //connectToServer(serverName, port, name);
  connectToServer(argv[1], port, name);

  char* gameType="RANDOM_PLAYER difficulty=2 timeout=100 seed=123 start=0";
  char gameName[50]="";
  int sizeX=50;
  int sizeY=50;
  int nbWalls;
  //waitForSnakeGame( gameType, gameName, &sizeX, &sizeY, &nbWalls);
  waitForSnakeGame( argv[3], gameName, &sizeX, &sizeY, &nbWalls);

  /*while(){
  waitForSnakeGame("TOURNAMENT")*/


  int* walls=(int*) malloc(4*nbWalls*sizeof(int));
  int start;
  start=getSnakeArena(walls);
  printArena();

  //affichier dans un tableau le position du mur
  for(int i=0; i<4*nbWalls; i++){
    printf("%d ",walls[i] );
  }
  printf("\n");

  //creation d'un plan marque en code 1(mur) ou 0(vide)
  int terrain[2*sizeY+1][sizeX+1];

  for (int i=0; i<2*sizeY+1; i++){
    for (int j=0; j<sizeX+1; j++){
      terrain[i][j]=0;
    }
  }

  for (int i=0; i<sizeX+1;i++){
    terrain[0][i]=1;
    terrain[2*sizeY][i]=1;
  }

  for (int i=0; i<2*sizeY+1;i++){
    terrain[i][0]=1;
    terrain[i][sizeX]=1;
  }



  /*for (int i=0; i<2*sizeY+1; i++){
    for (int j=0; j<sizeX+1; j++){
      printf("%d ", terrain[i][j]);
    }
    printf("\n");
  }*/



  for (int i=0; i<4*nbWalls; i++){
    int x,y,egaleX,egaleY;
    x=walls[i]+walls[i+2];
    egaleX=walls[i]&walls[i+2];
    i++;
    y=walls[i]+walls[i+2];
    egaleY=walls[i]&walls[i+2];
    i+=2;
    terrain[y+1][x+1]=1;
    if (egaleX==1){
      terrain[y][x-1]=1;
      terrain[y][x]=1;
      terrain[y][x+1]=1;
    }
    if (egaleY==1){
      terrain[y-1][x]=1;
      terrain[y][x]=1;
      terrain[y+1][x]=1;
    }
  }




  t_position mypos;
  t_position itpos;
  mypos.posx=3;
  mypos.posy=sizeY;
  itpos.posx=sizeX-3;
  itpos.posy=sizeY;

  terrain[mypos.posy][mypos.posx]=5;
  terrain[itpos.posy][itpos.posx]=9;

  //affichage du terrain code
  for (int i=0; i<2*sizeY+1; i++){
    for (int j=0; j<sizeX+1; j++){
      printf("%d ", terrain[i][j]);
    }
    printf("\n");
  }

  t_move monMove;
  t_move sonMove;

  t_return_code mystate=0;
  t_return_code itstate=0;

  //boucle pour le deplacemet manuelle
  /*while( (mystate==0) && (itstate==0) )
		{
			monMove=deplace();
      printf("%d\n",monMove);
			if(monMove==NORTH || monMove==EAST || monMove==SOUTH || monMove==WEST )
			{

				mystate=sendMove(monMove);
				itstate=getMove(&sonMove);
				printArena();

			}
    }*/

  //boucle pour le deplacement automatique

  while ( (mystate==0) && (itstate==0)){

      monMove=deplace_aut();
    if(monMove==NORTH || monMove==SOUTH || monMove==WEST || monMove==EAST )
    {

      mystate=sendMove(monMove);
      //position(mypos);
      itstate=getMove(&sonMove);
      //position(itpos);
      //terrain[mypos.posy][mypos.posx]=5;
      //terrain[itpos.posy][itpos.posx]=9;
      printArena();

      /*for (int i=0; i<2*sizeY+1; i++){
        for (int j=0; j<sizeX+1; j++){
          printf("%d ", terrain[i][j]);
        }
        printf("\n");
      }*/

    }
  }


  while (mystate==1 && itstate==-1){
    char comment[]="Vous avez gagné";
    sendComment(comment);
  }

  while (mystate==-1 && itstate==1){
    char comment[]="Vous avez perdu";
    sendComment(comment);
  }

  free(walls);


  closeConnection();

  return 1;

}
