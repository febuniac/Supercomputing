#include <iostream>
#include "boost/filesystem.hpp" 

using namespace boost::filesystem;
//Um script que baixa uma lista de arquivos texto para teste 
int main(int argc, char **argv) {
    
    path p(".");
    
    for (auto &entry : directory_iterator(p)) {
        std::cout << entry.path().string() << is_regular_file(entry.path()) << "\n";
        
    }
    
    return 0;
}
//1-Recebe dois argumentos: um diretório e uma string
//2-Busca nos arquivos deste diretório esta string. 
//3-A saída do programa é uma lista de pares(arquivo:linha)onde a string foi encontrada. 
