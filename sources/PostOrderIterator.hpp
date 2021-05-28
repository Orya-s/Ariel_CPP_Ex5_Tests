#pragma once
#include <stack>
#include <stdexcept>
#include <iostream>
#include "Node.hpp"

namespace ariel 
{
    template<typename T>
    class PostOrderIterator
    {        
        private:
            Node<T>* pointer_to_current_node;
            std::stack<Node<T>*> nodes1, nodes2;
            

        public:
            PostOrderIterator(Node<T>* ptr = nullptr) : pointer_to_current_node(ptr) 
            {
                if(ptr) nodes1.push(ptr);
            } 
            ~PostOrderIterator() {}
            
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
            
            PostOrderIterator &operator++() {
                if ((nodes1.empty()))
                    pointer_to_current_node = nullptr;
            
                while (!nodes1.empty()) {
                    pointer_to_current_node = nodes1.top();
                    nodes1.pop();
                    nodes2.push(pointer_to_current_node);
            
                    if (pointer_to_current_node->left)
                    {
                        nodes1.push(pointer_to_current_node->left);
                    }
                    if (pointer_to_current_node->right)
                    {
                        nodes1.push(pointer_to_current_node->right);
                    }
                }
            
                if (nodes1.empty()) {
                    if (!nodes2.empty()) {
                        pointer_to_current_node = nodes2.top();
                        nodes2.pop();
                    }
                }

                return *this;
            }

            // assigning operator
            PostOrderIterator& operator=(PostOrderIterator *other) 
            {
                if (pointer_to_current_node != nullptr) delete pointer_to_current_node;
                pointer_to_current_node = other->pointer_to_current_node;
                return *this;
            }
            
            const PostOrderIterator operator++(int) {
                // check that performs deep copy
                PostOrderIterator tmp = *this;
                ++pointer_to_current_node;
                return tmp;
            }

            bool operator==(const PostOrderIterator &other) const {
                return pointer_to_current_node == other.pointer_to_current_node;
            }

            bool operator!=(const PostOrderIterator &other) const {
                return pointer_to_current_node != other.pointer_to_current_node;
            }

            Node<T>* get_ptr() const
            {
                return pointer_to_current_node;
            }
    };
}