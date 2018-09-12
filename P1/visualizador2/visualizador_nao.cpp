#include <omp.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "visualizador.h"
#include <stdio.h>
#include <iterator>
#include <math.h>

struct simulacao s;
struct _ball b;
using namespace std;
typedef std::chrono::high_resolution_clock Time;
using namespace std::chrono;
int proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
int proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;

void testes(std::vector<ball> &bodies, simulacao s, double delta_t,long iter){
    
    for(long n = 0; n<iter; n++){ 
        double delta_t=0.01;
        //ballmove
        
        for (int i = 0; i < (bodies.size()); i++){ 
       int g = 10;
       int acel= s.mu *bodies[i].mass *g;
       
  
        bodies[i].x = bodies[i].x + (bodies[i].vx*delta_t);
        bodies[i].y = bodies[i].y + (bodies[i].vy*delta_t);

        if(bodies[i].vx>0){
            if (bodies[i].vx - acel*delta_t <= 0){
            bodies[i].vx = 0;
            }
            else{
            bodies[i].vx -= acel*delta_t; 
            }    
        }
        else{
            if (bodies[i].vx + acel*delta_t >= 0){
                bodies[i].vx = 0;
            }
            else{
                bodies[i].vx += acel*delta_t; 
            }  
        }

        if(bodies[i].vy>0){
            if (bodies[i].vy - acel*delta_t <= 0){
                bodies[i].vy = 0;
            }
            else{

                bodies[i].vy -= acel*delta_t; 
            }    
        }
        else{
            if (bodies[i].vy + acel*delta_t >= 0){
                bodies[i].vy = 0;
            }
            else{
                bodies[i].vy += acel*delta_t; 
            }  
        }
    }

        //ballhitball
        
        for (int i = 0; i < (bodies.size()); i++){
            for (int j = i+1; j < (bodies.size()); j++){
                double cateto1 =(bodies[i].x - bodies[j].x);
                double cateto2 = (bodies[i].y - bodies[j].y);
                int hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
                if (hipotenusa <(bodies[i].radius + bodies[j].radius)){//Checando colisão
                // if ((bodies[i].radius + bodies[j].radius)<=hipotenusa) {
                printf("Choque de Bolas! \n");
                cout<<" A:"<<bodies[i].id<<"\n"<<"B:"<< bodies[j].id<<"\n";
                
                //BOLA1 A
                proj_j = (bodies[j].vx*cateto1+bodies[j].vy*cateto2)/(hipotenusa);//Constante de projeção da Bola1
                vjhip_x = (proj_j*cateto1)/hipotenusa;
                vjhip_y = (proj_j*cateto2)/hipotenusa;
                
                vjhip_parallel_x = bodies[j].vx-vjhip_x;
                vjhip_parallel_y = bodies[j].vy-vjhip_y;
                
                vjhip_espelhado_x = -(vjhip_x);
                vjhip_espelhado_y = -(vjhip_y);
                
                bodies[j].vx = vjhip_espelhado_x - vjhip_parallel_x;//novo_vetor_j_x
                bodies[j].vy = vjhip_espelhado_y - vjhip_parallel_y;//novo_vetor_j_y

                //BOLA2 B
                proj_i = (bodies[i].vx*cateto1+bodies[i].vy*cateto2)/(hipotenusa);//Constante de projeção da Bola2
                vihip_x = (proj_i*cateto1)/hipotenusa;
                vihip_y = (proj_i*cateto2)/hipotenusa;
                
                vihip_parallel_x = bodies[i].vx-vihip_x;
                vihip_parallel_y = bodies[i].vy-vihip_y;
                
                vihip_espelhado_x = -(vihip_x);
                vihip_espelhado_y = -(vihip_y);
        
                bodies[i].vx = vihip_espelhado_x - vihip_parallel_x;//novo_vetor_i_x
                bodies[i].vy = vihip_espelhado_y - vihip_parallel_y;//novo_vetor_i_y
                if ( (proj_i>0 &proj_j<0)){//|(proj_i<0 &proj_j>0)
                    proj_i=--proj_i;
                    proj_j=-proj_j;
                }
                if((proj_i>0 &proj_j>0)){//|(proj_i<0 &proj_j<0) 
                    proj_j=-proj_j;
                }
                }
            }
            }
            }

        // ball hit wall
       
        for (int i = 0; i <= (bodies.size()); i++){
            if((bodies[i].x - bodies[i].radius)<=0){
            printf("colisão com parede da esquerda");
            bodies[i].vx = -bodies[i].vx;
            cout<< "vx esq"<<bodies[i].vx << endl;
            }
            else if((bodies[i].y - bodies[i].radius)<=0){
            printf("colisão com parede de baixo");
            bodies[i].vy = -bodies[i].vy;
            cout<< "vx baix"<<bodies[i].vy<< endl;
            }
            else if((bodies[i].y +bodies[i].radius)>=s.field_height){
            printf("colisão com parede de cima");
            bodies[i].vy = -bodies[i].vy;
            cout<< "vx cim"<<bodies[i].vy<< endl;
            }
            else if((bodies[i].x + bodies[i].radius)>= s.field_width){
            printf("colisão com parede da direita");
            bodies[i].vx = -bodies[i].vx;
            cout<< "vx dir"<<bodies[i].vx<< endl;
            }
        }
        }

void read_file(){

  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}

std::vector<ball> save_to_vec(std::vector<ball> &list_balls){
  read_file();
  //criando listas de bolas //for que vai lendo e jogando no lista de bolas
  std::cout<<s.n;
  for (int i = 0; i < s.n; i++){
    cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy;
    list_balls.push_back(b);
    }
  return list_balls;
}
int main(int argc, char const *argv[])
{   
    
   // unsigned long iter = atoi(argv[1]);
    std::vector<ball> list_balls;
    save_to_vec(list_balls);
    Time::time_point t1 = Time::now();
    testes(list_balls,s,0.01,10000);
    Time::time_point t2 = Time::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    std::cout << "Tempo:" << time_span.count()<<'\n';

    return 0;
}