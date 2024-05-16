/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Yash Yagnik
 * Date        : 9/26/2023
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>


using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    for (size_t i = 0; i < s.size(); i++){
        if (('a' - s[i] ) >= 7){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.


    unsigned int vector = 0;

    for (size_t i = 0; i < s.size(); i++){
        unsigned int setter = (1 << (s[i] - 'a'));
        if ((vector & setter) == setter){
            cout << "Duplicate letters found." << endl;
            return false;
        }
        vector = vector | setter;
    }
    cout << "All letters are unique." << endl;
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if (argc > 2){
        cerr << "Usage: " << argv[0] << " <string>";
    }

    else if(argc < 2){
        cerr << "Usage: " << argv[0] << " <string>";
    }
    else{
        if (!(is_all_lowercase(argv[1]))){
            cerr << "Error: String must contain only lowercase letters." << endl;
        }

        else{
            all_unique_letters(argv[1]);
        }
    }

        //cout << is_all_lowercase("Hello");
        //cout << 'a' - 'Z';




}
