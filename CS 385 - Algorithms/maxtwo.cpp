//
// Created by yashy on 9/6/2023.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
    int n, m;
    istringstream iss;

    if (argc != 3){
        cerr << "Usage: " << argv[0] << "<int> <int>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if (!(iss >> n)){
        cerr << "Err: first command line arg must be an int" << endl;
        return 1;
    }

    iss.clear();

    iss.str(argv[2]);
    if (!(iss >> m)){
        cerr << "Err: second command line arg must be an int" << endl;
        return 1;
    }

    cout << "n is: " << n << endl;
    cout << "m is: " << m << endl;
    cout << "max(" << n << "," << m << ")" << endl << max(n, m);
    /*cout << fixed << 1.0/ 10000000.0;*/

    return 0;
}
