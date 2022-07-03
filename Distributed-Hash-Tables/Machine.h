#pragma once
#include"Machine_Node.h"
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<fstream>
#include"sha1.h"
#include<ctime>
using namespace std;

SHA1 sha;


//MACHINE CLASS OF CIRCULAR LINKED LIST
template <class type>
class Machine {             //CIRCULAR SINGLY LINKED LIST IN WHICH MACHINE ARE CONNECTED TOGETHER
private:
    Machine_Node<type>* Head;
    int identifier_bits;
    Machine_Node<type>** array;
public:
    //DEFAULT CONTRUCTOR
    Machine() {
        Head = NULL;
        identifier_bits = 0;
        array = NULL;
    }
    Machine(int Identifier_bits, int number_of_mahines_with_automatic_allocation_of_ids) {
        Head = NULL;
        identifier_bits = Identifier_bits;

        int max_machines = pow(2, Identifier_bits);
        array = new Machine_Node<type>*[max_machines];
        for (int i = 0; i < max_machines; i++) {
            array[i] = NULL;
        }

        //AUTOMATIC ALLOCATION OF IDS
        for (int i = 0; i < number_of_mahines_with_automatic_allocation_of_ids; i++) {
            automaticAllocationOfId();
        }
    }
    //RETURNS IDENTIFIER BITS
    int get_identifier_bits() {
        return identifier_bits;
    }
    //INSERTS A MACHINE INTO THE NETWORK (CIRCULAR LINKED LIST)
    //MACHINES GET SORTED WHEN INSERTED
    Machine_Node<type>*& insert(int newVal) {
        Machine_Node<type>* newNode = new Machine_Node<type>;
        newNode->key = newVal;
        if (Head == NULL) {
            Head = newNode;
            newNode->Next = Head;
        }
        else {

            if (Head->Next == Head) {
                Head->Next = newNode;
                newNode->Next = Head;
                if (Head->key > newVal)
                    Head = newNode;
            }
            else {

                Machine_Node<type>* traversal = Head;
                do {
                    if (traversal->key > newVal)
                        break;
                    traversal = traversal->Next;
                } while (traversal != Head);

                if (traversal != Head) {
                    Machine_Node<type>* previous = Head;
                    while (previous->Next != traversal)
                        previous = previous->Next;
                    previous->Next = newNode;
                    newNode->Next = traversal;
                }
                else {
                    Machine_Node<type>* newLink = Head;
                    while (newLink->Next != Head)
                        newLink = newLink->Next;
                    newLink->Next = newNode;
                    newNode->Next = Head;
                    if (Head->key > newVal)
                        Head = newNode;
                }
            }

        }
        //ITIALISES THE VALUES OF THIS MACHINES FT_TABLE
        newNode->ft.setFT(identifier_bits, newVal, newNode->Next);
        populate_all_ft();//REPOPULATE ALL THE FT TABLES
        return newNode;
    }
    void delete_node(type id) {
        int value = get_ID(id);

        //VALIDATION
        while (array[value] == NULL) {
            cout << "Machine doesn't exist" << endl;
            cin >> id;
            value = get_ID(id);
        }

        Machine_Node<type>* temp = Head;
        while (temp->Next->key != value) {
            temp = temp->Next;
        }
        Machine_Node<type>* temp2 = temp->Next;
        temp->Next = temp->Next->Next;
        if (temp == Head) {
            Head = Head->Next;
        }

        import_data(temp2);
        array[temp2->key] = NULL;
        delete temp2;
        temp2 = NULL;
        populate_all_ft();
    }
    void import_data(Machine_Node<type>* temp) {
        Machine_Node<type>* node = Head->ft.succ2(temp->key, temp->Next);
        //cout << "NODE EXPORTED TO:" << node->key << endl;
        temp->data.export_data(node->data, temp->data.getRoot());
        //node->data.Insert_Data_Node(node->data.getRoot(),temp->);
    }
    bool isEmpty() {
        if (Head == NULL)
            return true;
        return false;
    }
    //DISPLAY ALL THE NODES IN THE NETWORK
    void display() {
        Machine_Node<type>* temp = Head;
        do {
            cout << "ID:" << temp->key << endl;
            temp->ft.display();
            cout << "----------------" << endl;
            temp = temp->Next;
        } while (temp != Head);
    }
    void automaticAllocationOfId() {
        int id;
        int max_machines = pow(2, identifier_bits);
        srand(time(NULL));
        while (true) {
            id = rand() % max_machines - 1;
            if (array[id] == NULL) {
                array[id] = insert(id);
                break;
            }
        }
        import_data(array[id]->Next);
    }
    void set_machine_id(type machine_key) {
        int id = get_ID(machine_key);
        while (array[id] != NULL) {
            cout << "ID already allocated try again" << endl;
            cin >> machine_key;
            id = get_ID(machine_key);
        }
        cout << "ID:" << id << endl;
        array[id] = insert(id);
        import_data(array[id]->Next);
    }
    //POPULATE THE GIVEN ROUTING TABLE
    void populate_ft(Machine_Node<type>*& node) {
        node->ft.populate_FT(node->Next);
    }
    //POPULATE ALL THE ROUTING TABLE'S IN THE NETWORK
    void populate_all_ft() {
        Machine_Node<type>* temp = Head;
        do {
            populate_ft(temp);
            temp = temp->Next;
        } while (temp != Head);

    }
    //GETTING ID FROM THE KEY WITHIN THE RANGE
    int get_ID(type key) {
        string hash = sha(key);
        unsigned long long int total = 0, power = 1;
        for (int idx = 7; idx >= 0; idx--) {
            if (hash[idx] >= '0' && hash[idx] <= '9') {
                total += (hash[idx] - 48) * power;
            }
            else if (hash[idx] >= 'a' && hash[idx] <= 'f') {
                total += (hash[idx] - 87) * power;
            }
            power *= 16;
        }
        int nodeID = total % static_cast<int>(pow(2, identifier_bits));
        return nodeID;
    }
    //FUNCTION THAT IS CALLED TO ADD DATA
    void insert_data(type machine_key, type key, type value) {
        int nodeID = get_ID(key);
        int machine = get_ID(machine_key);
        //cout << "NodeID:" << nodeID << endl;
        array[machine]->insert_data(nodeID, sha(key), value);
        // NodeID is captured from first twelve characters of SHA1 hash
        // use that NodeID to traverse to said machine (or succeeding machine that has the node of machine for insertion)
        // store value with key inside said machine 
    }
    void delete_data(type machine_key, type key) {
        int nodeID = get_ID(key);
        int machine = get_ID(machine_key);
        while (array[machine]==NULL) {
            cout << "Machine doesn't exist, try again" << endl;
            cin >> machine_key;
            machine = get_ID(machine_key);
        }
        array[machine]->delete_data(nodeID, sha(key));
    }
    void displayAVL(type machine_id_key) {
        int machine_id = get_ID(machine_id_key);
        while (array[machine_id] == NULL) {
            cout << "Machine doesn't exist, try again" << endl;
            cin >> machine_id_key;
            machine_id = get_ID(machine_id_key);
        }
        //cout << "CHECK:" << array[machine_id]->key << endl;
        array[machine_id]->data.printInPreOrder(array[machine_id]->data.getRoot());
        cout << endl;
    }
    void displayFT(type machine_id_key) {
        int machine_id = get_ID(machine_id_key);
        while (array[machine_id] == NULL) {
            cout << "Machine doesn't exist, try again" << endl;
            cin >> machine_id_key;
            machine_id = get_ID(machine_id_key);
        }
        array[machine_id]->ft.display();
    }
};