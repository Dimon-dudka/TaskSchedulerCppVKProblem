//--------------------------------------------------------------------------------------------
//  03.11.2024
//  Made by Dmitrii Dudin
//  VK Tech Backend Problem
//--------------------------------------------------------------------------------------------

#pragma once
#include <ctime>
#include <functional>

class ScheduledTask {
public:

    ScheduledTask() = default;
    ScheduledTask(std::function<void()> _task,std::time_t _timestep) : timestep(_timestep){
        task = std::move(_task);
    }

    void execute_task() {
        task();
    }

    std::time_t get_timestep() const {
        return timestep;
    }

    bool operator>(const ScheduledTask& other) const {
        return timestep > other.timestep;
    }

private:
    std::function<void()> task;
    std::time_t timestep;
};