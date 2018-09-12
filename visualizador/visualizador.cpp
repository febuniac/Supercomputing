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

//Criando arquivos GUI e COLLISIONS
ofstream gui;
ofstream collisions;
Visualizador::Visualizador(std::vector<ball> &bodies, simulacao s, double delta_t,int GUI,int COLLISIONS) :
    delta_t(delta_t),
    GUI(GUI),
    COLLISIONS(COLLISIONS),
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
    gui.open ("GUI.txt");
    if(GUI == 0){
        gui <<"INFORMAÇÕES DO GUI"<<'\n';
    }
    //Abrindo Collisions
    collisions.open ("COLLISIONS.txt");
    if(COLLISIONS == 0){
        collisions <<"INFORMAÇÕES DAS COLISÕES"<<'\n';
    }
}

Visualizador::~Visualizador() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


void Visualizador::draw() {
    SDL_SetRenderDrawColor(renderer, 160, 160, 185, 255);
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
    bodies = bodiesprox;
}

void Visualizador::ball_move(){//Funções de movimento das bolas
    double delta_t=0.01;
    
    for (int i = 0; i < (bodies.size()); i++){ 
       float g = 9.8;
       double fat= s.mu *bodies[i].mass *g;//Fat         acel =mu*g
       //decompondo em x e y
       double acel_x=fat*(bodiesprox[i].vx/(sqrt(pow(bodiesprox[i].vx,2)+pow(bodiesprox[i].vy,2))));//a*cos (cos=vx/hip)
       double acel_y=fat*(bodiesprox[i].vy/sqrt(pow(bodiesprox[i].vx,2)+pow(bodiesprox[i].vy,2)));//a*sen (sen=vy/hip)
  
        bodiesprox[i].x = bodies[i].x + (bodies[i].vx*delta_t);
        bodiesprox[i].y = bodies[i].y + (bodies[i].vy*delta_t);
        
        //ATRITO
        if(bodies[i].vx>0){
            bodiesprox[i].vx = bodies[i].vx - delta_t * fat;
            if(bodiesprox[i].vx<0){
                bodiesprox[i].vx = 0;
            }
        }
        else{
           bodiesprox[i].vx = bodies[i].vx + delta_t * fat;
            if(bodiesprox[i].vx>0){
                bodiesprox[i].vx = 0;
            }
        }
        
        if(bodies[i].vy>0){
            bodiesprox[i].vy = bodies[i].vy - delta_t * fat;
            if(bodiesprox[i].vy<0){
                bodiesprox[i].vy = 0;
            }
        }
        else{
            bodiesprox[i].vy = bodies[i].vy + delta_t * fat;
            if(bodiesprox[i].vy>0){
                bodiesprox[i].vy = 0;
            }
        }
    }
}

void Visualizador::ball_hit_wall(){//Simulando colisões entre bolas e as paredes do campo
  for (int i = 0; i <= (bodies.size()); i++){
    //colisão com parede da esquerda
    if((bodiesprox[i].x - bodiesprox[i].radius)<=0){
      bodiesprox[i].vx = -bodiesprox[i].vx;
      bodiesprox[i].x = bodies[i].x;
    }
    //colisão com parede de baixo
    if((bodiesprox[i].y - bodiesprox[i].radius)<=0){
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
    }
    //colisão com parede de cima
    if((bodiesprox[i].y +bodiesprox[i].radius)>=s.field_height){
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
    }
    //colisão com parede da direita
    if((bodiesprox[i].x + bodiesprox[i].radius)>= s.field_width){
      bodiesprox[i].vx = -bodiesprox[i].vx;
      bodiesprox[i].x = bodies[i].x;
    }
  }
}
void Visualizador::ball_hit_ball(){

    for (int i = 0; i < (bodies.size()); i++){
      for (int j = i+1; j < (bodies.size()); j++){
        double cateto1 =(bodies[i].x - bodies[j].x);
        double cateto2 = (bodies[i].y - bodies[j].y);
        double hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
        double soma_r = (bodiesprox[i].radius + bodiesprox[j].radius);
        if (hipotenusa <= soma_r){//Checando colisão
            if(COLLISIONS == 0){
                collisions <<"CHOQUE:"<<" ID0:"<<bodies[i].id<<" "<<"ID1:"<< bodies[j].id<<"\n";
            }
    
          //BOLA1 A
          double proj_j = (bodies[j].vx*cateto1+bodies[j].vy*cateto2)/(hipotenusa);//Constante de projeção da Bola1
          double vjhip_x = (proj_j*cateto1)/hipotenusa;
          double vjhip_y = (proj_j*cateto2)/hipotenusa;
          
          double vjhip_parallel_x = bodies[j].vx-vjhip_x;
          double vjhip_parallel_y = bodies[j].vy-vjhip_y;
         
          double vjhip_espelhado_x = -(vjhip_x);
          double vjhip_espelhado_y = -(vjhip_y);
         
          bodies[j].vx = vjhip_espelhado_x - vjhip_parallel_x;//novo_vetor_j_x
          bodies[j].vy = vjhip_espelhado_y - vjhip_parallel_y;//novo_vetor_j_y

          //BOLA2 B
          double proj_i = (bodies[i].vx*cateto1+bodies[i].vy*cateto2)/(hipotenusa);//Constante de projeção da Bola2
          double vihip_x = (proj_i*cateto1)/hipotenusa;
          double vihip_y = (proj_i*cateto2)/hipotenusa;
          
          double vihip_parallel_x = bodies[i].vx-vihip_x;
          double vihip_parallel_y = bodies[i].vy-vihip_y;
        
          double vihip_espelhado_x = -(vihip_x);
          double vihip_espelhado_y = -(vihip_y);
   
          bodies[i].vx = vihip_espelhado_x - vihip_parallel_x;//novo_vetor_i_x
          bodies[i].vy = vihip_espelhado_y - vihip_parallel_y;//novo_vetor_i_y
          
          if ( (proj_i >= 0 && proj_j <= 0)){//|(proj_i<0 &proj_j>0)
            proj_i=--proj_i;
            proj_j=-proj_j;
          }
          if((proj_i>=0 && proj_j>=0)){//|(proj_i<0 &proj_j<0) 
              proj_j=-proj_j;
          }
         }
       }
     }

  }
void Visualizador::do_iteration() {
    char* pPath;
    pPath = getenv ("PATH");
    if (pPath!=NULL)
        printf ("The current path is: %s",pPath);
    double tempo = (iter/delta_t)/100;
    //Escrevendo o Tempo no GUI
    if(GUI == 0){
      gui <<"Tempo: "<<tempo<<" sec"<<'\n';
      gui << "[";
    }
  for (unsigned g = 0; g < bodies.size(); g++){
      //Escerevendo infos no GUI
      if(GUI == 0){
          gui <<"IDbola:"<<bodiesprox[g].id<<"("<<" "<<" rad: "<<
          bodiesprox[g].radius<<","<<" mass: "<<
          bodiesprox[g].mass<<","<<" x: "<<
          bodiesprox[g].x<<","<<" y: "<<
          bodiesprox[g].y<<","<<" vx: "<<
          bodiesprox[g].vx<<","<<" vy: "<<
          bodiesprox[g].vy<<" "<<")"<<";"<<"\n";
      }
  }
    Visualizador::ball_move();
    Visualizador::ball_hit_wall();
    Visualizador::ball_hit_ball();
    //Diagramação do GUI
    if (GUI == 0){
        gui << "]" << '\n';
    }
    iter++;
}



