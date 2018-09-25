#include <iostream>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>

#include "semaphore.cpp"

using namespace std;

std::mutex mutexs;
void produce(queue<int>& q, semaphore& s){

	int it =rand()%101;;
	//std::unique_lock<std::mutex> lk(mutexs);
    q.push(it);
	cout << "Produz: " << it << "\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
    s.release();

    produce(q,s);
}

void consume(queue<int>& q, semaphore& s){

	s.acquire();
	cout << "Consome: " <<pow(q.front(),2) << "\n";
	//std::unique_lock<std::mutex> lk(mutexs);
    this_thread::sleep_for(std::chrono::milliseconds(500));
    q.pop();	
	
    consume(q,s);

}

int main(){
    srand (time(NULL));
	queue<int> q;

	semaphore s(0);


	thread t1(produce,ref(q),ref(s));
	thread t2(consume,ref(q),ref(s));


	t1.join();
	t2.join();
}