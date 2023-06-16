#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

class SnakeGame {

      int width;
      int height;
      int fruitY, fruitX, snakeX, snakeY;
      int score = 0;
      int inputLevel;
      
      enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
      eDirection dir;
      bool gameOver;

      int sizeX;
      int sizeY;
      int * tailX;
      int * tailY;
      int nTail;

      void spawnNewFruit() {
         fruitX = rand() % width;
         if(fruitX == width || fruitX == width-1) {
            fruitX--;
         }
         if(fruitX == 0) {
            fruitX++;
         }
         fruitY = rand() % (height+1);
         if(fruitY == height) {
            fruitY--;
         }
         if(fruitY == 0) {
            fruitY++;
         }
      }

      void setupSnake() {
         score = 0;
         if (inputLevel == 3) {
            width = 20;
            height = 20;
         } else {
            width = 30;
            height = 30;
         }
         dir = STOP;
         gameOver = false;
         sizeX = 2;
         sizeY = 2;
         tailX = (int *) malloc (sizeX * sizeof(int));
         tailY = (int *) malloc (sizeY * sizeof(int));
         nTail = 0;
         snakeX = width/2;
         snakeY = height/2;
         spawnNewFruit();
      }

      //Função para desenhar a arena do snake
      void drawSnake() {
         std::ostringstream out;
         for (int i = 0; i < width; ++i) {
            out << "# ";
         } out << "\n";

         for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
               if (j == 0 || j == width-1) {
                  out << "#";
               } else if (snakeY == i && snakeX == j) {
                  out << "O";
               }else if (fruitY == i && fruitX == j) {
                  out <<"F";
               }else { 
                  //Boolean para decidir se vai printar um espaço em branco, ou se ainda existe um segmento de calda naquela posição
                  bool print = false;
                  for (int k = 0; k < nTail; ++k) {
                     if (i==tailY[k] && j==tailX[k]) {
                        out <<"o";
                        print = true;
                     }
                  }
                  if(!print) out  << " ";
               }
               out << ' ';
            }out <<"\n";
         }

         for (int i = 0; i < width; ++i) {
            out << "# ";
         } out << "\n";
         out << "\n";
         out  << "Score: "<< score << "\n";
         
         system("CLS");
         std::cout << out.str();
      }


      //Coleta o input do player
      void inputSnake() {
         if(_kbhit()) {
            switch(_getch()) {
               case 'w':
                  if (dir != DOWN) {
                     dir = UP;
                  }   
                  break;
               case 's':
                  if (dir != UP) {
                     dir = DOWN;
                  }   
                  break;
               case 'a':
                  if (dir != RIGHT) {
                     dir = LEFT;
                  }   
                  break;
               case 'd':
                  if (dir != LEFT) {
                     dir = RIGHT;
                  }   
                  break;
               case '0':
                  gameOver = true;
                  break;
            }
         }
      }

      bool saveScore(char * userName){
            FILE * arq;
            arq = fopen("score.txt", "a");

            if(!arq)
            {
               std::cout << "Erro: Não foi possível abrir o arquivo." << std::endl;
               return false;
            }

            fprintf(arq, "[%s] %d\n",userName, score);
            return true;
      }

      static int extrairNumero(const std::string& str) {
         std::stringstream ss(str);
         std::string palavra;
         int numero;
         while (ss >> palavra) {
            if (std::stringstream(palavra) >> numero) {
                  return numero;
            }
         }

         return 0; // Valor padrão caso não seja encontrado um número
      }

      // Função de comparação que compara apenas a parte numérica dos valores
      static bool compararNumeros(const std::string& str1, const std::string& str2) {
         int num1 = extrairNumero(str1);
         int num2 = extrairNumero(str2);

         return num1 > num2;
      }

      auto readScore(){
         int cont = 0;
         std::ifstream arquivo("score.txt");
         std::vector<std::string> valores;
         std::string linha;

         while (std::getline(arquivo, linha)) {
            valores.push_back(linha);
         }

         // Ordenar o vetor usando a função de comparação
         std::sort(valores.begin(), valores.end(), compararNumeros);

         for (const auto& str : valores) {
               cont++;
               std::cout << "-----------------------\n";
               std::cout << str << std::endl;
               if(cont == 3){
                  std::cout << "-----------------------\n";
                  break;
               }
         }
      }

      //Tudo de lógica para as mecânicas da cobrinha funcionar
      void logicSnake() {

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

         if (snakeX<1 || snakeX>width-2 || snakeY<0 || snakeY>(height-1)) {
            gameOver=true;
         }

         for (int i = 0; i < nTail; ++i) {
            if (snakeX == tailX[i] && snakeY == tailY[i]) {
               gameOver = true;
            }
         }

         if (snakeX == fruitX && snakeY == fruitY) {
            spawnNewFruit();
            score+=10;
            nTail++;
            ++sizeX;
            ++sizeY;
            if ((sizeX + sizeY) % 2 == 0){
               tailX = (int *) realloc(tailX, sizeX*sizeof(int));
               tailY = (int *) realloc(tailY, sizeY*sizeof(int));
            }
         }   
      }

      //TODO Game over screen () {}

      char * get_nome(){
         char * userName = new char[4];
         std::cout << "USERNAME (ate 3 caracteres): ";
         for (int i = 0; i < 3; i++) {
            userName[i] = std::cin.get(); // Lê um caractere por vez
         }
         getchar();
         userName[3] = '\0';

         return userName;
      }

      int chooseLevel() {
         int input;
         printf("\n\tEasy - Press 1\n");
         printf("\tHard - Press 2\n");
         printf("\tD00M - Press 3\n");
         printf("\tOption: ");
         scanf("%i", &input);
         return input;
      }

   public:

      void run(){
         int resp = 0;
         char * userName = nullptr;

         do{
            std::cout << "[1]. Start Game\n";
            std::cout << "[2]. Ranking\n";
            std::cout << "[3]. Exit\n";
            std::cout << "[OPTION]:\t";
            std::cin >> resp;
            getchar();
            system("CLS");
            switch(resp){
               case 1:
                  system("CLS");
                  userName = get_nome();
                  inputLevel = chooseLevel();
                  setupSnake();
                  while(!gameOver) {
                     drawSnake();
                     inputSnake();
                     logicSnake();
                     switch(inputLevel) {
                        case 1:
                           Sleep(60);
                           break;
                        case 2:
                           Sleep(30);
                           break;
                        case 3:
                           Sleep(20);
                           break;
                        default:
                           Sleep(60);
                           break;
                     }
                  }
                  system("CLS");
                  fflush(stdin);
                  printf("---GAME OVER---");
                  char inputGameOver;
                  do{
                     std::cout << "\n\n\nPress enter to continue ...";
                     inputGameOver = std::cin.get();
                  }while(inputGameOver != '\n');
                  saveScore(userName);
                  system("CLS");
                  break;
               case 2:
                  readScore();
                  Sleep(2000);
                  system("CLS");
                  break;
            }
         }while(resp != 3);
      }
};