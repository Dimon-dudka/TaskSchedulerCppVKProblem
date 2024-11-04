//--------------------------------------------------------------------------------------------
//  Made by Dmitrii Dudin
//  VK Tech Backend Problem
//--------------------------------------------------------------------------------------------
#include <iostream>

#include "TaskScheduler.h"

int main() {

    TaskScheduler task_scheduler;

    //  TaskScheduler usage example
    //  May be replaced with another check
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread([i, &task_scheduler]() {
            for (int j = 0; j < 100; ++j) {
                task_scheduler.add([i, j]() {
                    std::cout << "Thread number: " << i << " | " << "Task number: " << j << std::endl;
                }, std::time(nullptr) + rand() * i % 10);
            }

        }));
    }

    //  wait all tasks
    //  may be unused but for more visibility its here
    std::this_thread::sleep_for(static_cast<std::chrono::seconds>(task_scheduler.get_time_for_thread_wait()));

    //  main thread going to wait all threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
