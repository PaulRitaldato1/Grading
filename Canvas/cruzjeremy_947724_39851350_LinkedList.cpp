//
// Created by Jeremy Cruz on 9/12/18.
//

#include "LinkedList.h"
#include <cstdlib>
#include "stdio.h"
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

/*
 * This method works to acquire a substring between the quotes of the inputted string.
 *
*/
string extractSubstring(string lstring){

    int firstQuote = lstring.find("\"");
    int lastQuote = lstring.rfind("\"");

    int totChar = 0;
    int counter = firstQuote;

    while(counter+1<lastQuote){
        counter++;
        totChar++;
    }


    string exString = lstring.substr( firstQuote+1, totChar );

    return exString;

}


/*
 * This method is for the delete function.
 * It works to grab the index of the node that will be deleted
 * from the inputted string.
 */
int extractInt(string userString){

    string check = userString;

    int length = check.length();
    char char_array[length+1];

    strcpy(char_array, check.c_str());

    for(int i = 0;i<length; i++){
        if (isdigit(char_array[i])){
            int found = (char_array[i]-'0');
            return found;
        }
    }
}



int main() {

    LinkedList linkList; // Initializes Linked List object

    bool cont = true; // Boolean to keep the program running

    while(cont){

        //MENU STATEMENT

        //cout << "Options:\n1. insertEnd 'insert text' \n2. insert Line # 'insert text'\n3. delete Line # \n4. print \n5. search Line #\n6. quit (exits program)" << endl;

        string userInput = "";
        string data = "";
        int index = 0;

        getline(cin,userInput);

        if((userInput.find("insertEnd")!=(-1)) && (userInput.find("\"")>(userInput.find("insertEnd"))) && (userInput.find("\""))!=userInput.rfind("\"")){ // Insert line/ node at end of linked List
            string data = extractSubstring(userInput);
            if (data.length()<=80){
                linkList.insertEnd(data);
            }
        }
        else if(userInput.find("insert")!= -1 && (userInput.find("\"")>(userInput.find("insert"))) && (userInput.find("\""))!=userInput.rfind("\"")){ // insert a node at given index

            string data = extractSubstring(userInput);
            int index = extractInt(userInput);

            if (data.length()<=80){
                linkList.insert(data, index);
            }
            else{
                cout << "Line is too long" << endl;
            }

        }
        else if(userInput.find("search")!=-1 && (userInput.find("\"")>(userInput.find("search")))){ // search through each node

            string searchString = extractSubstring(userInput);
            linkList.search(searchString);

        }
        else if(userInput.find("print")!=-1){ // print the lines case

            linkList.printList();

        }
        else if(userInput.find("delete")!=-1){ // delete a line/node case

            int deleteIndex = extractInt(userInput);
            linkList.deleteNode(deleteIndex);

        }
        else if(userInput.find("edit")!=-1){ // Case where user edits the string

            string editString = extractSubstring(userInput);
            int editIndex = extractInt(userInput);

            linkList.edit(editIndex, editString);

        }
        else if(userInput.find("quit")!=-1){ // the quit case

            break;

        }
        else{
            cout << "Invalid input. Try again.\n" << endl; // The case that the user did not input any keywords
        }

    }

}






