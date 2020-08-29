#ifndef time_H
#define time_H
#include<iostream>
#include<windows.h>
#include<fstream>

using namespace std;

class time {
private:
	int hour; //store hours
	int min;//store minutes
	int sec; // stor second
	BOOL setxy(int x, int y);// this will set cursor position
public:
	time(); // default constructor
	time(int hour, int min, int sec); // parameterized constrctor
	time(time&); // copy constructor
	void setTime(int hour, int min, int sec); // set value of sec, min, and hours
	int gethour(); // return hours
	int getminute(); // return minutes
	int getsecond(); // return second
	void operator =(const time& p);
	void setInput(int x, int& y); //take input and form boarder around that data by taking x any y cordinates
	friend ostream& operator<<(ostream&, const time&); //output on console
	friend istream& operator>>(istream&, time&);
	friend ofstream& operator<<(ofstream&, time&);
	friend ifstream& operator>>(ifstream&, time&);
	~time();
};
time::time() {
	hour = 0;
	min = 0;
	sec = 0;
}

time::time(int hour, int min, int sec) {
	setTime(hour, min, sec);
}
time::time(time& t) {
	setTime(t.hour, t.min, t.sec);
}


void time:: setInput(int x, int & y) {
	char c;// store ':'
	sec = -1;
	hour = -1;
	min = -1;
	setxy(x, y);
	while (hour <= 0 || min < 0 || sec < 0 || hour >= 24 || min > 60 || sec > 60) { // get patient arrival time
		setxy(x, y); cout << "                  ";//remove recently output line
		setxy(x, y);
		cin >> sec >> c >> min >> c >> hour;
		
	}
}
BOOL time::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void time:: setTime(int hour, int min, int sec) {
	this->hour = hour;
	this->min = min;
	this->sec = sec;
}

int time::gethour() {
	return this->hour;
}

int time::getminute() {
	return this->min;
}

int time::getsecond() {
	return this->sec;
}

void time::operator =(const time& p) {
	this->sec = p.sec;
	this->min = p.min;
	this->hour = p.hour;
}
ifstream& operator>>(ifstream& fin, time& t) {
	fin >> t.hour;
	fin >> t.min;
	fin >> t.sec;
	return fin;
}

ofstream& operator<<(ofstream& fout, time& t) {
	fout << "\t" << t.hour;
	fout << " " << t.min;
	fout << " " << t.sec;
	return fout;
}

ostream& operator<<(ostream& out, const time& p) { // display output in given format
	cout << p.hour << " : " << p.min << " : " << p.sec;
	return out;
}
istream& operator>>(istream& in, time& p) {
	char c;// store ':'
	p.sec = -1;
	p.hour = -1;
	p.min = -1;
	
	while (p.hour <= 0 || p.min < 0 || p.sec < 0 || p.hour >= 24 || p.min > 60 || p.sec > 60) { // get patient arrival time
		cin >> p.sec >> c >> p.min >> c >> p.hour;
	}
	return in;
}
time::~time() {

}
#endif // !time_H
