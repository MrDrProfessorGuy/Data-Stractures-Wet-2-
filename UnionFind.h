//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_UNIONFIND_H
#define DATA_STRACTURES_WET_2_UNIONFIND_H



#include "UpTree.h"
#include "Group.h"


class UnionFind {

private:
public:
    int size;
    UpTree* set;
    
    UnionFind(int size);
    UnionFind(const UnionFind&) = delete;
    ~UnionFind();

    Group& find(int group_id);
    void unite(int group1, int group2);
    
    

};


#endif //DATA_STRACTURES_WET_2_UNIONFIND_H
