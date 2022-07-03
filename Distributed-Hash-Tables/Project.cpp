#include "Machine.h"

//DISPLAY MENU FUNCTION WHICH IS PROMPTED EVERYTIME
int display_menu() {
    int num;
    cout << "Press 1 to add machine" << endl;
    cout << "Press 2 to remove a machine" << endl;
    cout << "Press 3 to add data in the form of (key,value) pair, from any machine" << endl;
    cout << "Press 4 to remove data by providing key from any machine" << endl;
    cout << "Press 5 to print the routing table of any machine" << endl;
    cout << "Press 6 to print AVL tree along with file location, line no and corresponding values" << endl;
    cout << "Press 7 to exit" << endl;
    cin >> num;
    return num;
}

int main() {
    //CLEARING UP THE FILE
    //ofstream outputFile;
    //outputFile.open("file0.txt");
    //outputFile.close();

    int identifier_bits;
    cout << "Enter the number of bits of identifier space?" << endl;    //ENTERING NUMBER OF IDENTIFIERS BITS
    cin >> identifier_bits;

    int max_number_of_machines;
    max_number_of_machines = pow(2, identifier_bits);            //MAXIMMUM NUMBER OF MACHINE THAT THE NETWORK CAN MANAGE

    //NUMBER OF MACHINES THAT USER WANT TO ENTER INTIALLY
    int number_of_machines;
    cout << "Enter the number of machines(Equal or Less than " << max_number_of_machines << ")" << endl;
    cin >> number_of_machines;

    //VALIDATION THAT NUMBER OF MACHINES ARE LESS THAN THE MAXIMUM NUMBER
    while (number_of_machines > max_number_of_machines) {
        cout << "Invalid Input" << endl;
        cin >> number_of_machines;
    }

    //ASKING USER FOR THE NUMBER OF MACHINES THAT USER WANT TO ASSIGN THE
    //ID MANUALLY
    int number_of_manual_id_machines;
    cout << "Enter the number of machines you want to assign ID manually" << endl;
    cin >> number_of_manual_id_machines;

    //VALIDATION
    while (number_of_manual_id_machines > number_of_machines && number_of_manual_id_machines < 0) {
        cout << "Invalid input" << endl;
        cin >> number_of_manual_id_machines;
    }

    //MAKING THE OBJECT OF CIRCUALR LINKED LIST
    Machine<string> Machine_Circular_Linked_List(identifier_bits, number_of_machines - number_of_manual_id_machines);
    
    string id;
    for (int i = 0; i < number_of_manual_id_machines; i++) {
        cout << "Enter id for the machine" << endl;
        cin >> id;
        Machine_Circular_Linked_List.set_machine_id(id);
    }

    //PROMPTING THE MENU TO PERFORM TASKS
    //UNTILL THE USER END IT
    while (true) {
        string key = "";
        string value = "";
        string id = "";
        char ans = '\0';
        switch (display_menu()) {
        case 1:
            cout << "Press Y to you want to allocate the ID else it will be done automatically: ";
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                cout << "Enter ID: ";
                cin >> id;
                Machine_Circular_Linked_List.set_machine_id(id);
            }
            else {
                Machine_Circular_Linked_List.automaticAllocationOfId();
            }
            cout << endl;
            Machine_Circular_Linked_List.display();//TO BE OMMITTED
            break;
        case 2:
            cout << "Enter the id of machine that you have to delete: ";
            cin >> id;
            Machine_Circular_Linked_List.delete_node(id);
            Machine_Circular_Linked_List.display();
            break;
        case 3:
            cout << "Enter the key: ";
            cin >> key;
            cout << "Enter the value: ";
            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, value);
            cout << "Enter Machine ID: ";
            cin >> id;
            Machine_Circular_Linked_List.insert_data(id, key, value);
            //Machine_Circular_Linked_List.displayAVL(id);
            break;
        case 4:
            cout << "Enter the key:";
            cin >> key;
            cout << "Enter the id of the machine: ";
            cin >> id;
            Machine_Circular_Linked_List.delete_data(id, key);
            //Machine_Circular_Linked_List.displayAVL(id);
            break;
        case 5:
            cout << "Enter the id of the machine: ";
            cin >> id;
            Machine_Circular_Linked_List.displayFT(id);
            break;
        case 6:
            cout << "Enter the id of the machine: ";
            cin >> id;
            Machine_Circular_Linked_List.displayAVL(id);
            break;
        case 7:
            return 0;
        }
    }
    return 0;
}