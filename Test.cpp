#include "BinaryTree.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace ariel;


TEST_CASE("Creating a BinaryTree tests")
{
    // int BT
    BinaryTree<int> bt;
    int root = 1;
    bt.add_root(root);
    CHECK_NOTHROW(bt.add_root(2));
    CHECK_EQ(*bt.begin_preorder(), 2);

    BinaryTree<int> b;  // checking =(other) operator
    bt = BinaryTree<int>();

    // double BT
    BinaryTree<double> bt_d;
    double root_d = 2.2;
    bt_d.add_root(root_d);
    CHECK_NOTHROW(bt_d.add_root(0.25));
    CHECK_EQ(*bt_d.begin_inorder(), 0.25);


    // char BT
    BinaryTree<char> bt_c;
    char root_c = 'a';
    bt_c.add_root(root_c);
    char n_root = 'b';
    CHECK_NOTHROW(bt_c.add_root(n_root));
    CHECK_EQ(*bt_c.begin_postorder(), n_root);


    // string BT
    BinaryTree<string> bt_s;
    string root_s = "root";
    bt_s.add_root(root_s);
    string new_root = "new root";
    CHECK_NOTHROW(bt_s.add_root(new_root));
    CHECK_EQ(*bt_s.begin_postorder(), new_root);
}


TEST_CASE("adding childs before root test")
{
    BinaryTree<int> bt;
    CHECK_THROWS(bt.add_left(0, 1));
    CHECK_THROWS(bt.add_right(2, 0));

    BinaryTree<double> bt_d;
    CHECK_THROWS(bt_d.add_left(0, 0.21));
    CHECK_THROWS(bt_d.add_right(0, 2.34));

    BinaryTree<char> bt_c;
    CHECK_THROWS(bt_c.add_left('a', '1'));
    CHECK_THROWS(bt_c.add_right('f', 'm'));

    BinaryTree<string> bt_s;
    CHECK_THROWS(bt_s.add_left("000", "111111"));
    CHECK_THROWS(bt_s.add_right("no root", "son"));
}


TEST_CASE("iteraiting empty / root tree test")
{
    BinaryTree<int> bt;
    for (auto it = bt.begin_preorder(); it != bt.end_preorder(); ++it) 
    {
        CHECK_NOTHROW(*it);     
    }  
    for (auto it = bt.begin_inorder(); it != bt.end_inorder(); ++it) 
    {
        CHECK_NOTHROW(*it);  
    } 
    for (auto it = bt.begin_postorder(); it != bt.end_postorder(); ++it) 
    {
        CHECK_NOTHROW(*it);  
    }

    BinaryTree<string> bt1;
    for (auto it = bt1.begin_preorder(); it != bt1.end_preorder(); ++it) 
    {
        CHECK_NOTHROW(*it);     
    }  
    for (auto it = bt1.begin_inorder(); it != bt1.end_inorder(); ++it) 
    {
        CHECK_NOTHROW(*it);  
    } 
    for (auto it = bt1.begin_postorder(); it != bt1.end_postorder(); ++it) 
    {
        CHECK_NOTHROW(*it);  
    }

    BinaryTree<float> bt2;
    float root = 1.1;
    bt2.add_root(root);
    CHECK_EQ(*bt2.begin_preorder(), root);
    CHECK_EQ(*bt2.begin_inorder(), root);
    CHECK_EQ(*bt2.begin_postorder(), root);

    CHECK_THROWS(bt2.add_right(2,2));

    for (auto it = bt2.begin_preorder(); it != bt2.end_preorder(); ++it) 
    {
        CHECK_EQ(*it, root);
    }  
    for (auto it = bt2.begin_inorder(); it != bt2.begin_inorder(); ++it) 
    {
        CHECK_EQ(*it, root);
    } 
    for (auto it = bt2.begin_postorder(); it != bt2.end_postorder(); ++it) 
    {
        CHECK_EQ(*it, root);
    }  
}


TEST_CASE("simple iterating test")
{
    BinaryTree<int> bt;
    bt.add_root(1).add_left(1,2).add_right(1,3);
    int inorder[3] = {2, 1, 3};
    int idx = 0;
    for (const int& element: bt) 
    {  
        CHECK_EQ(element, inorder[idx++]);
    } 

    int post[3] = {2, 3, 1};
    idx = 0;
    for (auto it = bt.begin_postorder(); it != bt.end_postorder(); ++it) 
    {
        CHECK_EQ(*it, post[idx++]);
    }  


    BinaryTree<string> bts;
    bts.add_root("root").add_left("root", "left son").add_right("root", "right son").add_left("left son", "l l grand");
    string preorder[4] = {"root", "left son", "l l grand", "right son"};
    idx = 0;
    for (auto it = bts.begin_preorder(); it != bts.end_preorder(); ++it) 
    {
        CHECK_EQ(*it, preorder[idx++]);
    }
}


TEST_CASE("iterating tree with random numbers")
{
    BinaryTree<int> bt;
    int root = 1;
    bt.add_root(root);
    int arr[10];
    for(int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 20;
    }
    // for (auto i: arr)     
    // {    
    //     cout << i << ", ";    
    // }    
    // cout << endl;
    
    bt.add_left(root, arr[0]).add_right(root, arr[1]);
    bt.add_left(arr[0], arr[2]).add_right(arr[0], arr[3]);
    bt.add_left(arr[1], arr[4]).add_right(arr[1], arr[5]);
    bt.add_left(arr[2], arr[6]).add_right(arr[2], arr[7]);
    bt.add_left(arr[3], arr[8]).add_right(arr[3], arr[9]);

    int pre[11] = {root, arr[0], arr[2], arr[6], arr[7], arr[3], arr[8], arr[9], arr[1], arr[4], arr[5]};
    int idx = 0;
    for (auto it = bt.begin_preorder(); it != bt.end_preorder(); ++it) 
    {
        CHECK_EQ(*it, pre[idx++]);
    }  

    int in[11] = {arr[6], arr[2], arr[7], arr[0], arr[8], arr[3], arr[9], root, arr[4], arr[1], arr[5]};
    idx = 0;
    for (auto it = bt.begin_inorder(); it != bt.end_inorder(); ++it) 
    {
        CHECK_EQ(*it, in[idx++]);
    }

    int post[11] = {arr[6], arr[7], arr[2],arr[8], arr[9], arr[3], arr[0], arr[4], arr[5], arr[1], root};
    idx = 0;
    for (auto it = bt.begin_postorder(); it != bt.end_postorder(); ++it) 
    {
        CHECK_EQ(*it, post[idx++]);
    }  
}
