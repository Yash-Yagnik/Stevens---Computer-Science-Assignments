/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Vraj Patel and Yash Yagnik
 * Date        : 10/17/23
 * Description : Solves the waterjug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions, State *_parent) :           // changed struct to take in parent as parameter
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }


};

void bfs(int a, int b, int c, int A, int B, int C){
    bool **array = new bool*[a + 1];                       // creates 2D arrray of booleans to store if state has been visited or not
    for(int i = 0; i < (a + 1); i++){
        array[i] = new bool[b + 1];
        fill(array[i], array[i] + (b + 1), false);
    }
    queue<State*> q;         // queue to store states that are created
    State *s = new State(0, 0, c, "Initial state.", nullptr);   // initial state
    State cur = *s;      // state that stores the current state being visited
    stack<State> sol;    // stack to store the reversed order for the solution
    queue<State*> toDel; // queue to delete the states that were popped from queue afterwards 
    bool init = false;   
    
    q.push(s);
    while(q.empty() != true){      // loops until queue is empty and all possibilites were visited
        State *ad = q.front();     // pointer for the address of of parent for states being created
        cur = *(q.front());        // updates current
        toDel.push(q.front());
        q.pop();

        if(cur.a == A && cur.b == B && cur.c == C){                   // checks if solution is reached
            if(cur.parent == nullptr){                                // checks if the initial state is already the solution
                cout << cur.directions << cur.to_string() << endl;
                init = true;
                break;
            }
            while((cur.parent) != nullptr){                          // add states linking up to the solution to stack
                sol.push(cur);
                cur = *(cur.parent);
            }
            sol.push(*s);                                           // pushes on initial state
            while(sol.empty() != true){                            // prints out solution
                cout << sol.top().directions << sol.top().to_string() << endl;
                sol.pop();
            }
            break;
        }
        else if(array[cur.a][cur.b] == true){        // checks if state has been visited
            continue;
        }
        else{
            array[cur.a][cur.b] = true;
            if(cur.c != 0 && cur.a != a){             // pouring from C to A
                if((cur.c + cur.a) <= a){       // checks if all of the gallon will be poured
                    if(cur.c == 1){
                        q.push(new State((cur.c + cur.a), cur.b, 0, "Pour " + to_string(cur.c) + " gallon from C to A.", ad));
                    }
                    q.push(new State((cur.c + cur.a), cur.b, 0, "Pour " + to_string(cur.c) + " gallons from C to A.", ad));
                }
                else{
                    if((cur.c - (cur.c - (a - cur.a))) == 1){
                        q.push(new State(a, cur.b, (cur.c - (a - cur.a)), "Pour " + to_string(cur.c - (cur.c - (a - cur.a))) + " gallon from C to A.", ad));
                    }
                    q.push(new State(a, cur.b, (cur.c - (a - cur.a)), "Pour " + to_string(cur.c - (cur.c - (a - cur.a))) + " gallons from C to A.", ad));
                }
            }
            if(cur.b != 0 && cur.a != a){            // pouring from B to A
                if((cur.b + cur.a) <= a){      // checks if all of the gallon will be poured
                    if(cur.b == 1){
                        q.push(new State((cur.b + cur.a), 0, cur.c, "Pour " + to_string(cur.b) + " gallon from B to A.", ad));
                    }
                    q.push(new State((cur.b + cur.a), 0, cur.c, "Pour " + to_string(cur.b) + " gallons from B to A.", ad));
                }
                else{
                    if((cur.b - (cur.b - (a - cur.a))) == 1){
                        q.push(new State(a, (cur.b - (a - cur.a)), cur.c, "Pour " + to_string(cur.b - (cur.b - (a - cur.a))) + " gallon from B to A.", ad));
                    }
                    q.push(new State(a, (cur.b - (a - cur.a)), cur.c, "Pour " + to_string(cur.b - (cur.b - (a - cur.a))) + " gallons from B to A.", ad));
                }
            }
            if(cur.c != 0 && cur.b != b){          // pouring from C to B
                if((cur.c + cur.b) <= b){       // checks if all of the gallon will be poured
                    if(cur.c == 1){
                        q.push(new State(cur.a, (cur.c + cur.b), 0, "Pour " + to_string(cur.c) + " gallon from C to B.", ad));
                    }
                    q.push(new State(cur.a, (cur.c + cur.b), 0, "Pour " + to_string(cur.c) + " gallons from C to B.", ad));
                }
                else{
                    if((cur.c - (cur.c - (b - cur.b))) == 1){
                        q.push(new State(cur.a, b, (cur.c - (b - cur.b)), "Pour " + to_string(cur.c - (cur.c - (b - cur.b))) + " gallon from C to B.", ad));
                    }
                    q.push(new State(cur.a, b, (cur.c - (b - cur.b)), "Pour " + to_string(cur.c - (cur.c - (b - cur.b))) + " gallons from C to B.", ad));
                }
            }
            if(cur.a != 0 && cur.b != b){            // pouring from A to B
                if((cur.a + cur.b) <= b){      // checks if all of the gallon will be poured
                    if(cur.a == 1){
                        q.push(new State(0, (cur.a + cur.b), cur.c, "Pour " + to_string(cur.a) + " gallon from A to B.", ad));
                    }
                    q.push(new State(0, (cur.a + cur.b), cur.c, "Pour " + to_string(cur.a) + " gallons from A to B.", ad));
                }
                else{
                    if((cur.a - (cur.a - (b - cur.b))) == 1){
                        q.push(new State((cur.a - (b - cur.b)), b, cur.c, "Pour " + to_string(cur.a - (cur.a - (b - cur.b))) + " gallon from A to B.", ad));
                    }
                    q.push(new State((cur.a - (b - cur.b)), b, cur.c, "Pour " + to_string(cur.a - (cur.a - (b - cur.b))) + " gallons from A to B.", ad));
                }
            }
            if(cur.b != 0 && cur.c != c){             // pouring from B to C
                if((cur.b + cur.c) <= c){      // checks if all of the gallon will be poured
                    if(cur.b == 1){
                        q.push(new State(cur.a, 0, (cur.b + cur.c), "Pour " + to_string(cur.b) + " gallon from B to C.", ad));
                    }
                    q.push(new State(cur.a, 0, (cur.b + cur.c), "Pour " + to_string(cur.b) + " gallons from B to C.", ad));
                }
                else{
                    if((cur.b - (cur.b - (c - cur.c))) == 1){
                        q.push(new State(cur.a, (cur.b - (c - cur.c)), c, "Pour " + to_string(cur.b - (cur.b - (c - cur.c))) + " gallon from B to C.", ad));
                    }
                    q.push(new State(cur.a, (cur.b - (c - cur.c)), c, "Pour " + to_string(cur.b - (cur.b - (c - cur.c))) + " gallons from B to C.", ad));
                }
            }
            if(cur.a != 0 && cur.c != c){            // pouring from A to C
                if((cur.a + cur.c) <= c){     // checks if all of the gallon will be poured
                    if(cur.a == 1){
                        q.push(new State(0, cur.b, (cur.a + cur.c), "Pour " + to_string(cur.a) + " gallon from A to C.", ad));
                    }
                    q.push(new State(0, cur.b, (cur.a + cur.c), "Pour " + to_string(cur.a) + " gallons from A to C.", ad));
                }
                else{
                    if((cur.a - (cur.a - (c - cur.c))) == 1){
                        q.push(new State((cur.a - (c - cur.c)), cur.b, c, "Pour " + to_string(cur.a - (cur.a - (c - cur.c))) + " gallon from A to C.", ad));
                    }
                    q.push(new State((cur.a - (c - cur.c)), cur.b, c, "Pour " + to_string(cur.a - (cur.a - (c - cur.c))) + " gallons from A to C.", ad));
                }
            }
            
        }

    }
    if(q.empty() == true){  // checks if initial state was the solution, prints no solution otherwise
        if(init == false){
            cout << "No solution." << endl;
        }
    }
    else{
        while(q.empty() != true){         // deletes states left in q
            delete q.front();
            q.pop();
        }
    }

    for(int i = 0; i < (a + 1); i++){     // deletes 2D array 
        delete [] array[i];
    }
    delete [] array;

    while(toDel.empty() != true){        // deletes states that were popped from q
        delete toDel.front();
        toDel.pop();
    }
}



int main(int argc, char* argv[]) {
    // State s(0, 0, 8, "Initial state.");
    // cout << s.to_string() << endl;
    // s.a += 3;
    // s.c -= 3;
    // cout << s.to_string() << endl;
    // return 0;

    if(argc != 7){      // checks for correct num of arguments
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    }
    else{
        int num;
        int vals [6];
        istringstream iss;
        for(int i = 1; i < argc; i++){   // checks if valid arguments are inputted
            iss.str(argv[i]);
            if(!(iss >> num) || num < 0 || (num == 0 && i <= 3)){
                if(i <= 3){
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "; 
                }
                else{
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug "; 
                }
                if(i == 1 || i == 4){
                    cerr << "A." << endl;
                }
                if(i == 2 || i == 5){
                    cerr << "B." << endl;
                }
                if(i == 3 || i == 6){
                    cerr << "C." << endl;
                }
                return 0;
            }
            else{
                vals[i - 1] = num;
            }
            iss.clear();
        }

        if(vals[3] > vals[0]){
            cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        }
        else if(vals[4] > vals[1]){
            cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        }
        else if(vals[5] > vals[2]){
            cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        }
        else if(vals[3] + vals[4] + vals[5] != vals[2]){
            cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        }
        else{    // runs bfs if all arguments are correct
            bfs(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]);
        }
    }
}
