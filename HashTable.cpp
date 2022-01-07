#include "HashTable.h"
#include "iostream"
#include <ostream>



HashTable::HashTable(): size(INITIAL_SIZE), curr_amount(0){
    array = new SortedList<Player>[INITIAL_SIZE];
}

HashTable::HashTable(const HashTable& hashTable): size(hashTable.size), curr_amount(hashTable.curr_amount){
    array = new SortedList<Player>[hashTable.size];
    for(int i = 0; i < size; i++){
        array[i] = hashTable.array[i];
    }
}

HashTable::~HashTable(){
    delete [] array;
}

int HashTable::hashFunc(int id){
    return id % size;
}

bool HashTable::exists(int playerID){
    if (findPlayer(playerID) != nullptr){
        return true;
    }
    return false;
}

Player* HashTable::findPlayer(int playerID){
    SortedList<Player>* curr_list = &array[hashFunc(playerID)];
    SortedList<Player>::const_iterator iter = curr_list->begin();
    SortedList<Player>::const_iterator end = curr_list->end();
    
    while(iter != end){
        if((*iter).id == playerID){
            return &(*iter);
        }
        iter++;
    }
    return &(*iter); //not found?
}

void HashTable::insert(Player& new_player){
    if(exists(new_player.id)){
        //FAILURE
    }
    
    if(curr_amount == size){
        rehash(true);
    }
    SortedList<Player>* curr_list = &array[hashFunc(new_player.id)];
    curr_list->insert(new_player);
    curr_amount++;
}
void HashTable::remove(int playerID){
    if(!exists(playerID)){
        //FAILURE
    }
    
    SortedList<Player>* curr_list = &array[hashFunc(playerID)];
    SortedList<Player>::const_iterator iter = curr_list->begin();
    SortedList<Player>::const_iterator end = curr_list->end();
    while((*iter).id != playerID){
        iter++;
    }
    curr_list->remove(iter);
    curr_amount--;
    
    if(size > INITIAL_SIZE &&  curr_amount == size/(GROW_FACTOR*GROW_FACTOR)){
        rehash(false);
    }
}

/*
*   action == true expansion
*   action == flase shrink
*/
//TODO: handle bad_alloc
void HashTable::rehash(bool action){
    int old_size = size;
    SortedList<Player> *tmp = array;
    int new_size;
    
    if(action){
        new_size = size*GROW_FACTOR;
    }
    else{
        new_size = size/GROW_FACTOR;
    }
    array = new SortedList<Player>[new_size]; //Bad_alloc?
    size = new_size;
    curr_amount = 0;
    
    
    for(int i = 0; i < old_size; i++ ){
        
        SortedList<Player>::const_iterator iter = tmp[i].begin();
        SortedList<Player>::const_iterator end = tmp[i].end();
        
        while(iter != end){
            array[hashFunc((*iter).id)].insert((*iter)); //Bad_alloc?
            curr_amount++;
            iter++;
        }
    }
    delete [] tmp;
}

void HashTable::printHash(int index){
    if (index != -1){
        std::cout << index;
    
        SortedList<Player>::const_iterator iter = array[index].begin();
        SortedList<Player>::const_iterator end = array[index].end();
    
        while(iter != end){
            std::cout << "-> " << (*iter).id;
            iter++;
        }
        std::cout << std::endl;
        return;
    }
    
    for(int i = 0; i < size; i++){
        std::cout << i;
        
        SortedList<Player>::const_iterator iter = array[i].begin();
        SortedList<Player>::const_iterator end = array[i].end();
        
        while(iter != end){
            std::cout << "-> " << (*iter).id;
            iter++;
        }
        std::cout << std::endl;
    }
}


