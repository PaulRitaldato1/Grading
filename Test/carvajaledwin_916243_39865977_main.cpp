//
//  main.cpp
//  Assignment1_DataStructures
//
//  Created by Edwin Carvajal on 9/13/18.
//  Copyright © 2018 Edwin Carvajal. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "LinkedList_Class.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
        
    string input, substring;
    LinkedList newList;
    while(getline(cin, input)){
        
        if(input.find("insertEnd") != string::npos){
            //get string from find value to the end
            string checkStatement = "insertEnd ";
            substring = input.substr(input.find(checkStatement) + checkStatement.size());
            //parse out the "'s
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            newList.insertEnd(substring);
        }
        else if(input.find("insert ") != string::npos){
            stringstream ss;
            ss << input;
            int found = 0;
            string temp;
            while(!ss.eof()){
                ss >> temp;
                //if temp can be piped into an int, then it is the number
                if(stringstream(temp) >> found){
                    break;
                }
            }
            //concatenate the strings for the command and the value
            string newTemp = "insert " + temp + " ";
            substring = input.substr(input.find(newTemp) + newTemp.size());
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            newList.insertSpecific(found, substring);
        }
        else if(input.find("delete") != string::npos){
            stringstream ss;
            ss << input;
            int found = 0;
            string temp;
            while(!ss.eof()){
                ss >> temp;
                //find the int value from the statment
                if(stringstream(temp) >> found){
                    break;
                }
            }
            newList.deleteSpecific(found);
        }
        else if(input.find("edit") != string::npos){
            stringstream ss;
            ss << input;
            int found = 0;
            string temp;
            while(!ss.eof()){
                ss >> temp;
                if(stringstream(temp) >> found){
                    break;
                }
            }
            string newTemp = "edit " + temp + " ";
            substring = input.substr(input.find(newTemp) + newTemp.size());
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            newList.editSpecific(found, substring);
        }
        else if(input.find("print") != string::npos){
            newList.printList();
        }
        else if(input.find("search") != string::npos){
            //get string from find value to the end
            string checkStatement = "search ";
            substring = input.substr(input.find(checkStatement) + checkStatement.size());
            //parse out the "'s
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            substring.erase(remove(substring.begin(), substring.end(), '"'));
            newList.searchList(substring);
        }
        else if(input.find("quit") != string::npos){
            return 0;
        }
        else{
            cout << "Improper input" << endl;
            continue;
        }

    }
    return 0;
}
