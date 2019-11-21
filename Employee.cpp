#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include "Employee.h"
using namespace std;

//////////CONSTRUCTORS
CEmployee::CEmployee() {
	id = "0000";
	fName = "None";
	lName = "None";
	payRate = 0.00;
	marriagestatus = UNKNOWN;
}

CEmployee::CEmployee(std::string new_id, std::string new_fName, std::string new_lName, float new_payRate, MaritalStatus new_marriagestatus) {
	id = new_id;
	fName = new_fName;
	lName = new_lName;
	payRate = new_payRate;
	marriagestatus = new_marriagestatus;
}

CEmployee::CEmployee(const CEmployee& emp) {
	id = emp.id;
	fName = emp.fName;
	lName = emp.lName;
	payRate = emp.payRate;
	marriagestatus = emp.marriagestatus;
}

CEmployee::~CEmployee() {
}

////////// MUTATORS
void CEmployee::set_payRate(float new_payRate) {
	if (new_payRate < 12.00) { payRate = 12.00; }
	else if (new_payRate > 100.00) { payRate = 100.00; }
	else { payRate = new_payRate; }
}

////////// ACCESSORS
float CEmployee::get_payRate() { return payRate; }

//////////FUNCTIONS
void CEmployee::getInfo()
{
	cout << "Enter employee ID: ";
	cin >> id;
	cout << "Enter employee first and last name, seperated by a space: ";
	cin >> fName >> lName;
	fName[0] = toupper(fName[0]);
	lName[0] = toupper(lName[0]);
	cout << "Enter employee marriage status (Enter S for SINGLE or M for MARRIED): ";
	string ms;
	cin >> ms;
	if (ms == "S") { marriagestatus = SINGLE; }
	else { marriagestatus = MARRIED; }
	cout << "Enter employee hourly payrate: $";
	cin >> payRate;
	cout << endl;
}

void CEmployee::showInfo()
{
	cout << "Employee ID: " << id << endl;
	cout << "Employee name: " << fName << " " << lName << endl;
	string ms;
	if (marriagestatus == MARRIED) { ms = "Married"; }
	else if (marriagestatus == SINGLE) { ms = "Single"; }
	else { ms = "Unknown"; }
	cout << "Employee marriage status:	" << ms << endl;
	cout << "Employee hourly payrate:	$" << setprecision(2) << fixed << payRate << endl;
	cout << endl;
}

std::ostream& operator << (std::ostream& out, const CEmployee& c) {
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);
	return out;
}

std::istream& operator >> (std::istream& in, CEmployee& c) {
	char ms;
	in >> c.id >> c.fName >> c.lName >> c.payRate >> ms;
	if (ms = 'S') c.marriagestatus = SINGLE;
	else c.marriagestatus = MARRIED;
	return in;
}




