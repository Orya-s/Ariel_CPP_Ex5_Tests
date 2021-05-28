#pragma once
#include <stack>
#include <stdexcept>
#include <iostream>
#include "Node.hpp"

namespace ariel 
{
    template<typename T>
    class InOrderIterator
    {        
        private:
            Node<T>* pointer_to_current_node;
            Node<T>* stk_iter;   
            Node<T>* temp = nullptr;   
            std::stack<Node<T>*> nodes;  

        public:
            InOrderIterator(Node<T>* ptr = nullptr) : pointer_to_current_node(ptr), stk_iter(ptr) {}
            ~InOrderIterator() {}
            
            T& operator*() const 
            {
                if (!pointer_to_current_node)
                    std::cout << "No value in node" << std::endl;
                return pointer_to_current_node->val;
            }

            T* operator->() const 
            { 
                return &(pointer_to_current_node->val); 
            }

            InOrderIterator &operator++() {
                if (stk_iter != nullptr || !nodes.empty()) {

                    while (stk_iter != nullptr) 
                    {
                        nodes.push(stk_iter);
                        stk_iter = stk_iter->left;
                    }   // stk_iter is now nullptr

                    stk_iter = nodes.top();
                    nodes.pop();
                    
                    if (!temp) 
                    {
                        pointer_to_current_node = stk_iter;
                    }
                    else 
                    {
                        pointer_to_current_node = temp;
                    }
                    stk_iter = stk_iter->right;
                    temp = stk_iter;
                } 
                else 
                {
                    pointer_to_current_node = nullptr;
                }

                return *this;
            }

            // assigning operator
            InOrderIterator& operator=(InOrderIterator *other) 
            {
                if (pointer_to_current_node != nullptr) delete pointer_to_current_node;
                pointer_to_current_node = other->pointer_to_current_node;
                return *this;
            }
            
            const InOrderIterator operator++(int) {
                // check that performs deep copy
                InOrderIterator tmp = *this;
                ++pointer_to_current_node;
                return tmp;
            }

            bool operator==(const InOrderIterator &other) const {
                return pointer_to_current_node == other.pointer_to_current_node;
            }

            bool operator!=(const InOrderIterator &other) const {
                return pointer_to_current_node != other.pointer_to_current_node;
            }

            Node<T>* get_ptr() const
            {
                return pointer_to_current_node;
            }
    };
}