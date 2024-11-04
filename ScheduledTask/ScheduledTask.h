//--------------------------------------------------------------------------------------------
//  Made by Dmitrii Dudin
//  VK Tech Backend Problem
//--------------------------------------------------------------------------------------------

#pragma once
#include <ctime>
#include <functional>

class ScheduledTask
{
public:
	using Function = std::function<void()>;

	ScheduledTask() = default;

	ScheduledTask(Function _task, std::time_t _timestep) : task(std::move(_task)), timestep(_timestep)
	{}

	void execute_task()
	{
		task();
	}

	std::time_t get_timestep() const
	{
		return timestep;
	}

	bool operator>(const ScheduledTask &other) const
	{
		return timestep > other.timestep;
	}

private:
	Function task;
	std::time_t timestep;
};
