/*
This program will numerically compute a 2D physical problem of
balls moving on a plan

History: Written by Felipe Frid Buniac, 08/2018.
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;


// typedef struct ball {
//   int id ;
//   double radius ;
//   double mass ;
//   //posição
//   double x ;
//   double y ;
//   //velocidade
//   double vx ;
//   double vy ;
// } ball;



struct simulacao {//para guardar os valores da simulação (usar return)
  double field_width, field_height, n, mu, alpha_w, alpha_b;
} ;
struct simulacao s;
struct ball b;



// reading the file with program info
void read_file(){
  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  cout<< s.field_width<<s.field_width<<"\n";
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}

std::vector<ball> list_balls (s.n);

vector<ball> save_to_vec(){
  read_file();
  cout<< s.field_width<<s.field_width<<"\n";
  //lista de bolas
  for (int i = 0; i <= (s.n); i++){
    if (!(cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy)){
      list_balls.push_back(b);
      cout<< b.id<< b.radius<< b.mass<<b.x<< b.y<< b.vx<< b.vy<<"\n";
    //for que vai lendo e jogando no lista de bolas FAZER
    }
    //vector<bola> printf(list_balls[i]);
  }
  return list_balls;
}
// struct campo {
//   int width;
//   int height;
// } ;
//calcula posicoes no proximo instante de tempo e checa se houve colisoes para ver se vai mexer a bola ou mexer na velocidade
//se colidir com bola
//se no proximo instante de tempo as bolas forem bater eu aponto o vetor de velociddade para o lado da colisao e na proxima interacao elas se movem
// void ball_move(){}
// void ball_hit_ball(){}
// void ball_hit_wall(){}

  // int main () {
  //   save_to_vec();

  //   return 0;
  // }
// classes:
//
// ball
// campo
// shock
// ballposition
//
//
// lista de bolas
// e campos
// posicO E VELOCIDADE DAS BOLAS

//https://www.tenouk.com/Module19.html
