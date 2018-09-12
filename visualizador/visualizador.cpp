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

//GUI
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
}

void Visualizador::ball_move(){//Funções de movimento das bolas
    double delta_t=0.01;
    
    for (int i = 0; i < (bodies.size()); i++){ 
       float g = 9.8;
       double fat= s.mu *bodies[i].mass *g;//Fat         acel =mu*g
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

void Visualizador::ball_hit_wall(){
  for (int i = 0; i <= (bodies.size()); i++){
    if((bodiesprox[i].x - bodiesprox[i].radius)<=0){
      bodiesprox[i].vx = -bodiesprox[i].vx;
      bodiesprox[i].x = bodies[i].x;
    }
    else if((bodiesprox[i].y - bodiesprox[i].radius)<=0){
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
    }
    else if((bodiesprox[i].y +bodiesprox[i].radius)>=s.field_height){
      bodiesprox[i].vy = -bodiesprox[i].vy;
      bodiesprox[i].y = bodies[i].y;
    }
    else if((bodiesprox[i].x + bodiesprox[i].radius)>= s.field_width){
      bodiesprox[i].vx = -bodiesprox[i].vx;
      bodiesprox[i].x = bodies[i].x;
    }
  }
}
void Visualizador::do_iteration() {
    Visualizador::ball_move();
    Visualizador::ball_hit_wall();
    iter++;
}




