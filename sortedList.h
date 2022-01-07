#ifndef SORTEDLIST_SORTEDLIST_H
#define SORTEDLIST_SORTEDLIST_H
#include <stdexcept>
#include <new>


template<class T>
    class SortedList;

/**************************************************/
/********************* Node *********************/
/**********************************************/
    
    template<class T>
    class Node{
    private:
        T* data;
        Node* next;
        Node* previus;

        /**
         * constructor for a dummy Node that holds no data
         */
        Node() : data(nullptr), next(nullptr), previus(nullptr){
        
        }
        /**
         * linkNodes: link next and previus pointers of two given nodes in the given order.
         * @tparam T
         * @param first_node
         * @param second_node
         */
        static void linkNodes(Node& first_node, Node& second_node);
    
    public:
        friend class SortedList<T>;
        explicit Node(const T& node_data, Node* previus_node = nullptr, Node* next_node = nullptr){
            data = new T(node_data);
            previus = previus_node;
            next = next_node;
        }
        ~Node(){
            if (data != nullptr){
                delete data;
            }
        }
        Node(const Node&) = delete;
        /**
         * Node<T>::remove - link the previus and next nodes (if exist) and delete the node.
         * @tparam T
         */
        void remove();
    };

    template<class T>
    void Node<T>::linkNodes(Node<T>& first_node, Node<T>& second_node){
        first_node.next = &second_node;
        second_node.previus = &first_node;
    }

    template <class T>
    void Node<T>::remove(){
        Node<T>::linkNodes(*previus, *next);
        delete this;
    }



/*******************************************************/
/********************* SortedList *********************/
/*****************************************************/
    template<class T>
    class SortedList {
    public:
        class const_iterator;
        class RealConst_iterator;
        SortedList() : size(2){
            Node<T>::linkNodes(head, end_node);
        }
        SortedList(const SortedList& list) : size(2){
            Node<T>::linkNodes(head, end_node);
            RealConst_iterator end_of_list = list.constEnd();
            RealConst_iterator iterator = list.constBegin();

            try {
                while (iterator != end_of_list){
                    insert(*iterator);
                    iterator++;
                }
            }
            catch (const std::bad_alloc& ) {/// in case one of the new allocations fail
                removeNodes();
                throw ;
            }
        }
        ~SortedList(){
            removeNodes();
        }
        /**
         * Create and return an identical Copy  of the given list
         * @param sortedList
         * @return
         *  sortedList
         */
        SortedList& operator=(const SortedList& sortedList){
            if (this == &sortedList){
                return *this;
            }
            Node<T> tmp_head, current_node;
            SortedList<T> list_copy = SortedList<T>(sortedList); // create a new copy before deleting current data
            
            removeNodes(); // allocation success ==> delete data
            if (list_copy.length() != 0){
                // Link data
                Node<T>* last_node = (list_copy.end_node).previus;
                Node<T>::linkNodes(head, *(list_copy.head.next));
                Node<T>::linkNodes(*(last_node), end_node);
                // Unlink tmp list from data
                Node<T>::linkNodes(list_copy.head, list_copy.end_node);
            }
           
            size = list_copy.size;
            return *this;
        }
        /**
         * insert the given data to the list, keeping the list ordered
         * @param data
         */
        void insert(const T& data){
            Node<T>* new_node = new Node<T>(data);// bad alloc is the caller's problem, can't help in here
            
            Node<T>* current_node = head.next;
            while (current_node != &end_node){
                if (data < *current_node->data){
                    Node<T>* previus = current_node->previus;
                    Node<T>::linkNodes(*previus, *new_node);
                    Node<T>::linkNodes(*new_node, *current_node);
                    size++;
                    return;
                }
                current_node = current_node->next;
            }
            Node<T>* previus = current_node->previus;
            Node<T>::linkNodes(*previus, *new_node);
            Node<T>::linkNodes(*new_node, *current_node);
            size++;
        }
        /**
         * remove the data the given iterator is pointing at
         * @param iterator
         */
        void remove(const_iterator& iterator){
            const_iterator end_of_list = end();
            if (iterator == end_of_list){
                throw std::out_of_range("");
            }
            Node<T>* to_delete = find(*iterator);
            if (to_delete == nullptr){
                throw std::out_of_range("");
            }
            to_delete->remove();
            size--;
        }
        /**
         * return the number of data elements in the list
         * @return
         */
        int length() const{
            return (size-2);
        }
        /**
         * return const_pointer to the first (smallest) data element
         */
        const_iterator begin(){
            return ++const_iterator(head);
        }
        RealConst_iterator constBegin() const{
            return ++RealConst_iterator(head);
        }
        /**
         * return const_pointer to the last (biggest) data element
         */
        const_iterator end(){
            return const_iterator(end_node);
        }
        RealConst_iterator constEnd() const{
            return RealConst_iterator(end_node);
        }
    
        template<class Condition>
        SortedList filter(Condition condition) const;
        SortedList<T> apply(T function(const T)) const{
            
            SortedList<T> new_list = SortedList<T>();
            const_iterator end_of_list = end();
            const_iterator iterator = begin();
            while (iterator != end_of_list){
                new_list.insert(function(*iterator));
                iterator++;
            }
            return new_list;
        }
    
    private:
        Node<T> head;
        Node<T> end_node;
        int size;
        
        Node<T>* find(const T& data) const{
            Node<T>* current_node = head.next;
            while (current_node != &end_node){
                // We shouldn't assume T has defined operator==()
                if (!(*current_node->data < data) &&
                    !(data < *current_node->data)){
                    return current_node;
                }
                current_node = current_node->next;
            }
            return nullptr;
        }
        void removeNodes(){
            const_iterator end_of_list = end();
            const_iterator iterator = begin();
            while (iterator != end_of_list){
                remove(iterator);
                iterator = begin();
            }
        }
    };

/***********************************************************/
/********************* const_iterator *********************/
/*********************************************************/

    template<class T>
    class SortedList<T>::const_iterator{
        Node<T>* node;
        
        const_iterator() = delete;
        const_iterator(Node<T>& node_ptr) : node(&node_ptr){
        }

    
    public:
        friend class SortedList<T>;
        const_iterator(const const_iterator&) = default;///remove const?
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;
        const_iterator& operator++(){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            node = node->next; // node->next is null_ptr by default
            return *this;
        }
        const_iterator operator++(int){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            const_iterator tmp_iterator = *this;
            ++(*this);
            return tmp_iterator;
            
        }
        const_iterator& operator--(){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            node = node->previus; // node->previus is null_ptr by default
            return *this;
        }
        const_iterator operator--(int){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            const_iterator tmp_iterator = *this;
            --(*this);
            return tmp_iterator;
        }
        T& operator*() const{
            if (node == nullptr){
                throw std::out_of_range("");
            }
            return *(node->data);
        }
        
        bool operator==(const const_iterator& iterator) const{
            if (iterator.node == nullptr || node == nullptr){
                return false;
            }
            if (node == iterator.node){
                return true;
            }

/*        /// using < in case T has not implemented '==' or '>'
        if (!(*(node->data) < *(iterator.node->data)) &&
            !(*(iterator.node->data) < *(node->data))){
            return true;
        }
        */
            return false;
        }
        bool operator!=(const const_iterator& iterator) const{
            return !(node == iterator.node);
            
        }
    };

    template<class T>
    class SortedList<T>::RealConst_iterator{
        const Node<T>* node;
    
        RealConst_iterator() = delete;
        RealConst_iterator(const Node<T>& node_ptr) : node(&node_ptr){
        }
    
    
    public:
        friend class SortedList<T>;
        RealConst_iterator(const RealConst_iterator&) = default;///remove const?
        RealConst_iterator& operator=(const RealConst_iterator&) = default;
        ~RealConst_iterator() = default;
        RealConst_iterator& operator++(){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            node = node->next; // node->next is null_ptr by default
            return *this;
        }
        RealConst_iterator operator++(int){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            RealConst_iterator tmp_iterator = *this;
            ++(*this);
            return tmp_iterator;
            
        }
        RealConst_iterator& operator--(){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            node = node->previus; // node->previus is null_ptr by default
            return *this;
        }
        RealConst_iterator operator--(int){
            if (node == nullptr){
                throw std::out_of_range("");
            }
            RealConst_iterator tmp_iterator = *this;
            --(*this);
            return tmp_iterator;
        }
        T& operator*() const{
            if (node == nullptr){
                throw std::out_of_range("");
            }
            return *(node->data);
        }
        
        bool operator==(const RealConst_iterator& iterator) const{
            if (iterator.node == nullptr || node == nullptr){
                return false;
            }
            if (node == iterator.node){
                return true;
            }
    
    /*        /// using < in case T has not implemented '==' or '>'
            if (!(*(node->data) < *(iterator.node->data)) &&
                !(*(iterator.node->data) < *(node->data))){
                return true;
            }
            */
            return false;
        }
        bool operator!=(const RealConst_iterator& iterator) const{
            return !(node == iterator.node);
            
        }
    };
    
/*************************************************************/
/********************* Function Objects *********************/
/***********************************************************/
    template<class T>
    template<class Condition>
    SortedList<T> SortedList<T>::filter(Condition condition) const {
        SortedList<T> filtered_list;
        for (typename SortedList<T>::const_iterator iterator = begin(); iterator != end(); ++iterator) {
            if (condition(*iterator)) {
                filtered_list.insert(*iterator);
            }
        }
        return filtered_list;
    }
    
    



#endif //SORTEDLIST_SORTEDLIST_H
