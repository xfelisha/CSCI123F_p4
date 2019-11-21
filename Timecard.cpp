#include<iostream>
#include<string>
#include <iomanip>
#include "Timecard.h"
using namespace std;

//////////CONSTRUCTORS
CTimecard::CTimecard() {
	id = "0000";
	hours = 0.0;
}

CTimecard::CTimecard(std::string new_id, float new_hours) {
	id = new_id;
	hours = new_hours;
}

CTimecard::CTimecard(const CTimecard& emp) {
	id = emp.id;
	hours = emp.hours;
}

CTimecard::~CTimecard() {
}

//////////MUTATORS
void CTimecard::set_hours(float new_hours) {
	if (new_hours < 10) { hours = 10; }
	else if (new_hours > 80) { hours = 80; }
	else { hours = new_hours; }
}

//////////ACCESSORS
float CTimecard::get_hours() { return hours; }

//////////FUNCTIONS
void CTimecard::getInfo() {
	cout << "Enter hours worked by employee: ";
	cin >> hours;
	cout << endl;
}

void CTimecard::showInfo() {
	cout << "Employee ID: " << id << endl;
	cout << "Employee hours: " << hours << endl;
	cout << endl;
}

std::ostream& operator << (std::ostream& out, const CTimecard& c) {
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);
	return out;
}

std::istream& operator >> (std::istream& in, CTimecard& c) {
	in >> c.id >> c.hours;
	return in;
}