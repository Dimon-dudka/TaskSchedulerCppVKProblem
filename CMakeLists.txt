cmake_minimum_required(VERSION 3.29)

project(VKTechBackend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/ScheduledTask/ScheduledTask.h
        ${CMAKE_SOURCE_DIR}/TaskScheduler/TaskScheduler.h
)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/ScheduledTask/ScheduledTask.cpp
        ${CMAKE_SOURCE_DIR}/TaskScheduler/TaskScheduler.cpp
)

add_executable(VKTechBackend ${SOURCES} ${HEADERS})

target_include_directories(VKTechBackend
        PUBLIC ${CMAKE_SOURCE_DIR}/ScheduledTask
        PUBLIC ${CMAKE_SOURCE_DIR}/TaskScheduler
)