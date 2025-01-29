#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstring>

using namespace std;

// Constants
const char* VERSION = "0.0.1";

// Global Variables
string USER_HOME;

// Function Headers

/// @brief Initializes a new folder for storing files
void init();

/// @brief Initializes a git repository in the current folder
void initGit();

/// @brief Checks to see if the user has a .agro folder in their home directory
void checkDotFolder();

/// @brief Displays a message and prompts the user for a response
/// @param buff Buffer to store the response 
/// @param message Message to display to the user
void prompt(string& buff, const char* message);

/// @brief Displays a message and prompts the user for a response
/// @param message Message to display to the user
/// @return Users response
string prompt(const char* message);

/// @brief Displays the help message
void help();

/// @brief Displays the version of the program
void version();

/// @brief Adds a folder to the agro
/// @param agroName Name of the agro to add the folder to
/// @param folderPath Path to the folder to add
void add(string agroName, string folderPath);

/// @brief Removes a folder from the agro if it exists
/// @param agro Name of the agro to remove the folder from
/// @param folderPath Path to the folder to remove
void remove(string agro, string folderPath);

/// @brief Lists all of the agros that the user has
/// @param agro Name of the agro to list
void list(string agro);

/// @brief Updates the agro with the latest files
/// @param agro Name of the agro to update
void update(string agro);

/// @brief Pushes the agro to the git repository
/// @param agro Name of the agro to push
void push(string agro);

/// @brief Pulls the agro from the git repository
/// @param agro Name of the agro to pull
void pull(string agro);

/// @brief Searches the agro list for a specific agro
/// @param agro Name of the agro to search for
/// @return Returns true if the agro exists
bool searchAgro(string agro);

/// @brief Checks to see if the agro .include file includes a specific folder
/// @param agro Name of the agro to search
/// @return Returns true if the agro includes the folder
bool searchAgroIncludes(string agro);

/// @brief Gets the path to the agro
/// @param agro Name of the agro to get the path for
string getAgroPath(string agro);

int main(int argc, char* argv[]){
    USER_HOME = getenv("HOME");
    checkDotFolder();
    cout << "cwd: " << filesystem::current_path() << endl;

    cout << getAgroPath("mason") << endl;
    exit(0);

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
        list();
    }
    if (strcmp(argv[1], "update") == 0){
        
    }
    if (strcmp(argv[1], "push") == 0){
        
    }
    if (strcmp(argv[1], "pull") == 0){
        
    }
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
    ifstream file(USER_HOME + "/.agro/agro.list");
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
    ifstream file(USER_HOME + "/.agro/agro.list");
    string line;
    while (getline(file, line)){
        cout << line << endl;
    }
    file.close();
}

void checkDotFolder(){
    if (!filesystem::exists(USER_HOME + "/.agro")){
        filesystem::create_directory(USER_HOME + "/.agro");
        ofstream file(USER_HOME + "/.agro/agro.list");
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
    ifstream file(USER_HOME + "/.agro/agro.list");
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

void version(){
    cout << "agro version " << VERSION << endl;
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

    ofstream agroList(USER_HOME + "/.agro/agro.list", ios::app);
    agroList << name << ":" << filesystem::current_path() << endl;

    cout << "Folder created and initialized!" << endl;
}
