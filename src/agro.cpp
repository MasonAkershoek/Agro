#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstring>
#include "../include/agroFuncs.hpp"

// Constants
const char* VERSION = "0.0.1";

using namespace std;

void version(){
    cout << "agro version " << VERSION << endl;
}

int main(int argc, char* argv[]){
    checkDotFolder();
    cout << "cwd: " << filesystem::current_path() << endl;

    // Error checking
    if (argc <= 1){
        cout << "Must provide at lease one command!" << endl;
        cout << "Usage: updateConf [command] [args]" << endl;
        exit(1);
    }

    // Help/Version
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") ==0){
        help();
    }
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0){
        version();
    }

    // Commands
    if (strcmp(argv[1], "init") == 0){
        init();
    }
    if (strcmp(argv[1], "add") == 0){
        if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "--agro") == 0){
            if (!searchAgro(argv[3])){
                cout << "Agro does not exist!" << endl;
                exit(1);
            }
            if (strcmp(argv[4], "-f") == 0 || strcmp(argv[4], "--folder") == 0){
                for(int i = 5; i < argc; i++){
                    add(argv[3], argv[i]);
                }
            }else{
                if (prompt("Do you want to add the current folder to the agro? [Y/n]: ") == "Y"){
                    add(argv[3], filesystem::current_path());
                }
            }
        }
    }
    if (strcmp(argv[1], "remove") == 0){
        if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "--agro") == 0){
            if (!searchAgro(argv[3])){
                cout << "Agro does not exist!" << endl;
            }
        }
        if (strcmp(argv[4], "-f") == 0 || strcmp(argv[4], "--folder") == 0){
            for(int i = 5; i < argc; i++){
                remove(argv[3], argv[i]);
            }
        }else{
            if (prompt("Do you want to remove the current folder from the agro? [Y/n]: ") == "Y"){
                remove(argv[3], filesystem::current_path());
            }
        }
        
    }
    if (strcmp(argv[1], "list") == 0){
        list(argv[3]);
    }
    if (strcmp(argv[1], "update") == 0){
        
    }
    if (strcmp(argv[1], "push") == 0){
        
    }
    if (strcmp(argv[1], "pull") == 0){
        
    }
}
