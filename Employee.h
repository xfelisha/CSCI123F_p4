#ifndef CEMPLOYEE_H
#define CEMPLOYEE_H

enum MaritalStatus { UNKNOWN, SINGLE, MARRIED };

class CEmployee
{
private:
	float payRate;
public:
	std::string id;
	std::string fName;
	std::string lName;
	MaritalStatus marriagestatus;

	//////////CONSTRUCTORS
	CEmployee();																														///default constructor
	CEmployee(std::string new_id, std::string new_fName, std::string new_lName, float new_payRate, MaritalStatus new_marriagestatus);	///paramertized constructor
	CEmployee(const CEmployee& emp);																									///copying constructor
	~CEmployee();																														///destructor

	//////////MUTATORS
	void set_payRate(float);

	//////////ACCESSORS
	float get_payRate();

	//////////FUNCTIONS
	void getInfo();
	void showInfo();

	friend std::ostream& operator << (std::ostream& out, const CEmployee& c);
	friend std::istream& operator >> (std::istream& in, CEmployee& c);
};


#endif