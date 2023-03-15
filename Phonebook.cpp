#include "Phonebook.h"
#include <iostream>
#include <fstream>

#include "PhonebookException.h"

void PhoneBook::openTerminal()
{
	std::string command;
	std::cout << "--------------------------\n";
	std::cout << "Welcome to your phonebook!\n";
	std::cout << "--------------------------\n";
	while (true) {
		try {
			std::cout << "Enter the command: ";
			std::cin >> command;
			if (command == "NEW") {
				newContact();
			}
			else if (command == "SEARCH") {
				search();
			}
			else if (command == "SELECT") {
				select();
			}
			else if (command == "DELETE") {
				deleteContact();
			}
			else if (command == "EDIT") {
				edit();
			}
			else if (command == "CALL") {
				call();
			}
			else if (command == "CALL_HISTORY") {
				call_history();
			}
			else if (command == "EXIT") return;
		}
		catch (const PhonebookException& error) {
			std::cerr << error.what() << std::endl;
		}
	}
}

void PhoneBook::loadPhoneBook(const std::string& filepath)
{
	if (!initialized) {
		std::ifstream input(filepath);
		if (input.is_open()) {
			std::string s;
			while (getline(input, s)) {
				auto lastComa = s.find_last_of(',');
				//prvo je ime a drugo je broj;
				enteries.inserEntry(s.substr(0, lastComa), s.substr(lastComa + 1));
			}
		}
		auto& instance = getInstance();
		// populate instance;
		initialized = true;
	}
}

PhoneBook& PhoneBook::getInstance()
{
	static PhoneBook instance;
	return instance;
}

Number* PhoneBook::assignPhone()
{
	std::string number;
	while (true) {
		std::cout << "- Enter new contact number: ";
		std::getline(std::cin, number);
		static std::string nums = "0123456789";
		if (number.substr(0, 7) == "+381 11"
			|| number.substr(0, 3) == "011") {
			return new Landline(number);
		}
		else if (number.substr(0, 6) == "+381 6" && nums.find(number[6]) != std::string::npos
			|| number.substr(0, 2) == "06" && nums.find(number[2]) != std::string::npos) {
			return new Mobile(number);
		}
		std::cout << "Wrong number format!" << std::endl;
	}
}

void PhoneBook::newContact()
{
	std::string name;
	Number* number;
	std::cout << "- Enter new contact name: ";
	std::cin.ignore();
	std::getline(std::cin, name);
	number = assignPhone();
	enteries.inserEntry(name, number);
}

void PhoneBook::search() const
{
	std::string prefix;
	std::cout << "- Enter the contact name or first few letters: ";
	std::cin.ignore();
	std::getline(std::cin, prefix);
	enteries.search(prefix);
}

void PhoneBook::select()
{
	std::string name;
	std::cout << "- Enter the contact name: ";
	std::cin.ignore();
	std::getline(std::cin, name);
	enteries.select(name);
	std::cout << "- Contact " << *enteries.getSelected() << " is now selected.\n";
}

void PhoneBook::deleteContact()
{
	if (isSelected()) {
		std::cout << "- Contact " << *enteries.getSelected() << " has been deleted.\n";
		auto selected = enteries.getSelected()->contact;
		enteries.deleteSelected();
		for (std::size_t i = 0; i < callHistory.size(); i++) {
			if (callHistory[i].contact == selected) {
				callHistory[i].contact = nullptr;
			}
		}
	}
	else throw nothing_is_selected();
}

void PhoneBook::edit()
{
	std::string nameBefore = enteries.getSelectedContact()->getName();
	std::string name;
	auto selected = enteries.getSelected()->contact;
	if (isSelected()) {
		int change;
		std::cout << "What do you want to change: \n";
		std::cout << "1. Name \n";
		std::cout << "2. Number \n";
		std::cout << "3. Both \n";
		std::cin >> change;
		if (change == 1) {
			std::cout << "- Enter new contact name: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			selected->setName(name);
			enteries.edit(selected, nameBefore);
		}
		else if (change == 2) {
			std::cin.ignore();
			Number* number = assignPhone();
			enteries.edit(number);
		}
		else if (change == 3) {
			std::cin.ignore();
			std::cout << "- Enter new contact name: ";
			std::getline(std::cin, name);
			Number* number = assignPhone();
			selected->setName(name);
			selected->setNumber(number);
			enteries.edit(selected, nameBefore);
		}
		else std::cout << "Not a valid option! \n";
	}
	else {
		throw nothing_is_selected();
	}
}

void PhoneBook::call()
{
	if (isSelected()) {
		if (callHistory.size() >= 10)
			callHistory.pop_back();
		//radi constructovanje direktno
		callHistory.emplace_front(enteries.getSelectedContact());
		std::cout << "Calling " << *enteries.getSelected() << std::endl;
	}
	else {
		throw nothing_is_selected();
	}
}

void PhoneBook::call_history() const
{
	if (!callHistory.empty()) {
		for (auto& entry : callHistory) {
			if (entry.contact) {
				std::cout << "--- " << *entry.contact << std::endl;
			}
			else {
				std::cout << "--- " << entry.number << '\n';
			}
		}
	}
	else throw call_history_empty();
}
