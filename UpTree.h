//
// Created by guy cohen on 03/01/2022.
//

#ifndef DATA_STRACTURES_WET_2_UPTREE_H
#define DATA_STRACTURES_WET_2_UPTREE_H

#include "AVL_Node.h"
#include "Group.h"


class UpTree {
public:
    UpTree();
    UpTree(const UpTree&);
    ~UpTree();
    
    AVL_Node<int, Group> head;
    
    
    
};


#endif //DATA_STRACTURES_WET_2_UPTREE_H
