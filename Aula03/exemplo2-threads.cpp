#include <thread>
#include <iostream>


\
void funcao_rodando_em_paralelo_id(int id) {
    std::cout << "id=" << id << std::endl;
}


int main() {


    // Cria thread e a executa.
    // Primeiro argumento é a função a ser executada.

    // Os argumentos em seguida são passados diretamente
    // para a função passada no primeiro argumento.
    std::thread t0(funcao_rodando_em_paralelo_id,0);
    std::thread t1(funcao_rodando_em_paralelo_id,1);
    std::thread t2(funcao_rodando_em_paralelo_id,2);
    std::thread t3(funcao_rodando_em_paralelo_id,3);


    // Espera até que a função acabe de executar.
    t0.join();
    t1.join();
    t2.join();
    t3.join();

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}




// https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
