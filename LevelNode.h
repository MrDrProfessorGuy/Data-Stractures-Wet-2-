//
// Created by guy cohen on 03/01/2022.
//

#ifndef DATA_STRACTURES_WET_2_LEVELNODE_H
#define DATA_STRACTURES_WET_2_LEVELNODE_H

#include "memory"
#include "cmath"
#include "assert.h"
#include "LevelData.h"

namespace Tree{
    class LevelTree;
}


class AVL_Node {
public:
    friend Tree::LevelTree;
    typedef AVL_Node Node;
    Node* right;
    Node* left;
    Node* parent;
    int height;
    int key;
    LevelData data;
    
    
    /// Assumption: T has copy constructor
    AVL_Node(int& key, LevelData& data): right(), left(), parent(),
                                           height(0), key(key), data(data){
    };
    ~AVL_Node(){
    }
    /// Assumption: Key has "operator <"
    bool operator<(const AVL_Node& node) const{
        return key < (node.key);
    }
    bool operator>(const AVL_Node& node) const{
        return node.operator<(*this);
    }
    bool operator==(const AVL_Node& node2) const{
        if (!(this->operator<(node2)) && !(node2.operator<(*this))){
            return true;
        }
        return false;
    }
    bool operator!=(const AVL_Node& node2) const{
        if (!(this->operator==(node2))){
            return true;
        }
        return false;
    }
    
    static void swap(AVL_Node& node_1, AVL_Node& node_2){
        int temp_key = node_1.key;
        LevelData temp_data = node_1.data;
        
        node_1.key = node_2.key;
        node_1.data = node_2.data;
        
        node_2.key = temp_key;
        node_2.data = temp_data;
    }
    
    void setRight(Node* right_node){
        assert(this != right_node);
        
        right = right_node;
        if (right_node != nullptr){
            right_node->parent = this;
        }
    }
    void setLeft(Node* left_node){
        assert(this != left_node);
        
        left = left_node;
        if (left_node != nullptr){
            left_node->parent = this;
        }
    }
    
    static int getHeight(const Node* node){
        if (node == nullptr){
            return -1;
        }
        return node->height;
    }
    void updateHeight(){
        int max = getHeight(left);
        
        if (getHeight(right) > max){
            max = getHeight(right);
        }
        height = 1 + max;
    }
    int getBalance(){
        return getHeight(left) - getHeight(right);
    }
    
    void reset(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }


private:
    AVL_Node(): right(), left(), parent(),
                  height(0), key(0), data(0){}
    
};





#endif //DATA_STRACTURES_WET_2_LEVELNODE_H
