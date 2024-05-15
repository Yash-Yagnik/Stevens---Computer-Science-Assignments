/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Yash Yagnik
 * Date        : 10/16/23
 * Description : Water Jug Puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
# include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions, State *_parent) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void bfs(int a_capacity, int b_capacity, int c_capacity, int a_goal, int b_goal, int c_goal){
    queue<State> solutions;
    //State curr_solution = State(a, b, c, "pour");
    solutions.push(State(0, 0, c_capacity, "Initial state.", nullptr));

    // Declare a 2D array with 'num_rows' rows.
    bool **visited = new bool*[a_capacity + 1];
    // For each row, make an array of 'num_cols' booleans.
    for(int i = 0; i < a_capacity + 1; i++) {
        visited[i] = new bool[b_capacity + 1];
    // Initialize the new row.
        fill(visited[i], visited[i] + b_capacity + 1, false);
    }

    //visited[0][0] = true;


    while (!solutions.empty()) {
        State curr_solution = solutions.front();
        //cout << curr_solution.to_string() << endl;
        solutions.pop();


        if ((curr_solution.a == a_goal) && (curr_solution.b == b_goal) && (curr_solution.c == c_goal)) {

            for(size_t i = 0; i <= solutions.size(); i++){
                State front = solutions.front();
                cout << front.to_string() << endl;
                solutions.pop();
            }

            cout << curr_solution.to_string() << endl;
            cout << curr_solution.parent; //SEG FAULT

        }


        if (!visited[curr_solution.a][curr_solution.b]) {
            visited[curr_solution.a][curr_solution.b] = true;
            if ((curr_solution.a != a_capacity) && c_capacity > 0) {
                if ((a_capacity - curr_solution.a) < curr_solution.c) {
                    solutions.push(State(a_capacity, curr_solution.b, curr_solution.c - (a_capacity - curr_solution.a),
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from C to A.", &solutions.back()));
                } else if ((curr_solution.c + curr_solution.a) < a_capacity) {
                    solutions.push(State(curr_solution.c + curr_solution.a, curr_solution.b, 0,
                                         "Pour " + to_string(curr_solution.c) + " gallons from C to A.", &solutions.back()));
                }
            }

            if (curr_solution.a != a_capacity && b_capacity > 0) {
                if ((a_capacity - curr_solution.a) < curr_solution.b) {
                    solutions.push(State(a_capacity, curr_solution.b, curr_solution.b - (a_capacity - curr_solution.a),
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from B to A.", &solutions.back()));
                } else if ((curr_solution.b + curr_solution.a) < a_capacity) {
                    solutions.push(State(curr_solution.b + curr_solution.a, 0, curr_solution.c,
                                         "Pour " + to_string(curr_solution.b) + " gallons from B to A.", &solutions.back()));
                }
            }

            if (curr_solution.b != b_capacity && c_capacity > 0) {
                if ((b_capacity - curr_solution.b) < curr_solution.c) {
                    solutions.push(State(curr_solution.a, b_capacity, curr_solution.c - (b_capacity - curr_solution.b),
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from C to B.", &solutions.back()));
                } else if ((curr_solution.c + curr_solution.b) <= b_capacity) {
                    solutions.push(State(curr_solution.a, curr_solution.c + curr_solution.b, 0,
                                         "Pour " + to_string(curr_solution.c) + " gallons from C to B.", &solutions.back()));
                }
            }

            if (curr_solution.b != b_capacity && a_capacity > 0) {
                if ((b_capacity - curr_solution.b) < curr_solution.a) {
                    solutions.push(State(curr_solution.a - (b_capacity - curr_solution.b), b_capacity, curr_solution.c,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from A to B.", &solutions.back()));
                } else if ((curr_solution.a + curr_solution.b) <= b_capacity) {
                    solutions.push(State(0, curr_solution.a + curr_solution.b, curr_solution.c,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from A to B.", &solutions.back()));
                }
            }

            if (curr_solution.c != c_capacity && b_capacity > 0) {
                if ((c_capacity - curr_solution.c) < curr_solution.b) {
                    solutions.push(State(curr_solution.a, curr_solution.a - (b_capacity - curr_solution.b), c_capacity,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from B to C.", &solutions.back()));
                } else if ((curr_solution.b + curr_solution.c) <= c_capacity) {
                    solutions.push(State(curr_solution.a, 0, curr_solution.c + curr_solution.b,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from B to C.", &solutions.back()));
                }
            }

            if (curr_solution.c != c_capacity && a_capacity > 0) {
                if ((c_capacity - curr_solution.c) < curr_solution.a) {
                    solutions.push(State(curr_solution.a - (c_capacity - curr_solution.c), curr_solution.b, c_capacity,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from A to C.", &solutions.back()));
                } else if ((curr_solution.a + curr_solution.c) <= c_capacity) {
                    solutions.push(State(0, curr_solution.b, curr_solution.c + curr_solution.a,
                                         "Pour " + to_string(a_capacity - curr_solution.a) + " gallons from A to C.", &solutions.back()));
                }
            }

        }
        }



    if (visited[a_goal][b_goal]){
        cout << "Initial State. " << "(" << 0 << ", " << 0 << ", " << c_capacity << ")" << endl;
    }
    else{
        cout << "No solution." << endl;
    }


    // Delete each row first.
    for(int i = 0; i < a_capacity + 1; i++) {
        delete [] visited[i];
    }
    // Delete the array itself.
    delete [] visited;

    //cout << "No solution." << endl;
}

int main(int argc, char * const argv[]) {
    /*
    State s(0, 0, 8, "Initial state.");
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;
     */
    int userNum;
    int totalGoal = 0;

    if (argc != 7){
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 0;
    }
    else if (atoi(argv[3]) == 0){
        cerr << "Error: Invalid capacity '0' for jug C." << endl;
        return 0;
    }
    else {
        for (int i = 1; i < argc; i++){
            istringstream iss(argv[i]);
            if (atoi(argv[i]) < 0 || !(iss >> userNum) ){
                if (i < 4){

                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug ";
                }
                else{
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug ";
                }

                if (i == 1 || i == 4){
                    cerr << "A." << endl;
                    return 0;
                }
                else if (i == 2 || i == 5){
                    cerr << "B." << endl;
                    return 0;
                }
                else{
                    cerr << "C." << endl;
                    return 0;
                }

            }
            else{
                if (i > 3){
                    totalGoal += userNum;
                    if (i == (argc - 1)){
                        if (atoi(argv[4]) > atoi(argv[1])){
                            cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
                            return 0;
                        }
                        else if (atoi(argv[5]) > atoi(argv[2])){
                            cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
                            return 0;
                        }
                        else if (atoi(argv[6]) > atoi(argv[3])){
                            cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
                            return 0;
                        }

                        else if (totalGoal != atoi(argv[3])){
                            cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
                            return 0;
                        }
                    }
                }
            }
        }
        bfs(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    }



}
