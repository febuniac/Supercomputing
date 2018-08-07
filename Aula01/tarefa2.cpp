#include <iostream>
#include <random>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>       /* tempo rodando */
#include <ctime>

using namespace std;

double soma_positivos1 (double *a, int n){
  //std::chrono::time_point<std::chrono::system_clock> start, end;

  double resultado =0 ;//resultyado final das somas dos posityivos inicializado em 0

  for (int i=0 ; i<n ; i++)//percorrendo o array "a"de acordo com o tamanho "n"
  {
    //checa positividade
    if (a[i]>=0){
      //std::cout<<"\nvalor_SP1:"<<a[i]<<"\n";
      resultado+=a[i];
    }
    else{
      continue;
    }
  }
  //std::cout << " \n RESULTADO 1: "
            //<< resultado ;
  return resultado;
}

double soma_positivos2 (double *a, int n){
  //std::chrono::time_point<std::chrono::system_clock> start, end;

  double resultado2 =0 ;

  for (int j=0 ; j<n ; j++)
  {
    //checa positividade
    //std::cout<<"\nvalor_SP2:"<<a[j]<<"\n";
    resultado2+=(a[j]>=0)?a[j]:0;
  }
  //std::cout << "\n RESULTADO 2: "
            //<< resultado2;

  return resultado2;
}


int main (int argc, char *argv[]) {
  int size = 1000000;//tamanho do array "a"

  double *vetor= new double[size]; //"criando o array"
  int result;
  double rnum;

  /* initialize random seed: */
  srand (time(NULL));

  for ( int n=0 ; n<size ; n++ )
  {
    /* generate secret number between 0 and 20: */
  rnum = rand() % 20 + 1;
  vetor[n] = rnum - 10;//num randomico do array

  }
  auto start = std::chrono::high_resolution_clock::now();
  int x = soma_positivos1(vetor, size);
  //std::cout << vetor[0];
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
  std::time_t end_time = std::chrono::high_resolution_clock::to_time_t(end);

std::cout << "\n finished computation 1 at " << std::ctime(&end_time)
          << " elapsed time 1 : " << elapsed_seconds.count() << "s\n";

auto start2 = std::chrono::high_resolution_clock::now();
int y = soma_positivos2(vetor, size);
//std::cout << vetor[0];
auto end2 = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> elapsed_seconds2 = elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end2-start2);
std::time_t end_time2 = std::chrono::high_resolution_clock::to_time_t(end2);

std::cout << "\n finished computation 2 at " << std::ctime(&end_time2)
        << "elapsed time 2: " << elapsed_seconds.count() << "s\n";
  //int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
  //                         (end-start).count();
  //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  //std::cout << "finished computation at " << std::ctime(&end_time)
  //          << "elapsed time: " << elapsed_seconds << "s\n";
  std::cout << x<< y;

  return 0;
//g++-8 -O2 -ffast-math -ft-mavx tarefa2.cpp


}
