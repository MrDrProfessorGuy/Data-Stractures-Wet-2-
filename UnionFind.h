#ifndef DATA_STRACTURES_WET_2_UNIONFIND_H
#define DATA_STRACTURES_WET_2_UNIONFIND_H

#include "Group.h"
#include "memory"



class UnionFind{
    static const int NA = -1;
    
    int size;
    int* group_size;
    int* parent;
    std::shared_ptr<Group>* group;
    
    bool validId(int group_id) const{
        if (0 < group_id && group_id <= size){
            return true;
        }
        return false;
    }

    int groupRoot(int group_id, bool shrink=false, int root_id=NA){
        int counter = 0;
        int current_group = group_id;
        while (parent[current_group] != current_group){
            current_group = parent[current_group];
            if (shrink && validId(root_id)){ /// shrink
                parent[current_group] = root_id;
            }
            counter++;
            assert(counter < size+1);
        }
        return current_group;
    }

    void merge(Group& root, Group& group2, int group1_id, int group2_id){
        root.merge(group2);
        group_size[group1_id] += group_size[group2_id];
        group_size[group2_id] = NA;
        parent[group2_id] = group1_id;
        group[group2_id].reset();
    }
public:
    // Time: O(size)
    UnionFind(int size): size(size), group_size(new int[size+1]), parent(new int[size+1]),
                        group(new std::shared_ptr<Group>[size+1]){
        /// TODO: add try-catch for bad_alloc
        for (int group_id = 1; group_id <= size; group_id++) {
            group_size[group_id] = 1;
            parent[group_id] = group_id;
            group[group_id] = std::shared_ptr<Group>(new Group(group_id));
        }
    }
    UnionFind(const UnionFind&) = delete;
    // Time: O(size)
    ~UnionFind(){
        for (int group_id = 1; group_id <= size; group_id++) {
            group[group_id].reset();
        }
        delete[] group_size;
        delete[] parent;
        delete[] group;
    }
    
    Group& find(int group_id){
        int root_id = groupRoot(group_id);
        groupRoot(group_id, true, root_id);
        return *group[root_id];
    }
    
    void unite(int group1_id, int group2_id){
        if (groupRoot(group1_id) == groupRoot(group2_id)){
            return;
        }
        Group& group1 = find(group1_id);
        Group& group2 = find(group2_id);
        int group1_size = group_size[groupRoot(group1_id)];
        int group2_size = group_size[groupRoot(group2_id)];
        
        if (group1_size >= group2_size){
            merge(group1, group2, group1_id, group2_id);
        }
        else{
            merge(group2, group1, group2_id, group1_id);
            //group2.id = group1_id;
        }
    }

    
};


#endif //DATA_STRACTURES_WET_2_UNIONFIND_H
