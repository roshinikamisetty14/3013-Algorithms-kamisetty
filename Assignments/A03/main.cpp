#include <iostream>

using namespace std;

//Initialize an array of size 100
int A[100];

//Create a linked list node
struct Node {

	//Initialize a variable x	
    int x;
	//Indicates the next item in the list
    Node *next;

	// Default structure node
    Node() {
		 // Assign value -1 to x
        x = -1;
		 // Set next node to null
        next = NULL;

    }
	
 	// Parameterized structure node
    Node(int n) {
		 // Assign value n to x
        x = n;
		 // Set next.node value to null
        next = NULL;

    }

};



// Create a class List
class List {

private:

	// Initialize a variable head node
    Node *Head;
	// Initialize a variable tail node
    Node *Tail;
	// Initialize a variable list
    int Size;




public:

    List() {
		// Set values of head and tail node to null
        Head = Tail = NULL;
		// Set initial size as 0
        Size = 0;

    }




    void Push(int val) {

        // allocate new memory and init node

        Node *Temp = new Node(val);


			// Check if the curreny node is Head node or a tail node if it is not a head node or a tail node then allocate the node value to the Temp value

        if (!Head && !Tail) {

            Head = Tail = Temp;

        } 
        // If the current node is a Tail node then next next node 
        else {
            Tail->next = Temp;
            Tail = Temp;

        }
		// Increment size by 1
        Size++;

    }




    void Insert(int val) {

        // allocate new memory and init node

        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;

			// Set Head node to temp
        Head = Temp;

		//Chrcks if the node is the Tail node
        if (!Tail) {
				// set Tail node as head node
            Tail = Head;

        }
			// increment size by 1
        Size++;

    }



	// Method to print the Til node
    void PrintTail() {
			
   			// print the value of Tail
        cout << Tail->x << endl;

    }



	// Method to retrieve the linked list
    string Print() {
			
   				// Set Current node to Head node
        Node *Temp = Head;
			// Initialize a variable list of type String
        string list;
		
  		// Iterate through the list
        while (Temp != NULL) {
				
    		// Add elements into the list
            list += to_string(Temp->x) + "->";

			// Move to the next node
            Temp = Temp->next;

        }
			// returns the linked list
        return list;

    }
    // not implemented

    int Pop() {
			
   			// Decrement the size of the list if an element is deleted
        Size--;

        return 0; //

    }




    List operator+(const List &Rhs) {

        // Create a new list that will contain both when done

        List NewList;

        // Get a reference to beginning of local list

        Node *Temp = Head;




        // Loop through local list and Push values onto new list

        while (Temp != NULL) {

				// Add the Temp valur to the list at the current node
            NewList.Push(Temp->x);
				// Set temp to next node to insert the next element into the list
            Temp = Temp->next;

        


        // Get a reference to head of Rhs

        Temp = Rhs.Head;

        // Same as above, loop and push

        while (Temp != NULL) {
        
        		// Add an element into the list

            NewList.Push(Temp->x);

            Temp = Temp->next;

        }

        // Return new concatenated version of lists

        return NewList;

    }




    // Implementation of [] operator.  This function returns an

    // int value as if the list were an array.

    int operator[](int index) {

		// Set Temp node to Head node
        Node *Temp = Head;
		
			// Checks the condition if index is greater than the size it returns Index out of bound
        if (index >= Size) {

            cout << "Index out of bounds, exiting";

            exit(0);

        } else {
            for (int i = 0; i < index; i++) {

                Temp = Temp->next;

            }

            return Temp->x;

        }

    }




    friend ostream &operator<<(ostream &os, List L) {

        os << L.Print();

        return os;

    }

};




int main(int argc, char **argv) {

	// Declare two lists L1 and L2
    List L1;

    List L2;



	// Interate 25 times through the list and add an element into list L1
    for (int i = 0; i < 25; i++) {

        L1.Push(i);

    }



	// Iterate 50 times and insert the elements into list L2
    for (int i = 50; i < 100; i++) {

        L2.Push(i);

    }




    // Print the last elemenet in list L1

    L1.PrintTail();
     // Print the last elemenet in list L2

    L2.PrintTail();



	// add ekements of list L1, list L2 and put them in a list L3
    List L3 = L1 + L2;

    cout << L3 << endl;
    cout << L3[5] << endl;

    return 0;

}
