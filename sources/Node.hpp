#pragma once

namespace ariel
{
    template<typename T>
    struct Node
    {
        T val;
        Node* left;
        Node* right;
        Node() {}
        ~Node() {}
        Node(const T& v) : val(v) {left = right = nullptr;}
        Node(const Node& other) : val(other.val), left(other.left), right(other.right) {}
    };
}