//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_DYNAMICARRAY_H
#define DATA_STRACTURES_WET_2_DYNAMICARRAY_H

#include "Player.h"
#include "sortedList.h"

class DynamicArray {



private:
    const int GROW_FACTOR = 4;
    const int INITIAL_SIZE = 2;
    
    
    int size;
    SortedList<Player> Array[];

public:
    
    DynamicArray(int size) : Array(size){};
    ~DynamicArray();
    void insert(int index, Player& playerID);
    void remove(int index, int playerID);
    Player& find(int index) const;
    
};


#endif //DATA_STRACTURES_WET_2_DYNAMICARRAY_H
