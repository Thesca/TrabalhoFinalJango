#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

#include "common.h"

using namespace std;

#define width 40
#define height 20


//Variáveis globais TODOOOOO (eu sei que tá erradissimo usar globais, vou resolver assim que aprender como)
int fruitY, fruitX, snakeX, snakeY, score;
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

int * tailX = (int *) malloc (2 * sizeof(int));
int * tailY = (int *) malloc (2 * sizeof(int));
int nTail;


//Printar uma linha para a parte de cima e de baixo da arena
void printLineSnake() {
   for (int i = 0; i < width; ++i) {
      cout << "#";
   } cout << endl;
}

//Setup para o jogo snake
void setupSnake() {
   fruitX = rand() % width;
   fruitY = rand() % height;
   snakeX = width/2;
   snakeY = height/2;
}

//Função para desenhar a arena do snake
void drawSnake() {

   system("CLS");

   printLineSnake();

   for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
         if (j == 0 || j == width-1) {
            cout << "#";
         } else if (snakeY == i && snakeX == j) {
            cout<<"O";
         }else if (fruitY == i && fruitX == j) {
            cout<<"F";
         }else { 
            //Boolean para decidir se vai printar um espaço em branco, ou se ainda existe um segmento de calda naquela posição
            bool print = false;

            for (int k = 0; k < nTail; ++k) {
               if (i==tailY[k] && j==tailX[k]) {
                  cout<<"o";
                  print = true;
               }
            }if(!print) cout << " ";
         }
      }cout<<endl;
   }
   printLineSnake();
   cout<<endl;
   cout << "Score: "<< score << endl;
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
bool logicSnake() {

   //Iniciando váriaveis para acompanhar a calda
   int prevX = tailX[0];
   int prevY = tailY[0];
   int prev2X, prev2Y;
   tailX[0] = snakeX;
   tailY[0] = snakeY;

   //Looping para as atribuições dos membros anteriores da calda
   for (int i = 1; i < nTail; ++i) {
      prev2X = tailX[i];
      prev2Y = tailY[i];
      tailX[i] = prevX;
      tailY[i] = prevY;
      prevX = prev2X;
      prevY = prev2Y;
   }

   bool gameOver = false;
   switch(dir) {
      case UP:
         if (dir == DOWN) {
            break;
         }
         snakeY--;
      case DOWN:
         if (dir == UP) {
            
            break;
         }
         snakeY++;
         break;
      case LEFT:
         if (dir == RIGHT) {
            break;
         }
         snakeX--;
         break;
      case RIGHT:
         if (dir == LEFT) {
            break;
         }
         snakeX++;
         break;
      default:
         break;
   }

   if (snakeX<1 || snakeX>width-2 || snakeY<0 || snakeY>(height-1)) {
      gameOver=true;
   }

   for (int i = 0; i < nTail; ++i) {
      if (snakeX == tailX[i] && snakeY == tailY[i]) {
         gameOver = true;
      }
   }

   if (snakeX == fruitX && snakeY == fruitY) {
      score+=10;
      fruitX = rand() % width;
      fruitY = rand() % height;
      nTail++;
      if ((sizeof(tailX)/4 + sizeof(tailY)/4) % 2 == 0) {
         tailX = (int *) realloc(tailX, (nTail+2)*sizeof(int));
         tailY = (int *) realloc(tailY, (nTail+2)*sizeof(int));
      }
   }
   return gameOver;
}

void initSnake () {

   bool gameOver;
   setupSnake();
   while(!gameOver) {
      drawSnake();
      inputSnake();
      gameOver = logicSnake();
      Sleep(40);
   }
}