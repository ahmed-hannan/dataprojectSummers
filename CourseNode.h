#pragma once
#include "StudentTree.h"
#include "QuizHeap.h" 

struct CourseNode {
	// Members
	CourseNode* front, * back;
	int data, strength;
	string name, code;
	StudentTree* students;
	QuizHeap* qheap;
	int numquizzes;


	// Constructor
	CourseNode(int val = 0, string name = "", string code = "", int s = 0) {
		this->data = val;
		strength = s;
		front = back = nullptr;
		this->name = name;
		this->code = code;
		students = nullptr;
		qheap = nullptr;
		numquizzes = 0;
	}

	void initializeStudents() {
		students = new StudentTree;
		students->readDataFromFile(strength);
	}

	void initializeQuizHeap() {
		qheap = new QuizHeap;
		qheap->readDataFromFile();
	} 

	void displayCourseDetails() {
		cout << name << "(" << code << ")\n";
	}

	void Driver() {
		int choice = -1;
		do {
			system("cls");
			displayCourseDetails();
			cout << "1) Students\n2) View Quiz Marks\n3) Exit\nSelect action: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				cin.ignore();
				//cout << "Students in ";
				students->Driver();
				break;
			}

			case 2: {
				cout << "Quiz marks of ";
				displayCourseDetails();
				qheap->print();
				cin.ignore();
				break;
			}
			case 3: {
				break;
			}
			default:
				cout << "Invalid choice :)\n";
			}
			if (choice != 3)
				cin.ignore();
		} while (choice != 3);
	}
};