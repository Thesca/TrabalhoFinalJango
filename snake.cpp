#include <iostream>
#include <conio.h>
#include "snake.h"

using namespace std;

#define widthSnake 40
#define heightSnake 20


//Variáveis globais TODOOOOO (eu sei que tá erradissimo usar globais, vou resolver assim que aprender como)
int fruitY, fruitX, snakeX, snakeY;
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

//Printar uma linha para a parte de cima e de baixo da arena
void printLineSnake() {
   for (int i = 0; i < widthSnake; ++i) {
      cout << "#";
   } cout << endl;
}

//Setup para o jogo snake
void setupSnake() {
   fruitX = rand() % widthSnake;
   fruitY = rand() % heightSnake;
   snakeX = widthSnake/2;
   snakeY = heightSnake/2;
}

//Função para desenhar a arena do snake
void drawSnake () {

   system("CLS");

   printLineSnake();

   for (int i = 0; i < heightSnake; ++i) {
      for (int j = 0; j < widthSnake; ++j) {
         if (j == 0 || j == widthSnake-1) {
            cout << "#";
         } else if (snakeY == i && snakeX == j) {
            cout<<"O";
         }else if (fruitY == i && fruitX == j) {
            cout<<"F";
         }else { 
            cout<<" ";
         }
      }cout<<endl;
   }
   printLineSnake();
}

//Coleta o input do player
void inputSnake() {
   if(kbhit()) {
      switch(getch()) {
         case 'w':
            dir = UP;
            break;
         case 's':
            dir = DOWN;
            break;
         case 'a':
            dir = LEFT;
            break;
         case 'd':
            dir = RIGHT;
            break;
         default:
            break;
      }
   }
}

//Tudo de lógica para as mecânicas da cobrinha funcionar
void logicSnake() {

   switch(dir) {
      case UP:
         snakeY--;
         break;
      case DOWN:
         snakeY++;
         break;
      case LEFT:
         snakeX--;
         break;
      case RIGHT:
         snakeX++;
         break;
      default:
         break;
   }
}