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
#include <omp.h>
using namespace std;
typedef std::chrono::high_resolution_clock Time;
ofstream myfile;


Visualizador::Visualizador(std::vector<ball> &bodies, simulacao s, double delta_t,int GUI) :
    delta_t(delta_t),
    GUI(GUI),
    s(s),
    bodiesprox(bodies),
    bodies(bodies)
    {
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
    Time::time_point t1 = Time::now();
    while (!SDL_QuitRequested()) {
        do_iteration();       
        draw();
    }
    Time::time_point t2 = Time::now();
   std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double > >(t2 - t1);
    std::cout << "Tempo de duração" <<" "<< time_span.count()<<'\n';
    bodies = bodiesprox;
  //Parar de escrever no GUI 
    myfile.close(); 
}



double Visualizador::ball_move(){//Funções de movimento das bolas
    double delta_t=0.01;
    double atualiza_x;
    double atualiza_y;
    //list_balls = current
    //list_balls2 = new
    
    for (int i = 0; i < (bodies.size()); i++){ 
       float g = 9.8;
       int acel= s.mu *bodies[i].mass *g;
       int acel_x=acel*(bodiesprox[i].vx/(sqrt(pow(bodiesprox[i].vx,2)+pow(bodiesprox[i].vy,2))));//a*cos (cos=vx/hip)
       int acel_y=acel*(bodiesprox[i].vy/sqrt(pow(bodiesprox[i].vx,2)+pow(bodiesprox[i].vy,2)));//a*sen (sen=vy/hip)
  
        bodiesprox[i].x = bodies[i].x + (bodies[i].vx*delta_t);
        bodiesprox[i].y = bodies[i].y + (bodies[i].vy*delta_t);
        if(bodies[i].vx>0){
            bodiesprox[i].vx = bodies[i].vx - delta_t * acel_x;
            if(bodiesprox[i].vx<0){
                bodiesprox[i].vx = 0;
            }
        }
        else{
           bodiesprox[i].vx = bodies[i].vx + delta_t * acel_x;
            if(bodiesprox[i].vx>0){
                bodiesprox[i].vx = 0;
            }
        }
        
        if(bodies[i].vy>0){
            bodiesprox[i].vy = bodies[i].vy - delta_t * acel_y;
            if(bodiesprox[i].vy<0){
                bodiesprox[i].vy = 0;
            }
        }
        else{
            bodiesprox[i].vy = bodies[i].vy + delta_t * acel_y;
            if(bodiesprox[i].vy>0){
                bodiesprox[i].vy = 0;
            }
        }
    }

      
  return atualiza_x, atualiza_y;
}

void Visualizador::read_file(){
  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}
// double proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
// double proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;
void Visualizador::ball_hit_ball(){
    double hipotenusa;
    double proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
    double proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;
    for (int i = 0; i < (bodies.size()); i++){
      for (int j = i+1; j < (bodies.size()); j++){
        double cateto1 = (bodiesprox[i].x - bodiesprox[j].x);
        double cateto2 = (bodiesprox[i].y - bodiesprox[j].y);
        
        hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
        double soma_r = (bodiesprox[i].radius + bodiesprox[j].radius);
        if (hipotenusa < soma_r){//Checando colisão
            myfile.open ("GUI.txt");
            if(GUI == 0){
                myfile <<"CHOQUE:"<<" A:"<<bodies[i].id<<"\n"<<"B:"<< bodies[j].id<<"\n";
            }
            bodiesprox[i].x = bodies[i].x;
            bodiesprox[i].y = bodies[i].y;
            bodiesprox[j].x = bodies[j].x;
            bodiesprox[j].y = bodies[j].y;
        
          
          //BOLA1
          bodiesprox[i].vx = (bodies[i].vx*(bodies[i].mass-bodies[j].mass)+2*bodies[j].vx*bodies[j].mass)/(bodies[i].mass+bodies[j].mass);
          bodiesprox[i].vy = (bodies[i].vy*(bodies[i].mass-bodies[j].mass)+2*bodies[j].vy*bodies[j].mass)/(bodies[i].mass+bodies[j].mass);
          //BOLA2
          bodiesprox[j].vx = (bodies[j].vx*(bodies[j].mass-bodies[i].mass)+2*bodies[i].vx*bodies[i].mass)/(bodies[j].mass+bodies[i].mass);;
          bodiesprox[j].vy = (bodies[j].vy*(bodies[j].mass-bodies[i].mass)+2*bodies[i].vy*bodies[i].mass)/(bodies[j].mass+bodies[i].mass);;
        }
      }
    }
    myfile.close(); 
  }

void Visualizador::ball_hit_wall(){
  for (int i = 0; i <= (bodies.size()); i++){
    if((bodiesprox[i].x - bodiesprox[i].radius)<=0){
      //printf("colisão com parede da esquerda");
      bodiesprox[i].vx = -bodiesprox[i].vx;
      bodiesprox[i].x = bodies[i].x;

      //cout<< "vx esq"<<bodies[i].vx << endl;
    }
    else if((bodiesprox[i].y - bodiesprox[i].radius)<=0){
      //printf("colisão com parede de baixo");
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
      //cout<< "vx baix"<<bodies[i].vy<< endl;
    }
    else if((bodiesprox[i].y +bodiesprox[i].radius)>=s.field_height){
      //printf("colisão com parede de cima");
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
      //cout<< "vx cim"<<bodies[i].vy<< endl;
    }
    else if((bodiesprox[i].x + bodiesprox[i].radius)>= s.field_width){
      //printf("colisão com parede da direita");
      bodiesprox[i].vx = -bodiesprox[i].vx;
      //cout<< "vx dir"<<bodies[i].vx<< endl;
      bodiesprox[i].x = bodies[i].x;
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
          myfile <<"("<<bodiesprox[g].id<<","<<bodiesprox[g].radius<<","<<bodiesprox[g].mass<<","
                <<bodiesprox[g].x<<","<<bodiesprox[g].y<<","<<bodiesprox[g].vx
                <<","<<bodiesprox[g].vy<<")"<<";";
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