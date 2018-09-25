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
    s.release();
    
    this_thread::sleep_for(std::chrono::milliseconds(700));
    produce(q,s);
}

void consume(queue<int>& q, semaphore& s){

	s.acquire();
	cout << "Consome: " <<pow((q.front()),2) << "\n";
	//std::unique_lock<std::mutex> lk(mutexs);
    q.pop();	
    
    this_thread::sleep_for(std::chrono::milliseconds(100));
    consume(q,s);

}

int main(){
	queue<int> q;

	semaphore s(0);


	thread t1(produce,ref(q),ref(s));
	thread t2(consume,ref(q),ref(s));


	t1.join();
	t2.join();
}