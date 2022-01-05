#ifndef DATA_STRACTURES_WET_2_HASHTABLE_H
#define DATA_STRACTURES_WET_2_HASHTABLE_H

#include "Player.h"
#include "sortedList.h"


class HashTable {

private:
    const int GROW_FACTOR = 4;
    const int INITIAL_SIZE = 2;
    

    
    

public:
    int size;
    SortedList<Player> Array;
    
    HashTable();
    HashTable(const HashTable&) = delete;
    ~HashTable();
    
    
    int HashFunc(int id);
    Player& find(int playerID);
    bool exists(int playerID);
    void insert(Player& new_player);
    void remove(int playerID);
    

};


#endif //DATA_STRACTURES_WET_2_HASHTABLE_H
