cmake_minimum_required(VERSION 3.23)
project(club_simulator)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-Wall")

add_executable(club_simulator src/main.cpp "src/Time.cpp" "src/Table.cpp" "src/Utils.cpp")
