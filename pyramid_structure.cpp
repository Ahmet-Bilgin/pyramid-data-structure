// Pyramid Data Structure
// Author: Ahmet Bilgin
// Language: C++
// Description: Custom pyramid structure using linked lists

#include <iostream>
using namespace std;

//Pyramid Struct's Node
struct Node {
char data;
Node* right;

Node(char d) :data (d),right (NULL){}

};

//Pyramid Function
void add(Node*& head,char c){
//If the list is empty choose the new node head    
    if(head==NULL){ 
        head= new Node (c);
        return;
    }

    Node* tail=head;
//Find the Last node     
    while (tail->right)
    tail = tail->right;
//Connect Last node's pointer to new node
    tail->right = new Node(c);
}

//Showing the Pyramid
void printpyramid(Node** rows, int rowCount){
    cout<<"\n Pyramid Structure \n";

    //Traversal between every row
    for(int i=0; i<rowCount; i++){
        Node* current=rows[i];
    
    //Traversal between every node on a row
        while (current !=NULL)
        {
            cout<<current->data<<" ";
            current= current->right;
        }
        cout<<endl;    
    }
}

//Printing Inorderly
void printinorder(Node** rows, int rowCount){
    cout << "\n Print inorder \n";

    for (int i = 0; i<rowCount; i++) {
    Node* current = rows[i];
        while (current) {
        cout << current->data << " ";
        current = current->right;
        }
    }
    cout << endl;
}

//Printing Column
void printcolumn(Node** rows, int rowCount){
    cout<<"\n Column print \n";  
    //Holding the longest row's length
    int maxrowlength=0;

    //Finding the longest row
    for (int i = 0; i < rowCount; i++) {
    int length = 0;
    Node* current = rows[i];
    
    //Traversal between every node on a row
    while (current !=NULL) {
        length++;
        current = current->right;
    }

    //If the other row is longer change it to longest
    if (length > maxrowlength) {
        maxrowlength = length;
    }
    }

    // Printing column by column 1D
    for (int c = 0; c < maxrowlength; c++) {
        for (int r = 0; r < rowCount; r++) {
            Node* current = rows[r];
            int column = 0;

            //In r. row move to c. columm
            while (current && column < c) {
                current = current->right;
                column++;
            }

            //If there is a c. column print
            if (current)
                cout << current->data << " ";
        }
    }
    cout << endl;

}

void printpriority(Node** rows, int rowCount){
    cout << "\n Print by priority \n";
    int maxpriority = 0;

    // Find max priority
        for (int i = 0; i < rowCount; i++) {
        int j = 0;                         
        Node* current = rows[i];          

        while (current != NULL) {
        int priority = i + j;          // Priority = row + column

        if (priority > maxpriority) {
            maxpriority = priority;
        }
        current = current->right;      
        j++;                            
        }
    }
        // Print by priority
        for (int p = 0; p <= maxpriority; p++) {          
            for (int i = 0; i < rowCount; i++) {          
        int j = 0;                                
        Node* current = rows[i];                  

        // Traversal between every node in row
        while (current != NULL) {

            //if priority equal p value print
            if (i + j == p)
                cout << current->data << " ";

            current = current->right;             
            j++;                                  
            }
        }
    }
    cout << endl;
    }

//Searching Index
bool search(Node** rows, int rowCount, char target){
    //Traversal between every row
    for (int i = 0; i < rowCount; i++) {
        int column = 0;
       
        Node* current = rows[i];
        
        //Traversal between every node in a row
        while (current !=NULL) {

        //If the value found print
        if (current->data == target) {
        cout << "value found at " << i<<". row , ";
        cout <<column<<". column , ";
        cout << " Priority value: " << i + column << endl;
        return true;
        }

    column++;
    current = current->right;
    }

    }
    //If the value is not found print
    cout << "\n There is not "<< target<< " in pyramid "<<endl;
    return false;   
} 

//Check proper
bool isproper(Node** rows, int rowCount){
    int prevrowCount = 0;                     

    //Traverse all rows
    for (int i = 0; i < rowCount; i++) {
        int count = 0;                  
        Node* current = rows[i];          

        //Count nodes in the current row
        while (current != NULL) {
            count++;                     
            current = current->right;     
        }

        //For proper each row have one more element than the previous row
        if (i > 0 && count != prevrowCount + 1)
            return false;   //Pyramid structure is not proper

        prevrowCount = count;                
    }

    return true;            //Pyramid structure is proper
}


//Removes a node from a single row  and returns the removed node without deleting
Node* deleterow(Node*& head, char value){

    //If the row is empty, nothing to delete
    if (head == NULL)
        return NULL;

    //If the first node contains the value
    if (head->data == value) {
        Node* removedNode = head;   //Store the node to be removed
        head = head->right;     //Update head to the next node
        return removedNode;     //Return removed node 
    }

    Node* previous = head;  //Pointer to previous node
    Node* current = head->right;    //Pointer to current node

    //Traverse the linked list
    while (current != NULL) {

        //If the target value is found
        if (current->data == value) {
            previous->right = current->right;
            return current;                   
        }

        previous = current;             
        current = current->right;       
    }

    //Value not found in this row
    return NULL;
}


//Searches all rows and deletes 
void deletenode(Node** rows, int rowCount, char value){

    //Traverse each row in the pyramid
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {

        //Try to delete the node from the current row
        Node* removedNode = deleterow(rows[rowIndex], value);

        //Remove node
        if (removedNode != NULL){
            delete removedNode;           
            cout << "Element deleted (Row: " << rowIndex << ")\n";
            return;                       
        }
    }

    //Value not found in any row
    cout << "Element to delete was not found.\n";
}

//Add a new element
void addlater(Node** rows, int rowCount, int rowIndex, char value){
    //Check row index 
    if (rowIndex < 0 || rowIndex >= rowCount) {
    cout << "Invalid row index.\n";
    return;
    }
    
    add(rows[rowIndex], value);
    cout<<"Element added to row "<< rowIndex<<endl;
}

int main(){

    int rowCount;
    cout<<"Enter number of rows: ";
    cin>>rowCount;

    //Create dynamic array of row heads
    Node** rows = new Node*[rowCount];

    //Make rows empty
    for (int i = 0; i < rowCount; i++) {
        rows[i] = NULL;
    }

    //Initial pyramid creation
    for (int i = 0; i < rowCount; i++) {
        int elementCount;
        cout << "How many elements in row " << i << "? ";
        cin >> elementCount;

        cout << "Enter elements: ";
        for (int j = 0; j < elementCount; j++) {
            char value;
            cin >> value;
            add(rows[i], value);
        }
    }

    //Print pyramid in different ways
    printpyramid(rows, rowCount);
    printinorder(rows, rowCount);
    printcolumn(rows, rowCount);
    

    if (!isproper(rows, rowCount))
    printpriority(rows, rowCount);

    //Check if pyramid is proper
    if (isproper(rows, rowCount))
        cout << "\nPyramid is proper\n";
    else
        cout << "\nPyramid is NOT proper\n";

    //Search operation
    char searchValue;
    cout << "\nEnter value to search: ";
    cin >> searchValue;
    search(rows, rowCount, searchValue);

    //Delete operation
    char deleteValue;
    cout << "\nEnter value to delete: ";
    cin >> deleteValue;
    deletenode(rows, rowCount, deleteValue);

    //Print pyramid after deletion
    printpyramid(rows, rowCount);

    //Add later operation
    int targetRow;
    char newValue;
    cout << "\nEnter row index to add new element: ";
    cin >> targetRow;
    cout << "Enter value to add: ";
    cin >> newValue;

    addlater(rows, rowCount, targetRow, newValue);

    //Print pyramid after adding
    printpyramid(rows, rowCount);

    return 0;
}



