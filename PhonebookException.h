#pragma once
#include <exception>

class PhonebookException{
public:
	virtual const char* what() const noexcept = 0;
};

class number_not_copied : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- no memory to copy a number";
	}
};

class word_not_found : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- no contacts have been found";
	}
};

class call_history_empty : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- call history is EMPTY!";
	}
};

class contact_exists : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- Contact already EXISTS!";
	}
};

class not_valid_number : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- Number is not VALID!";
	}
};

class nothing_is_selected : public PhonebookException {
	virtual const char* what() const noexcept override {
		return "- Nothing is SELECTED!";
	}
};

