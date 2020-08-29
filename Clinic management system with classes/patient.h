#ifndef Patient_H
#define Patient_H

#include<iostream>
#include"person.h"
#include"date.h"
#include"name.h"
#include"pastRecord.h"
#include<windows.h>
#include<fstream>

using namespace std;

class patient : public person {
private:
	int pId; 
	int rec;//determine how many record are present of a person
	pastRecord* history;
	int x; // store x component of boarder
	int y; // store y component of boarder

public:
	patient();
	void newPatientRec(int , pastRecord&); // add new patient
	void addPatientRec(pastRecord& p); // add just record if patient already exist
	int getPid(); //return patient id
	pastRecord* gethistory(); // return patient history
	bool datePresent(date&); // return patient checkup date
	bool doctorIdPresent(int dId); // return false if doctor id not present and vise versa
	void setxyValues(int x, int y); //set boarder initial point
	int getY(); // return y cordinante of cursor
	void setInput(int x,int &y); // set xy cordinante of cursor position
	friend ostream& operator <<(ostream&, patient&);
	friend istream& operator >>(istream&, patient&);
	friend ofstream& operator <<(ofstream&, patient&);
	friend ifstream& operator >>(ifstream&, patient&);
	~patient();
};
patient::patient() :person() {
	rec = 0;
	pId = 0;
	history = NULL;
}
void patient::newPatientRec(int pid, pastRecord& record) {
	this->rec++;
	this->pId = pid;
	history = new pastRecord;
	*history = record;
}
void patient::addPatientRec(pastRecord& record) {
	int i;
	this->rec++;
	pastRecord* temp = history;
	history = new pastRecord[rec];
	for (i = 0; i < rec - 1; i++) { // copy data
		history = &temp[i];
	}
	history[i] = record;
}

bool patient::doctorIdPresent(int dId) {
	for (int i = 0; i < rec; i++) {
		if (dId == history[i].getAssignedDoc()) {
			return true;
		}
	}
	return false;
}
bool patient::datePresent(date& d) {
	for (int i = 0; i < rec ; i++) {
		if (d == history[i].getDate()) { //check is date present
			return true;
		}
	}
	return false;
}

int patient::getPid() {
	return this->pId;
}
pastRecord* patient::gethistory() {
	return history;
}

void patient::setxyValues(int x, int y) {
	this->x = x;
	this->y = y;
}
int patient::getY() {
	return y;
}

ifstream& operator >>(ifstream& fin, patient& p) {
	p.person::inputFile(fin);
	fin >> p.pId;
	fin >> p.rec;
	p.history = new pastRecord[p.rec];
	for (int i = 0; i < p.rec; i++) {
		fin >> p.history[i];
	}

	return fin;
}
ofstream& operator <<(ofstream& fout, patient& p) {
	p.person::outputFile(fout);
	fout << "\t" << p.pId;
	fout << "\t" << p.rec;
	for (int i = 0; i < p.rec; i++) { // print history
		fout << "\t";
		fout << p.history[i];
	}
	return fout;
}
ostream& operator <<(ostream& out, patient& p) {
	int horizontal = 12 + (9 * p.rec);
	p.setxy(p.x, p.y); p.y++;
	for (int i = 0; i < 60; i++) { // top boarder line
		cout << char(176);
	}
	for (int i = 0; i < horizontal; i++) { // left boarder line
		p.setxy(p.x, p.y + i); cout << char(176);
	}
	for (int i = 0; i < horizontal; i++) {
		p.setxy(p.x + 59, p.y + i); cout << char(176);
	}
	p.setxy(p.x, p.y + horizontal); p.y++;
	for (int i = 0; i < 60; i++) { // top boarder line
		cout << char(176);
	}
	p.setxy(p.x + 18, p.y-1); cout << ">>>>>>>> Record <<<<<<<";
	p.setxy(p.x + 1, p.y);
	out << "Patient Id Number : " << p.pId;
	p.person::output(p.x , p.y);
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "------------------------ History ------------------------";
	for (int i = 0; i < p.rec; i++) {
		p.history[i].output(p.x, p.y);
	}
	p.y++;
	return out;
}
void patient::setInput(int x, int& y) {
	person::setInput(x, y);
}

istream& operator >>(istream& in, patient& p) {
	p.person::input();
	return in;
}
patient :: ~patient() {
	if (history != NULL) {
		delete[]history;
		history = NULL;
	}
}
#endif // !Patient_H
