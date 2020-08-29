#ifndef date_H
#define date_H
#include<iostream>
#include<windows.h>
#include<fstream>

using namespace std;

class date {
private:
	int day;
	int month;
	int year;
	BOOL setxy(int x, int y);// this will set cursor position
public:
	date(); // default constructor
	date(int, int,int ); // parametarized constructor;
	void setDate(int, int,int );// ste values;
	int getDay(); //return day
	int getmonth(); // return month
	int getyear(); // return year
	void setInput(int x, int& y); // take in put by getting xy cordinantes of coursor
	void operator =(const date&); 
	bool operator ==(const date&); 
	friend ostream& operator<<(ostream&, const date&); //output on console
	friend istream& operator>>(istream&, date&); // input from console
	friend ofstream& operator<<(ofstream&, date&); // output in file
	friend ifstream& operator>>(ifstream&, date&); // input from file
	~date();
};

date::date() {
	day = 0;
	month = 0;
	year = 0;
}
date::date(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}
void date::setInput(int x, int& y) { // input by adjusting xy cordinantes of coursor
	char c; // store "/"

	while (day <= 0 || month <= 0 || year <= 0 || day > 31 || month > 12) { // get patient arrival date
		setxy(x, y); cout << "                "; //remove recently output line
		setxy(x, y);
		cin >> day >> c >> month >> c >> year;
	}
	y++;
}
BOOL date::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void date::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

int date::getDay() { // return day
	return this->day;
}
int date::getmonth() { // return month
	return this->month;
}
int date::getyear() { // return year
	return this->year;
}

void date::operator =(const date& p) {
	this->day = p.day;
	this->month = p.month;
	this->year = p.year;
}
bool date:: operator ==(const date& d) {
	if (day == d.day && month == d.month && year == d.year) {
		return true;
	}
	return false;
}
ostream& operator<<(ostream& out, const date& p) { // display output in given format
	cout << p.day <<" / " << p.month << " / " << p.year;
	return out;
}
istream& operator>>(istream& in, date& p) {
	char c; // store "/"
	while (p.day <= 0 || p.month <= 0 || p.year <= 0 || p.day > 31 || p.month > 12) { // get patient arrival date
		cin >> p.day >> c >> p.month >> c >> p.year;
		if (p.day <= 0 || p.month <= 0 || p.year <= 0 || p.day > 31 || p.month > 12) {
			cout << "\nAgain enter date : ";
		}
	}
	return in;
}

ifstream& operator>>(ifstream& fin, date& d) {
	fin >> d.day;
	fin >> d.month;
	fin >> d.year;
	return fin;
}
ofstream& operator<<(ofstream& fout, date& d) {
	fout << "\t" << d.day << " " << d.month << " " << d.year;
	return fout;
}
date::~date() {

}



#endif