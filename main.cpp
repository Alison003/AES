#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//message to be encrypted/decrypted
string message [4][4];
//key is: multiprogramming
string key [4][4] = {{"6d","69","67","6d"},
                     {"75","70","72","69"},
                     {"6c","72","61","6e"},
                     {"74","6f","6d","67"}};

string invKey [4][4];

int matrix [4][4] = {{2,3,1,1},
                     {1,2,3,1},
                     {1,1,2,3},
                     {3,1,1,2}};

int invMatrix [4][4] = {{-4/35, 3/35, -11/35, 17/35},
                        {17/35, -4/35, 3/35, -11/35},
                        {-11/35, 17/35, -4/35, 3/35},
                        {3/35, -11/35, 17/35, -4/35}};

int rCon [4][10] = {{1,2,4,8,10,20,40,80,27,36},
                   {0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0},};

int invRCon [4][10] = {{36,27,80,40,20,10,8,4,2,1},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},};

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

string invSBox [16][16] = {{"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},
                           {"7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"},
                           {"54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"},
                           {"08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"},
                           {"72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"},
                           {"6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"},
                           {"90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"},
                           {"d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"},
                           {"3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"},
                           {"96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"},
                           {"47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"},
                           {"fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"},
                           {"1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"},
                           {"60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"},
                           {"a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"},
                           {"17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}};

string result_arr[4][1];

void getInput();
void getMessage();
void Decrypt();
void invRoundKey();
void invSubBytes();
void invShiftRows();
void invMixColumns();
void Encrypt();
void subBytes();
void shiftRows();
void mixColumns();
void roundKey();
void exclusiveOr(string arr[4][1], string arr_1[4][1]);

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
    cout << "Looking for file encrypted.txt to encrypt it... Please make sure it has a set of 16 chars\n";

    fstream f;
    string tmp;
    stringstream ss;
    int i = 0;
    int x = 0;
    f.open("encrypted.txt",ios::in);
    if (f.is_open()){
        while(getline(f, tmp) && i < 4){
            for(char c : tmp){
                if(c == ' '){
                    continue;
                }
                else {
                    ss << hex << int(c);
                    message[x][i] = ss.str();
                    ss.flush();
                    x++;
                }

                if(x%3 == 0){
                    i++;
                }
            }
        }
    }
    Decrypt();
}

void Decrypt() {
    invRoundKey();
    for (int i = 0; i < 9; i++){
        invShiftRows();
        invSubBytes();
        invRoundKey();
        invMixColumns();
    }
    invShiftRows();
    invSubBytes();
    invRoundKey();

    ofstream f;
    f.open("decrypted.txt");
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            f << message[row][col];
        }
    }
}

void invShiftRows(){
    //row 0: no shift
    //row 1: shift 1
    string temp = message[1][3];
    for(int i = 3; i > 0; i--){
        message[1][i-1] = message[1][i];
    }
    message[1][0] = temp;

    //row 2: shift 2
    string temp1 = message[2][3];
    string temp2 = message[2][2];
    for(int i = 2; i > 0; i--){
        message[2][i - 1] = message[2][i];
    }
    message[2][0] = temp1;
    message[2][1] = temp2;

    //row 3: shift 3
    temp1 = message[3][3];
    temp2 = message[3][2];
    string temp3 = message[3][1];

    message[3][3] = message[3][0];
    message[3][2] = temp1;
    message[3][1] = temp2;
    message[3][0] = temp3;
}

void invSubBytes() {
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
            message[j][i] = invSBox[first][second];
        }
    }
}

void invMixColumns() {
    int value;

    stringstream s;
    int decimal;
    string hex;

    for(int column = 0; column < 4; column++){
        for(int row = 0; row < 4; row++){
            for (int i = 0; i < 4; i++){
                s << message[i][column];
                s >> hex >> decimal;
                value += (decimal * invMatrix[row][i]);
            }
            s << hex << hex;
            message[row][column] = hex;
            value = 0;
        }
    }
}

void invRoundKey() {
    string origKey [4][1];
    string newKey [4][1];
    string newBlock [4][4];

    for (int i = 0; i < 4; i++){
        if (i == 0){
            //get last column of original key
            for (int j = 0; j < 4; j++){
                origKey[j][i] = key[j][i];
                newKey[j][i] = key[j][3];
            }

            //shift up one
            string temp;
            temp = newKey[0][1];
            for (int j = 0; j < 3; j++){
                newKey[j][1] = newKey[j+1][1];
            }
            newKey[3][1] = temp;

            //sub bytes
            stringstream stream;
            int first;
            int second;
            for(int h = 0; h < 4; h++){
                for(int j = 0; j < 4; j++){
                    int x = newKey[j][h].at(0);
                    stream << x;
                    stream >> hex >> first;
                    int y = newKey[j][h].at(1);
                    stream << y;
                    stream >> hex >> second;
                    newKey[j][h] = invSBox[first][second];
                }
            }

            //XOR with the index column of original key
            exclusiveOr(origKey, newKey);

            //XOR with the rcon table column
            string rConRow [4][1];
            for (int j = 0; j < 4; j++){
                rConRow[j][1] = invRCon[j][i];
            }
            exclusiveOr(rConRow, newKey);

        }else{
            //XOR previous column of new key with next column in original key
            string nextKey [4][1];
            for (int j = 0; j < 4; j++){
                nextKey[j][1] = newKey[j][1];
            }

            for (int j = 0; j < 4; j++){
                origKey[j][i] = key[j][i];
            }

            exclusiveOr(origKey, nextKey);
        }
        for (int j = 0; j < 4; j++){
            newBlock[j][i] = newKey[j][1];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            key[i][j] = newBlock[i][j];
        }
    }
}

//Gets message to be encrypted
void getMessage() {
    cout << "Looking for file input.txt to encrypt it... Please make sure it has a set of 16 chars\n";

    fstream f;
    string tmp;
    stringstream ss;
    int i = 0;
    int x = 0;
    f.open("input.txt",ios::in);
    if (f.is_open()){
        while(getline(f, tmp) && i < 4){
            for(char c : tmp){
                if(c == ' '){
                    continue;
                }
                else {
                    ss << hex << int(c);
                    message[x][i] = ss.str();
                    ss.flush();
                    x++;
                }

                if(x%3 == 0){
                    i++;
                }
            }
        }
    }
    Encrypt();
}

void roundKey(){
    string origKey [4][1];
    string newKey [4][1];
    string newBlock [4][4];

    for (int i = 0; i < 4; i++){
        if (i == 0){
            //get last column of original key

            for (int j = 0; j < 4; j++){
                origKey[j][i] = key[j][i];
                newKey[j][i] = key[j][3];
            }

            //shift up one
            string temp;
            temp = newKey[0][1];
            for (int j = 0; j < 3; j++){
                newKey[j][1] = newKey[j+1][1];
            }
            newKey[3][1] = temp;

            //sub bytes
            stringstream stream;
            int first;
            int second;
            for(int h = 0; h < 4; h++){
                for(int j = 0; j < 4; j++){
                    int x = newKey[j][h].at(0);
                    stream << x;
                    stream >> hex >> first;
                    int y = newKey[j][h].at(1);
                    stream << y;
                    stream >> hex >> second;
                    newKey[j][h] = sBox[first][second];
                }
            }

            //XOR with the index column of original key
            exclusiveOr(origKey, newKey);

            //XOR with the rcon table column
            string rConRow [4][1];
            for (int j = 0; j < 4; j++){
                rConRow[j][1] = rCon[j][i];
            }
            exclusiveOr(rConRow, newKey);

        }else{
            //XOR previous column of new key with next column in original key
            string nextKey [4][1];
            for (int j = 0; j < 4; j++){
                nextKey[j][1] = newKey[j][1];
            }

            for (int j = 0; j < 4; j++){
                origKey[j][i] = key[j][i];
            }

            exclusiveOr(origKey, nextKey);
        }
        for (int j = 0; j < 4; j++){
            newBlock[j][i] = newKey[j][1];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            key[i][j] = newBlock[i][j];
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
    message[3][1] = temp1;
    message[3][2] = temp2;
    message[3][3] = temp3;
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
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            message[j][i] = message[j][i] + key[j][i];
        }
    }

    for (int i = 0; i < 9; i++){
        subBytes();
        shiftRows();
        mixColumns();
        roundKey();
    }

    subBytes();
    shiftRows();
    roundKey();

    ofstream f;
    f.open("encrypted.txt");
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            f << message[row][col];
        }
    }
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
    int a = binary[0];
    int b = binary[1];
    bin[0] = char(a);
    bin[1] = char(b);
    return bin;
}

// 01
// 11
// 10
void exclusiveOr(string arr[4][1], string arr_1[4][1]){
    string result = "  ";
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
}

int main() {
    menu();
    return 0;
}