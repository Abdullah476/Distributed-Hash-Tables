//DATA NODE THAT STORES THE FILENAME AND LINE NO
//WHERE DATA IS SAVED
#include<fstream>
using namespace std;
template <class type>
class Data_Node {
public:
    type key;               //SHA KEY THAT IS STORED
    type file_name;         //FILE WHERE THE DATA IS STORED
    type value;
    int line_no;            //LINE NO WHERE THE DATA IS STORED
    int height;             //HEIGHT OF THE NODE (USED IN THE IMPLENTATION OF THE AVL)
    Data_Node<type>* left;  //LEFT NODE OF THE AVL NODE
    Data_Node<type>* right; //.RIGHT NODE OF THE AVL NODE

    Data_Node(type key, type value, type file_name, int line_no) {
        this->key = key;
        this->file_name = file_name;
        this->line_no = line_no;
        this->value = value;
        height = 1;
        left = NULL;
        right = NULL;
        

        //WRITING THE VALUE THAT IS TO BE STORED
        ofstream outputFile;
        outputFile.open(file_name + ".txt", ios_base::app);
        outputFile << value << endl;
        outputFile.close();
    }

    type display_value() {
        type value;
        ifstream inputFile;
        inputFile.open(file_name + ".txt");
        for (int i = 0; i < line_no; i++) {
            getline(inputFile, value);
        }
        inputFile.close();
        return value;
    }

    void remove_value() {
        type value = "";
        fstream outputFile;
        outputFile.open(file_name + ".txt", ios::out | ios::app);
        for (int i = 0; i < line_no; i++) {
            getline(outputFile, value);
            cout << "value:" << value << endl;
        }
        outputFile << " ";
        outputFile.close();
    }
};