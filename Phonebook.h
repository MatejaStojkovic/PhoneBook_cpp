#pragma once
#include <string>
#include <queue>
#include "Trie.h"


class PhoneBook
{
public:
	// otvara interaktivan terminal
	void openTerminal();
	// ucitava podatke u container
	void loadPhoneBook(const std::string& filepath);
	// za singleton
	static PhoneBook& getInstance();

private:
	PhoneBook() = default;
	Trie enteries;
	struct CallHistoryEntry {
		Contact const* contact;
		std::string number;
		CallHistoryEntry(Contact const* contact) : 
			contact(contact), number(contact->getStringNumber()){}
	};
	std::deque<CallHistoryEntry> callHistory;
	bool isSelected() const { return enteries.isSelected(); }
	Number* assignPhone();
	// za novi contact
	void newContact();
	// trazi sta mu se da prefixom i ispisuje
	void search() const;
	// selectuje contact
	void select();
	// brise contact
	void deleteContact();
	// menja contact na neki od 3 nacina
	void edit();
	// ubacuje broj u call_history
	void call();
	// ispisuje call_history
	void call_history() const;
	static inline bool initialized = false;
};

