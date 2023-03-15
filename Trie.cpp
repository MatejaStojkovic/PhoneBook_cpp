#include "Trie.h"
#include <iostream>
#include <queue>
#include <stack>
#include "PhonebookException.h"
#include <utility>


Trie::~Trie()
{
	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		for (auto& elem : queue.front()->children) {
			if (elem)  queue.push(elem);
		}
		if(queue.front()->contact) delete queue.front()->contact;
		delete queue.front();
		queue.pop();
	}
	selectedNode = nullptr;
}

unsigned char Trie::getIndex(const char& c) const
{
	if (c == ' ') return 0;
	else if (c >= 'a' && c <= 'z') return c - 'a' + 1;
	else if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
	else if (c == '-') return 27;
	//else if (c >= '0' && c <= '9') return c - '0' + 28;
	//return 38;
	return 28;
}



void Trie::inserEntry(const std::string& name, const std::string& number)
{
	Node* curr = root;
	for (auto& c : name) {
		int index = getIndex(c);
		if (!curr->children[index]) {
			curr->children[index] = new Node();
		}
		curr = curr->children[index];
	}
	if (curr->contact) return; //mozda da se baci exception ako traze
	curr->contact = new Contact(name, setPhone(number));
}

void Trie::inserEntry(Contact* contact)
{
	std::string name = contact->getName();
	Node* curr = root;
	for (auto& c : name) {
		int index = getIndex(c);
		if (!curr->children[index]) {
			curr->children[index] = new Node();
		}
		curr = curr->children[index];
	}
	if (curr->contact) return; //mozda da se baci exception ako traze
	curr->contact = contact;
}

void Trie::inserEntry(const std::string& name, Number* number)
{
	Node* curr = root;
	for (auto& c : name) {
		int index = getIndex(c);
		if (!curr->children[index]) {
			curr->children[index] = new Node();
		}
		curr = curr->children[index];
	}
	if (curr->contact) return;
	curr->contact = new Contact(name, number);
}

void Trie::search(const std::string& name) const
{
	Node* curr = root;
	std::stack<Node*> s;
	for (auto& c : name) {
		int index = getIndex(c);
		if (curr->children[index] == nullptr) {
			throw word_not_found();
		}
		curr = curr->children[index];
	}
	std::cout << "- contacts have been found: \n";
	s.push(curr);
	while(!s.empty()) {
		curr = s.top();
		if (curr->contact) std::cout << "--- " << * curr << std::endl;
		s.pop();
		for (int i = SYMBOL_COUNT - 1; i >= 0; i--) {
			if (curr->children[i]) s.push(curr->children[i]);
		}
	}
}

void Trie::search(Node* node) const
{
	std::string name = node->contact->getName();
	search(name);
}

void Trie::select(const std::string& name)
{
	Node* curr = root;
	for (auto& c : name) {
		int index = getIndex(c);
		if (curr->children[index] == nullptr) {
			//znaci da nema te reci
			throw word_not_found();
		}
		curr = curr->children[index];
	}
	if (!curr->contact) throw word_not_found();
	selectedNode = curr;
}

void Trie::select(Node* node)
{
	std::string name = node->contact->getName();
	select(name);
}

bool Trie::isEmpty(Node* node) const
{
	if (node->children[0]) return false;
	return !memcmp(node->children, node->children + 1, (SYMBOL_COUNT - 1) * sizeof(Node*));
}

void Trie::deleteSelected()
{	
	std::string name = selectedNode->contact->getName();
	Node* curr = root;
	std::stack<std::pair<Node*,char>> stack;
	for (auto& c : name) {
		int index = getIndex(c);
		stack.push(std::make_pair(curr->children[index], index));
		curr = curr->children[index];
	}
	auto& top = stack.top();
	delete top.first->contact;
	top.first->contact = nullptr;
	while (!stack.empty()) {
		top = stack.top();
		stack.pop();
		if (isEmpty(top.first) && !stack.empty()) { // ako nema dece
			stack.top().first->children[top.second] = nullptr;
			delete top.first;
		}
		else {
			selectedNode = nullptr;
			return;
		}
	}
}

bool Trie::isSelected() const
{
	if (selectedNode) return true;
	return false;
}

void Trie::edit(Contact* contact, const std::string& name)
{
	editDelete(name);
	inserEntry(contact);
	select(contact->getName());
}
void Trie::edit(Number* number)
{
	selectedNode->contact->setNumber(number);
}

void Trie::editDelete(const std::string& name)
{
	Node* curr = root;
	std::stack<std::pair<Node*, char>> stack;
	for (auto& c : name) {
		int index = getIndex(c);
		stack.push(std::make_pair(curr->children[index], index));
		curr = curr->children[index];
	}
	auto& top = stack.top();
	top.first->contact = nullptr;
	while (!stack.empty()) {
		top = stack.top();
		stack.pop();
		if (isEmpty(top.first) && !stack.empty()) { // ako nema dece
			stack.top().first->children[top.second] = nullptr;
			delete top.first;
		}
		else return;
	}
}

std::ostream& operator<<(std::ostream& os, const Trie::Node& node)
{
	return os << *node.contact;
}

Number* Trie::setPhone(const std::string& number)
{
	static std::string nums = "0123456789";
	if (number.substr(0, 7) == "+381 11"
		|| number.substr(0, 3) == "011") {
		return new Landline(number);
	}
	else if (number.substr(0, 6) == "+381 6" && nums.find(number[6]) != std::string::npos
		|| number.substr(0, 2) == "06" && nums.find(number[2]) != std::string::npos) {
		return new Mobile(number);
	}
	else throw not_valid_number();
}