#ifndef THREAD_HPP
#define THREAD_HPP

#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include <semaphore>

#define SLOTS 5 // num of allowed thread to work concurrently

class Thread {
    private: 
        uint16_t id;                                // id of the thread
        std::unique_ptr<std::thread> _thread;                       // the workerthread
        static void workerThread(Thread* aThread, std::counting_semaphore<SLOTS>& sem);  // method for the actual working thread
    
    public:
        Thread(uint16_t id);                        // default constructor
        void doWork(std::counting_semaphore<SLOTS>& sem);                     // simulates thread working
        uint16_t getID();                           // returns id
        void run(std::counting_semaphore<SLOTS>& sem);                        // creates the thread
        void wait();
};

#endif