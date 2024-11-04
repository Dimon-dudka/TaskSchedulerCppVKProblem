//--------------------------------------------------------------------------------------------
//  03.11.2024
//  Made by Dmitrii Dudin
//  VK Tech Backend Problem
//--------------------------------------------------------------------------------------------

#include "TaskScheduler.h"

#include <future>

TaskScheduler::TaskScheduler() : b_is_running(true), start_timestamp(std::time(nullptr))
                                      , time_for_sleep(0) {
    worker_thread = std::thread(&TaskScheduler::process_tasks, this);
}

TaskScheduler::~TaskScheduler() {
    {
        std::scoped_lock lock(scheduling_mutex);
        b_is_running = false;
    }

    scheduling_cv.notify_all();
    worker_thread.join();
}

void TaskScheduler::add(std::function<void()> _task, std::time_t _timestep) {
    std::scoped_lock lock(scheduling_mutex);

    if (!b_is_running)
        return;

    tasks.emplace(ScheduledTask({_task, _timestep}));
    compare_new_timestep(_timestep);
    scheduling_cv.notify_one();
}

std::time_t TaskScheduler::get_time_for_thread_wait() {
    std::scoped_lock lock(scheduling_mutex);
    return time_for_sleep;
}


void TaskScheduler::process_tasks() {
    while (b_is_running) {
        ScheduledTask task;
        {
            std::unique_lock<std::mutex> lock(scheduling_mutex);
            scheduling_cv.wait(lock, [this] { return !tasks.empty() || !b_is_running; });

            if (!b_is_running && tasks.empty()) {
                return;
            }

            auto current_time = std::time(nullptr);
            while (!tasks.empty() && tasks.top().get_timestep() <= current_time) {
                auto square = [] (int num) { return num * num; };
                task = tasks.top();
                tasks.pop();
                lock.unlock();
                task.execute_task();
                lock.lock();
            }

            if (!tasks.empty()) {
                std::this_thread::sleep_for(
                    std::chrono::system_clock::duration(tasks.top().get_timestep() - current_time));
            }
        }
    }
}

void TaskScheduler::compare_new_timestep(std::time_t _timestamp) {
    time_for_sleep = std::max(time_for_sleep, _timestamp - start_timestamp);
}
