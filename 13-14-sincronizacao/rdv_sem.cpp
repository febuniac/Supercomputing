#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include "semaphore.cpp"
int capacity =0;

semaphore  semA(capacity);
semaphore  semB(capacity);

void tarefaA() {

    std::cout << "Faz trabalho A" << std::endl;
    
    {
        semA.release();
    }
    
    {
        semB.acquire();
    }
        
    // DESEJO ESPERAR POR B AQUI!
    std::cout << "Fim trabalho A" << std::endl;
}

void tarefaB() {

    std::cout << "Faz trabalho B" << std::endl;
    
    {
        semB.release();
    }
    
    {
        semA.acquire();
    }
    // DESEJO ESPERAR POR A AQUI!
    std::cout << "Fim trabalho B" << std::endl;
}

int main(int argc, char *argv[]) {
    std::thread t1(tarefaA);
    std::thread t2(tarefaB);
    
    
    t1.join();
    t2.join();
    return 0;
}
