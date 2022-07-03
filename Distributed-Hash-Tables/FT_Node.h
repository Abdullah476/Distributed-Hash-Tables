#pragma once
#include"Machine_Node.h"
#include<string>
#include<iostream>
using namespace std;
template <class type>
class Machine_Node;
//FT NODE 
template <class type>
class FT_Node {
public:
    int count;//int
    int machine_id;
    Machine_Node<type>* machine_pointer;
    FT_Node<type>* Next;
    FT_Node<type>* Previous;
    FT_Node() {
        count = 0;
        machine_id = 0;
        machine_pointer = NULL;
        Next = NULL;
        Previous = NULL;
    }
};