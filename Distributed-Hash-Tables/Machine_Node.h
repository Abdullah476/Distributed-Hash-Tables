#pragma once
#include "FT.h"
#include "Data_AVL_Tree.h"

//MACHINE NODES THAT ARE IN CIRCULAR LINKED LIST
//IT STORES THE OBJECT'S OF AVL TREE AND FT TABLE & KEY
template <class type>
class Machine_Node {
public:
    int key;                        //HASHING KEY
    Data_AVL_Tree<type> data;       //OBJECT AVL TREE THAT CONTAINS DATA
    FT<type> ft;                    //OBJECT OF FT TABLE CLASS
    Machine_Node* Next;
    //DEFAULT CONTRUCTOR
    Machine_Node() {                //CONSTRUCTOR
        key = -1;
        Next = NULL;
    }
    //PARAMETRIZED CONSTRUCTOR
    Machine_Node(int identifier_bits, int id) {
        key = -1;
        Next = NULL;
        ft.setFT(identifier_bits, id, Next);
    }
    //DATA IS INSERTED THROUGH THIS MACHINE
    //THEN DISTRIBUTED AND STORED AT THE RIGHT MACHINE
    void insert_data(int NodeID, type key, type value) {
        Machine_Node<type>* temp = ft.search(ft.succ2(NodeID, Next)->key, this);
        //cout << "TEMP KEY:" << temp->key << endl;
        temp->data.Insert_Data_Node(temp->data.getRoot(), key, value);
        temp->data.printInPreOrder(temp->data.getRoot());
    }
    //REQUEST TO DELETE DATA COMES HERE WITH THE KEY
    //RIGHT MACHINE IS IDENTIFIED AND THEN DATA IS DELETED
    void delete_data(int NodeID, type key) {
        Machine_Node<type>* temp = ft.search(ft.succ2(NodeID, Next)->key, this);
        temp->data.deleteAVLNode(temp->data.getRoot(), key);
        //cout << "AVL after deletion" << endl;
        temp->data.printInPreOrder(temp->data.getRoot());
    }

};
