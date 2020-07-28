cmake_minimum_required(VERSION 3.15)
project(Pokemon C)

set(CMAKE_C_STANDARD 99)

add_executable(Pokemon MainSecond.c Pokemon.c Pokemon.h Defs.h LinkedList.c LinkedList.h MaxHeap.c MaxHeap.h BattleByCategory.c BattleByCategory.h)