#include "thread.hpp"
#include <functional>
#include <memory>

/*
 Method: 
   Constructor
 
 Desc:
   This constructor assings an id to this instance
*/


Thread::Thread(uint16_t id) {
    this->id = id;
}

/*
 Method: 
   doWork()

 Desc:
   This method allows the thread to simulate "work"
*/

void Thread::doWork(std::counting_semaphore<SLOTS>& sem) {
    using namespace std::literals::chrono_literals;

    std::cout << id << ": Hello!" << std::endl;

    while (true) {
      // -- SEMAPHORE: acquires here, waits until signaled
      sem.acquire();

      std::cout << id << ": wokeup\n";
      std::cout << id << ": working...\n";
      std::this_thread::sleep_for(5s);
      std::cout << id << ": done!\n";
      std::cout << id << ": going back to sleep.\n";
      
      // -- SEMAPHORE: release lock here --
      sem.release();
    }
}

/*
 Method: 
   getID()

 Desc:
   Returns this objects id
*/
uint16_t Thread::getID() {
    return id;
}

/*
 Method:
   run()

 Desc:
   Creates instance of thread and pass this instance as the parameter
*/
void Thread::run(std::counting_semaphore<SLOTS>& sem) {
    // _thread = new std::thread(workerThread, this, std::ref(sem));
    _thread = std::make_unique<std::thread>(&Thread::workerThread, this, std::ref(sem));
}

/*
 Method: 
   workerThread(Thread* thread)

 Desc:
   This calls the do work function
*/
void Thread::workerThread(Thread* aThread, std::counting_semaphore<SLOTS>& sem) {
  aThread->doWork(sem);
}

/*
 Method:
  wait()

 Desc:
  This method calls the main process to wait until this thread is terminated
*/
void Thread::wait() {
  if (_thread && _thread->joinable()) {
    _thread->join();
  }
}