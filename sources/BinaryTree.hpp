#pragma once
#include <string>
#include <iostream>
#include <sstream>

namespace ariel
{
    // template <typename T>
    // struct Node
    // {
    //     T data;
    //     Node<T> *left;
    //     Node<T> *right;

    //     Node<T>(T data)
    //     {
    //         this->data = data;
    //         left = right = nullptr;
    //     }
    // };


    template<typename T>
    class BinaryTree
    {
        // inner Node class
        struct Node {
            T val;
            Node* left;
            Node* right;
            Node(const T& v) : val(v) {left = right = nullptr;}
            Node(const T& v, Node* r, Node* l) : val(v) {left = right = nullptr;}

        };
        
        
        private:
            Node* root;

        public:
            BinaryTree() {root = nullptr;};
            ~BinaryTree() {delete root;};


            class iterator     // inner class
            {
                private:
                    Node* pointer_to_current_node;

                public:

                    iterator(Node* ptr = nullptr) : pointer_to_current_node(ptr) {}

                    T& operator*() const
                    {
                        return pointer_to_current_node->val;
                    }

                    T* operator->() const 
                    {
                        return &(pointer_to_current_node->val);
                    }

                    iterator& operator++()
                    {
                        pointer_to_current_node = pointer_to_current_node->left;
                        return *this;
                    }

                    const iterator operator++(int)
                    {
                        iterator temp = *this;
                        pointer_to_current_node = pointer_to_current_node->left;
                        return temp;
                    }

                    bool operator==(const iterator &it) const
                    {
                        return pointer_to_current_node == it.pointer_to_current_node;
                    }

                    bool operator!=(const iterator &it) const
                    {
                        return pointer_to_current_node != it.pointer_to_current_node;
                    }

                    // friend std::ostream &operator<<(std::ostream &os, const BinaryTree &b);

            };  // END OF CLASS ITERATOR
            


            BinaryTree& add_root(T val)
            {
                if (root)
                {
                    root->val = val;
                }
                else
                {
                    root = new Node(val);
                }
                
                return *this;
            }
            BinaryTree& add_left(T father, T son)
            {
                if (!root)
                {
                    throw("Illegal action - this tree has no root");
                }
                
                return *this;
            }
            BinaryTree& add_right(T father, T son)
            {
                if (!root)
                {
                    throw("Illegal action - this tree has no root");
                }
                
                return *this;
            }


            iterator begin()
            {
                return iterator(root);
            }

            iterator end()
            {
                return iterator(nullptr);
            }


            iterator begin_preorder()
            {
                return iterator(root);
            }

            iterator end_preorder()
            {
                return iterator(nullptr);
            }
            iterator begin_inorder()
            {
                return iterator(root);
            }
            iterator end_inorder()
            {
                return iterator(nullptr);
            }
            iterator begin_postorder()
            {
                return iterator(root);
            }
            iterator end_postorder()
            {
                return iterator(nullptr);
            }

           
            // Node<T>& get_root()
            // {
            //     if (this->root)
            //     {
            //         return *this->root;
            //     }
            //     throw("there is no root for this tree");
            // }
           

            friend std::ostream& operator << (std::ostream& os, const BinaryTree<T>& bt)
            {
                return os;
            }

    };    
} 