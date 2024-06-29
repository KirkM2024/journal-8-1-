// Project 2 by Kirk Mashburn.

#include "Project2.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
Project2::Project2(unsigned int size) : tableSize(size) {
    table.resize(tableSize);
}

// Destructor
Project2::~Project2() {
    for (auto node : table) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
}

// Add Courses
void Project2::addCourses(const vector<Course>& listCourse) {
    std::cout << "Adding courses..." << std::endl;
    // Loop through courses.
    for (const auto& course : listCourse) {
        // Call insertCourse.
        insertCourse(course);
    }
}

// Insert Course
void Project2::insertCourse(const Course& course) {
    // Create key, with deliniator of 4.
    unsigned int key = hash(stoi(course.courseName.substr(4)));
    // Create Hash value.
    unsigned int hashValue = hash(key);

    Node* newNode = new Node(course, key);
    if (table[hashValue] == nullptr) {
        table[hashValue] = newNode;
    }
    else {
        Node* temp = table[hashValue];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Search Course
Project2::Course Project2::searchCourse(const string& coursenum){
    // Create key, with deliniator of 4.
    unsigned int key = hash(stoi(coursenum.substr(4)));
    // Create Hash value.
    unsigned int hashValue = hash(key);

    // Create temp node for searching.
    Node* temp = table[hashValue];
    // While tempNode is not empty.
    while (temp != nullptr) {
        // If course name is found return course.
        if (temp->course.courseName == coursenum) {
            return temp->course;
        }
        // Keep searching.
        temp = temp->next;
    }
    
    
}



// Print Courses
void Project2::printCourses() const {
    // Loop through each node for the size of the table.
    for (unsigned int i = 0; i < tableSize; i++) {
        // Set temp node to current place in the table.
        Node* temp = table[i];
        // If temp node is not empty.
        while (temp != nullptr) {
            // Print out each courses data.
            std::cout << "Course: " << temp->course.courseName << ", Title: " << temp->course.title << std::endl;
            // Continue searching.
            temp = temp->next;
        }
    }
}


// Read file line by line with ifstream.
// credit: https://stackoverflow.com/questions/7868936/
vector<Project2::Course> readfile(const string& filename) {
    vector<Project2::Course> courses;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        // Create a streamstream for every line read. 
        istringstream ss(line);
        // Create course object "course"
        Project2::Course course;
        
        // Create string to check for prerequisites.
        string preq;

        // Use getline built in function. 
        // If getline has a courseName read it.
        if (getline(ss, course.courseName, ',')) {
            //If getline has a title read it.
            if (getline(ss, course.title, ',')) {
                // If getline has a prereq read it.
                while (getline(ss, preq, ',')){
                    // If there is a prereq do the below.
                    if (!preq.empty()) {
                        // Trim any leading/trailing spaces
                        preq.erase(0, preq.find_first_not_of(" \t\r\n"));
                        preq.erase(preq.find_last_not_of(" \t\r\n") + 1);
                        // add preq to the course object. 
                        course.prerequisites.push_back(preq);
                    }
                }

                // Output for verification and testing.
                /**cout << "Read course: " << course.courseName << ", " << course.title << endl;
                    *for (const auto& prereq : course.prerequisites) {
                        cout << "Prerequisite: " << prereq << endl;
                    *}
                */

                // Add course to the end of the courses vector.
                courses.push_back(course);
            }
            else {
                // error checking for title.
                cerr << "Error: Failed to read title from line: " << line << endl;
            }
        }
        else {
            // error checking for courseName.
            cerr << "Error: Failed to read courseName from line: " << line << endl;
        }
    }

    return courses;
}


// Main menu function modified from previous assignments.
int main()
{
    Project2 myCourses;
    vector<Project2::Course> courses;
    int choice = 0;
    string input;

    while (choice != 9) {
        cout << "1: Load file into data structure." << endl;
        cout << "2: Print all courses." << endl;
        cout << "3: Search by course title." << endl;
        cout << "9: Exit the program." << endl;
        cout << "Enter your choice: ";
        cin >> choice; 

        switch (choice) {
        case 1:
            // Read from the file.
            courses = readfile("CS 300 ABCU_Advising_Program_Input.csv");
            // Once the file is read build courses.
            myCourses.addCourses(courses);
            break;

        case 2:
            // Print courses.
            myCourses.printCourses();
            break;
 
        case 3:
            cout << "input course number to search: ";
            cin >> input;

            try {
                // Search for a specific course
                Project2::Course course = myCourses.searchCourse(input);
                cout << "Found course: " << course.title << " " << course.courseName << "\n";
            }
            catch (const runtime_error& e) {
                cout << e.what() << "\n";
            }
            catch (const exception& e) {
                // This will catch other exceptions derived from std::exception
                cout << "Exception: " << e.what() << "\n";
            }
            break;
        case 9:
            cout << "Exiting Program, Good Bye..." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    }
    return 0;
}

