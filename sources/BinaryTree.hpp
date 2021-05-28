#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include "InOrderIterator.hpp"
#include "PreOrderIterator.hpp"
#include "PostOrderIterator.hpp"

// using std::string, std::to_string, std::cout;

namespace ariel
{
    template<typename T>
    class BinaryTree
    {
        // inner Node class
        // struct Node {
        //     T val;
        //     Node* left;
        //     Node* right;
        //     Node(const T& v) : val(v) {left = right = nullptr;}
        //     Node(const Node& other) : val(other.val), left(other.left), right(other.right) {}
        //     // check if needed -
        //     // Node(const T& v, Node* r, Node* l) : val(v), left(l), right(r) {}
        // };
        
        
        private:
            Node<T>* root;
            // Node<T> *temp = new Node<T>;

        public:
            // constructors & destructors
            BinaryTree() {root = nullptr;};
            BinaryTree(const BinaryTree<T> &bt) : root(bt.root) {}
            ~BinaryTree() 
            {
                deleteTree(root);
                // if(temp != nullptr) delete temp;
            }

            void deleteTree(Node<T> *leaf)
            {
                if(leaf)
                {
                    deleteTree(leaf->left);
                    deleteTree(leaf->right);
                    delete leaf;
                }
                // if(temp) {delete temp;}
            }


            // class iterator     // inner class
            // {
            //     private:
            //         Node<T>* pointer_to_current_node;

            //     public:

            //         iterator(Node<T>* ptr = nullptr) : pointer_to_current_node(ptr) {}

            //         T& operator*() const
            //         {
            //             return pointer_to_current_node->val;
            //         }

            //         T* operator->() const 
            //         {
            //             return &(pointer_to_current_node->val);
            //         }

            //         iterator& operator++()  // prefix 
            //         {
            //             pointer_to_current_node = pointer_to_current_node->left;
            //             return *this;
            //         }

            //         const iterator operator++(int)  // postfix
            //         {
            //             iterator t = *this;
            //             pointer_to_current_node = pointer_to_current_node->left;
            //             return t;
            //         }

            //         bool operator==(const iterator &it) const
            //         {
            //             return pointer_to_current_node == it.pointer_to_current_node;
            //         }

            //         bool operator!=(const iterator &it) const
            //         {
            //             return pointer_to_current_node != it.pointer_to_current_node;
            //         }

            // };  // END OF CLASS ITERATOR

            

            // adding nodes functions
            BinaryTree& add_root(T val)
            {
                if (root)
                {
                    root->val = val;
                }
                else
                {
                    root = new Node<T>(val);
                }
                return *this;
            }

            BinaryTree& add_left(T father, T son)
            {
                if (!root)
                {
                    throw("Illegal action - this tree has no root");
                }
                // if (root->val == father)
                // {
                //     root->left = new Node<T>(son);
                //     return *this;
                // }

                Node<T> *temp = nullptr;
                for (auto it = begin_inorder() ; it != end_inorder() ; ++it) 
                {   
                    if (*it == father)
                    {
                        temp = it.get_ptr();
                        // std::cout << *it << " = " << temp->val << std::endl;
                        it = end_inorder();
                    }
                }  

                if (temp == nullptr)
                {
                    // delete temp;
                    throw "First Element Does Not Exist In The Binary Tree";
                }

                if (temp->left)
                {
                    temp->left->val = son;
                    // delete temp; // ?
                    return *this;
                }
                
                //Node<T>* f = temp;  
                Node<T>* s = new Node<T>(son);
                temp->left = s;
                
                // delete temp; //  ???

                return *this;
            }

            BinaryTree& add_right(T father, T son)
            {
                if (!root)
                {
                    throw("Illegal action - this tree has no root");
                }
                
                Node<T> *temp = nullptr;
                for (auto it = begin_inorder() ; it != end_inorder() ; ++it) 
                {   
                    if (*it == father)
                    {
                        temp = it.get_ptr();
                        // std::cout << *it << " = " << temp->val << std::endl;
                        it = end_inorder();
                    }
                }  

                if (temp == nullptr)
                {
                    // delete temp;
                    throw "First Element Does Not Exist In The Binary Tree";
                }

                if (temp->right)
                {
                    temp->right->val = son;
                    return *this;
                }
                
                Node<T>* f = temp;  
                Node<T>* s = new Node<T>(son);
                f->right = s;
                //delete temp; ???

                return *this;
            }


            // assigning operator
            BinaryTree<T>& operator=(BinaryTree<T> *other) 
            {
                if (root != nullptr) delete root;
                root = other->root;
                return *this;
            }

            // Move constructor and operator=:
            BinaryTree(BinaryTree&& other)
            {
                root = other.root;
                other.root = nullptr;
            }
            void operator=(BinaryTree&& other)
            {
                if (root) delete root;
                root  = other.root;
                other.root = nullptr;
            }


            // iterating functions
            InOrderIterator<T> begin()
            {
                return begin_inorder();
            }
            InOrderIterator<T> end()
            {
                return end_inorder();
            }

            PreOrderIterator<T> begin_preorder()
            {
                return ++(PreOrderIterator<T>(root));
            }
            PreOrderIterator<T> end_preorder()
            {
                return PreOrderIterator<T>(nullptr);
            }

            InOrderIterator<T> begin_inorder()
            {
                return ++(InOrderIterator<T>(root));
            }
            InOrderIterator<T> end_inorder()
            {
                return InOrderIterator<T>(nullptr);
            }

            PostOrderIterator<T> begin_postorder()
            {
                return ++(PostOrderIterator<T>(root));
            }
            PostOrderIterator<T> end_postorder()
            {
                return PostOrderIterator<T>(nullptr);
            }

           

            friend std::ostream& operator << (std::ostream& os, const BinaryTree<T>& bt)
            {
                return os;
            }

            // friend std::ostream& operator<<(std::ostream& out, const BinaryTree& tree) {
            //     out << tree.root->val;
            //     if (tree.root->left)
            //         out << "(" << (*tree.root->left)  << ")";
            //     if (tree.root->right)
            //         out << "[" << (*tree.root->right)  << "]";
            //     return out;
            // }

    };    
} 