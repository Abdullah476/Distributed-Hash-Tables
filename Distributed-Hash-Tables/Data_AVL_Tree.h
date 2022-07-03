#pragma once
#include "Data_Node.h"
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<fstream>
#include"sha1.h"
#include<ctime>
#include<algorithm>
using namespace std;


//AN AVL TREE IMPLEMENTATION THAT STORES 
//DATA_NODES (SORT ON THE BASIS OF THE KEY)
template <class type>
class Data_AVL_Tree {
private:
    Data_Node<type>* root;
    int count;
    int line_no;
public:
    Data_AVL_Tree() {
        root = NULL;
        count = 0;
        line_no = 0;
    }
    Data_Node<type>*& getRoot() {
        return root;
    }
    //Calculating Height
    int Height(Data_Node<type>* node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }
    // Right Rotation
    Data_Node<type>* rightRotation(Data_Node<type>* L1) {
        Data_Node<type>* L2 = L1->left;
        Data_Node<type>* temp = L2->right;

        L2->right = L1;
        L1->left = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }
    // Left Rotation
    Data_Node<type>* leftRotation(Data_Node<type>* L1) {
        Data_Node<type>* L2 = L1->right;
        Data_Node<type>* temp = L2->left;

        L2->left = L1;
        L1->right = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }
    //RL Rotation
    Data_Node<type>* RLrotation(Data_Node<type>* L1) {
        L1->left = leftRotation(L1->left);
        return rightRotation(L1);
    }
    //LR Rotation
    Data_Node<type>* LRrotation(Data_Node<type>* L1) {
        L1->right = rightRotation(L1->right);
        return leftRotation(L1);
    }
    // Get balance factor
    int getBalanceFactor(Data_Node<type>* node) {
        if (node == NULL) {
            return 0;
        }
        return Height(node->left) - Height(node->right);
    }
    // Insert a AVLNode
    void Insert_Data_Node(Data_Node<type>*& node, type k, type value) {
        if (node == NULL) {
            node = new Data_Node<type>(k, value, getFile(), line_no);
            return;
        }
        else if (k < node->key) {
            Insert_Data_Node(node->left, k, value);
        }
        else if (k > node->key) {
            Insert_Data_Node(node->right, k, value);
        }
        else {
            return;
        }
        node->height = 1 + max(Height(node->left), Height(node->right));
        if (getBalanceFactor(node) > 1) {       //It means key is added to the left subtree
            if (k < node->left->key) {          //Due to insertion at left side of left subtree
                node = rightRotation(node);
                return;
            }
            else if (k > node->left->key) { //Due to insertion at right side of left subtree
                node = RLrotation(node);
                return;
            }
        }
        else if (getBalanceFactor(node) < -1) { //It means key is added to the right subtree
            if (k > node->right->key) {         //Due to insertion at right side of right subtree
                node = leftRotation(node);
                return;
            }
            else if (k < node->right->key) {        //Due  to insertion at left side of right subtree
                node = LRrotation(node);
                return;
            }
        }
        return;
    }
    // Getting Node with minimum value
    Data_Node<type>* AVLNodeWithMimumValue(Data_Node<type>* node) {
        Data_Node<type>* temp = node;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }
    //Deleting Node
    void deleteAVLNode(Data_Node<type>*& node, type k) {
        if (node == NULL) {
            return;
        }
        else if (k < node->key) {
            deleteAVLNode(node->left, k);
        }
        else if (k > node->key) {
            deleteAVLNode(node->right, k);
        }
        else {
            if (!node->left || !node->right) {
                Data_Node<type>* temp;
                if (node->left) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else {
                    *node = *temp;
                }
                cout << "Value being deleted: ";
                cout << temp->display_value() << endl;
                temp->remove_value();
                delete temp;
            }
            else {
                Data_Node<type>* temp = AVLNodeWithMimumValue(node->right);
                node->key = temp->key;
                deleteAVLNode(node->right, temp->key);
            }
        }
        if (node == NULL) {
            return;
        }
        node->height = 1 + max(Height(node->left), Height(node->right));
        if (getBalanceFactor(node) > 1) {
            if (getBalanceFactor(node->left) >= 0) {
                node = rightRotation(node);
                return;
            }
            else {
                node = RLrotation(node);
                return;
            }
        }
        else if (getBalanceFactor(node) < -1) {
            if (getBalanceFactor(node->right) <= 0) {
                node = leftRotation(node);
                return;
            }
            else {
                node = LRrotation(node);
                return;
            }
        }
        else {
            return;
        }
    }
    // Printing in Pre-Order
    void printInPreOrder(Data_Node<type>* AVLNode) {
        if (AVLNode == NULL) {
            return;
        }
        cout << AVLNode->file_name <<","<<AVLNode->line_no<< "->" << AVLNode->value << endl;

        printInPreOrder(AVLNode->left);
        printInPreOrder(AVLNode->right);
    }
    //getFileName
    type getFile() {
        if (line_no == 101) {
            line_no = 0;
            count++;
        }
        else {
            line_no++;
        }
        type str = "file";
        str += to_string(count);
        return str;
    }
    //
    void export_data(Data_AVL_Tree<type>& temp, Data_Node<type>* AVLNode) {
        if (AVLNode == NULL) {
            return;
        }
        //cout << AVLNode->file_name << "->" << AVLNode->display_value() << endl;
        temp.Insert_Data_Node(temp.getRoot(), AVLNode->key, AVLNode->value);

        export_data(temp, AVLNode->left);
        export_data(temp, AVLNode->right);

    }
};
