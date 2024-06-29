#ifndef PROJECT2_HPP
#define PROJECT2_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Project2 {

// Creates course structure from assignment HashTable bids.
public:
    // create the object to hold courses
    struct Course {
        string courseName;
        string title;
        vector<string> prerequisites;
    };
    // Use a built in node object to help manipulate course data. 
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        Node() : key(UINT_MAX), next(nullptr) {}
        Node(Course aCourse) : Node() { course = aCourse; }
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) { key = aKey; }
    };

private:
    // Create the hash table of nodes.
    vector<Node*> table;
    unsigned int tableSize;

    // Basic hash function.
    unsigned int hash(int key) const {
        return key % tableSize;
    }

public:
    // Declare functions to use in Project2.cpp.
    Project2(unsigned int size = 100);
    ~Project2();

    void insertCourse(const Course& course);
    Course searchCourse(const string& coursenum);
    void addCourses(const vector<Course>& listCourse);
    void printCourses() const;
    vector<Project2::Course> readfile(const string& filename);
};



#endif // PROJECT2_HPP
