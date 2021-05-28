#pragma once
#include <stack>
#include <stdexcept>
#include <iostream>
#include "Node.hpp"

namespace ariel 
{
    template<typename T>
    class PreOrderIterator
    {        
        private:
            Node<T>* pointer_to_current_node;
            std::stack<Node<T>*> nodes;  

        public:
            PreOrderIterator(Node<T>* ptr = nullptr) : pointer_to_current_node(ptr) 
            {
                if(ptr) nodes.push(ptr);
            } 
            ~PreOrderIterator() {}
            
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
            
            // void iterativePreorder(node* root)
            // {
            //     /* Pop all items one by one. Do following for every popped item
            //     a) print it
            //     b) push its right child
            //     c) push its left child
            //     Note that right child is pushed first so that left is processed first */
            //     if (!nodes.empty()) 
            //     {
            //         // Pop the top item from stack and print it
            //         pointer_to_current_node = nodes.top();
                    
            //         nodes.pop();
            
            //         // Push right and left children of the popped node to stack
            //         if (pointer_to_current_node->right)
            //             nodes.push(pointer_to_current_node->right);
            //         if (pointer_to_current_node->left)
            //             nodes.push(pointer_to_current_node->left);
            //     }
            //     else
            //     {
            //         pointer_to_current_node = nullptr;
            //     }
            // }

            PreOrderIterator &operator++() {
                if (!nodes.empty()) 
                {
                    pointer_to_current_node = nodes.top();
                    nodes.pop();
            
                    if (pointer_to_current_node->right)
                    {
                        nodes.push(pointer_to_current_node->right);
                    }
                    if (pointer_to_current_node->left)
                    {
                        nodes.push(pointer_to_current_node->left);
                    }
                }
                else
                {
                    pointer_to_current_node = nullptr;
                }

                return *this;
            }

            // assigning operator
            PreOrderIterator& operator=(PreOrderIterator *other) 
            {
                if (pointer_to_current_node != nullptr) delete pointer_to_current_node;
                pointer_to_current_node = other->pointer_to_current_node;
                return *this;
            }
            
            const PreOrderIterator operator++(int) {
                // check that performs deep copy
                PreOrderIterator tmp = *this;
                ++pointer_to_current_node;
                return tmp;
            }

            bool operator==(const PreOrderIterator &other) const {
                return pointer_to_current_node == other.pointer_to_current_node;
            }

            bool operator!=(const PreOrderIterator &other) const {
                return pointer_to_current_node != other.pointer_to_current_node;
            }

            Node<T>* get_ptr() const
            {
                return pointer_to_current_node;
            }
    };
}