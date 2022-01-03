//
// Created by guy cohen on 03/01/2022.
//

#ifndef DATA_STRACTURES_WET_2_LEVELTREE_H
#define DATA_STRACTURES_WET_2_LEVELTREE_H

#include "AVL_Node.h"
#include "LevelData.h"
#include "exception"
#include "iostream"



typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3,
    NODE_EXISTS = -4,
    NODE_DONT_EXIST = -5
} Status;

    
    
class LevelTree {
    typedef AVL_Node<int, LevelData>* Node;

public:
    class Iterator;
    
    LevelTree(): head(nullptr), size(0) {};
    LevelTree(Iterator& tree1, Iterator& tree2, int combined_size): head(nullptr), size(combined_size){
        merge(tree1, tree2, combined_size);
    }
    LevelTree(const LevelTree&) = delete;
    ~LevelTree(){
        clearTree();
        head = nullptr;
    }
    
    void clearTree(){
        if(size > 0){
            clearTreeAux(head);
        }
        size = 0;
        head = nullptr;
    }
    
    Status merge(Iterator& tree1, Iterator& tree2, int combined_size){
        try{
            size = combined_size;
            if (combined_size > 0){
                int tree_height = (int)log2(combined_size);
                head = new AVL_Node<int, LevelData>();
                head->height = tree_height;
                int nodes_left = combined_size-1;
                
                FullTree(head, nodes_left, tree_height);
                halfFullTree(head, nodes_left, tree_height);
                mergeAux(tree1, tree2, head);
            }
            
        }
        catch (std::bad_alloc& e){
            clearTree();
            throw e;
        }
        
        return SUCCESS;
    }
    
    void balance_merge(Node root){
        if (root->right != nullptr){
            balance_merge(root->right);
        }
        balanceTree(root);
        if (root->left != nullptr){
            balance_merge(root->left);
        }
    }
    
    void print(){
        printTree(head);
    }
    
    void printTree(Node root){
        if (root == nullptr){
            return;
        }
        if (root->left != nullptr){
            printTree(root->left);
        }
        int parent_id = -1;
        int left_id = -1;
        int right_id = -1;
        
        std::cout << "============ player " << *(root->key) << "============" << std::endl;
        if (root->parent != nullptr){
            parent_id = *(root->parent->key);
        }
        if (root->right != nullptr){
            right_id = *(root->right->key);
        }
        if (root->left != nullptr){
            left_id = *(root->left->key);
        }
        std::cout << "parent: " << parent_id << std::endl;
        std::cout << "left: " << left_id << std::endl;
        std::cout << "right: " << right_id << std::endl;
        std::cout << std::endl;
        
        
        if (root->right != nullptr){
            printTree(root->right);
        }
    }
    
    int getSize(){
        return size;
    }
    Iterator root(){
        return Iterator(head);
    }
    Iterator firstInOrder(Node node = nullptr){
        if (node == nullptr){
            node = head;
        }
        return Iterator(smallest(node));
    }
    Iterator lastInOrder(Node node = nullptr){
        if(node == nullptr){
            node = head;
        }
        return Iterator(highest(node));
    }
    //O(Log(size))
    LevelData* findOld(const int key) const{
        if (head == nullptr){
            return nullptr;
        }
        Node iter = this->head;
        while(iter != nullptr && *(iter->key) != key)
        {
            if(*(iter->key) < key){
                iter = iter->right;
            }
            else{
                iter = iter->left;
            }
        }
        if (iter == nullptr){
            return nullptr;
        }
        return iter->data;
    }
    
    
    LevelData* find(const int key, bool ReturnNULL = true) const{
        if (head == nullptr){
            return nullptr;
        }
        Node iter = this->head;
        Node last_right = nullptr;
        while(iter != nullptr && *(iter->key) != key)
        {
            if(key < *(iter->key)){
                iter = iter->left;
            }
            else{
                last_right = iter;
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right->data;
            }
            return nullptr;
        }
        return iter->data;
    }
    LevelData getRank(const int key, LevelData initial_rank, bool ReturnNULL = true) const{
        if (head == nullptr){
            return initial_rank;
        }
        
        Node iter = this->head;
        LevelData rank(initial_rank);
        LevelData last_right_rank(rank);
        while(iter != nullptr && *(iter->key) != key){
            if(key < *(iter->key)){
                rank += *(iter->data);
                if (iter->right != nullptr){
                    rank -= *(iter->right->data);
                }
                iter = iter->left;
            }
            else{
                last_right_rank = rank;
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right_rank;
            }
            return initial_rank;
        }
        return rank;
    }

    LevelData getLevelDataRank(const int key, LevelData initial_rank, int dataFunc(LevelData&), bool ReturnNULL = true) const{
        if (head == nullptr){
            return initial_rank;
        }
        LevelData rank(initial_rank);
        LevelData last_right_rank(rank);
        Node iter = this->head;
        while(iter != nullptr && dataFunc(*(iter)->data) != key){
            if(key < dataFunc(*(iter)->data)){
                rank += dataFunc(*(iter)->data);
                if (iter->right != nullptr){
                    rank -= dataFunc(*(iter->right)->data);
                }
                iter = iter->left;
            }
            else{
                last_right_rank = rank;
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right_rank;
            }
            return initial_rank;
        }
        return rank;
    }
    bool exists(const int& key) const{
        if (find(key) == nullptr){
            return false;
        }
        return true;
    }
    
    //O(Log(size))
    LevelData* insert(int key, LevelData data){ // update trees' info
        Status status = FAILURE;
        Node new_node = new AVL_Node<int,LevelData>(key, data);
        Node node = nullptr;
        
        if (size > 0){
            node = insertNodeAux(this->head, new_node, status);
            if (node != new_node){
                delete new_node;
                new_node = node;
            }
        }
        else{
            head = new_node;
            status = SUCCESS;
        }
        
        if (status == SUCCESS){
            size++;
        }
        return new_node->data;
    }
    Status removeNode(int key){
        //not_finished + update trees' info
        Status status = FAILURE;
        if (size == 1 && key == *(head->key)){
            delete head;
            head = nullptr;
            status = SUCCESS;
        }
        else{
            removeNodeAux(this->head, key, status);
        }
        
        if (status == SUCCESS){
            size--;
        }
        return status;
    }
    static Node highest(Node root){
        if(root == nullptr){
            return nullptr;
        }
        while(root->right != nullptr)
        {
            root = root->right;
        }
        return root;
    }
    static Node smallest(Node root){
        if (root == nullptr){
            return nullptr;
        }
        while (root->left != nullptr)
        {
            root = root->left;
        }
        return root;
    }

    static Node nextInOrder(Node root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (root->right != nullptr) {
            return smallest(root->right);
        }
        else {
            Node tmp_root = root->parent;
            Node prev_root = root;
            
            while (tmp_root != nullptr) {
                if (tmp_root->left == prev_root) {
                    return tmp_root;
                }
                prev_root = tmp_root;
                tmp_root = tmp_root->parent;
            }
            return nullptr;
        }
    }
    static Node reverseNextInOrder(Node root){
        if(root == nullptr) {
            return nullptr;
        }
        if(root->left != nullptr) {
            return highest(root->left);
        }
        else{
            Node tmp_root = root->parent;
            Node prev_root = root;
            while(tmp_root != nullptr){
                if(tmp_root->right == prev_root){
                    return tmp_root;
                }
                prev_root = tmp_root;
                tmp_root = tmp_root->parent;
            }
            return nullptr;
        }
    }
    
    class Iterator{
        
        Node root;
    public:
        friend Iterator& sum(Iterator& iter1, Iterator& iter2);
        explicit Iterator(Node node):root(node){}
        Iterator(const Iterator&) = default;
        ~Iterator() = default;
        
        LevelData* operator*(){
            if (root == nullptr){
                return nullptr;
            }
            return (root->data);
        }
        Iterator& operator++(){
            root = nextInOrder(root);
            return *(this);
        }
        Iterator operator++(int){
            Iterator tmp_iter(root);
            ++(*this);
            return tmp_iter;
        }
        Iterator& operator--(){
            root = reverseNextInOrder(root);
            return *(this);
        }
        Iterator operator--(int){
            Iterator tmp_iter(root);
            --(*this);
            return tmp_iter;
        }
        Iterator& operator=(const Iterator& iter) = default;

        int* getKey() const{
            if (root == nullptr){
                return nullptr;
            }
            return root->key;
        }
        
        bool operator<(const Iterator& iterator) const{
            if (root != nullptr){
                if (iterator.root != nullptr){
                    return *getKey() < *(iterator.getKey());
                }
                return true;
            }
            else{
                return false;
            }
        }
        bool operator>(const Iterator& iterator) const{
            return iterator.operator<(*this);
        }
        bool operator==(const Iterator& iterator) const{
            if (!(this->operator<(iterator)) && !(iterator.operator<(*this))){
                return true;
            }
            return false;
        }
        bool operator!=(const Iterator& iterator) const{
            if (!(this->operator==(iterator))){
                return true;
            }
            return false;
        }
    };

private:
    Node head;
    int size;
    
    void clearTreeAux(Node root){
        if (root != nullptr){
            clearTreeAux(root->left);
            clearTreeAux(root->right);
        }
        delete root;
        root = nullptr;
    }
    
    Iterator& sum(Iterator& iter1, Iterator& iter2){
    
    }
    
    Iterator nextInMerge(Iterator& iter1, Iterator& iter2){
        if (*iter1 != nullptr){
            if (*iter2 != nullptr){
                if (iter1 < iter2){
                    return iter1++;
                }
                return iter2++;
            }
            return iter1++;
        }
        return iter2++;
    }
    LevelData nextInRankMerge(Iterator& iter1, Iterator& iter2){
        LevelData data(0);
        if (*iter1 != nullptr){
            if (*iter2 != nullptr){
                if (iter1 < iter2){
                    data = (*(*iter1));
                    iter1++;
                    return data;
                }
                else if (iter1 == iter2){
                    data = (*(*iter1)) + (*(*iter2));
                    iter1++;
                    iter2++;
                    return data;
                }
                data = (*(*iter2));
                iter2++;
                return data;
            }
            data = (*(*iter1));
            iter1++;
            return data;
        }
        data = (*(*iter2));
        iter2++;
        return data;
    }
    void mergeRankAux(Iterator& tree1, Iterator& tree2, Node current_node){
        if (current_node->left != nullptr){
            mergeAux(tree1, tree2, current_node->left);
        }
        LevelData current_data = nextInRankMerge(tree1, tree2);
        int level = current_data.getLevel();
        current_node->setKey(level);
        current_node->setData(current_data);
        
        if (current_node->right != nullptr){
            mergeAux(tree1, tree2, current_node->right);
        }
        
    }
    
    void mergeAux(Iterator& tree1, Iterator& tree2, Node current_node){
        if (current_node->left != nullptr){
            mergeAux(tree1, tree2, current_node->left);
        }
        Iterator current_data = nextInMerge(tree1, tree2);
        current_node->key = new int(*current_data.getKey());
        current_node->data = new LevelData(*(*current_data));
        
        if (current_node->right != nullptr){
            mergeAux(tree1, tree2, current_node->right);
        }
        
    }
    
    void halfFullTree(Node current_node, int& nodes_left, int current_height){
        if (current_node->right != nullptr){
            halfFullTree(current_node->right, nodes_left, current_height-1);
        }
        if (current_node->left != nullptr){
            halfFullTree(current_node->left, nodes_left, current_height-1);
        }
        if (current_height == 0 && nodes_left < 0){
            if (current_node->parent->left == current_node){
                current_node->parent->left = nullptr;
            }
            else{
                current_node->parent->right = nullptr;
            }
            delete current_node;
            nodes_left++;
        }
    }
    
    void FullTree(Node current_node, int& nodes_left, int current_height){
        if (0 < current_height){
            Node left_node = new AVL_Node<int, LevelData>();
            left_node->height = current_height - 1;
            current_node->left = left_node;
            left_node->parent = current_node;
            FullTree(left_node, --nodes_left, current_height - 1);
        }
        
        if (0 < current_height){
            Node right_node = new AVL_Node<int, LevelData>();
            right_node->height = current_height - 1;
            current_node->right = right_node;
            right_node->parent = current_node;
            FullTree(right_node, --nodes_left, current_height - 1);
        }
        
        
    }
    
    // O(Log(size))
    Node insertNodeAux(Node root, Node new_node, Status& status){
        Node node = nullptr;
        if(*new_node < *root){
            if (root->left == nullptr){
                root->setLeft(new_node);
                status = SUCCESS;
                node = new_node;
            }
            else{
                node = insertNodeAux(root->left, new_node, status);
            }
        }
        else if (*new_node > *root){
            if (root->right == nullptr){
                root->setRight(new_node);
                status = SUCCESS;
                node =  new_node;
            }
            else{
                node = insertNodeAux(root->right, new_node, status);
            }
        }
        else{
            status = NODE_EXISTS;
            node = root;
        }
        
        if (status == SUCCESS){
            root->updateHeight();
            balanceTree(root);
        }
        return node;
    }
    
    void removeNodeAux(Node root, int key, Status & status){
        if (root == nullptr)
        {
            status = NODE_DONT_EXIST;
            return;
        }
        if(key < *(root->key)){
            removeNodeAux(root->left, key, status);
        }
        else if (*(root->key) < key){
            removeNodeAux(root->right, key, status);
        }
        else{
            remove_tree_node(root);
            //root = nullptr;
            status = SUCCESS;
            //return;
        }
        
        if (status == SUCCESS && root != nullptr){
            root->updateHeight();
            balanceTree(root);
        }
    }    //Node find(Node root ,Node node);
    void remove_tree_node(Node& root){
        // if root has 2 sub trees
        if(root->left != nullptr && root->right != nullptr) {
            Node next_order = smallest(root->right);
            
            AVL_Node<int, LevelData>::swap(*root, *next_order);
            if (next_order->right != nullptr) {
                AVL_Node<int, LevelData>::swap(*(next_order->right), *next_order);
                delete (next_order->right);
                next_order->right = nullptr;
            }
            else{
                if (next_order->parent->left == next_order){
                    next_order->parent->left = nullptr;
                }
                else{
                    next_order->parent->right = nullptr;
                }
                delete next_order;
                
            }
        }
        else{ // root has one sub-tree
            if (root->left != nullptr){
                AVL_Node<int, LevelData>::swap(*root, *(root->left));
                delete (root->left);
                root->left = nullptr;
            }
            else if (root->right != nullptr){
                AVL_Node<int, LevelData>::swap(*root, *(root->right));
                delete (root->right);
                root->right = nullptr;
            }
            else { //leaf
                if (root->parent != nullptr){
                    if (root->parent->right == root){
                        root->parent->right = nullptr;
                    }
                    else{
                        root->parent->left = nullptr;
                    }
                }
                if (root == head){
                    delete root;
                    root = nullptr;
                    head = nullptr;
                }
                else{
                    delete root;
                    root = nullptr;
                }
            }
        }// else // root has one sub-tree
    }
    
    void balanceTree(Node root) {
        int curr_balance = root->getBalance();
        if (curr_balance == -2) {
            if (root->right->getBalance() <= 0) {
                RR(root);
                return;
            }
            else {
                RL(root);
                return;
            }
        }
        else {
            if (curr_balance == 2) {
                if (root->left->getBalance() >= 0) {
                    LL(root);
                    return;
                }
                else {
                    LR(root);
                    return;
                }
            }
        }
    }
    
    //B = root, B_left = A
    void LL(Node B){
        Node parent = B->parent;
        
        Node A = B->left;
        
        B->left = A->right;
        if(A->right != nullptr) {
            A->right->parent = B;
        }
        
        A->right = B;
        B->parent = A;
        
        if(parent != nullptr){
            if (parent->left == B) {
                parent->left = A;
            }
            else {
                parent->right = A;
            }
        }
        else{
            head = A;
        }
        A->parent = parent;
        
        B->updateHeight();
        A->updateHeight();
        
    }
    void LR(Node C){
        RR(C->left);
        LL(C);
    }
    void RL(Node C){
        LL(C->right);
        RR(C);
    }
    void RR(Node B){
        Node parent = B->parent;
        Node A = B->right;
        
        B->right = A->left;
        if(A->left != nullptr){
            A->left->parent = B;
        }
        
        A->left = B;
        B->parent = A;
        
        if(parent != nullptr){
            if (parent->left == B){
                parent->left = A;
            }
            else{
                parent->right = A;
            }
        }
        else{
            head = A;
        }
        A->parent = parent;
        
        B->updateHeight();
        A->updateHeight();
    }
};



#endif //DATA_STRACTURES_WET_2_LEVELTREE_H
