cmake_minimum_required(VERSION 3.6)
project(GA_Knapsack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Population.cpp src/chromosome/Chromosome.cpp src/knapsack/Item.cpp src/knapsack/ItemList.cpp src/knapsack/ItemList.h)
add_executable(GA_Knapsack ${SOURCE_FILES})
