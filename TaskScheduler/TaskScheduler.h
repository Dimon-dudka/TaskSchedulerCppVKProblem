//--------------------------------------------------------------------------------------------
//  Made by Dmitrii Dudin
//  VK Tech Backend Problem
//--------------------------------------------------------------------------------------------

#pragma once

#include <condition_variable>
#include <ctime>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "ScheduledTask.h"


class TaskScheduler {
public:

    explicit TaskScheduler();
    TaskScheduler(const TaskScheduler &) = delete;
    TaskScheduler &operator=(const TaskScheduler &) = delete;

    ~TaskScheduler();

    void add(std::function<void()> _task,std::time_t _timestep);

    std::time_t get_time_for_thread_wait();

private:

    void process_tasks();
    void compare_new_timestep(std::time_t _timestamp);

    std::priority_queue<ScheduledTask,std::vector<ScheduledTask>
            , std::greater<>> tasks;
    std::mutex scheduling_mutex;
    std::condition_variable scheduling_cv;
    std::thread worker_thread;
    std::time_t start_timestamp, time_for_sleep;
    bool b_is_running;
};
