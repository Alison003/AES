#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//message to be encrypted/decrypted
string message;
int subKey = 4;

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
            fstream f;
            f.open("input.txt");
            if (f.is_open()){
                getline(f, message);
            }
            SubE();
        }else if (option == 2){
            fstream f;
            f.open("encrypted.txt");
            if (f.is_open()){
                getline(f, message);
            }
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

void SubE(){
    int num;
    char c;
    for (char & i : message){
        num = (int)i;
        num += 4;
        c = (char)num;
        i = c;
    }

    cout << "Encrypted message written to encrypted.txt\n";
    ofstream f;
    f.open("encrypted.txt");
    f << message;
}

void SubD(){
    int num;
    char c;
    for (char & i : message){
        num = (int)i;
        num -= 4;
        c = (char)num;
        i = c;
    }

    cout << "Decrypted message written to decrypted.txt\n";
    ofstream f;
    f.open("decrypted.txt");
    f << message;
}

void XORE(){

}

void XORD(){

}

int main() {
    menu();
    return 0;
}