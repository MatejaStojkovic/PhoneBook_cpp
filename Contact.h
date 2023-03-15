#pragma once
#include <string>
#include <sstream>
#include "Number.h"

class Contact
{
public:
	Contact(const std::string& name = "", Number* number = nullptr) : name(name), number(number) {}
	~Contact();
	Contact(const Contact& contact); // kopirajuci konstruktor
	Contact(Contact&& contact) noexcept; // premestajuci konstruktor
	Contact& operator=(const Contact& contact); // operator dodele
	Contact& operator=(Contact&& contact) noexcept; // premestajuci operator dodele

	void setName(const std::string& name);
	void setNumber(Number* number);
	friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
	std::string getName() const { return name; }
	Number* getNumber() const { return number; }
	std::string getStringNumber() const { return number->getNumber(); }
private:
	std::string name;
	Number* number;
};

