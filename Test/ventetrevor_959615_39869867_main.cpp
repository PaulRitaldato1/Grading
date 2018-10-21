//
//  main.cpp
//  Project1
//
//  Created by Trevor Vente on 9/15/18.
//  Copyright © 2018 Trevor Vente. All rights reserved.
//
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <sstream>
#include "LinkedList.hpp"

void split_in_args(std::vector<std::string>& qargs, std::string command){
    long len = command.length();
    bool qot = false, sqot = false;
    int arglen;
    for(int i = 0; i < len; i++) {
        int start = i;
        if(command[i] == '\"') {
            qot = true;
        }
        else if(command[i] == '\'') {
            sqot = true;
        }
        
        if(qot) {
            i++;
            start++;
            while(i < len && command[i] != '\"')
                i++;
            if(i < len)
                qot = false;
            arglen = i - start;
            i++;
        }
        else if(sqot) {
            i++;
            while(i < len && command[i] != '\'')
                i++;
            if(i < len)
                sqot = false;
            arglen = i - start;
            i++;
        }
        else{
            while(i < len && command[i] != ' ')
                i++;
            arglen = i - start;
        }
        qargs.push_back(command.substr(start, arglen));
    }
}

int main() {
    bool running = true;
    LinkedList* list = new LinkedList();
    
    std::string input;
    std::vector<std::string> results;
    do {
        std::getline(std::cin, input) ;
        if(input.empty()) {
            continue;
        }
        
        split_in_args(results, input);
        if(results.front().compare("insertEnd") == 0) {
            results.erase(results.begin());
            
            if(results.empty()) {
                continue;
            }
            else {
                list->insertEnd(results.front());
            }
        }
        else if(results.front().compare("insert") == 0) {
            results.erase(results.begin());
            if(results.empty()) {
                continue;
            }
            else {
                int index;
                try {
                    index = std::stoi(results.front());
                }catch(const std::exception) {
                    results.clear();
                    continue;
                }
                results.erase(results.begin());
                
                if(results.empty()) {
                    continue;
                }
                else {
                    list->insert(index, results.front());
                }
            }
        }
        else if(results.front().compare("edit") == 0) {
            results.erase(results.begin());
            if(results.empty()) {
                continue;
            }
            else {
                int index;
                try {
                    index = std::stoi(results.front());
                }catch(const std::exception) {
                    results.clear();
                    continue;
                }
                results.erase(results.begin());
                
                if(results.empty()) {
                    continue;
                }
                else {
                    list->edit(index, results.front());
                }
            }
        }
        else if(results.front().compare("search") == 0) {
            results.erase(results.begin());
            if(results.empty()) {
                continue;
            }
            else {
                list->search(results.front());
            }
        }
        else if(results.front().compare("print") == 0) {
            list->print();
        }
        else if(results.front().compare("delete") == 0) {
            results.erase(results.begin());
            if(results.empty()) {
                continue;
            }
            else {
                int index;
                try {
                    index = std::stoi(results.front());
                }
                catch(const std::exception) {
                    results.clear();
                    continue;
                }
                list->del(index);
            }
        }
        else if(results.front().compare("quit") == 0) {
            running = false;
        }
        else {
            continue;
        }
        results.clear();
    }while(running);
    return 0;
}
