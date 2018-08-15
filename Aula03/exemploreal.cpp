#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
using namespace std;


double soma_vetor_seq (double *vec, int n){
  double resultado =0 ;

  for (int i=0 ; i<n ; i++)//percorrendo o array "a"de acordo com o tamanho "n"
  {
		  resultado+=vec[i];

    }
		cout << "resultado: " << resultado;
  return resultado;
}
int main()
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(/*mean=*/1.0,/*stddev=*/5.0);
	int size = 10;
	double vetor[size]={};

	for (unsigned long n=0 ; n<size ; n++ )
	{
		double number = distribution(generator);
		vetor[n] = number;//num randomico do array
	}
	std::cout << "normal_distribution (1.0,5.0):" << std::endl;
	soma_vetor_seq (vetor, size);
  return 0;


		// int size = 3;
		// double arr[size];
    // random_device rd;
    // default_random_engine dre(rd());
		// std::normal_distribution<double> destribution(/*mean=*/1, /*stddev=*/5);
		//
    // generate(arr, arr + sizeof(arr) / sizeof(int), [&] () { return destribution(dre); });
    // for (int a : arr){
    //     cout << a << " ";
		// 	}
		// 	soma_vetor_seq (arr, size);
		// 	return 0;
}
// https://stackoverflow.com/questions/26051101/how-to-fill-an-array-with-random-values-from-a-range-duplicates-are-ok
// normal_distribution
