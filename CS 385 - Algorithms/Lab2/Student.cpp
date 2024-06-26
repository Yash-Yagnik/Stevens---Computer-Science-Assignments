/*******************************************************************************
 * Name        : Student.cpp
 * Author      : Yash Yagnik
 * Date        : 9/15/2023
 * Description : Student Class
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
    Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id}{

    }
    string full_name() const{
        cout << first_ << " " << last_;
        return 0;
    }

    int id() const{
        return id_;
    }

    float gpa() const {
        return gpa_;
    }

    void print_info() const {
        cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: " << id_<< endl;
    }

    /**
    * Takes a vector of Student objects, and returns a new vector
    * with all Students whose GPA is < 1.0.
    */




private:
    string first_, last_;
    float gpa_;
    int id_;
};

vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    // Iterates through the students vector, appending each student whose gpa is
    // less than 1.0 to the failing_students vector.
    for(size_t i = 0; i < students.size(); i++) {
        if (students[i].gpa() < 1.00){
            failing_students.push_back(students[i]);
        }
    }
    return failing_students;
}

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
    for(size_t i = 0; i < students.size(); i++){
        students[i].print_info();
    }
}


int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    }
    while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:" ;
    // Print a space and the word 'None' on the same line if no students are failing.
    // Otherwise, print each failing student on a separate line.
    if(find_failing_students(students).size() > 0){
        cout << endl;
        print_students(find_failing_students(students));
        return 0;
    }
    else{
        cout << " None";
        return 0;
    }
}
