#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//message to be encrypted/decrypted
string message [4][4];

void SubE();
void SubD();
void XORE();
void XORD();

void menu(){
    cout << "Please enter the number for the action you would like to perform\n";
    cout << "1. Substitution\n";
    cout << "2. XOR\n";

    int option;
    cin >> option;

    if(option == 1){//SUB
        cout << "Please enter the number for the action you would like to perform\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cin >> option;
        if (option == 1){
            SubE();
        }else if (option == 2){
            SubD();
        }else{
            cout << "That was not an option.\n";
        }
    }else if(option == 2){//XOR
        cout << "Please enter the number for the action you would like to perform\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cin >> option;
        if (option == 1){
            XORE();
        }else if (option == 2){
            XORD();
        }else {
            cout << "That was not an option.\n";
        }
    }else{
        cout << "That was not an option.\n";
    }
}

int main() {
    menu();
    return 0;
}