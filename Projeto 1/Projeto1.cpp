/*
This program will numerically compute a 2D physical problem of
balls moving on a plan

History: Written by Felipe Frid Buniac, 08/2018.
*/
#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

struct ball {
<id> <raio> <massa> <x0> <y0> <vx0> <vy0>
  int id ;
  int raio ;
  int massa ;
  int x0 ;
  int y0 ;
  int v_x0 ;
  int v_y0 ;
} ;

struct campo {
  int width;
  int height;
} ;

// reading a text file
void read_file(){
  double w, h, n, mu, alpha_w, alpha_b;
  if (!(cin >> w >> h >> n)) { throw 1; }
  if (!(cin >> mu >> alpha_w >> alpha_b)) { throw 1; }
}







// width
// height
// num_balls
// mu
// alpha_w
// alpha_b
// id
// raio
// massa
// x_0
// y_0
// vx_0
// vy_0
// }

int main () {
  read_file();

    return 0;
}
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
