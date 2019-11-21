#ifndef CTIMECARD_H
#define CTIMECARD_H

class CTimecard
{
private:
	float hours;

public:
	std::string id;

	//////////CONSTRUCTORS
	CTimecard();
	CTimecard(std::string new_id, float new_hours);
	CTimecard(const CTimecard& emp);
	~CTimecard();

	//////////MUTATORS
	void set_hours(float new_hours);

	//////////ACCESSORS
	float get_hours();

	//////////FUNCTIONS
	void getInfo();
	void showInfo();

	friend std::ostream& operator << (std::ostream& out, const CTimecard& c);
	friend std::istream& operator >> (std::istream& in, CTimecard& c);
};

#endif