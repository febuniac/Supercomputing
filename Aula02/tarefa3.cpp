#include <iostream>
#include <random>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>       /* tempo rodando */
#include <ctime>
#include <math.h>
// #include <funcs.cpp>
using namespace std;

double inner_prod(double *a, double *b, unsigned long n) {//falta
    double sum = 0;
    for (unsigned long i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sqrt(sum);
}

double sum_positive(double *a, unsigned long n) {
    double s = 0;
    for (unsigned long i = 0; i < n; i++) {
        if (a[i] > 0) {
            s += a[i];
        }
    }
    return s;
}

void sqrt_element(double *a, unsigned long n) {
    for (unsigned long i = 0; i < n; i++) {
        a[i] = sqrt(a[i]);
    }
}

void exp_element(double *a, unsigned long n) {
    for (unsigned long i = 0; i < n; i++) {
        a[i] = exp(a[i]);
    }
}

void log_element(double *a, unsigned long n) {
    for (unsigned long i = 0; i < n; i++) {
        a[i] = log(a[i]);
    }
}

void gauss(double *a, double *b, unsigned long n) { //falta
    double p = 1 / sqrt(2.0 * M_PI);
    for (unsigned long i = 0; i < n; i++) {
        b[i] = p * exp(-a[i]*a[i]/2);
    }
}


int main (int argc, char *argv[]) {
  unsigned long size = 10000000;//tamanho do array "a"
  double *vetor= new double[size]; //"criando o array"
  double *vetor2= new double[size]; //"criando o array"
  unsigned long result;
  double rnum;
  /* initialize random seed: */
  srand (time(NULL));
  for ( unsigned long n=0 ; n<size ; n++ )
  {/* generate secret number between 0 and 20: */
  rnum = rand() % 20 + 1;
  vetor[n] = rnum - 10;//num randomico do array
  vetor2[n] = rnum - 10;//num randomico do array
  }
  // unsigned long iteration = 5;
  // for (int k=0 ; k<=iteration ; k++ ){
  //   size *=10;
    std::cout << "Array Size:"<<size;
    auto start = std::chrono::high_resolution_clock::now();
    double x = inner_prod(vetor,vetor2, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(end-start);
    std::time_t end_time = std::chrono::high_resolution_clock::to_time_t(end);
    std::cout << "\n finished computation (inner_prod) at " << std::ctime(&end_time)
              << " elapsed time 1 : " << elapsed_seconds.count() << "s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    double y = sum_positive(vetor,size);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = elapsed_seconds2 = std::chrono::duration_cast<std::chrono::duration<double> >(end2-start2);
    std::time_t end_time2 = std::chrono::high_resolution_clock::to_time_t(end2);
    std::cout << "\n finished computation (sum_positive) at " << std::ctime(&end_time2)
              << "elapsed time 2: " << elapsed_seconds2.count() << "s\n";

    auto start3 = std::chrono::high_resolution_clock::now();
    sqrt_element(vetor, size);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = elapsed_seconds3 = std::chrono::duration_cast<std::chrono::duration<double> >(end3-start3);
    std::time_t end_time3 = std::chrono::high_resolution_clock::to_time_t(end3);
    std::cout << "\n finished computation (sqrt_element) at " << std::ctime(&end_time3)
              << "elapsed time 3: " << elapsed_seconds3.count() << "s\n";

    auto start4 = std::chrono::high_resolution_clock::now();
    exp_element(vetor, size);
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds4 = elapsed_seconds4 = std::chrono::duration_cast<std::chrono::duration<double> >(end4-start4);
    std::time_t end_time4 = std::chrono::high_resolution_clock::to_time_t(end4);
    std::cout << "\n finished computation (exp_element) at " << std::ctime(&end_time4)
              << "elapsed time 4: " << elapsed_seconds4.count() << "s\n";

    auto start5 = std::chrono::high_resolution_clock::now();
    log_element(vetor, size);
    auto end5 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds5 = elapsed_seconds5 = std::chrono::duration_cast<std::chrono::duration<double> >(end5-start5);
    std::time_t end_time5 = std::chrono::high_resolution_clock::to_time_t(end5);
    std::cout << "\n finished computation (log_element) at " << std::ctime(&end_time5)
              << "elapsed time 5: " << elapsed_seconds5.count() << "s\n";

    auto start6 = std::chrono::high_resolution_clock::now();
    gauss(vetor,vetor2, size);
    auto end6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds6 = elapsed_seconds6 = std::chrono::duration_cast<std::chrono::duration<double> >(end6-start6);
    std::time_t end_time6 = std::chrono::high_resolution_clock::to_time_t(end6);
    std::cout << "\n finished computation (gauss) at " << std::ctime(&end_time6)
              << "elapsed time 6: " << elapsed_seconds6.count() << "s\n \n";

    // auto start7 = std::chrono::high_resolution_clock::now();
    // gauss(vetor,vetor2, size);
    // auto end7 = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed_seconds7 = elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end7-start7);
    // std::time_t end_time7 = std::chrono::high_resolution_clock::to_time_t(end7);
    // std::cout << "\n finished computation 7 at " << std::ctime(&end_time7)
    //           << "elapsed time 7: " << elapsed_seconds.count() << "s\n";

    std::cout <<"Ignore:"<< x<< y<<"\n";
  // }

  return 0;

  // std::cout << "Array Size:"<<size;
  // high_resolution_clock::time_point t1 = high_resolution_clock::now();
  // log_element(vetor, size);
  // high_resolution_clock::time_point t2 = high_resolution_clock::now();
  // duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
  // std::cout << "It took me " << time_span.count() << " seconds.";
  // std::cout << std::endl;
//g++-8 -O2 -ffast-math -ft-mavx tarefa2.cpp

//g++-8 -O2 -o tarefa3 tarefa3.cpp
// g++-8 -O2 -ffast-math -ftree-vectorize -mavx -o tarefa3 tarefa3.cpp

}
