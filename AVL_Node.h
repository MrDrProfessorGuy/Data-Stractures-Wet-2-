

#ifndef CODE_AVL_NODE_H
#define CODE_AVL_NODE_H

#include "memory"
#include "cmath"
#include "assert.h"

class LevelTree;


template <class Key, class Data>
class AVL_Node {
public:
    friend LevelTree;
    //typedef std::shared_ptr<AVL_Node_T<T>> Node;
    typedef AVL_Node Node;
    Node* right;
    Node* left;
    Node* parent;
    int height;
    Key* key;
    Data* data;
    
    
    /// Assumption: T has copy constructor
    AVL_Node(Key& key, Data& data): right(), left(), parent(),
                                    height(0), key(nullptr), data(nullptr){
        this->key = new Key(key);
        try{
            this->data = new Data(data);
        }
        catch (std::bad_alloc& e){
            delete this->key;
            this->key = nullptr;
            this->data = nullptr;
        }
    };
    /*
    AVL_Node_T(const AVL_Node_T& node){
        data = new T(*node.data);
        right = node.right;
        left = node.left;
        parent = node.parent;
        
    }*/
    ~AVL_Node(){
        delete key;
        delete data;
        key = nullptr;
        data = nullptr;
    }

    void setData(Data& new_data){
        if (this->data == &new_data){
            return;
        }
        delete data;
        data = new Data(new_data);
    }
    void setKey(Key& new_key){
        if (this->key == &new_key){
            return;
        }
        delete key;
        data = new Key(new_key);
    }
    
    /// Assumption: Key has "operator <"
    bool operator<(const AVL_Node& node) const{
        return *key < *(node.key);
    }
    bool operator>(const AVL_Node& node) const{
        return node.operator<(*this);
    }
    bool operator==(const AVL_Node& node2){
        if (!(this->operator<(node2)) && !(node2.operator<(*this))){
            return true;
        }
        return false;
    }
    bool operator!=(const AVL_Node& node2){
        if (!(this->operator==(node2))){
            return true;
        }
        return false;
    }
    
    static void swap(AVL_Node& node_1, AVL_Node& node_2){
        Key* temp_key = node_1.key;
        Data* temp_data = node_1.data;
        
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
                height(0), key(nullptr), data(nullptr){}

};
/*
template<class Key, class T>
bool operator==(const AVL_Node_T<Key, T>& node1, const AVL_Node_T<Key, T>& node2){
    return (!(node1 < node2) && !(node2 < node1));
}
*/



#endif //CODE_AVL_NODE_H
