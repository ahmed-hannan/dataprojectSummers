#pragma once
#include "CourseNode.h"

int classnumber = 0;

using namespace std;




QuizHeap* Addheap(QuizHeap* list, QuizHeap* newone, int num)
{
	QuizHeap* newList = new QuizHeap[num + 1];
	for (int i = 0; i < num; i++)
	{
		newList[i] = list[i];
	}
	newList[num] = *newone;
	return newList;
}

Quiz2* Addheap(Quiz2* list, Quiz2* newone, int num)
{
	Quiz2* newList = new Quiz2[num + 1];
	for (int i = 0; i < num; i++)
	{
		newList[i] = list[i];
	}
	newList[num] = *newone;
	return newList;
}




class DoublyCircular {
	CourseNode* head;
	CourseNode* tail;
	int classnumber;
	

public:

	DoublyCircular() : head(nullptr), tail(nullptr), classnumber(0) {}

	void insertion(string, string);
	void insertNode(int, string, string);
	void deleteVal(int);
	void deleteNode(string n);
	void display();
	void deleteNode(CourseNode*);
	void deletion(string code);
	CourseNode* getHead() { return head; }
	bool classExists(string NodeCode);
	bool stringsEqual(string NodeCode, string currCode);
	CourseNode* checkClassNumber(int);
	void filehandlerClasses();
	bool userInputGiven();
	void userInputToDCLL();
	void classEventHandler();
	void classesUI();
	void singleClassManagement();
	void quizLoader();
};

bool DoublyCircular::classExists(string NodeCode) {
	CourseNode* temp = head;
	if (!temp)
		return false;

	do {
		if (stringsEqual(NodeCode, temp->code)) {
			return true;
		}
		temp = temp->front;
	} while (temp != head);
	return false;
}

bool DoublyCircular::stringsEqual(string NodeCode, string currCode) {
	return NodeCode == currCode;
}

void DoublyCircular::deletion(string code) {
	CourseNode* temp = head;
	bool found = false;
	while (temp->front) {
		if (code == temp->code || code == temp->name) {
			found = true;
			break;
		}
		temp = temp->front;
		if (temp == head)
			break;
	}

	if (found) {
		deleteNode(temp);
		return;
	}

	cout << "Not found in the list" << endl;
}

void DoublyCircular::insertion(string n, string c2) {
	string c;
	int idx = 0;
	while (c2[idx] != '\0') // removing spaces
	{
		if (c2[idx] != ' ')
			c += c2[idx];
		idx++;
	}

	if (!head) {
		head = new CourseNode(0, n, c);
		head->front = head;
		head->back = head;
		tail = head;
		classnumber++;
		return;
	}
	classnumber++;
	insertNode(head->data + 1, n, c);
}

void DoublyCircular::deleteNode(string n) {
	CourseNode* temp = head;
	int value = -1;
	while (temp->front) {
		if ((temp->front->name == n) || (temp->front->code == n)) {
			value = temp->data;
			deleteVal(value);
		}
		temp = temp->front;
		if (temp == head)
			break;
	}

	if (value == -1) {
		cout << "Course not found :(\n" << endl;
		return;
	}
}

void DoublyCircular::insertNode(int val, string n, string c2) {
	string c;
	int idx = 0;
	while (c2[idx] != '\0') // removing spaces
	{
		if (c2[idx] != ' ')
			c += c2[idx];
		idx++;
	}
	if (classExists(c)) {
		classnumber--;
		return;
	}

	CourseNode* newcourse = new CourseNode(val, n, c);
	newcourse->initializeStudents();
	newcourse->initializeQuizHeap();
	if (!head) // empty;
	{
		head = newcourse;
		head->back = head;
		head->front = head;
		tail = head;
		return;
	}
	if (head == tail) {
		tail->front = newcourse;
		CourseNode* temp = tail->front;
		temp->back = tail;
		tail = tail->front;
		tail->front = head;
		head->back = tail;
		return;
	}

	tail->front = newcourse;
	CourseNode* temp = tail->front;
	temp->back = tail;
	tail = tail->front;
	tail->front = head;
	head->back = tail;
	return;
}

void DoublyCircular::deleteVal(int val) {
	if (!head) // edge case
	{
		return;
	}

	if (head->data == val) {
		if (head == tail) {
			head = tail = nullptr;
			return;
		}

		head = head->front;
		head->back = tail;
		tail->front = head;
		return;
	}

	if (tail->data == val) {
		tail = tail->back;
		tail->front = head;
		head->back = tail;
		return;
	}

	CourseNode* temp = head;
	bool found = false;
	while (temp->front) {
		if (temp->front->data == val) {
			found = true;
			break;
		}

		temp = temp->front;
	}

	if (!found)
		return;

	CourseNode* temp2 = temp->front;
	temp->front = temp2->front;
	temp2->front->back = temp;
}

void DoublyCircular::display() {
	if (!head)
		return;
	//cout << '\n';
	CourseNode* temp = head;
	do {
		cout << temp->data + 1 << ") " << temp->name
			<< "(" << temp->code << ")\n";
		temp = temp->front;
	} while (temp != head);
}

void DoublyCircular::deleteNode(CourseNode* Dptr) {
	if (!head) // edge case
		return;
	if (head == tail) // only one StudentNode
	{
		if (head != Dptr) // edge case
		{
			return;
		}

		head = nullptr; // linked list is now empty
		return;
	}

	if (head == Dptr) // head StudentNode deleting
	{
		head = head->front;
		head->back = tail;
		tail->front = head;
		return;
	}

	if (tail == Dptr) {
		tail = tail->back;
		tail->front = head;
		head->back = tail;
		return;
	}

	CourseNode* temp = head;
	bool found = false;
	while (temp->front) {
		if (Dptr == temp) {
			found = true;
			break;
		}

		temp = temp->front;
		if (temp == head)
			break;
	}

	if (!found)
		return;

	CourseNode* temp2 = temp->front;
	temp->front = temp2->front;
	temp2->back = temp;
}

CourseNode* DoublyCircular::checkClassNumber(int x) {

	if (!head)
		return nullptr;
	if (x < 0)
		return nullptr;

	CourseNode* temp = head;

	while (temp) {
		if (temp->data == x)
			return temp;
		temp = temp->front;
	}
	return nullptr;
}

void DoublyCircular::filehandlerClasses() { 
	system("cls");
	cout << "COURSE MANAGEMENT TOOL\n";
	char choice;
	string filename, currline, coursename, courseid;
	do {
		cout << "Load default classes? (Y/N): ";
		cin >> choice;
	} while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N');
	if (choice == 'y' || choice == 'Y')
	{
		filename = "classes.txt";
		cout << "Default classes loaded :D\nPress any key to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.ignore();
	}
	else
	{
		cout << "Enter name of the file classes to load classes from: ";
		getline(cin >> ws, filename);
	}

	ifstream ClassInput(filename); // read
	while (!ClassInput.is_open())  // failed to find
	{
		cout << "Failed to find file, please re-enter the file name" << endl;
		getline(cin >> ws, filename);
		ClassInput.open(filename);
	}

	while (getline(ClassInput, currline)) {
		coursename = courseid = "";
		int idx = 0;
		if (currline[0] == '!') // Designated as a comment
			continue;
		if (currline[0] == '\0') // empty lines
			continue;

		while (currline[idx] != ',') {
			coursename += currline[idx];
			idx++;
			if (currline[idx] == '\0') {
				cout << "ERROR, standard not followed";
				continue;
			}
		}
		idx++; // skipping the ,
		while (currline[idx] != '\0') {
			courseid += currline[idx];
			idx++;
		}

		insertNode(classnumber++, coursename, courseid);
	}
}

bool DoublyCircular::userInputGiven() {
	int choice;
	cin >> choice;

	while (choice < 1 || choice > 4) {
		cout << "->";
		cin >> choice;
	}
	string name, code;
	cin.ignore();
	switch (choice) {
	case 1:
		cout << "Enter course name: ";
		getline(cin, name);
		cout << "Enter course ID: ";
		getline(cin, code);
		insertion(name, code);
		break;

	case 2:
		cout << "Enter name or code of the class to be deleted: ";
		getline(cin, name);
		deletion(name);
		break;

	case 3:
		display();
		break;
	case 4:
		return false;
	}
	return true;
}

void DoublyCircular::userInputToDCLL() {
	cout << "User Input Handler has been called!\nEnter 1 to enter a course\nEnter 2 to delete an entered course\nEnter 3 to display all current courses\nEnter 4 to exit the "
		"handler\n: ";
	while (userInputGiven())
		cout << "Choose Option: ";

	string input;
	cout << "Enter more classes using file? yes/no\n";
	cin >> input;
	if (input == "YES" || input == "yes" || input == "Yes" || input == "yEs" ||
		input == "yeS") {
		filehandlerClasses();
	}
	userInputToDCLL();
}

void DoublyCircular::classesUI() {
	int choice = -1;
	system("cls");
	display();
	CourseNode* c = nullptr;
	do {
		cout << ">Select course (-1 to return): ";
		cin >> choice;
		if (choice != -1) {
			c = checkClassNumber(choice - 1);
			if (c) {
				break; // exit the loop if a valid course is found
			}
			else {
				cout << "Invalid course number, please try again." << '\n';
			}
		}
	} while (choice != -1);

	if (c) {
		c->Driver();
	}
	else {
		cout << "No valid course selected." << '\n';
	}
}


void DoublyCircular::classEventHandler() {
	cout << "COURSE MANAGEMENT TOOL\n";
	filehandlerClasses();
	while (1) {
		system("cls");
		int choice = -1;
		cout << "COURSE MANAGEMENT TOOL\n1) View All Classes\n2) Add Class\n3) Delete Class\n4) Reload Classes\n5) Choose a class for further actions\n6) Exit Event Handler\n>Select action: ";
		while (choice > 6 || choice < 1) {
			cin >> choice;
			if (choice == 6)
				return;
		}

		string name, code;
		cin.ignore();
		switch (choice) {
		case 1:
		{
			classesUI();
			cin.get();
			break;
		}
		case 2:
			cout << "Enter name of class: ";
			getline(cin >> ws, name);
			cout << "Enter code of class: ";
			getline(cin >> ws, code);
			insertion(name, code);
			break;

		case 3:
			cout << "Enter code or name of the class to be deleted: ";
			getline(cin, name);
			deletion(name);
			break;

		case 4:
			cout << "Reloading classes...\n";
			// Dummy code for reloading classes
			filehandlerClasses();
			cout << "Classes reloaded successfully.\n";
			break; 

		case 5:
			singleClassManagement();
			break;
		case 6: 
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice" << endl;
		}
	}

}
void DoublyCircular::singleClassManagement()
{
	system("cls");
	cout << "Welcome to the Event Handler for a single class 1:< " << endl;
	CourseNode* curr = head;
	int choice = -1;
	while (1)
	{
		cout << "The current class is " << head->name << " with code = " << head->code << endl;
		cout << "Enter 1) To display current quizzes\n2) To add a new quiz\n3)To move to next class\n4) To move to previous class\n5) to exit.\n->";
		cin >> choice;

		string filename;
		fstream file;
		Quiz2* Qptr;
		switch (choice)
		{
		case 1:
			//curr->qheap->print();
			for (int i = 0; i < curr->numquizzes; i++)
			{
				int val = i;
				
				cout << "Quiz Average = " << curr->quizzes[val].average();
				curr->quizzes[val].highest();

			}
			cin.ignore();
			cin.ignore();
			break;
		case 2:
			//string filename;
			cout << "Enter file name to load quizzes from" << endl;
			cin >> filename;
			//fstream file(filename);
			file.open(filename);
			while (!file.is_open())
			{
				cout << "Enter file name to load quizzes from" << endl;
				cin >> filename;
				file.open(filename);
			}
			Qptr = new Quiz2;
			Qptr->readDataFromFile(filename);
			curr->quizzes = Addheap(curr->quizzes, Qptr, curr->numquizzes);
			//curr->quizzes[curr->numquizzes].print();
			curr->numquizzes++;
			
			break;

		case 3:
			curr = curr->front;
			
			break;
		
		case 4:
			curr = curr->back;
			break;
		case 5:
			return;
		}
			
		system("cls");
	}

	
}



