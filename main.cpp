#include <iostream>
#include <windows.h>
#include "snake.h"

int main () {
   
   setupSnake();
   while(1) {
      drawSnake();
      inputSnake();
      logicSnake();
      Sleep(40);
   }

   return 0;
}
