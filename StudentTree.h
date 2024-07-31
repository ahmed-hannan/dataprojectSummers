#pragma once
#include "Student.h"

using namespace std;

struct StudentNode {
	Student data;
	StudentNode* left, * right;
	int height;

	StudentNode(Student x = Student())
		: data(x), left(nullptr), right(nullptr), height(1) {}
};

class StudentTree {
private:
	StudentNode* root;

	int height(StudentNode* n) { return n ? n->height : 0; }

	int getBalance(StudentNode* n) {
		return n ? height(n->left) - height(n->right) : 0;
	}

	StudentNode* rightRotate(StudentNode* y) {
		StudentNode* x = y->left;
		StudentNode* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	StudentNode* leftRotate(StudentNode* x) {
		StudentNode* y = x->right;
		StudentNode* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		return y;
	}

	StudentNode* insert(StudentNode* n, Student data) {
		if (!n)
			return new StudentNode(data);

		if (data < n->data)
			n->left = insert(n->left, data);
		else if (data > n->data)
			n->right = insert(n->right, data);
		else
			return n;

		n->height = 1 + max(height(n->left), height(n->right));

		int balance = getBalance(n);

		if (balance > 1 && data < n->data)
			return rightRotate(n);

		if (balance < -1 && data > n->data)
			return leftRotate(n);

		if (balance > 1 && data > n->left->data) {
			n->left = leftRotate(n->left);
			return rightRotate(n);
		}

		if (balance < -1 && data < n->right->data) {
			n->right = rightRotate(n->right);
			return leftRotate(n);
		}

		return n;
	}

	void inOrder(StudentNode* root) {
		if (root) {
			inOrder(root->left);
			root->data.displayDetails();
			inOrder(root->right);
		}
	}

public:
	StudentTree() : root(nullptr) {}

	void insert(Student data) { root = insert(root, data); }


	StudentNode* minValueNode(StudentNode* s) {
		StudentNode* current = s;
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	StudentNode* deleteNode(StudentNode* root, Student data) {
		if (root == nullptr)
			return root;

		if (data < root->data)
			root->left = deleteNode(root->left, data);
		else if (data > root->data)
			root->right = deleteNode(root->right, data);
		else {
			if ((root->left == nullptr) || (root->right == nullptr)) {
				StudentNode* temp = root->left ? root->left : root->right;

				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else
					*root = *temp;
				delete temp;
			}
			else {
				StudentNode* temp = minValueNode(root->right);
				root->data = temp->data;
				root->right = deleteNode(root->right, temp->data);
			}
		}

		if (root == nullptr)
			return root;

		root->height = 1 + max(height(root->left), height(root->right));

		int balance = getBalance(root);

		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotate(root);

		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotate(root);

		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	//MEMBER FUNCTION THAT READS STUDENT INFO FROM A TXT FILE
	void readDataFromFile(int& strength) {
		strength = 60;
		string filename = "studentdata/DataStructures_Students.txt";
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Could not open the file!\n";
			return;
		}

		string line;
		vector<string> ids, names;

		// Read the first 60 lines as IDs
		for (int i = 0; i < 60; ++i) {
			if (getline(file, line)) {
				ids.push_back(line);
			}
			else {
				cerr << "Error reading ID at line " << i + 1 << endl;
				return;
			}
		}

		// Read the next 60 lines as names
		for (int i = 0; i < 60; ++i) {
			if (getline(file, line)) {
				names.push_back(line);
			}
			else {
				cerr << "Error reading name at line " << i + 61 << endl;
				return;
			}
		}

		// Ensure the number of IDs matches the number of names
		if (ids.size() != names.size()) {
			cerr << "Mismatch between the number of IDs and names\n";
			return;
		}

		vector<Student> students;
		// Create Student objects and store in the vector
		for (size_t i = 0; i < ids.size(); ++i) {
			students.push_back(Student(names[i], ids[i]));
		}

		// Insert each student
		for (const auto& student : students) {
			insert(student);
		}
	}

	StudentNode* search(StudentNode* root, string key) {

		if (root == nullptr || root->data.getID() == key)
		{
			if (!root)
				cout << "Student does not exist:(\n";
			return root;
		}

		if (root->data.getID() < key)
			return search(root->right, key);

		return search(root->left, key);
	}

	void userAddStudent() {
		Student toadd;
		cin >> toadd;
		insert(toadd);
		cout << "Student added successfully :)\n";
		cin.ignore();
	}

	void deleteUI() {
		cout << "Enter roll number of student to remove: ";
		string toremove;
		getline(cin >> ws, toremove);
		if (!isValidFormat(toremove))
		{
			cout << "Invalid roll number :)\n";
			return;
		}
		StudentNode* beremoved = search(root, toremove);
		if (beremoved)
		{
			beremoved->data.displayDetails();
			char choice = NULL;
			cout << "Remove student?(Y/N) Changes cannot be undone: ";
			do {
				cin >> choice;
			} while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N');

			if (choice == 'y' || choice == 'Y')
				deleteNode(root, beremoved->data);
		}
	}

	void searchUI() {
		cout << "Enter roll number of student to search: ";
		string tosearch;
		getline(cin >> ws, tosearch);
		if (!isValidFormat(tosearch))
		{
			cout << "Invalid roll number :)\n";
			cin.ignore();
			return;
		}
		StudentNode* searched = search(root, tosearch);
		if (searched)
		{
			searched->data.displayDetails();
		}
		else
		{
			cout << "Student not found :)\n";
		}
		cin.ignore();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}



	void displayTree() {
		if (root)
			inOrder(root);

		else
			cout << "Class empty :)\n";
		cin.ignore();
	}


	void Driver() {
		int choice = -1;
		do {
			system("cls");
			cout << "STUDENTS\n1) View All\n2) Add\n3) Remove\n4) Search\n5) Exit\n>Select action: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				displayTree();
				cin.get();
				break;
			}
			case 2: {
				cout << "ADD STUDENT\n";
				userAddStudent();
				break;
			}
			case 3: {
				cout << "REMOVE STUDENT\n";
				deleteUI();
				break;
			}

			case 4: {
				cout << "SEARCH STUDENT\n";
				searchUI();
				break;
			}

			case 5: {
				break;
			}
			default:
				cout << "Invalid choice :)\n";
			}

		} while (choice != 5);
	}
};
