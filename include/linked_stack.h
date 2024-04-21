/**
 * \file linked_stack.h
 * \brief This file declares the Linked Stack class used to develop the game
 *        Target Nine which is the assignment for University of Nicosia COMP211
 * \author Konstantinos Trimikliniotis
*/

#ifndef LINKED_STACK_H_
#define LINKED_STACK_H_

#include <exception>

/**
 * <code>LinkedStack</code> Stack implemented using connected Nodes with
 *                          the same interface as std::stack<> (main functionalities)
*/
template<typename T = int>
class LinkedStack {

    struct Node {
        T obj;
        Node* next;
    };

    Node* top_node = nullptr;
    int size_ = 0;

public:
    class EmptyStackException: public std::exception {
    private:
        const char* msg = "Cannot perform the operation because stack is empty";
    public:
        // Override what() to provide error message
        const char* what() const noexcept override {
            return msg;
        }
    };

    LinkedStack(){}

    LinkedStack(const LinkedStack& other) {
        LinkedStack tmp{};
        Node* head = other.top_node;
        while (head != nullptr) {
            tmp.push(head->obj);
            head = head->next;
        }
        head = tmp.top_node;
        while (head != nullptr) {
            push(head->obj);
            head = head->next;
        }
    }

    LinkedStack& operator=(const LinkedStack &other) {
        if (this == &other) {
            return *this;
        }
        clear();
        LinkedStack tmp{};
        Node* head = other.top_node;
        while (head != nullptr) {
            tmp.push(head->obj);
            head = head->next;
        }
        head = tmp.top_node;
        while (head != nullptr) {
            push(head->obj);
            head = head->next;
        }
        return *this;
    }

    /**
     * <code>top</code> returns the element on top
     * <BR>
     * @return The top element
     * @throws Throws EmptyStackException if stack is empty
    */
    T& top() const {
        if (empty()) {
            throw EmptyStackException();
        }
        return top_node->obj;
    }

    /**
     * <code>push</code> addes a new element to the stack
     * <BR>
     * @param obj Element to be added
     * @throws implicitly throws std::bad_alloc if there is no free memory
     *         on heap to create Node;
    */
    void push(const T& obj) {
        Node* new_node = new Node();
        // exception std::bad_alloc implicitly propagates
        new_node->obj = obj;
        new_node->next = top_node;
        top_node = new_node;
        size_++;
    }

    /**
     * <code>pop</code> removes the top element from the stack
     * <BR>
     * @throws Throws EmptyStackException if stack is empty
    */
    void pop() {
        if (empty()) {
            throw EmptyStackException();
        }
        Node* tmp = top_node;
        top_node = top_node->next;
        delete tmp;
        size_--;        
    }

    /**
     * <code>empty</code> checks if stack is empty
     * <BR>
     * @return true if empty, false otherwise
    */
    bool empty() const {
        return size_ == 0;
    }

    /**
     * <code>size</code> returns the size of the stack
     * <BR>
     * @return size of the stack as an integer
    */
    int size() const {
        return size_;
    }

    /**
     * <code>clear</code> clears the stack
    */
    void clear() {
        while (!empty()) {
            pop();
        }
    }

    ~LinkedStack() {
        clear();
    }
};

#endif