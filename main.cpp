

#include "LevelTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>



class TreeTest {

public:
    LevelTree tree;
    
    void insert(int a, int b){
        tree.insert(a, b);
    }
    void remove(int a){
        tree.removeNode(a);
    }
    
    
    void add(const int* data, int size) {
    
        for (int index = 0; index < size; index++) {
            insert(index, data[index]);
        }
    
    }
    
    bool shouldExist(const int* data, bool* data_checked, int size, int tree_data){
        for (int index = 0; index < size; index++) {
            if (data_checked[index] == false && data[index] == tree_data){
                data_checked[index] = true;
                return true;
            }
        }
        return false;
    }
    
    void check_tree(const int* data, int size){
        
        LevelTree::Iterator iter = tree.firstInOrder();
        int index = 0;
        while (*iter != nullptr){
            if (*(*iter) != index){
                std::cout << "iter = " << (*(*iter)) << " |||  index = " << index << std::endl;
            }
            iter++;
            index++;
        }
    }
    
    
    
    
};

Tree::LevelTree<int, int> tree;



void removeNum(int num){
    for(int i = 0; i < num; i++) {
        tree.removeNode(i);
    }
}

void print() {
    Tree::LevelTree<int, int>::Iterator iter = tree.firstInOrder();
    int index = 0;
    while (*iter != nullptr){
        if (*(*iter) != index){
            std::cout << (*(*iter)) <<  std::endl;
        }
        iter++;
        index++;
    }
}
void test1(){
    for(int i = 0; i < 500; i++) {
        tree.insert(i,i);
    }
    removeNum(499);
    print();
}

int main(){

    


}








int bob(){
    
    
    //Specific Cases
    
    /*correct output for the four next cases
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0 */
    
    //basic LL root change
    insert(3, 3);
    insert(2, 2);
    insert(1, 1);
    tree.print();
    tree.clearTree();
    
    //basic LR root change
    insert(3, 3);
    insert(1, 1);
    insert(2, 2);
    tree.print();
    tree.clearTree();
    
    //basic RR root change
    insert(1, 1);
    insert(2, 2);
    insert(3, 3);
    tree.print();
    tree.clearTree();
    
    //basic RL root change
    insert(1, 1);
    insert(3, 3);
    insert(2, 2);
    tree.print();
    tree.clearTree();
    
    //basic LR not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    insert(6, 6);
    insert(4, 4);
    insert(8, 8);
    insert(3, 3);
    insert(5, 5);
    insert(7, 7);
    insert(1, 1);
    insert(2, 2);
    tree.print();
    tree.clearTree();
    
    //basic LL not root change
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    6 BF: 1 Height: 3
    7 BF: 0 Height: 0
    8 BF: 1 Height: 1 */
    insert(6, 6);
    insert(4, 4);
    insert(8, 8);
    insert(3, 3);
    insert(5, 5);
    insert(7, 7);
    insert(2, 2);
    insert(1, 1);
    tree.print();
    tree.clearTree();
    
    //basic RR not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    insert(5, 5);
    insert(7, 7);
    insert(1, 1);
    insert(2, 2);
    insert(3, 3);
    tree.print();
    tree.clearTree();
    
    //basic RL not root change
    /*correct output
     * 1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    5 BF: 1 Height: 2
    7 BF: 0 Height: 0*/
    insert(5, 5);
    insert(7, 7);
    insert(1, 1);
    insert(3, 3);
    insert(2, 2);
    tree.print();
    tree.clearTree();
    
    //root deletion no roll successor is a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 1 Height: 2
    6 BF: 0 Height: 0*/
    insert(4, 4);
    insert(5, 5);
    insert(3, 3);
    insert(2, 2);
    insert(6, 6);
    remove(4);
    tree.print();
    tree.clearTree();
    
    //root deletion no roll successor is not a neighbour
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0 */
    insert(4, 4);
    insert(3, 3);
    insert(7, 7);
    insert(2, 2);
    insert(5, 5);
    insert(8, 8);
    insert(6, 6);
    remove(4);
    tree.print();
    tree.clearTree();
    
    //node deletion no roll successor is a neighbour case7
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    4 BF: 1 Height: 2
    5 BF: 0 Height: 0
    7 BF: 1 Height: 3
    8 BF: -1 Height: 1
    9 BF: 0 Height: 0*/
    insert(7, 7);
    insert(3, 3);
    insert(8, 8);
    insert(2, 2);
    insert(4, 4);
    insert(9, 9);
    insert(5, 5);
    insert(1, 1);
    remove(3);
    tree.print();
    tree.clearTree();
    
    //node deletion no roll successor is not a neighbour case8
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    5 BF: 0 Height: 2
    6 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 3
    10 BF: 0 Height: 0
    12 BF: -1 Height: 2
    13 BF: -1 Height: 1
    14 BF: 0 Height: 0*/
    insert(9, 9);
    insert(3, 3);
    insert(12, 12);
    insert(2, 2);
    insert(7, 7);
    insert(10, 10);
    insert(13, 13);
    insert(1, 1);
    insert(5, 5);
    insert(8, 8);
    insert(14, 14);
    insert(6, 6);
    remove(3);
    tree.print();
    tree.clearTree();
    
    //node deletion causing LR case9
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 0 Height: 1
    3 BF: 0 Height: 0
    4 BF: 0 Height: 2
    7 BF: -1 Height: 1
    8 BF: 0 Height: 0*/
    insert(7, 7);
    insert(2, 2);
    insert(8, 8);
    insert(1, 1);
    insert(4, 4);
    insert(9, 9);
    insert(3, 3);
    remove(9);
    tree.print();
    tree.clearTree();
    
    //node deletion causing LL case10
    /*correct output
    1 BF: 0 Height: 0
    2 BF: 1 Height: 1
    3 BF: 0 Height: 2
    4 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0*/
    insert(7, 7);
    insert(3, 3);
    insert(8, 8);
    insert(2, 2);
    insert(4, 4);
    insert(9, 9);
    insert(1, 1);
    remove(9);
    tree.print();
    tree.clearTree();
    
    //node deletion causing RR case11
    /*correct output
    2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    7 BF: 0 Height: 0
    8 BF: 0 Height: 2
    9 BF: -1 Height: 1
    10 BF: 0 Height: 0*/
    insert(3, 3);
    insert(2, 2);
    insert(8, 8);
    insert(7, 7);
    insert(1, 1);
    insert(9, 9);
    insert(10, 10);
    remove(1);
    tree.print();
    tree.clearTree();
    
    //node deletion causing RL case12
    /*correct output
    * 2 BF: 0 Height: 0
    3 BF: 1 Height: 1
    7 BF: 0 Height: 2
    10 BF: 0 Height: 0
    13 BF: 0 Height: 1
    14 BF: 0 Height: 0*/
    insert(3, 3);
    insert(2, 2);
    insert(13, 13);
    insert(7, 7);
    insert(1, 1);
    insert(14, 14);
    insert(10, 10);
    remove(1);
    tree.print();
    tree.clearTree();
    
    //double rotations RL and RR case 13
    /*correct output
    3 BF: 0 Height: 0
    5 BF: 0 Height: 1
    7 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    insert(9, 9);
    insert(3, 3);
    insert(15, 15);
    insert(1, 1);
    insert(7, 7);
    insert(13, 13);
    insert(19, 19);
    insert(5, 5);
    insert(11, 11);
    insert(17, 17);
    insert(21, 21);
    insert(23, 23);
    remove(1);
    tree.print();
    tree.clearTree();
    
    //double rotations RR and RR case 14
    /*correct output
    3 BF: 0 Height: 0
    7 BF: 0 Height: 1
    8 BF: 0 Height: 0
    9 BF: 0 Height: 2
    11 BF: 0 Height: 0
    13 BF: 1 Height: 1
    15 BF: 0 Height: 3
    17 BF: 0 Height: 0
    19 BF: -1 Height: 2
    21 BF: -1 Height: 1
    23 BF: 0 Height: 0*/
    insert(9, 9);
    insert(3, 3);
    insert(15, 15);
    insert(1, 1);
    insert(7, 7);
    insert(13, 13);
    insert(19, 19);
    insert(8, 8);
    insert(11, 11);
    insert(17, 17);
    insert(21, 21);
    insert(23, 23);
    remove(1);
    tree.print();
    tree.clearTree();
    
    //double rotations RL and LL case 15
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    17 BF: 0 Height: 0
    18 BF: 0 Height: 1
    20 BF: 0 Height: 0
     */
    insert(15, 15);
    insert(10, 10);
    insert(20, 20);
    insert(8, 8);
    insert(11, 11);
    insert(17, 17);
    insert(21, 21);
    insert(7, 7);
    insert(9, 9);
    insert(12, 12);
    insert(18, 18);
    insert(6, 6);
    remove(21);
    tree.print();
    tree.clearTree();
    
    //double rotations LR and LL case 16
    /*correct output
    6 BF: 0 Height: 0
    7 BF: 1 Height: 1
    8 BF: 1 Height: 2
    9 BF: 0 Height: 0
    10 BF: 0 Height: 3
    11 BF: -1 Height: 1
    12 BF: 0 Height: 0
    15 BF: 0 Height: 2
    20 BF: 0 Height: 0
    21 BF: 0 Height: 1
    22 BF: 0 Height: 0 */
    insert(15, 15);
    insert(10, 10);
    insert(20, 20);
    insert(8, 8);
    insert(11, 11);
    insert(17, 17);
    insert(22, 22);
    insert(7, 7);
    insert(9, 9);
    insert(12, 12);
    insert(21, 21);
    insert(6, 6);
    remove(17);
    tree.print();
    tree.clearTree();
    
    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: -1 Height: 2
    4 BF: 0 Height: 0
    6 BF: 1 Height: 1*/
    
    insert(5, 5);
    insert(3, 3);
    insert(6, 6);
    insert(2, 2);
    insert(4, 4);
    remove(5);
    tree.print();
    tree.clearTree();
    
    //delete node cause LR
    /*correct output
     * 2 BF: 0 Height: 0
    3 BF: 0 Height: 1
    6 BF: 0 Height: 0*/
    insert(5, 5);
    insert(3, 3);
    insert(6, 6);
    insert(2, 2);
    remove(5);
    tree.print();
    tree.clearTree();
    
    std::vector<int> vector;
    for (int i=1; i<=100; i++) vector.push_back(i);
    
    //Randomly insert and removes nodes
    for (int k = 0; k < 20; ++k) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            insert(*it, *it);
            
        }
        tree.print();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            remove(*it);
            tree.print();
            
        }
        tree.clearTree();
        tree.print();
        std::cout << '\n';
    }
    
    return 0;
}

