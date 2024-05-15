/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Yash Yagnik
 * Version     : 1.0
 * Date        : 10/30/2023
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/*
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */

long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if (array[i] > array[j]){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* temp = new int[length];
    long final_inversion_count = mergesort(array, temp, 0, length - 1);
    delete[] temp;
    return final_inversion_count;

}


long merge(int array[], int scratch[], int low, int mid, int high){
    int i1 = low, i2 = mid+1, i = low;
    long num_of_inversions = 0;
    while((i1 <= mid) && (i2 <= high)){
        if (array[i1] <= array[i2]){
            scratch[i++] = array[i1++];
        }
        else{
            scratch[i++] = array[i2++];
            num_of_inversions += mid - i1 + 1;
        }
    }

    while(i1 <= mid){
        scratch[i++] = array[i1++];
    }
    while(i2 <= high){
        scratch[i++] = array[i2++];
        //num_of_inversions += mid - i1 + 1;
    }
    for (int f = low; f <= high; f++){
        array[f] = scratch[f];
    }
    return num_of_inversions;

}

static long mergesort(int array[], int scratch[], int low, int high) {
    if (low < high){
        int mid = low + (high - low)/2;
        long inversions = 0;
        inversions += mergesort(&array[0], &scratch[0], low, mid);
        inversions += mergesort(&array[0], &scratch[0], mid + 1, high);
        return inversions + merge(&array[0], &scratch[0], low, mid, high);
    }
    /*
    for (size_t c = 0; c <= (size_t) high; c++){
        cout << array[c];
    }
    cout << endl;
     */
    return 0;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if (argc > 2){
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    else if (argc == 2){
        if (strcmp(argv[1], "slow") != 0){
            cout << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output

    //int nums[7] = {7, 3, 1, 6, 2, 6, 6};
    if (values.size() == 0){
        cout << "Error: Sequence of integers not received." << endl;
    }
    else if (argc == 1){
        cout << "Number of inversions (fast): " << count_inversions_fast(values.data(), values.size()) << endl;
    }
    else if (argc == 2){

        cout << "Number of inversions (slow): " << count_inversions_slow(values.data(), values.size()) << endl;
    }

//    for (size_t i = 0; i < values.size(); i++){
//        cout << values[i];
//    }

}
