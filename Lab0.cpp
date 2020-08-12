//
//  Lab0.cpp
//  Lab 0
//
//  Created by Amy Yu on 7/2/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <array>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template <typename T>
class DList
{
public:
    Node<T>* head;
    Node<T>* tail;
    
    T getData(Node<T>* ptr)
    {
        return (ptr->data);
    }
   
    void Append(T data)
    {
        Node<T>* temp = new Node<T>;
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
    }
    void Prepend(T data)
    {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->prev = nullptr;
        temp->next = head;
        
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            head->prev = temp;
            head = head->prev;
        }
    }
    
    void InsertAfter(T before, T data)
    {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        
        Node<T>* resultPtr = Search(before);
        
        if (resultPtr != nullptr)
        {
            temp->prev = resultPtr;
            temp->next = resultPtr->next;
            resultPtr->next = temp;
            temp->prev = resultPtr;
        }
    }
    
    void Remove(T data)
    {
        Node<T>* resultPtr = Search(data);
        if (resultPtr != nullptr)
        {
            Node<T>* tempPrev = resultPtr->prev;
            Node<T>* tempNext = resultPtr->next;
            tempPrev->next = tempNext;
            tempNext->prev = tempPrev;
            delete resultPtr;
        }
    }
    
    Node<T>* Search(T data)
    {
        Node<T>* temp = head;
        while (temp->data != data)
            temp = temp->next;
        if (temp == nullptr)
            return nullptr;
        else
            return temp;
    }
    
    bool IsEmpty()
    {
        if (head == nullptr)
            return true;
        else
            return false;
    }
    
    int GetLength()
    {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }
    
    void Print(Node<T>* ptr)
    {
        Node<T>* temp = ptr;
        if (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->next;
            Print(temp);
        }
    }
    
    void PrintReverse(Node<T>* ptr)
    {
        Node<T>* temp = ptr;
        if (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->prev;
            PrintReverse(temp);
        }
    }
};

template <typename T>
class Stack : public DList<T>
{
    Node<T>* top;
    Node<T>* bottom;
public:
    Stack() : DList<T>() { }
    void Push(T data)
    {
        Stack s;
        s.Prepend(data);
    }
    
    Node<T>* Pop()
    {
        Stack s;
        s.Remove(top);
        return top;
    }
};

template <typename T>
class Queue : public DList<T>
{
public:
    Node<T>* front;
    Node<T>* end;

    Queue() : DList<T>() {}
    
    void Enqueue(T data)
    {
        Queue q;
        q.Append(data);
    }
    
    Node<T>* Dequeue()
    {
        Queue q;
        q.Remove(front);
        return front;
    }
};


int main()
{
    DList<int>* list = new DList<int>;
    array<int, 10> arr = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
    
    cout << "Append:" << endl;
    for (int x = 0; x < arr.size(); x++)
        list->Append(arr[x]);   // tests Append and creates LinkedList
    list->Print(list->head);    // tests print
    
 /*   cout << "Prepend: " << endl;
    for (int x = 0; x < arr.size(); x++)
        list->Prepend(arr[x]);  // tests Prepend
     list->Print(list->head); */
    
    cout << "Insert After:" << endl;
    list->InsertAfter(68, 100);
    list->Print(list->head);

    cout << "Remove:" << endl;
    list->Remove(100);  // tests Remove
    list->Print(list->head);
    
    cout << "Search:" << endl;
    Node<int>* result = list->Search(68);
    cout << list->getData(result) << endl;  // tests Search
    
    cout << "IsEmpty?" << endl;
    if (list->IsEmpty() == true)    // tests IsEmpty
        cout << "true" << endl;
    else
        cout << "false" << endl;
    
    cout << "GetLength?" << endl;
    cout << list->GetLength() << endl;  // tests GetLength
    
}
