#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "scanner.h"
using namespace std;
void scannerFSM(Scanner myScannerm string str);
int main()
{
    Scanner testScanner;

    string str;
    cout << "Enter a line of code followed by endline" << endl;
    getline(cin, str);
    scannerFSM(testScanner, str);
}
void scannerFSM(Scanner myScanner, string str) {

}
