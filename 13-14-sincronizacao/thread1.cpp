#include <thread>
#include <iostream>
#include <mutex>

std::mutex mutex1;

void funcao_rodando_em_paralelo_id(int id) {
    {std::lock_guard<std::mutex> lock(mutex1);
    std::cout << "id=" << id << std::endl;}// Em C++ sempre que algo é criado ao abrir uma chave essa coisa é destruida no fecha chaves, 
    //aqui com o lock o mutex apenas destroi o mutex na destruição, essas chaves destroem o lock após o print. (destroi a variável)
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
