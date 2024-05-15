/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Yash Yagnik and Kyle Miller
 * Version     : 1.0
 * Date        : 12/6/2023
 * Description : Implementation of Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>

using namespace std;

long INF = __LONG_MAX__;
const int MAX_VERTICES = 26;

int len(long num) {
    if (num == 0) return 1;
    int length = 0;
    while (num != 0) {
        length++;
        num /= 10;
    }
    return length;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(const vector<vector<long>>& matrix, const string &label, int num_vertices,
    const bool use_letters = false, const bool pathlength = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
    len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
            for (int j = 0; j < num_vertices; j++) {
                cout << " " << setw(max_cell_width);
                if (matrix[i][j] == INF) {
                    cout << "-";
                } else if (use_letters) {
                    if(matrix[i][j] == i || matrix[i][j] == j){
                        cout << "-";
                    }else if(matrix[i][j] == -1){
                        cout << static_cast<char>(matrix[i][j] + '.');
                    }else{
                        cout << static_cast<char>(matrix[i][j] + 'A');
                    }
                } else {
                    cout << matrix[i][j];
                }
            }
            cout << endl;
    }
    cout << endl;
}

void floyd(vector<vector<long>>& dist, vector<vector<long>>& next) {
    int V = dist.size();
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = k;
                }
            }
        }
    }
}


string constructPath(int u, int v, const vector<vector<long>>& next) {
    if (u == v){
        return string(1, 'A' + u);
    }
    if (next[u][v] == -1){
        return "none";
    }
    string path = string(1, 'A' + u);
    while (u != v) {
        u = next[u][v];
        path += " -> " + string(1, 'A' + u);
    }
    return path;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    ifstream input_file(argv[1]);
    if (!input_file) {
        cout << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    string firstLine;
    getline(input_file, firstLine);
    istringstream iss(firstLine);
    int V;
    if (!(iss >> V)) {
        cout << "Error: Invalid number of vertices '" << firstLine << "' on line 1." << endl;
        return 1;
    }
    if (V < 1 || V > MAX_VERTICES) {
        cout << "Error: Invalid number of vertices '" << V << "' on line 1." << endl;
        return 1;
    }

    vector<vector<long>> dist(V, vector<long>(V, INF));
    vector<vector<long>> next(V, vector<long>(V, -1));
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
        next[i][i] = -1; 
    }

    string line;
    int lineNum = 1;
    while (getline(input_file, line)) {
        lineNum++;
        if (line.empty()) continue;

        istringstream iss(line);
        string u, v, weightstr;
        int weight;
        if (!(iss >> u >> v >> weightstr)) {
            cout << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
            return 1;
        }
        if (u.length() != 1 || u[0] < 'A' || u[0] >= 'A' + V) {
            cout << "Error: Starting vertex '" << u << "' on line " << lineNum << " is not among valid values A-" << char('A' + V - 1) << "." << endl;
            return 1;
        }
        if (v.length() != 1 || v[0] < 'A' || v[0] >= 'A' + V) {
            cout << "Error: Ending vertex '" << v << "' on line " << lineNum << " is not among valid values A-" << char('A' + V - 1) << "." << endl;
            return 1;
        }
        istringstream w(weightstr);
        if (!(w >> weight) || weight <= 0) {
            cout << "Error: Invalid edge weight '" << weightstr << "' on line " << lineNum << "." << endl;
            return 1;
        }

        int ui = u[0] - 'A';
        int vi = v[0] - 'A';
        dist[ui][vi] = weight;
        next[ui][vi] = vi;
    }
    display_table(dist, "Distance matrix:", V, false, false);
    floyd(dist, next);
    display_table(dist, "Path lengths:", V, false, true);
    display_table(next, "Intermediate vertices:", V, true, false);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << char('A' + i) << " -> " << char('A' + j)
                << ", distance: " << (dist[i][j] == INF ? "infinity" : to_string(dist[i][j]))
                << ", path: " << constructPath(i, j, next) << endl;
        }
    }

    return 0;
}