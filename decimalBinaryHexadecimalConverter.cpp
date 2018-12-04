//Convert Binary to Decimal
//8-bit unsigned stored in an array
#include <iomanip> 
#include <iostream> 
#include <cstdlib> 
#include <cmath> 
#include <fstream> 
#include <string>

using namespace std;

const int NUMBIT = 8;

int bin2dec(int bits[NUMBIT]) {
  int result = 0, bitValue = 1;
  //bitValue is intially 2^0

  for (int bitCnt = 0; bitCnt < NUMBIT; bitCnt++) {
    result += bits[bitCnt] * bitValue; //take placeholder and multiply by 2^n
    bitValue *= 2; //2^(n+1)
  }
  return result;
}

void dec2bin(int number, int bits[NUMBIT]) {
  int bitNum = 0;
  do {
    bits[bitNum] = number % 2;
    bitNum++;
    number /= 2;
  } while (number > 0);
}

int dec2hex(string hex[NUMBIT], int number) {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  int modulus = 0, index = 0;
  char hexadecim;
  while (number != 0) {
    modulus = number % 16;
    if (modulus > 9) {
      modulus -= 10;
      hexadecim = alphabet[modulus]; //letters input into string
      hex[index] = hexadecim;
    } else {
      hexadecim = '0' + modulus; //numbers input into string
      hex[index] = hexadecim; 
    }
    number /= 16;
    index++;
  }
  return index;
}

int hex2dec(int num) {
  if (num > 96) //lowercase letters entered
    num -= 87; //converted to 10-15
  else {
    if (num > 64) //uppercase letters entered
      num -= 55; //converted to 10-15
    else
      num -= 48; //converted to 1-9
  }
  return num;
}

void hex2bin(int num, int bits[NUMBIT]) {
  dec2bin(num, bits);
}

void inputArray(int bits[NUMBIT]) {
  int num = 0;
  cout << "Please input a binary number up to 8 digits." << endl;
  cin >> num;
  for (int cnt = NUMBIT - 1; cnt >= 0; cnt--)
    bits[cnt] = int(num / (pow(10, cnt))) % 2;
}

void printBin(int bits[NUMBIT]) {
  for (int cnt = NUMBIT - 1; cnt >= 0; cnt--)
    cout << bits[cnt];
  cout << endl;
  bits = {
    0
  };
}

int hexDecPrompt() {
  int number = 0;   //declutter from main
  string num2;
  cout << "Please input your number" << endl;
  cin >> num2;
  int numSize = num2.size() - 1, index = 0;
  while (num2[index] != 0) {
    number += hex2dec(num2[index]) * pow(16, numSize);
    index++;
    numSize--;
  }
  return number;
}

int main() {
  bool run = true;
  string num = "a", conv = "a";
  string num2[NUMBIT];
  int binary[NUMBIT] = {
    0
  };
  int number = 0;
  while (run) {
    cout << "Would you like to convert a decimal, binary or hexadecimal number? (d/b/h)" << endl;
    cin >> num;
    cout << "What would you like the number to be converted into? (d/b/h)" << endl;
    cin >> conv;
    if (num == "b" && conv == "d") {
      inputArray(binary);
      cout << bin2dec(binary) << endl;
    }
    if (num == "d" && conv == "b") {
      cout << "Please input a number:" << endl;
      cin >> number;
      dec2bin(number, binary);
      printBin(binary);
    }
    if (num == "h" && conv == "d") {
      number = hexDecPrompt();
      cout << number << endl;
    }
    if (num == "h" && conv == "b") {
      dec2bin(hexDecPrompt(), binary);
      printBin(binary);
    }
    if (num == "d" && conv == "h") {
      cout << "Please input a number:" << endl;
      cin >> number;
      int index = dec2hex(num2, number);
      while (index >= 0) {
        cout << num2[index];
        index--;
      }
      cout << endl;
    }
    if (num == "b" && conv == "h") {
      inputArray(binary);
      int index = dec2hex(num2, bin2dec(binary));
      while (index >= 0) {
        cout << num2[index];
        index--;
      }
      cout << endl;
    }
    if((num != "b" && num != "d" && num != "h") || (conv != "b" && conv != "d" && conv != "h"))
	    cout << "Invalid Choice" << endl;

    cout << "Would you like to continue? (y or n)" << endl;
    cin >> num;
    if (num == "n")
      run = false;
  }
}
