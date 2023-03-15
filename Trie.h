#pragma once
#include "Contact.h"
#include <sstream>
#include <string>

//int constexpr SYMBOL_COUNT = 39;
static std::ptrdiff_t constexpr SYMBOL_COUNT = 29;

class Trie
{
private:
	struct Node {
		// imamo 26 velikih i malih slova + ' ' + '-'
		Node* children[SYMBOL_COUNT];
		// kontakt koji sadrzi ime + pokazivac na broj
		Contact* contact;
		Node() : contact(nullptr), children{ 0 } {}
		~Node() = default;
	};
	Node* root;
	Node* selectedNode;

public:
	Trie() : root(new Node), selectedNode(nullptr) {}
	~Trie();
	unsigned char getIndex(const char& c) const;
	void inserEntry(const std::string& name, const std::string& number); // ovo je uglavnom za ucitavanje jer je brze bez provere
	void inserEntry(Contact* contact); // ovde su razne provere i koristi se kad ucitavam novi
	void inserEntry(const std::string& name, Number* number);
	void search(const std::string& name) const;
	void search(Node* node) const; // trazi node
	void select(const std::string& name); // selectuje ime
	void select(Node* node); //selectuje node
	bool isEmpty(Node* node) const; //proverava da li su sva deca nullptr
	Node* getSelected() const { return selectedNode; }
	void deleteSelected(); // bez parametara == za selectedNode
	void editDelete(const std::string& name); // za brisanje kad cuvak kontakt
	bool isSelected() const;
	void edit(Contact* contact, const std::string& name); // prima editovan contact i prethodno ime
	void edit(Number* number); // ovo se poziva kad samo broj menjamo
	Contact* getSelectedContact() const { return selectedNode->contact; }
	Number* setPhone(const std::string& number); // ovde su sve provere za broj

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
};