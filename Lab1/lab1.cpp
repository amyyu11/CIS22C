
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <array>
#include <string>

using namespace std;


const unsigned TABLE_SIZE = 512 * 1.25f;
static int maximum = TABLE_SIZE;

int getHash(string key)
{
    int sum = key[key.length()-1] - '0';    // uses sum of digits of ID
    for (int c = key.length()-2; c != key.length()-16; c--)
    {
        sum = sum + (key[c] - '0');
    }
    return sum % maximum;
}


class HashElement
{
private:
    int key = 0;
    string value = "";
    HashElement* next;
public:
    int used = 0;
    HashElement(int k=0, string v="")
    {
        key = k;
        value = v;
        next = nullptr;
    }
    void setValue(string v)
    {
        value = v;
    }
    int getKey()
    {
        return key;
    }
    string getValue()
    {
        return value;
    }
    HashElement *getNext()
    {
        return next;
    }
    void setNext(HashElement *next)
    {
        next = next;
    }
    operator int() { return getKey(); }
};

class linearProbing
{
    HashElement **table;
    int lpCollisions = 0;
public:
    linearProbing()
    {
        table = new HashElement*[TABLE_SIZE];   // creates array of linked list
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }
    
    string get(int key, string value)
    {
        int hash = getHash(value);
        while (table[hash]->getKey() != key && table[hash] != nullptr)
            hash = (hash + 1) % maximum;
        if (table[hash] == nullptr)
            return "empty";
        else
            return table[hash]->getValue();
    }
    
    void insert(int key, string value)
    {
        int hash = getHash(value);
        while (table[hash] != nullptr && table[hash]->getKey() != key)
            hash = (hash+1) % maximum;      // checks next bucket if not empty
        if (table[hash] != nullptr)
        {
            lpCollisions++;
            delete table[hash];
        }
        table[hash] = new HashElement(key, value);
        
        int test = table[hash]->getKey();
        if (test != hash)   // collision if new key does not equal original key
            lpCollisions++;

    }
    
    int getCollisions()
    {
        return lpCollisions;
    }
};

class Chaining
{
    int cCollisions = 0;
    HashElement **table;
public:
    Chaining()
    {
        table = new HashElement*[TABLE_SIZE];       // creates array of linked list
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }
  
    string get(int key, string value)
    {
        int hash = getHash(value);
        if (table[hash] == nullptr)
            return "empty";
        else {
            HashElement *entry = table[hash];
            while (entry != nullptr && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == nullptr)
                return "empty";
            else
                return entry->getValue();
        }
    }
    
    void insert(int key, string value) {
        int hash = getHash(value);
        if (table[hash] == nullptr)
            table[hash] = new HashElement(key, value);
        else {
            cCollisions++;  // collision if bucket is not empty
            HashElement *entry = table[hash];
            while (entry->getNext() != nullptr)
                entry = entry->getNext();

            if (entry->getKey() == key)
                entry->setValue(value);          // sets next element of linked list to value if there is a collision
            else
                entry->setNext(new HashElement(key, value));
        }
    }
    
    int getCollisions()
    {
        return cCollisions;
    }
};

class Resizing {
private:
    int rCollisions = 0;
    int startSize;
    int size;
    HashElement **table;
    
    void resize() {     // dynamic array
        int oldSize = startSize;
        startSize *= 2;
        HashElement **oldTable = table;
        table = new HashElement*[startSize];
        for (int i = 0; i < startSize; i++)
            table[i] = nullptr;
        size = 0;
        for (int hash = 0; hash < oldSize; hash++)
            if (oldTable[hash] != nullptr) {
                HashElement *oldEntry;
                HashElement *entry = oldTable[hash];
                while (entry != nullptr) {
                    insert(entry->getKey(), entry->getValue());
                    oldEntry = entry;
                    entry = entry->getNext();
                    delete oldEntry;
                }
            }
        delete[] oldTable;
    }
    
public:
    Resizing() {
        startSize = 10;
        table = new HashElement*[startSize];        // creates array of linked list
        for (int i = 0; i < startSize; i++)
            table[i] = nullptr;
    }
    
    string get(int key) {
        int hash = (key % startSize);
        if (table[hash] == nullptr)
            return "empty";
        else {
            HashElement *entry = table[hash];
            while (entry != nullptr && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == nullptr)
                return "empty";
            else
                return entry->getValue();
        }
    }
    
    void insert(int key, string value) {
        int hash = (key % startSize);
        if (table[hash] == nullptr) {
            table[hash] = new HashElement(key, value);
            size++;
        }
        else
        {
            rCollisions++;      // collision if bucket is not empty 
            HashElement *entry = table[hash];
            while (entry->getNext() != nullptr)
                entry = entry->getNext();
            if (entry->getKey() == key)
                entry->setValue(value);
            else {
                entry->setNext(new HashElement(key, value));
                size++;
            }
        }
        if (size >= startSize)
            resize();       // increases size of array
    }
    
    int getCollisions()
    {
        return rCollisions;
    }
    
};

int main()
{
    int count = 0;
    string elements[512];
    
    ifstream inputFile;
    inputFile.open("names.txt");
    
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        exit(1);
    }
    while(count < 512 && inputFile >> elements[count])
        count++;
    
    inputFile.close();
  
    linearProbing htable;
    Chaining htable2;
    Resizing htable3;
    for (int x=0; x<elements.size(); x++)
    {
        int hash = getHash(elements[x]);
        htable.insert(hash, elements[x]);
        htable2.insert(hash, elements[x]);
        htable3.insert(hash, elements[x]);
    }

    cout << "\nStatistics:" << endl;
    cout << "\tLinear Probing Collisions = " << (htable.getCollisions()) << endl;
    cout << "\tChaining Collisions = " << (htable2.getCollisions()) << endl;
    cout << "\tResizing Collisions = " << (htable3.getCollisions()) << endl;
}
