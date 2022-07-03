#pragma once
#include"FT_Node.h"
#include"Machine_Node.h"
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;


//FT(ROUNTING TABLE) IS MAITAINED AT EVERY MACHINE
//IT IS MAINTAINED ACCORDING TO THE GIVEN SPECIFICATION
template <class type>
class FT {
private:
    FT_Node<type>* head;            //HEAD OF DOUBLY LINKED LIST
    int count;                      //COUNT VARIABLE THAT MAITAINS THE COUNT
    int id;                         //ID OF THE CORESSDONDING MACHINE
    int identifier_bits;            //IDENTIFIER BITS (NUMBER OF INSERTIONS)
    Machine_Node<type>* Next;       //NEXT FT_NODE
public:
    //DEFAULT CONTRUCTOR
    FT() {
        head = NULL;
        count = 1;
        id = 0;
        Next = NULL;
        identifier_bits = 0;
    }
    //SETTER FUNCTION TO SET THE VALUES OF ID, IDENTIFIER AND NEXT POINTER
    void setFT(int identifier_bits_, int id_, Machine_Node<type>*& Next_) {
        head = nullptr;
        Next = Next_;
        count = 1;
        identifier_bits = identifier_bits_;
        id = id_;
    }
    //TO INSERT FT NODE
    void insert(Machine_Node<type>* machine_pointer) {
        if (count > identifier_bits) {
            return;
        }
        FT_Node<type>* NewNode = new FT_Node<type>;
        NewNode->machine_id = machine_pointer->key;
        NewNode->machine_pointer = machine_pointer;
        NewNode->count = count;

        if (head == NULL) {
            head = NewNode;
            head->Next = NULL;
            head->Previous = NULL;
        }
        else {
            FT_Node<type>* temp = head;
            while (temp->Next != NULL) {
                temp = temp->Next;
            }
            temp->Next = NewNode;
            NewNode->Previous = temp;
            NewNode->Next = NULL;
        }
        count++;
    }
    //TO DELETE FT NODE
    void delete_node(type machine_id) {
        FT_Node<type>* temp = head;
        while (temp->machine_id != machine_id) {
            temp = temp->Next;
        }
        temp->Previous->Next = temp->Next;
        temp->Previous->Next->Previous = temp;
        delete temp;
    }
    //TO POPULATE FT TABLES OF MACHINE
    void populate_FT(Machine_Node<type>* next) {
        makeEmpty();
        this->Next = next;
        for (int i = 0; i < identifier_bits; i++) {
            insert(succ(id, Next));
        }
    }
    //RETURNS THE SUCCESOR OF A MACHINE ID (USED IN INSERTION)
    Machine_Node<type>* succ(int id, Machine_Node<type>* Next) {
        int num = id + pow(2, count - 1);
        if (num > (pow(2, identifier_bits))) {
            num = num % (static_cast<int>(pow(2, identifier_bits)));
        }
        Machine_Node<type>* temp = Next;

        while (true) {
            if (temp->key == temp->Next->key) {
                break;
            }
            else if (num < id) {
                while (temp->key < temp->Next->key) {
                    temp = temp->Next;
                }
                temp = temp->Next;
                while (temp->key < num) {
                    temp = temp->Next;
                }
                break;
            }
            else if (temp->key >= num) {
                break;
            }
            else if (temp->key > temp->Next->key) {
                temp = temp->Next;
                break;
            }
            temp = temp->Next;
        }
        return temp;
    }
    //DISPLAY THE VALUES OF FT TABLE
    // COUNT : MACHINE ID
    void display() {
        FT_Node<type>* temp = head;
        while (temp != NULL) {
            cout << temp->count << ":" << temp->machine_id << endl;
            temp = temp->Next;
        }
    }
    //TO DELETE ALL THE FT TABLES OF A MACHINE
    void makeEmpty() {
        while (head != NULL) {
            FT_Node<type>* temp = head;
            head = head->Next;
            delete temp;
            count--;
        }
    }
    //GETTER FUNTION OF MACHINE
    int get_identifier_bits() {
        return identifier_bits;
    }
    //RETURN A NODE OF THE SUCCESSOR
    Machine_Node<type>* succ2(int id_, Machine_Node<type>* Next) {
        int num = id_;
        Machine_Node<type>* temp = Next;
        while (true) {
            if (temp->key == temp->Next->key) {
                break;
            }
            else if (num < id) {
                while (temp->key < temp->Next->key) {
                    temp = temp->Next;
                }
                temp = temp->Next;
                while (temp->key < num) {
                    temp = temp->Next;
                }
                break;
            }
            else if (temp->key >= num) {
                break;
            }
            else if (temp->key > temp->Next->key) {
                temp = temp->Next;
                break;
            }
            temp = temp->Next;
        }
        return temp;

    }
    //SEARCH FUNCTION THAT WORKS BASED ON THE SPECIFICATIONS
    Machine_Node<type>* search(int key, Machine_Node<type>* node) {
        //cout << "KEY" << key << endl;
        if (key == id) {
            return node;
        }
        else if (key > id && key <= head->machine_id) {
            cout << "Jumped to:" << head->machine_id << endl;
            return head->machine_pointer->ft.search(key, head->machine_pointer);
        }
        else {
            FT_Node<type>* temp = head;
            for (int i = 0; i < (identifier_bits - 1); i++) {
                if (temp->machine_id < key && temp->Next->machine_id >= key) {
                    cout << "Jumped to:" << temp->machine_id << endl;
                    return temp->machine_pointer->ft.search(key, temp->machine_pointer);
                }
                temp = temp->Next;
            }
            cout << "Jumped to:" << temp->machine_id << endl;
            return temp->machine_pointer->ft.search(key, temp->machine_pointer);
        }

    }
};