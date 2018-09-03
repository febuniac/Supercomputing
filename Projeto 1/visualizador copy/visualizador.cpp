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
using namespace std;
typedef std::chrono::high_resolution_clock Time;


Visualizador::Visualizador(std::vector<ball> &bodies, simulacao s, double delta_t) :
    delta_t(delta_t),
    s(s),
    //field_width(field_width),
    //field_height(field_height),
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

void Visualizador::ball_hit_ball(){
    int hipotenusa;
    for (int i = 0; i < (bodies.size()); i++){
      for (int j = i+1; j < (bodies.size()); j++){
        double cateto1 =(bodies[i].x - bodies[j].x);
        double cateto2 = (bodies[i].y - bodies[j].y);
        hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
        if (hipotenusa < (bodies[i].radius + bodies[j].radius)){
          printf("Choque de Bolas!");
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
    Visualizador::ball_move();
    //SWAP(atualização de vetor p próximas posições)
    // temp = list_balls2;
    // list_balls2 = list_balls;
    // list_balls = temp;
    Visualizador::ball_hit_ball();
    Visualizador::ball_hit_wall();
    iter++;
}