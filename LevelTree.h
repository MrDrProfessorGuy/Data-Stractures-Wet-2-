//
// Created by guy cohen on 03/01/2022.
//

#ifndef DATA_STRACTURES_WET_2_LEVELTREE_H
#define DATA_STRACTURES_WET_2_LEVELTREE_H

#include "AVL_Node.h"
#include "LevelData.h"
#include "exception"
#include "iostream"
#include "library2.h"

    
    
class LevelTree {
    typedef AVL_Node<int, LevelData>* Node;

public:
    class Iterator;
    
    LevelTree(): head(nullptr), size(0) {};
    /*
    LevelTree(Iterator& tree1, Iterator& tree2, int combined_size): head(nullptr), size(combined_size){
        merge(tree1, tree2, combined_size);
    }
     */
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
    
    void checkInOrder(){
        int count = 0;
        checkInOrderAux(head, count);
        assert(count == size);
    }
    void checkInOrderAux(Node node, int& count){
        if (node == nullptr){
            return;
        }
        checkInOrderAux(node->left, count);
        count++;
        assert(*(node->key) == count);
        checkInOrderAux(node->right, count);
    }
    /*
    StatusType merge(Iterator& tree1, Iterator& tree2, int combined_size){
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
    */
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
    LevelData getExactLevelData(int level) const{
        Node node = findNode(level);
        if (node == nullptr){
            return LevelData(0);
        }
        LevelData data = *(node)->data;
        if (node->right != nullptr){
            data -= *(node->right->data);
        }
        if (node->left != nullptr){
            data -= *(node->left->data);
        }
        return data;
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
    LevelData getRank2(const int key, bool ReturnNULL = false) const{
        if (head == nullptr){
            return LevelData(key);
        }
        bool turned_left = false;
        bool turned_right = false;
        Node iter = this->head;
        LevelData rank(*(iter->data));
        LevelData rankSup = rank;
        rankSup.setLevel((*firstInOrder(head))->getLevel());
        
        while(iter != nullptr && *(iter->key) != key){
            if(key < *(iter->key)){
                rank.setLevel(*(iter->key));
                rank = rank - NodeRightRank(iter) - ExactLevelData(iter);
                iter = iter->left;
            }
            else{
                if (rankSup.getLevel() < rank.getLevel()){
                    rankSup = rank - NodeRightRank(iter);
                    rankSup.setLevel(*(iter->key));
                }
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return rankSup;
            }
            return LevelData(key);
        }
        rank = rank - NodeRightRank(iter);
        rank.setLevel(*(iter->key));
        return (rank);
    }
    LevelData getRankOLD(const int key, bool ReturnNULL = true) const{
        if (head == nullptr){
            return LevelData(key);
        }
        bool turned_left = false;
        Node iter = this->head;
        LevelData rank(key);
        rank = LevelData(*iter->data);
        LevelData last_right_rank = rank;
        //last_right_rank -= FuckTrees2(iter);
        
        while(iter != nullptr && *(iter->key) != key){
            if(key < *(iter->key)){
                rank -= ExactLevelData(iter) - NodeRightRank(iter);
                rank.setLevel(iter->data->getLevel());
                iter = iter->left;
                turned_left = true;
            }
            else{
                if (!turned_left){
                    last_right_rank = rank;
                    last_right_rank -= NodeRightRank(iter);
                    last_right_rank.setLevel(iter->data->getLevel());
                }
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right_rank;
            }
            return LevelData(key);
        }

        rank = rank - NodeRightRank(iter);
        rank.setLevel(iter->data->getLevel());
        return (rank);
    }
    LevelData getLevelDataRank(const int key, int dataFunc(LevelData&), bool ReturnNULL = true) const{
        if (head == nullptr){
            return LevelData(INVALID_LEVEL);
        }
        Node iter = this->head;
        Node last_right = nullptr;
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
                last_right = iter;
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

    LevelData getLevelDataRank3(const int key, int dataFunc(LevelData&), bool ReturnNULL = true) const{
        if (head == nullptr){
            return LevelData(key);
        }
        Node iter = this->head;
        LevelData rank = getRank(*(iter->key));
        //rank = LevelData(*iter->data);
        LevelData last_right_rank(INVALID_LEVEL);
        
        
        while(iter != nullptr && dataFunc(rank) != key){
            if(key < dataFunc(rank)){
                if (iter->right != nullptr){
                    rank -= (*(iter->right)->data);
                }
                rank -= ExactLevelData(iter);
                rank.setLevel(iter->data->getLevel());
                iter = iter->left;
            }
            else{
                last_right_rank = rank;
                last_right_rank -= NodeRightRank(iter);
                last_right_rank.setLevel(iter->data->getLevel());
                iter = iter->right;
            }
        }
        
        if (iter == nullptr){
            if (ReturnNULL == false){
                return last_right_rank;
            }
            return LevelData(key);
        }
        if (iter != head){
            rank = rank - NodeRightRank(iter);
        }
        rank.setLevel(iter->data->getLevel());
        return (rank);
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
        return status;
    }
    StatusType removeNode(int key){
        //not_finished + update trees' info
        StatusType status = FAILURE;
        if (size == 1 && key == *(head->key)){
            delete head;
            head = nullptr;
            status = SUCCESS;
        }
        else{
            LevelData* data = find(key);
            if (data == nullptr){
                return SUCCESS;
            }
            removeNodeAux(this->head, key, *data, status);
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
    Node findNode(const int key, bool ReturnNULL = true) const{
        if (head == nullptr){
            return smallest(head);
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
                return (last_right);
            }
            return smallest(head);
        }
        return (iter);
    }
    /*
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
    void mergeAux(Iterator& tree1, Iterator& tree2, Node current_node){
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
    
    void mergeAuxOLD(Iterator& tree1, Iterator& tree2, Node current_node){
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
    */
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
    
    void removeNodeAux(Node root, int key, LevelData data, StatusType & status){
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
            //remove_tree_node(&next_order);
        }
        else{ // root has one sub-tree
            if ((*root)->left != nullptr){
                LevelTree::swapNodeData((*root), (*root)->left);
                delete ((*root)->left);
                (*root)->left = nullptr;
            }
            else if ((*root)->right != nullptr){
                LevelTree::swapNodeData((*root), (*root)->right);
                delete ((*root)->right);
                (*root)->right = nullptr;
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
    void remove_tree_node2(Node& root){
        // if root has 2 sub trees
        if(root->left != nullptr && root->right != nullptr) {
            Node next_order = smallest(root->right);
            LevelTree::swapNodeData(root, next_order);
            if (next_order->right != nullptr) {
                LevelTree::swapNodeData(next_order->right, next_order);
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
                LevelTree::swapNodeData(root, root->left);
                delete (root->left);
                root->left = nullptr;
            }
            else if (root->right != nullptr){
                LevelTree::swapNodeData(root, root->right);
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
