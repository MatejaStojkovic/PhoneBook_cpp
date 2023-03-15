#pragma once
#include <string>
#include <sstream>

class Number
{
public:
	Number(const std::string& number) : number(number) {}
	virtual ~Number() = default;
	Number(const Number& num) = default;
	Number(Number&& num) = default;
	Number& operator=(const Number& num) = default;
	Number& operator=(Number&& num) = default;
	void setNumber(const std::string& number);
	friend std::ostream& operator<<(std::ostream& os, const Number& number);
	std::string getNumber() const { return number; }
	virtual Number* clone() const = 0;

private:
	std::string number;

};

class Landline : public Number {
public:
	Landline(const std::string& number) : Number(number) {}
	Landline(Landline const&) = default;
	Landline(Landline &&) = default;
	Landline& operator=(Landline const&) = default;
	Landline& operator=(Landline &&) = default;
	virtual ~Landline() override = default;
	virtual Number* clone() const { return new Landline(*this); }

private:

};

class Mobile : public Number {
public:
	Mobile(const std::string& number) : Number(number) {}
	Mobile(Mobile const&) = default;
	Mobile(Mobile&&) = default;
	Mobile& operator=(Mobile const&) = default;
	Mobile& operator=(Mobile&&) = default;
	virtual ~Mobile() override = default;
	virtual Number* clone() const { return new Mobile(*this); }

private:

};

