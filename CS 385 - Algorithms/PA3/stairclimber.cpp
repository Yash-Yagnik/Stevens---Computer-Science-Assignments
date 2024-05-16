/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Yash Yagnik
 * Date        : 10/7/2023
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> ways1;
vector<int> curr_way;



vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    if (num_stairs <= 0){
        ways1.push_back(curr_way);
    }

    for (int i = 1; i <= 3; i++){
        if (num_stairs >= i){
            curr_way.push_back(i);
            get_ways(num_stairs - i);
            curr_way.pop_back();

        }
    }
    return ways1;
}

void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating  accounting for the spaces after the number so solutions gets to the double digits
    // the vector of vectors and printing each combination.
    int user_stairs = 0;
    for (int i : ways[0]){
            user_stairs += i;
    }

    if (ways.size() == 1){
        cout << ways.size() << " way to climb " << user_stairs << " stair." << endl;
    }

    else{
        cout << ways.size() << " ways to climb " << user_stairs << " stairs." << endl;
    }

    if (ways.size() > 9){
        for (size_t i = 0; i < ways.size(); i++){
            if ((i + 1) <= 9){
                cout << " " << i + 1 << ". ";
            }
            else{
                cout << i + 1 << ". ";
            }

            for (size_t j = 0; j < ways[i].size(); j++){
                if (ways[i].size() == 1){
                    cout << "[" << ways[i][j] << "]" ;
                }
                else if (j == 0){
                    cout << "[" << ways[i][j] << ", " ;
                }

                else if (j == ways[i].size() - 1){
                    cout << ways[i][j] << "]" << endl;
                }
                else{
                    cout << ways[i][j] << ", " ;
                }
            }
        }
    }
    else{
        for (size_t i = 0; i < ways.size(); i++){
            cout << i + 1 << ". ";
            for (size_t j = 0; j < ways[i].size(); j++){
                if (ways[i].size() == 1){
                    cout << "[" << ways[i][j] << "]" ;
                }
                else if (j == 0){
                    cout << "[" << ways[i][j] << ", " ;
                }

                else if (j == ways[i].size() - 1){
                    cout << ways[i][j] << "]" << endl;
                }
                else{
                    cout << ways[i][j] << ", " ;
                }
            }
        }
    }
}

int main(int argc, char * const argv[]) {
//    vector<vector<int>> result;
//    display_ways(get_ways(5));

    if (argc <= 1 || argc > 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" ;
    }

    else if (atoi(argv[1]) <= 0){
        cerr << "Error: Number of stairs must be a positive integer.";
    }


    else{
        display_ways(get_ways(atoi(argv[1])));
    }
}
