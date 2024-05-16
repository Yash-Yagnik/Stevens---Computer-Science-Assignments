/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Yash Yagnik
 * Date        : 9/17/23
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_ = 0;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}
void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    int primes_in_curr_row = 0;
    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_  << ":"<< endl;
    if (num_primes_ <= primes_per_row){
        for (int i = 2; i <= limit_; i++){
            if ( is_prime_[i] == true && i != max_prime_){
                cout << i << " ";
            }
            else if (i == max_prime_){
                cout << i;
            }
        }
    }
    else{
        for (int i = 2; i <= limit_; i++){
            if (is_prime_[i] == true){
                if (primes_in_curr_row == primes_per_row - 1){

                    cout << setw(max_prime_width) << i;
                    cout << endl;
                    primes_in_curr_row = -1;
                }
                else{
                    if (i == max_prime_){
                        cout << setw(max_prime_width) << i;
                    }
                    else{
                        cout << setw(max_prime_width) << i << " ";
                    }
                }
                primes_in_curr_row++;
            }
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    //cout << "Sieve function is being called" << endl;

    // Initalize each value in the list to true
    is_prime_[0] = false;
    is_prime_[1] = false;
    num_primes_ = 0;
    for(int i = 2; i <= limit_; i++){
        is_prime_[i] = true;
    }

    // Sieve Algorithm
    for(int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i]){
            for(int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }

    // find the max prime number for the width
    for (int i = 2; i <= limit_; i++){
        if (i > max_prime_ && is_prime_[i]){
            max_prime_ = i;
        }
    }

    // Count the total number of primes
    for(int i = 2; i <= limit_; i++){
        if (is_prime_[i]){
            num_primes_++;
        }

    }

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int length_of_num = 0;
    while(num != 0){
        num /= 10;
        length_of_num++;
    }
    return length_of_num;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve test(limit);
    test.display_primes();

    return 0;
}
