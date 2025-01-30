#pragma once
#include <assert.h>
#include <iostream>
#include <filesystem>
#include "agroFuncs.hpp"

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

using namespace std;

void testInit(){
    init();
    IS_TRUE(searchAgro("test") == true);
    cout << "init function passed!" << endl;
}

void testPromtp(){
    string buff = "";
    prompt(buff, "Enter [Hello]: ");
    IS_TRUE(buff == "Hello");
    buff = "";
    buff = prompt("Enter [Hello]: ");
    IS_TRUE(buff == "Hello");
    cout << "prompt function passed!" << endl;
}

void testAdd(){
    add("test", "/home/mason/euclid/");
    IS_TRUE(searchAgroIncludes("test", "/home/mason/euclid/") == true);

}

void testRemove(){
    remove ("test", "/home/mason/euclid/");
    IS_TRUE(searchAgroIncludes("test", "/home/mason/euclid/") == false);
    cout << "remove function passed!" << endl;
}

void testList(){
    list("test");
}

void testUpdate(){
    
}

void testSearchAgro(){
    IS_TRUE(searchAgro("test") == true);
    IS_TRUE(searchAgro("notexist") == false);
    cout << "searchAgro function passed!" << endl;
}

void cleanUp(){
    filesystem::path path = DOTFOLDER + ".include";
    filesystem::remove(path);
}

int test(){
    testInit();
    //testPromtp();
    //testAdd();
    // testRemove();
    //testList();
    // testUpdate();
    //testSearchAgro();
    //cleanUp();
    return 0;
}