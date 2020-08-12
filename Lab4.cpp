//
//  main.cpp
//  Lab 4
//
//  Created by Amy Yu on 8/1/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

template <typename T>
struct TreeNode
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
};



template <typename T>
class balanceTree
{
public:
    void storeBSTNodes(TreeNode<T>* root, vector<TreeNode<T>*> &nodes)
    {
        // Base case
        if (root==NULL)
            return;
        
        // Store nodes in Inorder (which is sorted
        // order for BST)
        storeBSTNodes(root->left, nodes);
        nodes.push_back(root);
        storeBSTNodes(root->right, nodes);
    }
    
    /* Recursive function to construct binary tree */
    TreeNode<T>* buildTreeUtil(vector<TreeNode<T>*> &nodes, int start,
                        int end)
    {
        // base case
        if (start > end)
            return NULL;
        
        /* Get the middle element and make it root */
        int mid = (start + end)/2;
        TreeNode<T> *root = nodes[mid];
        
        /* Using index in Inorder traversal, construct
         left and right subtress */
        root->left  = buildTreeUtil(nodes, start, mid-1);
        root->right = buildTreeUtil(nodes, mid+1, end);
        
        return root;
    }
    
    // This functions converts an unbalanced BST to
    // a balanced BST
    TreeNode<T>* buildTree(TreeNode<T>* root)
    {
        // Store nodes of given BST in sorted order
        vector<TreeNode<T>*> nodes;
        storeBSTNodes(root, nodes);
        
        // Constucts BST from nodes[]
        int n = nodes.size();
        return buildTreeUtil(nodes, 0, n-1);
    }
    
    void print(TreeNode<T> *root)
    {
        if (root == NULL)  return;
        
        queue<TreeNode<T> *> q;
        
        q.push(root);
        
        while (true)
        {
            int count = q.size();
            if (count == 0)
                break;
            
            while (count > 0)
            {
                TreeNode<T> *node = q.front();
                q.pop();
                
                if (!node) {
                    cout << "-" << " ";
                } else {
                    cout << node->data << " ";
                    q.push(node->left);
                    q.push(node->right);
                }
                
                count--;
            }
            cout << endl;
        }
    }
    
    TreeNode<T>* newNode(T data)
    {
        TreeNode<T>* node = new TreeNode<T>;
        node->data = data;
        node->left = node->right = NULL;
        return (node);
    }
};

int main()
{
    balanceTree<int> x;
    TreeNode<int>* root = x.newNode(20);
/*    int arr[] = {18, 15, 10, 9, 8, 7, 6, 5};
    for (int i = 0; i < 8; i++)
    {
        root->left = x.newNode(arr[i]);
        root = root->left;
    } */
    root->left = x.newNode(18);
    root->left->left = x.newNode(15);
    root->left->left->left = x.newNode(10);
    root->left->left->left->left = x.newNode(9);
    root->left->left->left->left->left = x.newNode(8);
    root->left->left->left->left->left->left = x.newNode(7);
    root->left->left->left->left->left->left->left = x.newNode(6);
    root->left->left->left->left->left->left->left->left = x.newNode(5); 
    
    root = x.buildTree(root);
    
    x.print(root);
}
