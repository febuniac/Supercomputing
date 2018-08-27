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
#include "Projeto1.cpp"
// #include <vector>
// #include <stdio.h>
// #include <iostream>
// #include <vector>
// #include <iterator>
// using namespace std;


int main(int argc, char ** argv) {
    
    // std::vector<ball> balls(100 * 100);
    // for (int i = 0; i <= (s.n); i++) {
    //     for (int j = 0; j < 100; j++) {
    //         balls[i*100 + j].x = i*10;
    //         balls[i*100 + j].y = j*10;
    //         balls[i*100 + j].radius = 4;
    //     }
    // }
    //Visualizador v(balls, 1000, 1000, 0.01);

    // struct simulacao {//para guardar os valores da simulação (usar return)
    // double field_width, field_height, n, mu, alpha_w, alpha_b;
    // } ;
    // struct simulacao s;
    // struct _ball b;

    // std::vector<ball> list_balls (s.n);
    // // reading the file with program info
    // if (!(cin >> s.field_width >> s.field_height >> s.n)) 
    // if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) 
    // //adding to a vector
    // for (int i = 0; i <= (s.n); i++){
    //     if (!(cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy)){
    //     list_balls.push_back(b);
    //     cout<< b.id<< b.radius<< b.mass<<b.x<< b.y<< b.vx<< b.vy<<"\n";
    //     }
    // }
        save_to_vec();
        cout<< b.id<< b.radius<< b.mass<<b.x<< b.y<< b.vx<< b.vy<<"\n";
        cout<< s.field_height<< s.field_width<<"\n";
        Visualizador v(list_balls, s.field_height, s.field_width, 0.01);
        v.run();
    return 0; 
}
