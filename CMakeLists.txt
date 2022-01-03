cmake_minimum_required(VERSION 3.19)
project(Data_Stractures_Wet_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Data_Stractures_Wet_2
        main2.cpp
        Player.cpp Player.h
        Group.cpp Group.h
        Game.cpp Game.h
        LevelData.cpp LevelData.h
        HashTable.cpp HashTable.h
        UnionFind.cpp UnionFind.h
        LevelNode.h
        LevelTree.h)