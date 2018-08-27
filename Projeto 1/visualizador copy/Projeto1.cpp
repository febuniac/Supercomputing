/*
This program will numerically compute a 2D physical problem of
balls moving on a plan

History: Written by Felipe Frid Buniac, 08/2018.
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>

using namespace std;

// struct campo {
//   int width;
//   int height;
// } ;
//calcula posicoes no proximo instante de tempo e checa se houve colisoes para ver se vai mexer a bola ou mexer na velocidade
//se colidir com bola
//se no proximo instante de tempo as bolas forem bater eu aponto o vetor de velociddade para o lado da colisao e na proxima interacao elas se movem

typedef struct _ball {
  int id ;
  double radius ;
  double mass ;
  //posição
  double x ;
  double y ;
  //velocidade
  double vx ;
  double vy ;
} ball;



struct simulacao {//para guardar os valores da simulação (usar return)
  double field_width, field_height, n, mu, alpha_w, alpha_b;
} ;
struct simulacao s;
struct _ball b;



// reading the file with program info
void read_file(){
  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}

std::vector<ball> list_balls (s.n);
std::vector<ball> list_balls2 (s.n); 

vector<ball> save_to_vec(){
  read_file();
  //cout<< s.field_width<<s.field_width<<"\n";
  //lista de bolas
  for (int i = 0; i < (s.n); i++){
    cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy;
    list_balls.push_back(b);
    list_balls2.push_back(b);
    //for que vai lendo e jogando no lista de bolas 
    //vector<bola> printf(list_balls[i]);
  }
  return list_balls;
}

  double ball_move(){
    double delta_t=0.1;
    double atualiza_x;
    double atualiza_y;
    //list_balls = current
    //list_balls2 = new
    for (int i = 0; i < (s.n); i++){
       
       atualiza_x = list_balls[i].x + (list_balls[i].vx*delta_t);
       list_balls2[i].x = atualiza_x;
        
       atualiza_y = list_balls[i].y + (list_balls[i].vy*delta_t);
       list_balls2[i].y = atualiza_y;
       //b = list_balls2[i];

       cout << list_balls.at(i).x << ", ";
       cout << list_balls.at(i).y << ' '<<endl;

       cout << list_balls2.at(i).x << ", ";
       cout << list_balls2.at(i).y << ' '<< endl;
    }
  return atualiza_x, atualiza_y;

  }

  void ball_hit_ball(){
    int hipotenusa;
    for (int i = 0; i < (s.n); i++){
      for (int j = i+1; j < (s.n); j++){
        double cateto1 =(list_balls[i].x - list_balls[j].x);
        double cateto2 = (list_balls[i].y - list_balls[j].y);
        hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
        if (hipotenusa < (list_balls[i].radius + list_balls[j].radius)){
          printf("Choque de Bolas!");
        }
      }
    }
  }
  void ball_hit_wall(){
    for (int i = 0; i < (s.n); i++){
      if((list_balls[i].x -list_balls[i].radius)<=0){
        printf("colisão com parede da esquerda");
        list_balls[i].vx = (list_balls[i].vx)*(-1);
        cout<< "vx esq"<<list_balls[i].vx << endl;
      }
      else if((list_balls[i].y -list_balls[i].radius)<=0){
        printf("colisão com parede de baixo");
        list_balls[i].vy = (list_balls[i].vy)*(-1);
        cout<< "vx baix"<<list_balls[i].vy<< endl;
      }
      else if((list_balls[i].y +list_balls[i].radius)>=s.field_height){
        printf("colisão com parede de cima");
        list_balls[i].vy = (-list_balls[i].vy);
        cout<< "vx cim"<<list_balls[i].vy<< endl;
      }
      else if((list_balls[i].x +list_balls[i].radius)>=s.field_width){
        printf("colisão com parede da direita");
        list_balls[i].vx = (-list_balls[i].vx);
        cout<< "vx dir"<<list_balls[i].vx<< endl;
      }
    }

  }

int main () {
  int iteration = 0;
  std::vector<ball> temp; 
  save_to_vec();
  while (iteration<10) {
    ball_move();
    //SWAP(atualização de vetor p próximas posições)
    temp = list_balls2;
    list_balls2 = list_balls;
    list_balls = temp;
    iteration++;
    ball_hit_ball();
    ball_hit_wall();

  }
  
  //cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy;
  return 0;
}

//https://www.tenouk.com/Module19.html
