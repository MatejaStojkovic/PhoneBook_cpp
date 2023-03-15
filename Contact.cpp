#include "Contact.h"
#include "PhonebookException.h"

std::ostream& operator<<(std::ostream& os, const Contact& c)
{
	return os << c.name << " " << * c.number;
}

Contact::~Contact()
{
	delete number;
	number = nullptr;
}

Contact::Contact(const Contact& contact)
{
	auto new_number = contact.number->clone();
	if (new_number == nullptr) throw number_not_copied();
	number = new_number;
	name = contact.name;
}


Contact::Contact(Contact&& contact) noexcept
{
	number = std::exchange(contact.number, nullptr);
	name = std::move(contact.name);
}

Contact& Contact::operator=(const Contact& contact) {
	if (this == &contact) {
		auto new_number = contact.number->clone();
		if (new_number == nullptr) throw number_not_copied();
		number = new_number;
		name = contact.name;
	}
	return *this;
}


Contact& Contact::operator=(Contact&& contact) noexcept
{
	if (this != &contact) {
		name = std::move(contact.name);
		number = std::exchange(contact.number, nullptr);
	}
	return *this;
}

void Contact::setName(const std::string& name)
{
	this->name = name;
}

void Contact::setNumber(Number* number)
{
	this->number = number;
}
