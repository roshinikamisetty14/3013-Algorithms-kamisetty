/* Header files */
#include "timer.hpp"
#include <iostream>
#include <fstream>
#include<vector>
#include<iomanip>
using namespace std;


/**
 * trieNode
 *
 * Description:
 *      trie data structure node
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class trieNode{

    public:
    char c;
    trieNode *child[26];
    int prefixCounter;


    // c - to store each char 
    // child - pointer arr to store the address of child nodes
    
    public:
    // constructors to store NULL in all child pointers
    trieNode()
    {
        for(int i=0;i<26;i++)
        {
            child[i] =NULL;
        }
    }        
};

/**
 * TrieDataStr
 *
 * Description:
 *      Trie data structure class
 *
 * Public Methods:
 *      - constructor
 *      - add word
 *      - findResult
 *
 * Usage:
 *      - See main program
 *
 */
class TrieDataStr
{
    private:
        trieNode *root;

    // root - pointer to store starting node of Trie Data structure

    public:
    /**
     * TrieDataStr
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
    TrieDataStr()
    {
        root = new trieNode;

        // store null in all the child pointers
        for(int i=0;i<26;i++)
        {
            root->child[i] =NULL;
        }
    
    }

    
    /**
     * addWord
     *
     * Description:
     *      Add the given word in the trie data structure
     *
     * Params:
     *     - string name
     *
     * Returns:
     *     - NULL
     */
    
    void addWord(string name)
    {
        trieNode *temp;    // creating pointer object of class trieNode

        //initalizing variables
        char ch;
        int index;
        int size;
        
        // calculating size of given name
        size = name.size();
        temp =root;
        

        // for loop to insert the whole name in the word one by one char
        for(int i=0;i<size;i++)  
        {
            // storing each char
            ch = name[i];
            // finding the index value of char
            // 97 is the ascie value of a so range of index is(0,25)
            index = int(ch) - 97;
            

            // if the child node is null
            if(temp->child[index]==NULL)
            {
                // create a new object of triNode and store it
                trieNode *newNode = new trieNode;
                
                // storing ch into the newNode
                newNode->c = ch;
                
                // assigning prefixCounter to 1
                newNode->prefixCounter = 1;

                // assigning the newNode to the empty child
                temp->child[index] = newNode;
            }

            // else increment the prefixCounter
            else
            {
                temp->child[index]->prefixCounter +=1;
            }
           
            // increment the pointer
            temp =temp->child[index];
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
        // temp - temporary pointer to visit the trie
        // result - vector to store the result
        // count - store the count the occurrence
        // size  - int to store the size of given word
        // i,j - variables to use in loop
        // index - temp variables
        // ch - charector variable
        //word - temperary variable to store the current word

        trieNode * temp = root;
        vector<string> result;
        char ch;
        string word;
        int i,j,size,count,index;
        count =0;
        size = name.size();
        
        word = name;


         // creating a object of Timer
        // starting the timer
        Timer T;
        T.Start();

        // code to count the words with given prefix

        // loop to search each char of name
        for(int i=0;i<size;i++)
        {
            // char storing
            ch = name[i];
            
             // finding the index value of char
            // 97 is the ascie value of a so range of index is(0,25)
            index = int(ch) - 97;
            
            // if char not found
            if(temp->child[index]==NULL)
            {
                return result;
            }
           
            temp =temp->child[index];        
        }
        
        count = temp->prefixCounter;
        // finding words with given prefix

        // code to find the words with given prefix

        // loop till the result size does not exceed 10
        while(result.size()<10)
        {
            // loop to traverse all childreen
            for(j=0;j<26;j++)
            {
                if(temp->child[j]!=NULL)
                {
                    // storing words starting with name
                    word = name + temp->child[j]->c;
                    result.push_back(word);
                }

                // break if we get all 10 words
                if(result.size()>=10) break;
            }
            // to out the while loop loop
            if(j!=26)   break;
            else
            {
                
                for(int i=0;i<26;i++)
                {
                    if(temp->child[i]!=NULL)
                    {
                        name = name + temp->child[i]->c;
                        temp = temp->child[i];
                        break;
                    }
                }
            }

        }
        
       // ending the timer
        T.End();

        // calculating seconds taken
        double seconds = T.MilliSeconds();
        seconds = seconds/double(1000);

        // printing the result
        cout<<endl<<count<<" words found in "<<fixed<<setprecision(3)<<seconds<<" seconds\n"<<endl;
        

        // returning result
        return result;
    }
};


// main function
int main()
{

    // creating object of fstream
    // creating object of linkedList
    // defining a string
    // defining a vector to store result
    fstream newfile;
    TrieDataStr dict;
    string name;
    vector<string> result;

 
    newfile.open("dictionary.txt",ios::in); //open a file to perform read operation using file object

    if (newfile.is_open())
    { //checking whether the file is open

        while(getline(newfile, name))  //read data from file object and put it into string.
        {
            dict.addWord(name);
        }
    }   

   newfile.close(); //close the file object.

  // taking input
    cin>>name;

    // storing result by calling findResult function
    result =dict.findResult(name);

    // if size is zero
    if(result.size()==0)
    {
        cout<<"No words with given prefix\n";
    }
    else
    {
        // outputting the result
        for(int i=0;i<result.size();i++)
        {
            cout<<result[i]<<"    ";
        }
    }
   
    return 0;
}