//
//  lab5.cpp
//  Lab 5
//
//  Created by Amy Yu on 8/4/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#define V 12
using namespace std;

struct Node
{
    int val;
    int cost;
    Node* next;
};

template <typename T>
class DArray
{
    int cap;
    int size;
    T *arr;
    
public:
    T & operator[] (unsigned int i)
    {
        return arr[i];
    }
    
    void reserve(int n, bool copy)
    {
        T *newArr;
        int i;
        
        newArr = new T[n];
        
        if (copy)
            for(i = 0; i < size; i++)
                newArr[i] = arr[i];
        
        if (arr != NULL)
            delete [] arr;
        
        arr = newArr;
        cap = n;
    }
    
    void push_back(const T& item)
    {
        if (size == cap)
        {
            if (cap == 0)
                reserve(1,false);
            else
                reserve(2 * cap, true);
        }

        arr[size] = item;
        size++;
    }
};

template <typename T>
class DMatrix
{
    int row;
    int col;
    DArray<T>** arr;
public:
    DMatrix<T>()
    {
        row = V;
        col = V;
        DArray<T>** arr = new DArray<T>*[10];
        for (int i = 0; i < 10; i++)
            arr[i] = new DArray<T>[10];
    }
    
    DMatrix<T>(int r, int c)
    {
        row = r;
        row = c;
        DArray<T>** arr = new DArray<T>* [col];
        for (int i = 0; i < col; i++)
            arr[i] = new DArray<T>[row];
    }
    
    ~DMatrix()
    {
        DArray<T>** arr = new DArray<T>* [col];
        for (int i = 0; i < row; i++)
            delete [] &arr[i];
        delete [] arr;
    }
    
    T operator() (int rows, int cols)
    {
        return (arr[cols*row + col]);
    }
    
    DMatrix<T>& operator= (DMatrix<T> mat)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                mat(i,j) = 0;
        }
        return mat;
    }
};

template <typename T>
class adjacencyMatrix
{
    DMatrix<int> matrix;
    int count;
public:
    adjacencyMatrix()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
                matrix(i, j) = 0;
        }
        count = 0;
    }
    
    T getVal(int i, int j)
    {
        return matrix(i, j);
    }
    
    void displayMatrix(int v) {
        int i, j;
        for(i = 0; i < v; i++) {
            for(j = 0; j < v; j++) {
                cout << matrix(i, j) << " ";
            }
            cout << endl;
        }
    }
    void add_edge(int e, int v, int w) {
        matrix(e, v) = w;
        matrix(v, e) = w;
    }
};

struct Edge {
    int src, dest, weight;
};

class Graph
{
    Node* getNode(int value, int weight, Node* head)
    {
        Node* newNode = new Node;
        newNode->val = value;
        newNode->cost = weight;
        
        newNode->next = head;
        
        return newNode;
    }
    
    int N;
    
public:
    Node **head;
    
    Graph(DArray<Edge> edges, int n, int N)
    {
        head = new Node*[N]();
        this->N = N;
        
        for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        
        for (int i = 0; i < n; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;
            
            Node* newNode = getNode(dest, weight, head[src]);

            head[src] = newNode;
            newNode = getNode(src, weight, head[dest]);
            head[dest] = newNode;
        }
    }
    
    ~Graph() {
        for (int i = 0; i < N; i++)
            delete[] head[i];
        
        delete[] head;
    }
};

int main() {
    
    adjacencyMatrix<int> G;
    G.add_edge(0, 1, 1306);
    G.add_edge(1, 2, 629);
    G.add_edge(1, 3, 919);
    G.add_edge(2, 3, 435);
    G.add_edge(3, 4, 1225);
    G.add_edge(3, 5, 1983);
    G.add_edge(4, 5, 1258);
    G.add_edge(3, 4, 1225);
    G.add_edge(3, 5, 1983);
    G.add_edge(4, 6, 1483);
    G.add_edge(5, 6, 1532);
    G.add_edge(0, 6, 2661);
    G.add_edge(6, 7, 661);
    G.add_edge(7, 8, 1145);
    G.add_edge(5, 8, 2113);
    G.add_edge(8, 9, 1709);
    G.add_edge(9, 10, 2145);
    G.add_edge(10, 11, 338);
    G.add_edge(8, 10, 383);
    G.add_edge(8, 11, 725);
    G.add_edge(7, 11, 1613);
    
    int edge;
    int visit[V];
    
    for(int i = 0; i < V; i++)
    {
        visit[i]=false;
    }
    
    edge = 0;
    
    visit[0] = true;
    
    int x;
    int y;
    int weight = 0;

    cout << endl;
    while (edge < V - 1)
    {
        int min = 100000000;
        x = 0;
        y = 0;
        
        for (int i = 0; i < V; i++)
        {
            if (visit[i]) {
                for (int j = 0; j < V; j++)
                {
                    if (!visit[j] && G.getVal(i, j))
                    {
                        if (min > G.getVal(i, j))
                        {
                            min = G.getVal(i, j);
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        
        switch (x) {
            case 0:
                cout << "Seattle";
                break;
            case 1:
                cout << "San Francisco";
                break;
            case 2:
                cout << "Los Angeles";
                break;
            case 3:
                cout << "Las Vegas";
                break;
            case 4:
                cout << "Denver";
                break;
            case 5:
                cout << "Dallas";
                break;
            case 6:
                cout << "Minneapolis";
                break;
            case 7:
                cout << "Chicago";
                break;
            case 8:
                cout << "Washington DC";
                break;
            case 9:
                cout << "Miami";
                break;
            case 10:
                cout << "New York";
                break;
            case 11:
                cout << "Boston";
                break;
            default:
                break;
        }
        cout <<  " -> ";
        switch (y) {
        case 0:
            cout << "Seattle";
            break;
        case 1:
            cout << "San Francisco";
            break;
        case 2:
            cout << "Los Angeles";
            break;
        case 3:
            cout << "Las Vegas";
            break;
        case 4:
            cout << "Denver";
            break;
        case 5:
            cout << "Dallas";
            break;
        case 6:
            cout << "Minneapolis";
            break;
        case 7:
            cout << "Chicago";
            break;
        case 8:
            cout << "Washington DC";
            break;
        case 9:
            cout << "Miami";
            break;
        case 10:
            cout << "New York";
            break;
        case 11:
            cout << "Boston";
            break;
        default:
            break;
        }
        
        cout << " :  " << G.getVal(x, y);
        cout << endl;
        
        visit[y] = true;
        edge++;
        
        weight = weight + G.getVal(x, y);
    }
    
    cout << endl;
    cout << "Total Kilometers: " << weight << endl;
}


/*
 Output:
 
 Seattle -> San Francisco :  1306
 San Francisco -> Los Angeles :  629
 Los Angeles -> Las Vegas :  435
 Las Vegas -> Denver :  1225
 Denver -> Dallas :  1258
 Denver -> Minneapolis :  1483
 Minneapolis -> Chicago :  661
 Chicago -> Washington DC :  1145
 Washington DC -> New York :  383
 New York -> Boston :  338
 Washington DC -> Miami :  1709
 
 Total Kilometers: 10572
 
 */
