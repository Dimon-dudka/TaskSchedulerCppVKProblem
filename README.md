# TaskSchedulerCppVKProblem
Implementation of the task scheduler as part of a task from VK Tech.  
The task scheduler itself runs in a single thread, performing the actions assigned to it.
However, you can access it from different threads.
The tasks are stored in a sorted order in the queue, based on their start time.


## API
The Task Scheduler has an API that provides the following features:
1) **void add(std::function<void()> _task,std::time_t _timestamp)** - adds a task to the scheduler with a runtime no earlier than _timestep.
2) **std::time_t get_time_for_thread_wait()** - returns the time it will take to wait for all tasks to complete.

## Technology stack
- C++20
- STL
- CMake
- Git
