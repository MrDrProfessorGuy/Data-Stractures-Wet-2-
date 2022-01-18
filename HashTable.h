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
    int curr_amount;
    SortedList<Player> *array;
    
    HashTable();
    HashTable(const HashTable&) = delete;
    ~HashTable();
    
    
    int hashFunc(int id);
    Player* findPlayer(int playerID);
    bool exists(int playerID);
    void insert(Player new_player);
    void remove(int playerID);
    void rehash(bool action);
    
    
};


#endif //DATA_STRACTURES_WET_2_HASHTABLE_H
