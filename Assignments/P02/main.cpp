/* Header files */
#include "timer.hpp"
#include <iostream>
#include <fstream>
#include<vector>
#include<iomanip>
using namespace std;


/**
 * wordNode
 *
 * Description:
 *      link list node
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class wordNode{

    public:
    string word;
    wordNode *next;


    // word - to store each word of dictionary
    // next - pointer to store the address of next node
};

/**
 * linkedList
 *
 * Description:
 *      link list class
 *
 * Public Methods:
 *      - constructor
 *      - add item
 *      - findResult
 *
 * Usage:
 *      - See main program
 *
 */
class linkedList
{
    private:
        wordNode *head,*tail;

    // head - pointer to store starting node of linked list
    // pointer to proceed in the link list

    public:
         /**
  * LinkedList
  *
  * Description:
  *      Constructor name param
  *
  * Params:
  *     - string name
  *
  * Returns:
  *     - NULL
  */
    linkedList()
    {
        head = NULL;
        tail = NULL;
    }

    /**
      * addNode
      *
      * Description:
      *      add names in the list
      *
      * Params:
      *     - string name
      *
      * Returns:
      *     - NULL
      */

    void addNode(string name)
    {
        wordNode *temp = new wordNode;
        temp->word = name;
        temp->next = NULL;

        if(head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }

    /**
      * findResult
      *
      * Description:
      *      -find the auto suggestion words
      *      - print the number of words found and time taken
      *      - return the auto-suggested words
      *
      * Params:
      *     - string name
      *
      * Returns:
      *     - vector of auto-suggested names
      */

    vector<string> findResult(string name)
    {

        // temp - temporary pointer to visit the list
        // result - vector to store the result
        // chack - string to store the current name to chack
        // count - int to count the number of times word occurs
        // size  - int to store the size of given word

        wordNode * temp = head;
        vector<string> result;
        string chack;
        int i,size,count;
        count =0;
        size = name.size();



        // creating a object of Timer
        // starting the timer
        Timer T;
        T.Start();



        // loop to get the first occurrence of given word
        while(temp!=NULL)
        {
            chack = temp->word;
            chack = chack.substr(0,size);

            if(name==chack) break;

            temp =temp->next;
        }


        //  storing first 10 names (if possible)
        for(i=0;i<10;i++)
        {
            chack = temp->word;
            if(name==chack.substr(0,size))
            {
                count++;
                result.push_back(chack);
            }
            else
            {
                break;
            }

            temp =temp->next;
        }

        // loop to find the count of all occurrence of given word
        while(temp!=NULL)
        {
            chack = temp->word;
            if(name == chack.substr(0,size)) count++;
            else break;

            temp = temp->next;
        }

        // ending the timer
        T.End();

        // calculating seconds taken
        double seconds = T.MilliSeconds();
        seconds = seconds/double(1000);

        // printing the result
        cout<<endl<<count<<" words found in "<<fixed<<setprecision(3)<<seconds<<" seconds\n"<<endl;
        return result;
    }

};


// main program
int main()
{
    // creating object of fstream
    // creating object of linkedList
    // defining a string
    // defining a vector to store result
    fstream newfile;
    linkedList myList;
    string name;
    vector<string> result;

    newfile.open("dictionary.txt",ios::in); //open a file to perform read operation using file object

    if (newfile.is_open())
    { //checking whether the file is open

        while(getline(newfile, name))  //read data from file object and put it into string.
        {
            myList.addNode(name);
        }
          newfile.close(); //close the file object.
   }

    // taking input
    cin>>name;

    // storing result by calling findResult function
    result =myList.findResult(name);

    // outputting the result
    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<"    ";
    }

}
// end of code