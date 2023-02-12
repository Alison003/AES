#include <iostream>
#include <sstream>

using namespace std;

//message to be encrypted/decrypted
string message [4][4];
//key is: multiprogramming
string key [4][4] = {{"6d","69","67","6d"},
                     {"75","70","72","69"},
                     {"6c","72","61","6e"},
                     {"74","6f","6d","67"}};

int matrix [4][4] = {{2,3,1,1},
                     {1,2,3,1},
                     {1,1,2,3},
                     {3,1,1,2}};

string sBox [16][16] = {{"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
                        {"ca","82","c9","7d","fa","59","47","f0","ad","d4","a2","af","9c","a4","72","c0"},
                        {"b7","fd","93","26","36","3f","f7","cc","34","a5","e5","f1","71","d8","31","15"},
                        {"04","c7","23","c3","18","96","05","9a","07","12","80","e2","eb","27","b2","75"},
                        {"09","83","2c","1a","1b","6e","5a","a0","52","3b","d6","b3","29","e3","2f","84"},
                        {"53","d1","00","ed","20","fc","b1","5b","6a","cb","be","39","4a","4c","58","cf"},
                        {"d0","ef","aa","fb","43","4d","33","85","45","f9","02","7f","50","3c","9f","a8"},
                        {"51","a3","40","8f","92","9d","38","f5","bc","b6","da","21","10","ff","f3","d2"},
                        {"cd","0c","13","ec","5f","97","44","17","c4","a7","7e","3d","64","5d","19","73"},
                        {"60","81","4f","dc","22","2a","90","88","46","ee","b8","14","de","5e","0b","db"},
                        {"e0","32","3a","0a","49","06","24","5c","c2","d3","ac","62","91","95","e4","79"},
                        {"e7","c8","37","6d","8d","d5","4e","a9","6c","56","f4","ea","65","7a","ae","08"},
                        {"ba","78","25","2e","1c","a6","b4","c6","e8","dd","74","1f","4b","bd","8b","8a"},
                        {"70","3e","b5","66","48","03","f6","0e","61","35","57","b9","86","c1","1d","9e"},
                        {"e1","f8","98","11","69","d9","8e","94","9b","1e","87","e9","ce","55","28","df"},
                        {"8c","a1","89","0d","bf","e6","42","68","41","99","2d","0f","b0","54","bb","16"}};

void getInput();
void getMessage();
void Decrypt();
void Encrypt();
void subBytes();
void shiftRows();
void mixColumns();
void roundKey();

void menu(){
    cout << "Please enter the number for the action you would like to perform\n";
    cout << "1. Encrypt a message\n";
    cout << "2. Decrypt a message\n";

    int option;
    cin >> option;

    if(option == 1){
        getInput();
    }else if(option == 2){
        getMessage();
    }else{
        cout << "That was not an option.\n";
    }
}

//Gets message to be decrypted
void getInput(){
    cout << "What message would you like to decrypt? (Please enter a 16 character message)\n";
    string userInput;
    cin >> userInput;

    //TODO: put encrypted message into 2D message array
    Decrypt();
}

void Decrypt() {
    //TODO: implement decrypting an encrypted message
}

//Gets message to be encrypted
void getMessage() {
    cout << "What message would you like to encrypt? (Please enter a 16 character message)\n";
    string userInput;
    cin >> userInput;

    stringstream ss;

    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ss << hex << int(userInput.at(index));
            message[j][i] = ss.str();;
            index++;
        }
    }
    Encrypt();
}

void roundKey(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            message[j][i] = message[j][i] + key[j][i];
        }
    }
}

void subBytes() {
    stringstream stream;
    int first;
    int second;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int x = message[j][i].at(0);
            stream << x;
            stream >> hex >> first;
            int y = message[j][i].at(1);
            stream << y;
            stream >> hex >> second;
            message[j][i] = sBox[first][second];
        }
    }
}

void shiftRows() {
    //row 0: no shift
    //row 1: shift 1
    string temp = message[1][0];
    for(int i = 0; i < 3; i++){
        message[1][i] = message[1][i + 1];
    }
    message[1][3] = temp;

    //row 2: shift 2
    string temp1 = message[2][0];
    string temp2 = message[2][1];
    for(int i = 0; i < 2; i++){
        message[2][i] = message[2][i + 2];
    }
    message[2][2] = temp1;
    message[2][3] = temp2;

    //row 3: shift 3
    temp1 = message[3][0];
    temp2 = message[3][1];
    string temp3 = message[3][2];
    message[3][0] = message[3][3];
    message[3][1] = message[3][0];
    message[3][2] = message[3][1];
    message[3][3] = message[3][2];
}

void mixColumns() {
    int value;

    stringstream s;
    int decimal;
    string hex;

    for(int column = 0; column < 4; column++){
        for(int row = 0; row < 4; row++){
            for (int i = 0; i < 4; i++){
                s << message[i][column];
                s >> hex >> decimal;
                value += (decimal * matrix[row][i]);
            }
            s << hex << hex;
            message[row][column] = hex;
            value = 0;
        }
    }
}

void Encrypt(){
    roundKey();

    for (int i = 0; i < 9; i++){
        subBytes();
        shiftRows();
        mixColumns();
        roundKey();
    }

    subBytes();
    shiftRows();
    roundKey();
}

string UnHex(string hex_c){
    //go from hex to decimal
    stringstream dec;
    dec << hex_c;

    int dec_val;
    dec >> hex >> dec_val;

    //go from decimal to binary
    int binary_inv[2];
    int i = 0;
    while (dec_val > 0){
        binary_inv[i] = dec_val % 2;
        dec_val = dec_val/2;
        i++;
    }

    //invert the array
    int binary[2];
    for (int x = 0; x < 2; x++){
        binary[x] = binary_inv[32-x];
    }

    string bin = "  ";
    bin[0] = binary[0];
    bin[1] = binary[1];
    return bin;
}

// 01
// 11
// 10
void exclusiveOr(){
    string result = "  ";
    string arr[4][1];
    string arr_1[4][1];
    string result_arr[4][1];
    for (int i = 0; i < 4; i ++){
        string tmp_one = arr[i][0];
        string tmp_two = arr_1[i][0];
        for(int x = 0; x < 2; x++){
            if(tmp_one[x] != tmp_two[x]){
                result[x] = '1';
            }
            else{
                result[x] = '0';
            }
        }
        result_arr[i][0] = result;
        result = "  ";
    }
//return result_arr;
}

int main() {
    menu();
    return 0;
}
