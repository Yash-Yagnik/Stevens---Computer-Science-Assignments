/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Yash Yagnik
 * Version : 1.0
 * Date    : September 9, 2023
 * Description: Computes the Square root of two command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon) {
    double last_guess = num;
    double next_guess;
    double difference = 2000;
    if (num < 0) {
        cerr << numeric_limits<double>::quiet_NaN();
        return 1;
    }

    else if (num == 0) {
        cout << fixed << setprecision(8) <<  0.0 << endl;
        return 0;
    }
    else if (num == 1) {
        cout << fixed << setprecision(8) << 1.0 << endl;
        return 0;
    }
    else {
        while (difference >= epsilon) {
            next_guess = (last_guess + num / last_guess) / 2;
            difference = abs(last_guess - next_guess);
            last_guess = next_guess;
        }
        cout << fixed << setprecision(8) << next_guess << endl;
        return 0;
    }
}

int main(int argc, char* argv[]){
    double user_num;
    double epsilon;

    istringstream iss;
    if (argc != 2 && argc != 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    iss.str(argv[1]);

    if (!(iss >> user_num)){
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    if (argc == 2){
        sqrt(user_num, 1e-7);
        return 0;
    }

    iss.clear();
    iss.str(argv[2]);

    if (!(iss >> epsilon) || epsilon <= 0){
        cerr << "Error: Epsilon argument must be a positive double." << endl;
        return 1;
    }

    if (argc == 3) {
        sqrt(user_num, epsilon);
        return 0;
    }
}