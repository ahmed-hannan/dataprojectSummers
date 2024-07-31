#pragma once
#include "libraries.h"
bool isValidFormat(const string&);

struct Student {
private:
	string sname, sid;

public:
	Student(string a = "", string n = "") : sname(a), sid(n) {}
	Student(const Student& other) : sname(other.sname), sid(other.sid) {}

	string getName() const { return sname; }
	void setName(string a) { sname = a; }

	string getID() const { return sid; }
	void setID(string n) { sid = n; }

	void displayDetails() { cout << "ID: " << sid << ", Name: " << sname << '\n'; }


	bool operator<(const Student& other) const {
		return compareID(sid, other.sid) < 0;
	}

	bool operator>(const Student& other) const {
		return compareID(sid, other.sid) > 0;
	}

	bool operator==(const Student& other) const {
		return sname == other.sname && sid == other.sid;
	}

	friend ostream& operator<<(ostream& os, const Student& student) {
		os << "Student Name: " << student.sname << ", Student ID: " << student.sid;
		return os;
	}

	friend istream& operator>>(istream& is, Student& student) {
		//is.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter Student Name: ";
		getline(is >> ws, student.sname);
		do {
			cout << "Enter Student ID: ";
			getline(is >> ws, student.sid);
		} while (!isValidFormat(student.sid));
		return is;
	}

private:
	static int compareID(const string& id1, const string& id2) {
		int batch1 = stoi(id1.substr(0, 2));
		int batch2 = stoi(id2.substr(0, 2));
		int roll1 = stoi(id1.substr(id1.find('-') + 1));
		int roll2 = stoi(id2.substr(id2.find('-') + 1));

		if (batch1 != batch2) {
			return batch1 - batch2; // Lower batch number is greater (ascending order)
		}
		return roll1 - roll2; // Normal roll number comparison (ascending order)
	}
};


bool isValidFormat(const string& str) {
	if (str.size() != 8) {
		return false;
	}

	// Check if the first two characters are digits
	for (int i = 0; i < 2; ++i) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}

	// Check if the third character is a letter
	if (!isalpha(str[2])) {
		return false;
	}

	// Check if the fourth character is a hyphen
	if (str[3] != '-') {
		return false;
	}

	// Check if the last four characters are digits
	for (int i = 4; i < 8; ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}

	return true;
}

