#include <iostream>

#define widthSnake 40
#define heightSnake 20

using namespace std;

void printLineSnake() {
   for (int i = 0; i < widthSnake; ++i) {
      cout << "#";
   } cout << endl;
}

//Setup para o jogo snake
void setupSnakeGame() {

}

//Função para desenhar a arena do snake
void drawSnake () {
   printLineSnake();

   for (int i = 0; i < heightSnake; ++i) {
      for (int j = 0; j < widthSnake; ++j) {
         if (j == 0 || j == widthSnake-1) {
            cout << "#";
         }else {
            cout<<" ";
         }
      }cout<<endl;
   }
   printLineSnake();
}

int main () {
   
   drawSnake();
   //while(!gameOverSnake);

   return 0;
}
