//
//  main.cpp
//  Lab 3
//
//  Created by Amy Yu on 7/26/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* next;
    TreeNode<T>* prev;
};


template <typename T>
class Queue
{
public:
    TreeNode<T>* head;
    TreeNode<T>* tail;
    int count = 0;
    
    void push(T data)
    {
        TreeNode<T>* temp = new TreeNode<T>;
        temp->data = data;
        temp->next = nullptr;
        temp->prev = tail;
        
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
        count++;
    }
    
    TreeNode<T>* pop()
    {
        TreeNode<T>* resultPtr = Search(head->data);
        if (resultPtr != nullptr)
        {
            TreeNode<T>* tempPrev = resultPtr->prev;
            TreeNode<T>* tempNext = resultPtr->next;
            tempPrev->next = tempNext;
            tempNext->prev = tempPrev;
            delete resultPtr;
            count--;
        }
        return head;
    }
    
    TreeNode<T>* Search(T data)
    {
        TreeNode<T>* temp = head;
        while (temp->data != data)
            temp = temp->next;
        if (temp == nullptr)
            return nullptr;
        else
            return temp;
    }
    
    int size()
    {
        return count;
    }
    
    T front()
    {
        return head->data;
    }
};

template <typename T>
class binaryTree
{
public:
    TreeNode<T>* newNode(int key)
    {
        TreeNode<T>* node = new TreeNode<T>;
        node->data = key;
        node->left = nullptr;
        node->right = nullptr;
        
        return node;
    }
    
    TreeNode<T>* insert(TreeNode<T>* root, T x)
    {
        
        if (root == nullptr)
        {
            TreeNode<T> * nnode = new TreeNode<T>;
            nnode->data = x;
            nnode->data = x;
            nnode->left = nullptr;
            nnode->right = nullptr;
            return nnode;
        }
        
        TreeNode<T> * cur = root;
        TreeNode<T> * ptr;
        while (cur != nullptr)
        {
            ptr = cur;
            if (x < cur->data)
                cur = cur->left;
            else
                cur = cur->right;
        }
        
        TreeNode<T>* node = new TreeNode<T>;
        node->data = x;
        node->left = nullptr;
        node->right = nullptr;
        if (x < ptr->data)
            ptr->left = node;
        else
            ptr->right = node;
        return root;
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
};

int main() {
    int elements[921];
    int count = 0;
    
    ifstream inputFile;
    inputFile.open("Numbers.txt");
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        exit(1);
    }
    while(count < 921 && inputFile >> elements[count])
        count++;
    
    inputFile.close();
    
    TreeNode<int> *root = nullptr;
    binaryTree<int> bst;
    
    for (int i = 0; i < 921; i++)
        root = bst.insert(root, elements[i]);
    TreeNode<int> *root = nullptr;

    int array[] = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
    binaryTree<int> bst;
    for (int i = 0; i < 10; i++)
       root = bst.insert(root, array[i]);
    
    bst.print(root);
    
}
