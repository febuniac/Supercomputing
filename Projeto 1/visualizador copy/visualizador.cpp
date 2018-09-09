/*
 * Copyright (c) 2018 Igor Montagner igordsm@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "visualizador.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include <stdio.h>

#include <chrono>

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;
typedef std::chrono::high_resolution_clock Time;
ofstream myfile;


Visualizador::Visualizador(std::vector<ball> &bodies, simulacao s, double delta_t,int GUI) :
    delta_t(delta_t),
    GUI(GUI),
    s(s),
    bodies(bodies) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    double ratio = (double) s.field_width / s.field_height;
    if (ratio > 1) {
        win_width = max_dimension;
        win_height = max_dimension / ratio;
    } else {
        win_width = max_dimension * ratio;
        win_height = max_dimension;
    }
    win = SDL_CreateWindow("Visualizador SUPERCOMP", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, win_width, win_height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    iter = 0;
    //Abrindo o GUI
    myfile.open ("GUI.txt");
    if(GUI == 0){
        myfile <<"INFORMAÇÕES DO GUI"<<'\n';
    }
   
}

Visualizador::~Visualizador() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


void Visualizador::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 185, 255);
    SDL_RenderClear(renderer);
    for (auto i = bodies.begin(); i != bodies.end(); i++) {
        filledCircleRGBA(renderer, i->x / s.field_width * win_width,
                         i->y / s.field_height* win_height,
                         i->radius / s.field_width * win_width,
                         255, 0 ,0, 255);
    }
    SDL_RenderPresent(renderer);
}


void Visualizador::run() {
    SDL_ShowWindow(win);
    draw();
    while (!SDL_QuitRequested()) {
        do_iteration();       
        draw();
    }
  //Para de escrever no GUI 
    myfile.close(); 
}



double Visualizador::ball_move(){
    double delta_t=0.1;
    double atualiza_x;
    double atualiza_y;
    //list_balls = current
    //list_balls2 = new
    for (int i = 0; i < (bodies.size()); i++){ 
       bodies[i].x = bodies[i].x + (bodies[i].vx*delta_t);
    //    list_balls2[i].x = atualiza_x;
        
       bodies[i].y = bodies[i].y + (bodies[i].vy*delta_t);
       //printf("BALL MOVE\Nx=%f\n", bodies[i].x);
    //    list_balls2[i].y = atualiza_y;
       //b = list_balls2[i];

    //   cout << list_balls.at(i).x << ", ";
    //   cout << list_balls.at(i).y << ' '<<endl;

    //   cout << list_balls2.at(i).x << ", ";
    //   cout << list_balls2.at(i).y << ' '<< endl;
    }
  return atualiza_x, atualiza_y;
}

void Visualizador::read_file(){
  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}
int proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
    int proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;
    // for (int i = 0; i < (bodies.size()); i++){
    //   for (int j = i+1; j < (bodies.size()); j++){
void Visualizador::ball_hit_ball(){
    int hipotenusa;
    int proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
    int proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;
    for (int i = 0; i < (bodies.size()); i++){
      for (int j = i+1; j < (bodies.size()); j++){
        double cateto1 =(bodies[i].x - bodies[j].x);
        double cateto2 = (bodies[i].y - bodies[j].y);
        hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
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

void Visualizador::ball_hit_wall(){
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
void Visualizador::do_iteration() {
  //Escrevendo no GUI
  if(GUI == 0){
      myfile <<"Instante de tempo (dT)"<<iter<<'\n';
      myfile << "[";
  }
  for (unsigned g = 0; g < bodies.size(); g++){
      //escerevndo no GUI
      if(GUI == 0){
          myfile <<"("<<bodies[g].id<<","<<bodies[g].radius<<","<<bodies[g].mass<<","
                <<bodies[g].x<<","<<bodies[g].y<<","<<bodies[g].vx
                <<","<<bodies[g].vy<<")"<<";";
      }
  }
    Visualizador::ball_move();
    Visualizador::ball_hit_ball();
    Visualizador::ball_hit_wall();
    //SWAP(atualização de vetor p próximas posições)
    // temp = list_balls2;
    // list_balls2 = list_balls;
    // list_balls = temp;
  
    if (GUI == 0){
        myfile << "]" << '\n';
    }
    iter++;
}