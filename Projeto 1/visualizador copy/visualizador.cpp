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


Visualizador::Visualizador(std::vector<ball> &bodies, int field_width, int field_height, double delta_t) :
    delta_t(delta_t),
    field_width(field_width),
    field_height(field_height),
    bodies(bodies) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    double ratio = (double) field_width / field_height;
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
        filledCircleRGBA(renderer, i->x / field_width * win_width,
                         i->y / field_height* win_height,
                         i->radius / field_width * win_width,
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

// void Visualizador::read_file(){
// struct simulacao {//para guardar os valores da simulação (usar return)
//   double field_width, field_height, n, mu, alpha_w, alpha_b;} ;
// struct simulacao s;
// struct _ball b;
// // reading the file with program info
//   if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
//   if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
// }

// vector<ball> Visualizador::save_to_vec(){}
// std::vector<ball> list_balls (s.n);

//   read_file();
  
//   for (int i = 0; i <= (s.n); i++){
//     if (!(cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy)){
//       list_balls.push_back(b);
//       cout<< b.id<< b.radius<< b.mass<<b.x<< b.y<< b.vx<< b.vy<<"\n";
//     }
//   }
//   return list_balls;
// }




void Visualizador::do_iteration() {

// struct simulacao {//para guardar os valores da simulação (usar return)
//   double field_width, field_height, n, mu, alpha_w, alpha_b;
// } ;
// struct simulacao s;
// struct _ball b;

// std::vector<ball> list_balls (s.n);
//   // reading the file with program info
//   if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
//   if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
//   //adding to a vector
//   for (int i = 0; i <= (s.n); i++){
//     if (!(cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy)){
//       list_balls.push_back(b);
//       cout<< b.id<< b.radius<< b.mass<<b.x<< b.y<< b.vx<< b.vy<<"\n";
//     }
// }
    iter++;
}




