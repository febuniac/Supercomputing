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
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <omp.h>

using namespace std;
struct simulacao s;
struct _ball b;


// reading the file with program info
void read_file(){
  if (!(cin >> s.field_width >> s.field_height >> s.n)) { throw 1; }
  if (!(cin >> s.mu >> s.alpha_w >> s.alpha_b)) { throw 1; }
}

//Função que le e salva informações em um vetor de bolas
std::vector<ball> save_to_vec(std::vector<ball> &list_balls){
  read_file();
  //criando listas de bolas 
  for (int i = 0; i < (s.n); i++){//for que vai lendo e jogando no lista de bolas
    cin >>b.id >>b.radius >> b.mass>>b.x>> b.y>> b.vx>> b.vy;
    list_balls.push_back(b);
    }
  return list_balls;
}

int main(int argc, char ** argv) {
        std::vector<ball> list_balls;
        save_to_vec(list_balls);
        Visualizador v(list_balls, s, 0.01,0);
        printf("x=%f \n", list_balls[0]);
        v.run();
    return 0; 
}
