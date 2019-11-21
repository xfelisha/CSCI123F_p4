#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include "Employee.h"
#include "TimeCard.h"
using namespace std;

const int MAX = 10;

int menu();
void listAllEmployees();
void listEmployeeInfo();
void UpdatePayRate();
void UpdateWorkingHours();
void DisplayPayStub();
void AddEmployee();
void RemoveEmployee();
void Quit();

float calcGrossPay(float hours, float wage, float overtimehours);
float calcInsurance(MaritalStatus mStatus);
void calcTotalTax(float taxableGrossPay, float& fedTax, float& stateTax, float& ssTax);

void readEmployees();
void writeEmployees();
void readTimeCards();
void writeTimeCards();

string searchbyname(string first, string last);
float searchbyid(string idsearch);

CEmployee employees[10];
CTimecard timecards[10];

void main()
{
	readEmployees();
	readTimeCards();

	int choice;
	do {
		system("CLS");
		choice = menu();

		switch (choice) {
		case 1:
			listAllEmployees();
			break;
		case 2:
			listEmployeeInfo();
			break;
		case 3:
			UpdatePayRate();
			break;
		case 4:
			UpdateWorkingHours();
			break;
		case 5:
			DisplayPayStub();
			break;
		case 6:
			AddEmployee();
			break;
		case 7:
			RemoveEmployee();
			break;
		case 8:
			Quit();
			break;
		default:
			cout << "That was an invalid choice, please try again! \n";
		}
		system("PAUSE");
	} while (choice > 0 && choice < 8);
}


int menu()
{
	int option;
	cout << "           SALARY CALCULATION SYSTEM MENU \n\n";
	cout << "1. List All Employees. \n";
	cout << "2. List Employee Information. \n";
	cout << "3. Update Employee Pay Rate\n";
	cout << "4. Update Employee Working Hours.\n";
	cout << "5. Display Paystub of One Employee.\n";
	cout << "6. Add an Employee.\n";
	cout << "7. Remove an Employee.\n";
	cout << "8. Quit. \n\n";
	cout << "Please select your option: ";
	cin >> option;
	while (option < 1 || option > 8)
	{
		cout << "Invalid option!!! Please select valid option: ";
		cin >> option;
	}
	return option;
}

////////// begin function definitions //////////
string searchbyname(string first, string last) {
	string result;
	for (int i = 0; i < MAX; i++) {
		if (employees[i].fName == first && employees[i].lName == last) {
			result = employees[i].id;
		}
		else result = "0000";
	}
	return result;
}

float searchbyid(string idsearch) {
	float result;
	for (int i = 0; i < MAX; i++) {
		if (timecards[i].id == idsearch) {
			result = timecards[i].get_hours();
		}
		else result = -1;
	}
	return result;
}

/// prints info so I don't have to do it all the time ///
void printEmployeeInfo(int e) {
	cout << endl;
	cout << "*****EMPLOYEE INFO*****" << endl;
	cout << "Employee ID:			" << timecards[e].id << endl;
	cout << "Name:					" << employees[e].fName << " " << employees[e].lName << endl;
	cout << "Payrate:				$" << fixed << setprecision(2) << employees[e].get_payRate() << endl;
	cout << "Hours:					" << timecards[e].get_hours() << endl;
	cout << endl;
	cout << endl;
}

/// option 1: listing information of all employees ///
void listAllEmployees() {
	cout << "Displaying all employees: " << endl;
	cout << endl;
	cout << "Name:" << "					Employee ID:" << endl;
	cout << "-------------------------------------------" << endl;

	ifstream emp_in;
	emp_in.open("Employee.dat");
	if (emp_in.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	for (int i = 0; i < MAX; i++) {
		cout << employees[i].fName << " " << employees[i].lName;
		cout << "					";
		cout << employees[i].id << endl;
	}
	emp_in.close();
}

/// option 2: input first/last name & return employee info + worked hours ///
void listEmployeeInfo() {
	string firstname, lastname, employeeid_lookup;
	cout << "Displaying employee information: " << endl;
	cout << endl;
	cout << "Enter the first and last name of the employee, separated by a space:	";
	cin >> firstname >> lastname;

	ifstream emp_in;
	emp_in.open("Employee.dat");
	if (emp_in.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	ifstream tc_in;
	tc_in.open("Timecard.dat");
	if (tc_in.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	employeeid_lookup = searchbyname(firstname, lastname);
	for (int i = 0; i < MAX; i++) {
		if (employees[i].id == employeeid_lookup) {
			printEmployeeInfo(i);
		}
	}
	tc_in.close();
	emp_in.close();
}

/// option 3: input first/last name & update payrate ///
void UpdatePayRate() {
	string firstname, lastname, employeeid_lookup;
	cout << "Updating employee payrate: " << endl;
	cout << endl;
	cout << "Enter the first and last name of the employee, separated by a space: " << endl;
	cin >> firstname >> lastname;

	fstream empfile;
	empfile.open("Employee.dat");
	if (empfile.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	float pr;
	employeeid_lookup = searchbyname(firstname, lastname);
	for (int i = 0; i < MAX; i++) {
		if (employees[i].id == employeeid_lookup) {
			cout << "The payrate of employee " << employeeid_lookup << " is: $" << employees[i].get_payRate() << endl;
			cout << "Please enter the new payrate: $";
			cin >> pr;
			employees[i].set_payRate(pr);
			cout << endl;
			cout << "Ok, the new payrate for employee" << employeeid_lookup << " is $" << employees[i].get_payRate() << "." << endl;
			cout << endl;
		}
	}
	empfile.close();
	cout << "The payrate has been updated and saved successfully.";
}

/// option 4: input first/last name & update working hours ///
void UpdateWorkingHours() {
	string firstname, lastname, employeeid_lookup;
	cout << "Updating employee working hours: " << endl;
	cout << endl;
	cout << "Enter the first and last name of the employee, separated by a space: " << endl;
	cin >> firstname >> lastname;

	fstream tcfile;
	tcfile.open("Timecard.dat");
	if (tcfile.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	float wh;
	employeeid_lookup = searchbyname(firstname, lastname);
	for (int i = 0; i < MAX; i++) {
		if (timecards[i].id == employeeid_lookup) {
			cout << "The working hours of employee " << employeeid_lookup << " is: " << timecards[i].get_hours() << endl;
			cout << "Please enter the new working hours: ";
			cin >> wh;
			timecards[i].set_hours(wh);
			cout << endl;
			cout << "Ok, the new working hours for employee " << employeeid_lookup << " is " << timecards[i].get_hours() << "." << endl;
			cout << endl;
		}
	}
	tcfile.close();
	cout << "The working hours have been updated and saved successfully.";
}

/// option 5: print paystub (from P1 & P2) ///
void DisplayPayStub() {
	string firstname, lastname, employeeid_lookup;
	cout << "Displaying paystub of one employee: " << endl;
	cout << endl;
	cout << "Enter the first and last name of the employee, separated by a space: " << endl;
	cin >> firstname >> lastname;

	ifstream emp_in;
	ifstream tc_in;

	emp_in.open("Timecard.dat", ios::in);
	if (emp_in.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	tc_in.open("Timecard.dat", ios::in);
	if (tc_in.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	employeeid_lookup = searchbyname(firstname, lastname);
	for (int i = 0; i < MAX; i++) {
		if (employees[i].id == employeeid_lookup) {
			cout << endl;
			cout << "            Your Pay-Roll Statement            " << endl;
			cout << "-----------------------------------------------" << endl;
			cout << "	Employee Name:			" << employees[i].fName << " " << employees[i].lName << endl;
			cout << "	Employee ID:			" << employees[i].id << endl;
			cout << endl;

			float wh;
			wh = timecards[i].get_hours();
			cout << "	TOTAL HOURS:			" << wh << endl;

			float overtimehours;
			float pr;
			pr = employees[i].get_payRate();

			if (wh <= 40) { overtimehours = 0; }
			else { overtimehours = (wh - 40); }

			cout << "	OVERTIME HOURS:			" << overtimehours << endl;
			cout << endl;
			cout << "	Hourly Rate:			$" << pr << endl;
			cout << endl;
			cout << endl;

			float GrossPay;
			GrossPay = calcGrossPay(wh, pr, overtimehours);
			cout << "	TOTAL EARNED:			$" << GrossPay << endl;

			MaritalStatus mStatus;
			mStatus = employees[i].marriagestatus;
			float insurance = calcInsurance(mStatus);

			float ssTax;
			float fedTax;
			float stateTax;
			calcTotalTax(GrossPay, fedTax, stateTax, ssTax);

			float NetPay;
			NetPay = (GrossPay - ssTax - fedTax - stateTax - insurance);
			GrossPay -= insurance;

			cout << "	Social Security Tax:	$" << ssTax << endl;
			cout << "	Federal Income Tax:		$" << fedTax << endl;
			cout << "	State Income Tax:		$" << stateTax << endl;
			cout << "	Health Insurance:		$" << insurance << endl;
			cout << "-----------------------------------------------" << endl;
			cout << "	TAKE HOME PAY:			$" << NetPay << endl;
			cout << endl;
		}
	}
	tc_in.close();
	emp_in.close();
}

/// option 6: add employee ///
void AddEmployee() {
	cout << "Adding an employee to file: " << endl;
	cout << endl;
	cout << "Checking if there is an available slot for employee information";
	Sleep(900);
	cout << ".";
	Sleep(900);
	cout << ".";
	Sleep(900);
	cout << ".";
	Sleep(900);

	ofstream empfile;
	empfile.open("Employee.dat", ios::app);

	if (empfile.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	for (int i = 1; i < MAX; i++) {
		if (employees[i].id != "0000") {
			cout << "Okay, there is available room in the file." << endl;
			cout << endl;

			ofstream tcfile;
			tcfile.open("Timecard.dat", ios::app);

			if (tcfile.fail()) {
				cout << "Error in opening file. \n";
				exit(1);
			}

			employees[i].getInfo();
			timecards[i].getInfo();

			tcfile.write((char*)&timecards, sizeof(timecards));
			tcfile.close();
			break;
		}
		else {
			cout << "There is no available room in the file.";
			break;
		}
	}
	empfile.close();
	cout << "The employee record has been added successfully.";
}

/// option 7: remove employee ///
void RemoveEmployee() {
	string firstname, lastname, employeeid_lookup;
	cout << "Removing an employee from file: " << endl;
	cout << endl;
	cout << "Enter the first and last name of the employee, separated by a space: " << endl;
	cin >> firstname >> lastname;

	fstream empfile;
	empfile.open("Employee.dat", ios::app, ios::out);
	fstream tcfile;
	tcfile.open("Timecard.dat", ios::app, ios::out);

	empfile.open("Timecard.dat", ios::in);
	if (empfile.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	tcfile.open("Timecard.dat", ios::in);
	if (tcfile.fail()) {
		cout << "Error in opening file. \n";
		exit(1);
	}

	CEmployee tempemp;
	CTimecard temptc;

	employeeid_lookup = searchbyname(firstname, lastname);
	for (int i = 0; i < MAX; i++) {
		if (employees[i].id == employeeid_lookup && timecards[i].id == employeeid_lookup) {
			employees[i] = tempemp;
			timecards[i] = temptc;
		}
	}
	tcfile.close();
	empfile.close();
	cout << "The employee record has been deleted successfully.";
}

/// option 8: quit ///
void Quit()
{
	writeEmployees();
	writeTimeCards();

	cout << "Have a nice day \n\n";
}


/// begin P2 functions ///
/// calculate GrossPay ///
float calcGrossPay(float hours, float wage, float overtimehours) {
	float GrossPay;
	float overtimepay = (wage * overtimehours * 1.50);
	float reghours;
	if (hours <= 40) {
		reghours = hours;
	}
	else {
		reghours = 40;
	}
	GrossPay = (reghours * wage) + overtimepay;
	return GrossPay;
}

/// calculate insurance ///
float calcInsurance(MaritalStatus mStatus) {
	float insurance;
	if (mStatus == MARRIED) { insurance = 50.00; }
	else { insurance = 0.00; }
	return insurance;
}

void calcTotalTax(float GrossPay, float& fedTax, float& stateTax, float& ssTax) {
	if (GrossPay > 1000.00) { fedTax = (GrossPay * 0.10); }
	else { fedTax = (GrossPay * 0.07); }

	if (GrossPay > 1000.00) { stateTax = (GrossPay * 0.04); }
	else { stateTax = (GrossPay * 0.03); }

	ssTax = (GrossPay * 0.06);

	return;
}

void readEmployees() {
	ifstream ins("Employee.dat", ios::in);
	if (ins.fail()) {
		cout << "Error in opening file.\n";
		exit(1);
	}

	std::string id, fName, lName;
	float payRate;
	char ms;

	for (int i = 0; i < MAX; i++) {
		while (ins >> id >> fName >> lName >> payRate >> ms) {
			int temp = std::stoi(employees[i].id);
			if (temp = i) {
				ins >> employees[i];
			}
		}
	}
	ins.close();
}


void writeEmployees()
{
	fstream empfile;
	if (empfile.fail()) {
		cout << "Error in opening file.\n";
		exit(1);
	}
	empfile.write((char*)&employees, sizeof(employees));
	empfile.close();
}

void readTimeCards() {
	ifstream ins("Timecard.dat", ios::in);
	if (ins.fail()) {
		cout << "Error in opening file.\n";
		exit(1);
	}

	string id;
	float hours;

	for (int i = 0; i < MAX; i++) {
		while (ins >> id >> hours) {
			int temp = std::stoi(timecards[i].id);
			if (temp = i) {
				ins >> timecards[i];
			}
		}
	}
	ins.close();
}

void writeTimeCards()
{
	fstream tcfile;
	if (tcfile.fail()) {
		cout << "Error in opening file.\n";
		exit(1);
	}
	tcfile.write((char*)&timecards, sizeof(timecards));
	tcfile.close();
}

