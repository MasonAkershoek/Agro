#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstring>
#include "../include/agroFuncs.hpp"

using namespace std;

string addHome(string path){
    return getenv("HOME") + path;
}

void remove(string agro, string folderPath){

}

void list(string agro){

}

void update(string agro){

}

bool searchAgroIncludes(string agro){
    ifstream file(".include");
    string line;
    while (getline(file, line)){
        if (line.find(agro) != string::npos){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void add(string agroName, string folderPath){
    if (searchAgroIncludes(folderPath)){
        cout << "Folder already exists in the agro!" << endl;
        exit(1);
    }
    ofstream file((getAgroPath(agroName) + ".include"), ios::app);
    file << folderPath << endl;
    file.close();
}

string getAgroPath(string agro){
    ifstream file(addHome("/.agro/agro.list"));
    string line;
    while (getline(file, line)){
        if (line.find(agro) != string::npos){
            file.close();
            return line.substr(line.find(":") + 1);
        }
    }
    file.close();
    return "";
}

void list(){
    ifstream file(addHome("/.agro/agro.list"));
    string line;
    while (getline(file, line)){
        cout << line << endl;
    }
    file.close();
}

void checkDotFolder(){
    if (!filesystem::exists(addHome("/.agro"))){
        filesystem::create_directory(addHome("/.agro"));
        ofstream file(addHome("/.agro/agro.list"));
        file << "#This file stores all of the current agros asociated with the user" << endl;
        file.close();
    }
}

void help(){
    cout << "Usage: updateConf [command] [args]" << endl;
    cout << "Commands:" << endl;
    cout << "  -h, --help: Show this help message" << endl;
    cout << "  init: Create and initialize a new git folder for storing files" << endl;
    cout << "  add: Add a folder to the agro" << endl;
    cout << "Args:" << endl;
    cout << "  -f, --folder: The folder[s] to add to the agro" << endl;
    cout << "  -a, --agro: The agro to add the folder to" << endl;
    exit(0);
}

bool searchAgro(string agro){
    ifstream file(addHome("/.agro/agro.list"));
    string line;
    while (getline(file, line)){
        if (line.find(agro) != string::npos){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void prompt(string& buff, const char* message){
    cout << message;
    getline(cin, buff);
    cout << endl;
}

string prompt(const char* message){
    string response = "";
    cout << message;
    getline(cin, response);
    cout << endl;
    return response;
}

void initGit(){
    string response = "";
    string gitURL = "";
    string branch = "";

    cout << "!!WARNING!! - Make sure you have git fully set up on your system!" << endl;
    prompt(response, "Do You want to continue? [Y/n]: ");
    if (response != "Y"){
        exit(1);
    }
    prompt(gitURL, "Enter the HTTP URL of the git repository: ");
    prompt(branch, "Enter the branch name [default: main]: ");
    if (branch == ""){
        branch = "main";
    }
    system("git init");
    system("echo '# My Agro' > README.md");
    system("git add README.md");
    system("git add .");
    system("git commit -m 'Initial commit'");
    system(("git remote add origin " + gitURL).c_str());
    system(("git push -u origin " + branch).c_str());
    cout << "Git repository initialized!" << endl;
}


void init(){
    string name;
    if (filesystem::exists(".include")){
        cout << "This folder is already setup!" << endl;
        exit(1);
    }
    if (prompt("Do you want to initialize this forlder as a git repository? [Y/n]: ") == "Y"){
        initGit();
    }

    prompt(name, "Enter the name of the agro: ");
    if (searchAgro(name)){
        cout << "An agro by that name already exists!" << endl;
        exit(1);
    }
    ofstream file(".include", ios::app);
    file << "# This file is use to store a path to the folders that you want to be stored" << endl;
    file << "# Example: ~/.config/hypr/" << endl;
    file << "name=" << name << endl;
    file.close();

    ofstream agroList(addHome("/.agro/agro.list"), ios::app);
    agroList << name << ":" << filesystem::current_path() << endl;

    cout << "Folder created and initialized!" << endl;
}