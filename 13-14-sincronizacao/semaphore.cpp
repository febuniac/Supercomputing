#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>

class semaphore
{
    public:
        void acquire();
        void release();
        semaphore(int max_threads);
    private:
        int permits;//vagas disponiveis para threads
        int capacity;//threads max do programa
        std::mutex m;
        std::condition_variable cv;
};

//contador vai de capacity até zero
semaphore::semaphore(int max_threads){
    capacity = max_threads;//maximo de threads qque meu semaphore pode ter
     permits = capacity;// comecamos na max capacidade (tudo livre)

}

void semaphore::acquire()
{
    std::unique_lock<std::mutex> lk(m);//thread que entra bloqueia para poder atualizar (apenas uma de cada vez)
    // while (permits<=0)//se as vagas forem zero
    // {
    //     //permit somente muda quando um release for chamado (liberou uma vaga)
    //     cv.wait(lk);
    // }
    //O while acima descereve o comportamento do lambda
    cv.wait(lk,[this]{return permits > 0;});//this avisa que o permits vem de fora (vem de semaphore)
    //se der um acquire, uma vaga é consumida
    permits-=1;
}


void semaphore::release()
{
    std::unique_lock<std::mutex> lk(m);
    permits+=1;//liberando uma vaga (tenho que avisar uma thread qualquer e nao todas [notify_all])
    cv.notify_one(); //avisando uma thread  "x" que liberou uma vaga
}




// def aquire():
//     int sinal =0
//     int capacidade=0
//     While(sinal==capacidade):  
//         wait()
//     if(sinal == 0):
//         notifyAll();
//     sinal+=1


// **Exercício**: escreva, em pseudo-código, qual deverá ser o comportamento do método `void release()`.\vspace{7em}
// def release():
//     int sinal =0
//     int capacidade=0
//     While(sinal==0):  
//         wait()
//     if(sinal == capacidade):
//         notifyAll();
//     sinal-=1