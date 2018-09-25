#include <iostream>
#include <thread>
#include <random>
#include <cmath>
#include <assert.h> 

#include "semaphore.cpp"

class queue_finita{
    public:
        queue_finita();
        void add(int it);
        int get();

    private:
        int to_produce;//posição p colocar proximo item
        int to_consume;//posicao p tirar proximo item
        int size;
        int data*;
};

queue_finita::queue_finita(){
    to_produce = 0;
    to_consume = 0;
    data = new int[size];
};


void queue_finita::add(int it){
    data[to_produce] = it;
    to_produce = (to_produce+1) % size;
    assert (to_produce!=to_consume);
}

int queue_finita::get(){
    assert (to_produce!=to_consume);
    int it = data[to_consume];
    to_consume=(to_produce+1) % size;
    return it;
}

std::mutex mutex;
void produce(FilaFinita<int>& q, semaphore& count,semaphore& vazios){
    int it = rand()%(100-0 + 1) + 0;
    std::cout<<it;
    vazios.acquire();
    std::unique_lock<std::mutex> lk(mutex);
    q.add(it);
    count.release();

    produce(q, count,vazios);
}

void consume(FilaFinita<int>& q, semaphore& count,semaphore& vazios){
    count.acquire();
    std::unique_lock<std::mutex> lk(mutex);
    int it = q.get();
    std::cout << pow(it, 2) << '\n';
    vazios.release();
    consume(q, count,vazios);
}

int main(int argc, char *argv[]) {
    int sizeq=0;
    FilaFinita<int> q(sizeq);
    semaphore count(0);
    semaphore vazios(sizeq);

    std::thread t0(produce, std::ref(q), std::ref(count),std::ref(vazios));
    
    std::thread t1(consume, std::ref(q), std::ref(count),std::ref(vazios));

    t0.join();
    t1.join();
    return 0;
}

// class queue_finita{
//     public:
//         queue_finita();
//         void add(int it);
//         int get();

//     private:
//         int to_produce;//posição p colocar proximo item
//         int to_consume;//posicao p tirar proximo item
//         int size;
//         int data[];
// };

// queue_finita::queue_finita(){
//     to_produce = 0;
//     to_consume = 0;
//     data = new data[size];
// };


// void queue_finita::add(int it){
//     data[to_produce] = it;
//     to_produce = (to_produce+1) % size;
//     assert (to_produce!=to_consume);
// }

// int queue_finita::get(){
//     assert (to_produce!=to_consume);
//     int it = data[to_consume];
//     to_consume=(to_produce+1) % size;
//     return it;
// }

//     return rand()%(100-0 + 1) + 0;
// }

// void consume_item(int item){
//     std::cout << pow(item, 2) << '\n';
// }

// void produce(FilaInfinita<int>& q, semaphore& s){
//     int it = produce_item();
//     q.add(it);
//     s.release();

//     produce(q, s);
// }

// void consume(FilaInfinita<int>& q, semaphore& s){
//     s.acquire();
//     int it = q.get();
//     consume_item(it);

//     consume(q, s);
// }

// int main(int argc, char *argv[]) {
//     FilaInfinita<int> q;
//     semaphore s(0);

//     std::thread t0(produce, std::ref(q), std::ref(s));
//     std::thread t1(consume, std::ref(q), std::ref(s));

//     t0.join();
//     t1.join();
//     return 0;
// }