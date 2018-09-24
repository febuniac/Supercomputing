#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

std::mutex A, B;
std::condition_variable cA, cB;
bool readyA =false;
bool readyB = false;
std::string data;

void tarefaA() {

    std::cout << "Faz trabalho A" << std::endl;
    
    {
        std::unique_lock<std::mutex> lk(A);
        readyA = true;
        cA.notify_one();
    }
    
    {
        std::unique_lock<std::mutex> lk(B);
        // processed = true;
        cB.wait(lk, []{return readyB;});
        // after the wait, we own the lock.
        // std::cout << "Worker B thread is processing data\n";
        // data += " after processing";
        // processed = true;
        // std::cout << "Worker B thread signals data processing completed\n";
        // lk.unlock();    
        // cB.notify_one();
    }
        
    // DESEJO ESPERAR POR B AQUI!
    std::cout << "Fim trabalho A" << std::endl;
}

void tarefaB() {

    std::cout << "Faz trabalho B" << std::endl;
    {
        std::unique_lock<std::mutex> lk(B);
        
        readyB = true;
        cB.notify_one();
    }
    {
        std::unique_lock<std::mutex> lk(A);
        cA.wait(lk, []{return readyA;});
         // after the wait, we own the lock.
        // std::cout << "Worker A thread is processing data\n";
        // data += " after processing";
        // processed = true;
        // std::cout << "Worker A thread signals data processing completed\n";
        // lk.unlock();
        // cA.notify_one();
        
        //cA.wait(lk);
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


 

 

 
// int main()
// {
//     std::thread worker(worker_thread);
 
//     data = "Example data";
//     // send data to the worker thread
//     {
//         std::lock_guard<std::mutex> lk(m);
//         ready = true;
//         std::cout << "main() signals data ready for processing\n";
//     }
//     cv.notify_one();
 
//     // wait for the worker
//     {
//         std::unique_lock<std::mutex> lk(m);
//         cv.wait(lk, []{return processed;});
//     }
//     std::cout << "Back in main(), data = " << data << '\n';
 
//     worker.join();
// }




// std::mutex m;
// std::condition_variable cv;
// std::string data;
// bool ready = false;
// bool processed = false;

// static std::condition_variable shutdown_cv;
// static std::mutex shutdown_cv_mutex;
// static bool memcached_can_shutdown = false;
// void shutdown_server(void) {

//     std::unique_lock<std::mutex> lk(shutdown_cv_mutex);
//     if (!memcached_can_shutdown) {
//         // log and proceed to wait shutdown
//         LOG_INFO("shutdown_server waiting for can_shutdown signal");
//         shutdown_cv.wait(lk, []{return memcached_can_shutdown;});
//     }
//     memcached_shutdown = true;
//     LOG_INFO("Received shutdown request");
//     event_base_loopbreak(main_base);
// }

// void worker_thread()
// {
//     // Wait until main() sends data
//     std::unique_lock<std::mutex> lk(m);
//     cv.wait(lk, []{return ready;});
 
//     // after the wait, we own the lock.
//     std::cout << "Worker thread is processing data\n";
//     data += " after processing";
 
//     // Send data back to main()
//     processed = true;
//     std::cout << "Worker thread signals data processing completed\n";
 
//     // Manual unlocking is done before notifying, to avoid waking up
//     // the waiting thread only to block again (see notify_one for details)
//     lk.unlock();
//     cv.notify_one();
// }