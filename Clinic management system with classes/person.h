#ifndef person_H
#define person_H
#include<iostream>
#include<conio.h>
#include"name.h"
#include"date.h"
#include<windows.h>
#include<fstream>

using namespace std;
class person {

private:
	name pName; //store person name
	date DOB;	//store date of birth of person
	int age;	//store age of person
	int Nid;	//store id card number of person
public:
	person();
	person(name&, date& , int, int);
	person(person& p);
	void setPerson(name& ,date& ,int ,int ); //set name date of birth age and cnic card number
	name getpName(); // return name of person
	date getDob(); // return dob of person 
	int getAge(); // return age
	int getNid(); // return cnic card number of that person
	void operator = (person&); // assignning value of one person to other person
	void output(int x, int& y); //print output by get xy cordinantes of coursor
	void outputFile(ofstream& fout); // out put in file
	void inputFile(ifstream& fin); // input from file
	void setInput(int, int&); // take data by taking xy cordinantes of coursot
	void input(); // take in put when we want to take firstly
	void print(); // print output when we want to print in top
	BOOL setxy(int x, int y);// this will set cursor position
	friend ostream& operator<<(ostream&, person&); // display information of a person
	~person();
};
void person::outputFile(ofstream& fout) {
	fout  << pName;
	fout  << DOB;
	fout << "\t" << age;
	fout << "\t" << Nid;
}
void person:: inputFile(ifstream& fin) {
	fin >> pName;
	fin >> DOB;
	fin >> age;
	fin >> Nid;
}

person::person() {
	this->age = 0;
	this->Nid = 0;
}
person::person(name& pname, date& dob, int age, int nid) {
	setPerson(pname, dob, age, nid);
}
person::person(person& p) {
	cout<<"wqe";
	setPerson(p.pName, p.DOB, p.age, p.Nid);
}
BOOL person::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void person:: operator = (person& p) {
	setPerson(p.pName, p.DOB, p.age, p.Nid);
}
void person:: setPerson(name& pname, date& dob, int Age, int nid) {
	this->pName = pname;
	this->DOB = dob;
	this->age = Age;
	this->Nid = nid;
}
name person:: getpName() {
	return this->pName; //return name
}
date person:: getDob() {
	return this->DOB; // return person BOB
}
int person:: getAge() {
	return this->age;//return person age
}
int person:: getNid() {
	return this->Nid; // return person national id card
}
void person::setInput(int x,int& y) {
	y++;
	pName.setinput(x, y);
	y++;
	setxy(x + 1, y);  //set cursor position
	cout << "Enter DOB and pattern is DD/MM/YYYY -> ";
	DOB.setInput(x + 40, y); y++; // get DOB from counsole of person
	age = -1;
	while (age < 0) {
		setxy(x + 1, y);
		cout << "Enter age : ";
		cin >> age;
		if (age < 0) {//executein case of wrong input
			setxy(x + 1, y);
			cout << "                   ";
		}
	}
	y++;
	y++;

	Nid = -1;
	while (Nid < 0) {
		setxy(x + 1, y);
		cout << "Enter national id card # : ";
		cin >> Nid;
		if (Nid < 0) {
			setxy(x + 1, y);
			cout << "                                 "; // remove message that display last time
		}
	}
	y++;
}

void person::input() {
	

	cout << "\nEnter DOB and pattern is DD/MM/YYYY -> ";
	cin >> DOB; // take in put of DOB of person
	age = -1;
	while (age < 0) {
		cout << "\nEnter age : ";
		cin >> age;
		if (age < 0) { // when age input wrong
			cout << "\n you are entering age in negative number!";
		}
	}
	Nid = -1;
	while (Nid < 0) {
		cout << "\nEnter national id card # : ";
		cin >> Nid;
		if (Nid < 0) {
			cout << "\nyou are entering Nid in negative numbers!";
		}
	}
}

void person::output(int x, int& y) { // show output by set coursor position
	y += 2;
	setxy(x + 1, y); y += 2;
	cout << "Name of person : " << pName;
	setxy(x + 1, y); y += 2;
	cout << "DOB of person : " << DOB;
	setxy(x + 1, y); y += 2;
	cout << "Age of person : " << age;
	setxy(x + 1, y); y += 2;
	cout << "National id card # of person : " << Nid;

}

void person::print() {
	cout << "Name of person : " << pName;
	cout << "\n\nDOB of person : " << DOB;
	cout << "\n\nAge of person : " << age;
	cout << "\n\nnational id card # of person : " << Nid;
}
ostream& operator<<(ostream& out, person& p) {
	p.print();
	return out;
}
person::~person() {
	
}
#endif // !person_H

