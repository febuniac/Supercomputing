#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>

std::mutex T0;
std::mutex T1;
std::condition_variable cT0, cT1;
bool T0ready = false;
bool T1ready = false;

void thread0(int &resultado_para_thread1) {
    // // faz trabalho longo
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    resultado_para_thread1 = 10;
    {
        std::unique_lock<std::mutex> lk(T0);
        T0ready = true;
    }
    cT0.notify_all();
    // // faz trabalho longo
    std::this_thread::sleep_for(std::chrono::milliseconds(1300));
    std::cout << "Fim thread0!" << std::endl;
   
}

void thread1(int const &resultado_da_thread0, int &resultado_para_thread2) {
    {
        std::unique_lock<std::mutex> lk(T0);
        cT0.wait(lk,[]{return T0ready;});
    }
    // // faz trabalho long com resultado de thread0
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    
    // finja que isto depende da thread0
    resultado_para_thread2 = 20; 
   {
       std::unique_lock<std::mutex> lk(T1);
        T1ready = true;
    }
    cT1.notify_all();
    std::cout << "Fim thread1!" << std::endl;
}

void thread2(int const &resultado_thread_0, int const &resultado_thread_1) {
    // // faz trabalho longo com resultado de thread0
    // std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    
    // // faz trabalho longo com resultado de thread1
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    {
        std::unique_lock<std::mutex> lk(T0);
        cT0.wait(lk,[]{return T0ready;});
    }
        // faz trabalho longo com resultado de thread0
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    {
        std::unique_lock<std::mutex> lk(T1);
        cT1.wait(lk,[]{return T1ready;});
    }
        // faz trabalho longo com resultado de thread1
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
   
    std::cout << "thread2:" << resultado_thread_0 + resultado_thread_1 << "\n";
    std::cout << "Fim thread2!" << std::endl;
}

int main(int argc, char **argv) {
    int res_t0, res_t1;
    
    std::thread t0(thread0, std::ref(res_t0));
    std::thread t1(thread1,std::ref(res_t0), std::ref(res_t1));
    std::thread t2(thread2,std::ref(res_t0), std::ref(res_t1));
    
    t0.join();
    t1.join();
    t2.join();

    return 0;
}
