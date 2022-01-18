#ifndef DATA_STRACTURES_WET_2_LEVELTREE_H
#define DATA_STRACTURES_WET_2_LEVELTREE_H

#include "AVL_Node.h"
#include "LevelData.h"
#include "exception"
#include "library2.h"

    
    
class LevelTree {
    typedef AVL_Node<int, LevelData>* Node;

public:
    class Iterator;
    
    LevelTree(): head(nullptr), size(0) {};
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
    
    int getSize(){
        return size;
    }
    Iterator root(){
        return Iterator(head);
    }
    
    Iterator firstInOrder(Node node = nullptr) const{
        if (node == nullptr){
            node = head;
        }
        return Iterator(smallest(node));
    }
    Iterator lastInOrder(Node node = nullptr) const{
        if(node == nullptr){
            node = head;
        }
        return Iterator(highest(node));
    }
    //Exact Level data;
    LevelData ExactLevelData(Node node) const{
        if (node == nullptr){
            return LevelData(INVALID_LEVEL);
        }
        LevelData data = *(node->data);
        if (node->right != nullptr){
            data -= *(node->right->data);
        }
        if (node->left != nullptr){
            data -= *(node->left->data);
        }
        return data;
    }
    
    LevelData NodeRightRank(Node node) const{
        if (node == nullptr){
            return LevelData(0);
        }
        LevelData data = LevelData(*(node->key));
        if (node->right != nullptr){
            data = data + *(node->right->data);
        }
        return data;
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
            if (ReturnNULL == false && last_right != nullptr){
                return last_right->data;
            }
            return nullptr;
        }
        return iter->data;
    }
    Iterator findIter(const int key, bool ReturnNULL = true){
        if (head == nullptr){
            return firstInOrder();
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
                return Iterator(last_right);
            }
            return firstInOrder();
        }
        return Iterator(iter);
    }
    LevelData getRank(const int key, bool ReturnNULL = false) const{
        LevelData* data = find(key, false);
        if (ReturnNULL){
            data = find(key, true);
        }
        
        if (data == nullptr){
            return LevelData(INVALID_LEVEL);
        }
        return getRank3(data->getLevel());
    }
    LevelData getRank3(const int key, bool ReturnNULL = false) const{
        if (head == nullptr){
            return LevelData(key);
        }
        Node iter = this->head;
        LevelData rank(*(iter->data));
        
        while(iter != nullptr && *(iter->key) != key){
            if(*(iter->key) < key){
                iter = iter->right;
            }
            else{
                rank.setLevel(*(iter->key));
                rank = rank - NodeRightRank(iter) - ExactLevelData(iter);
                iter = iter->left;
                
            }
        }
        
        if (iter == nullptr){
            return LevelData(key);
        }
        rank = rank - NodeRightRank(iter);
        rank.setLevel(*(iter->key));
        return (rank);
    }
    LevelData getLevelDataRank(const int key, int dataFunc(LevelData&), bool ReturnNULL = true) const{
        if (head == nullptr){
            return LevelData(INVALID_LEVEL);
        }
        Node iter = this->head;
        //Node last_right = nullptr;
        LevelData rank = *(iter->data) - NodeRightRank(iter);
        LevelData last_right_rank(INVALID_LEVEL);
        
        while(iter != nullptr && dataFunc(rank) != key){
            if(key < dataFunc(rank)){
                rank = rank - ExactLevelData(iter);
                if (iter->left != nullptr){
                    rank = rank - NodeRightRank(iter->left);
                    rank.setLevel(*(iter->left->key));
                }
                iter = iter->left;
            }
            else{
                //last_right = iter;
                last_right_rank = rank;
                last_right_rank.setLevel(*(iter->key));
                
                if (iter->right != nullptr){
                    rank = rank + *(iter->right->data) - NodeRightRank(iter->right);
                    rank.setLevel(*(iter->right->key));
                }
                iter = iter->right;
            }
        }
    
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right_rank;
            }
            return LevelData(INVALID_LEVEL);
        }
        rank.setLevel(*(iter->key));
        return rank;
    }
    
    bool exists(const int& key) const{
        if (find(key) == nullptr){
            return false;
        }
        return true;
    }
    
    LevelData* insertPlayer(Player player){
        LevelData data(player);
        return insert(player.level, data);
    }
    //O(Log(size))
    LevelData* insert(int key, LevelData data){ // update trees' info
        StatusType status = FAILURE;
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
    
    StatusType removePlayer(Player player){
        LevelData playerData(player);
        StatusType status = FAILURE;
        if (!exists(player.level)){
            return SUCCESS;
        }
        
        removeNodeAux(this->head, playerData.getLevel(), playerData, status);
        //removeNode(player.level);
        if (status == SUCCESS){
            size--;
        }
        //checkTreeForm();
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
    // O(Log(size))
    Node insertNodeAux(Node root, Node new_node, StatusType & status){
        Node node = nullptr;
        (*root->data) += *(new_node->data);
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
            status = INVALID_INPUT;
            node = root;
        }
        
        if (status == SUCCESS){
            root->updateHeight();
            balanceTree(root);
        }
        return node;
    }
    
    void removeNodeAux(Node root, int key, LevelData data, StatusType& status){
        if (root == nullptr){
            status = FAILURE;
            return;
        }
        (*root->data) -= data;
        if(key < *(root->key)){
            removeNodeAux(root->left, key, data, status);
        }
        else if (*(root->key) < key){
            removeNodeAux(root->right, key, data, status);
        }
        else{
            if (ExactLevelData(root).getSubPlayers() == 0){
                remove_tree_node(&root);
                root = nullptr;
                status = SUCCESS;
            }
        }
        
        if (status == SUCCESS && root != nullptr){
            root->updateHeight();
            balanceTree(root);
        }
    }    //Node find(Node root ,Node node);
    
    void swapNodeData(Node node1, Node node2){
        if (node1 == nullptr || node2 == nullptr){
            return;
        }
        int node1_level = (*node1->key);
        int node2_level = *(node2->key);
        LevelData node1Exact = ExactLevelData(node1);
        LevelData node2Exact = ExactLevelData(node2);
    
        node1->setKey(node2_level);
        (node1->data)->setLevel((*node2->data).getLevel());
        //*(node1->data) += node2Exact; ///Node1Exact SHOULD be 0!
    
        node2->setKey(node1_level);
        //*(node2->data) += node1Exact - node2Exact;
        (node2->data)->setLevel(node1_level);
        
    }
    void remove_tree_node(Node* root){
        // if root has 2 sub trees
        if((*root)->left != nullptr && (*root)->right != nullptr) {
            Node next_order = smallest((*root)->right);
            LevelTree::swapNodeData((*root), next_order);
            StatusType status;
            removeNodeAux((*root)->right, *(next_order->key), ExactLevelData(next_order), status);
            (*root)->updateHeight();
            balanceTree(*root);
            //remove_tree_node(&next_order);
        }
        else{ // root has one sub-tree
            if ((*root)->left != nullptr){
                LevelTree::swapNodeData((*root), (*root)->left);
                delete ((*root)->left);
                (*root)->left = nullptr;
                (*root)->updateHeight();
            }
            else if ((*root)->right != nullptr){
                LevelTree::swapNodeData((*root), (*root)->right);
                delete ((*root)->right);
                (*root)->right = nullptr;
                (*root)->updateHeight();
            }
            else { //leaf
                if ((*root)->parent != nullptr){
                    if ((*root)->parent->right == (*root)){
                        (*root)->parent->right = nullptr;
                    }
                    else{
                        (*root)->parent->left = nullptr;
                    }
                }
                if ((*root) == head){
                    delete (*root);
                    (*root) = nullptr;
                    head = nullptr;
                }
                else{
                    delete (*root);
                    (*root) = nullptr;
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
    
        LevelData tmp = *(B->data);
        *(B->data) = *(B->data) - *(A->data);
        LevelData::swapSubTreeData(*(A->data), tmp);
        
        B->left = A->right;
        if(A->right != nullptr) {
            *(B->data) = *(B->data) + *((A->right)->data);
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
        
        LevelData tmp = *(B->data);
        *(B->data) = *(B->data) - *(A->data);
        LevelData::swapSubTreeData(*(A->data), tmp);
        
        B->right = A->left;
        if(A->left != nullptr){
           *(B->data) = *(B->data) + *((A->left)->data);
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
