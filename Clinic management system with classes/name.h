#ifndef name_H
#define name_H
#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;

class name {
private:
	char* fName; // point person first name
	char* lName; // poitn person last name
	BOOL setxy(int x, int y);// this will set cursor position
public:
	name(); // default constructor
	name(char* firstName, char* secondName); // parameterized constructor
	name(const name& p); // copy constructor
	char* getFName();//return first name;
	char* getLName(); // return second name;
	void operator =(const name&);
	void name::setinput(int x, int& y); // take x and y cordinate for making frame and take input with in that frame
	friend ostream& operator<<(ostream&, const name&);
	friend ofstream& operator <<(ofstream&, name&);
	friend ifstream& operator >>(ifstream&, name&);
	~name();
};

name::name(){
	fName = NULL;
	lName = NULL;
}
name::name(char* firstName, char* secondName) {
	int sizeFName = strlen(firstName); // find size of first string
	int sizeLName = strlen(secondName); // find size of second string
	fName = new char[sizeFName + 1]; 
	lName = new char[sizeLName + 1];
	strcpy(fName, firstName);//copy first string
	strcpy(lName, secondName);//copy second string
	fName[sizeFName] = '\0';
	lName[sizeLName] = '\0';
}
name::name(const name& p) {
	int sizeFName = strlen(p.fName);// find size of first string
	int sizeLName = strlen(p.lName);//find size of second string
	this->fName = new char[sizeFName + 1];
	this->lName = new char[sizeLName + 1];
	strcpy(this->fName, p.fName);//copy first string
	strcpy(this->lName, p.lName);// copy second string
	this->fName[sizeFName] = '\0';
	this->lName[sizeLName] = '\0';
}
BOOL name::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
char* name:: getFName() {//return first name;
	return fName;
}
char* name::getLName() { // return second name;
	return lName;
}

void name::operator =(const name& p) { 
	if (this->fName != NULL && p.fName != NULL) {
		delete[]fName;
		delete[]lName;
		int sizeFName = strlen(p.fName);// find size of first string
		int sizeLName = strlen(p.lName);//find size of second string
		this->fName = new char[sizeFName + 1];
		this->lName = new char[sizeLName + 1];
		strcpy(this->fName, p.fName);//copy first string
		strcpy(this->lName, p.lName);// copy second string
		this->fName[sizeFName] = '\0';
		this->lName[sizeLName] = '\0';
	}
	else if (this->fName == NULL && p.fName != NULL) {
		int sizeFName = strlen(p.fName);// find size of first string
		int sizeLName = strlen(p.lName);//find size of second string
		this->fName = new char[sizeFName + 1];
		this->lName = new char[sizeLName + 1];
		strcpy(this->fName, p.fName);//copy first string
		strcpy(this->lName, p.lName);// copy second string
		this->fName[sizeFName] = '\0';
		this->lName[sizeLName] = '\0';
	}
	else if (this->fName != NULL && p.fName == NULL) {
		delete[]fName;
		delete[]lName;
		this->fName = NULL;
		this->lName = NULL;
	}
}
void name::setinput(int x, int& y) {
	int i = 0; // control array indexes;
	fName = new char[36];
	lName = new char[36];
	setxy(x, y); cout << char(176); y++;
	setxy(x, y); cout << char(176); y++;
	cout << "Enter first name : ";
	for (i = 0; fName[i-1] != (char)13; i++) {
		fName[i] = _getche();
	}
	fName[i-1] = '\0';

	setxy(x, y); cout << char(176); y++;
	setxy(x, y); cout << char(176); y++;
	cout << "Enter last name : ";
	for (i = 0; lName[i - 1] != (char)13; i++) {
		lName[i] = _getche();
	}
	lName[i - 1] = '\0';

}

ofstream& operator <<(ofstream& fout, name& n) {
	fout << "\t" << n.fName << " " << n.lName;
	return fout;
}

ostream& operator<<(ostream& fout, const name& p) {
	fout << p.fName << " " << p.lName;
	return fout;
}

ifstream& operator >>(ifstream& fin, name& n) {
	n.fName = new char[36];
	n.lName = new char[36];
	fin >> n.fName;
	fin >> n.lName;
	return fin;
}

name::~name() {
	if (fName != NULL) {
		delete[]fName;
		fName = NULL;
	}
	if (lName != NULL) {
		delete[]lName;
		lName = NULL;
	}
}



#endif // !person_H
