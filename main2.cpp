#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <string>

using namespace std;

//message to be encrypted/decrypted
string message;
string key = "peter what goes down";

void SubE();
void SubD();
void XORE(const string& arr, const string& arr_1);
void XORD();
string to_binary(const string& s);

void menu(){
    cout << "Please enter the number for the action you would like to perform\n";
    cout << "1. Substitution\n";
    cout << "2. XOR\n";

    int option;
    cin >> option;

    //Read from file
    fstream f;
    string temp;
    f.open("input.txt");
    if (f.is_open()){
        getline(f, message);
    }

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
            XORE(message, key);
        }else if (option == 2){
            XORD();
        }else {
            cout << "That was not an option.\n";
        }
    }else{
        cout << "That was not an option.\n";
    }
}

void XORE(const string& m, const string& k){
    string result = "";
    string b_m = to_binary(m);
    string b_k = to_binary(k);

    for(int x = 0; x < b_m.length(); x++) {
        if (b_m[x] != b_k[x]) {
            result[x] = '1';
        } else {
            result[x] = '0';
        }
    }
}

string to_binary(const string& s){
    string tmp = "";
    for(int i = 0; i < s.size(); i++){
        bitset<4> b (s.c_str()[i]);
        tmp += b.to_string();
    }
    return tmp;
}



int main() {
    menu();
    return 0;
}