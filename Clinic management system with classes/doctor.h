#ifndef doctor_H
#define doctor_H
#include<iostream>
#include<string>
#include"person.h"
#include"pastRecord.h"
#include<windows.h>
using namespace std;

class doctor : public person {
private:
	int dId; // store doctor id
	char* specialization; //General Physician, Orthopedic, Child Specialist etc.
	int* pateintsVisited; //Add patient id in the array for tracking complete
							//information of visited patients.
public:
	doctor();
	doctor(int , char* , name&, date&, int, int);
	doctor(doctor&);
	void setPatienVisited(int); // set patient visited id in patientvisited id
	void setDoctor(int , char*); // set doctor id and spalization
	int getDid(); // return docutor id
	char* getdoctorType(); // return doctor spacilization
	int* getPvisited(); // return patient visited
	void setInput(int x, int& y); // take person info input from counsol
	friend ostream& operator<<(ostream&, doctor& ); 
	friend ofstream& operator<<(ofstream&, doctor&);
	friend ifstream& operator>>(ifstream&, doctor&);
	~doctor();
};


doctor::doctor() : person() {
	this->dId = 0;
	specialization = NULL;
	pateintsVisited = new int;
	*pateintsVisited = -1;
}
doctor::doctor(int did, char* doctorType, name& pName, date& pDob, int pAge, int pnId) : person(pName, pDob,pAge,pnId) {
	int size = strlen(doctorType); // find size of string
	specialization = new char[size + 1]; // allocate memmory
	specialization[size] = '\0';
	strcpy(specialization, doctorType);
	this->dId = did;
	pateintsVisited = new int;
	*pateintsVisited = -1;
}
doctor::doctor(doctor& d):person(d) {
	this->dId = d.dId;
	int size = strlen(d.specialization); // find string length
	specialization = new char[size + 1];
	specialization[size] = '\0';
	strcpy(specialization, d.specialization); //string copy
	size = 0;
	for (int i = 0; d.pateintsVisited[i] != -1; i++) {
		size++;
	}
	pateintsVisited = new int[size + 1];
	pateintsVisited[size] = -1;
	for (int i = 0; i < size; i++) { // copy data
		pateintsVisited[i] = d.pateintsVisited[i];
	}
}
void doctor::setPatienVisited(int patientId) {
	int* temp = pateintsVisited;
	int size = 0;
	for (int i = 0; pateintsVisited[i] != -1; i++) { // find how many patient have been visited
		size++;
	}
	pateintsVisited = new int[size + 2];

	for (int i = 0; i < size; i++) { // copy data
		pateintsVisited[i] = temp[i];
	}
	pateintsVisited[size] = patientId;
	pateintsVisited[size + 1] = -1;
}
void doctor::setDoctor(int did, char* doctorType) {
	this->dId = did;
	int* temp = pateintsVisited;
	int size = strlen(doctorType);
	specialization = new char[size + 1];
	specialization[size] = '\0';
	strcpy(specialization, doctorType);
	this->dId = did;
}
int doctor::getDid() {
	return this->dId;
}
char* doctor:: getdoctorType() {
	return specialization;
}
int* doctor::getPvisited() {
	return this->pateintsVisited;
}
void doctor::setInput(int x, int& y) {
	person::setInput(x, y);
}
ostream& operator<<(ostream& out, doctor& doc) {
	int x = 30;
	int y = 3;
	y++;
	doc.setxy(x + 16, y); cout << ">>>>>>>>>>DOCTOR HISTORY<<<<<<<<<<"; y += 2;
	doc.setxy(x + 1, y);
	cout << "Doctor Id Number : " << doc.dId;
	doc.person::output(x, y); // call person output function
	doc.setxy(x+1, y); y += 2;
	cout << "Petient visited Id Number : ";
	for (int i = 0; doc.pateintsVisited[i] != -1; i++) {
		cout << doc.pateintsVisited[i] << ",";
	}
	doc.setxy(x + 1, y); 
	cout << "Specialization of doctor : "<< doc.specialization;
	return out;
}

ofstream& operator<<(ofstream& fout, doctor& d) {
	d.person::outputFile(fout);
	fout << "\t" << d.dId;
	fout << "\t";
	for (int i = 0; d.specialization[i] != '\0'; i++) {
		if (d.specialization[i] == ' ') {
			fout << "_";
		}
		else {
			fout << d.specialization[i];
		}
	}
	fout << "\t";
	for (int i = 0; d.pateintsVisited[i - 1] != -1; i++) {
		fout << d.pateintsVisited[i] << " ";
	}
	return fout;
}

ifstream& operator>>(ifstream& fin, doctor& d) {
	int size = 0;
	d.person::inputFile(fin);
	fin >> d.dId;
	d.specialization = new char[36];
	fin >> d.specialization;
	int a;
	fin >> a;
	if (a != -1) {
		while (a != -1) {
			int* temp = d.pateintsVisited;
			d.pateintsVisited = new int[size + 1];
			for (int i = 0; i < size; i++) {
				d.pateintsVisited[i] = temp[i];
			}
			d.pateintsVisited[size] = a;
			fin >> a;
			size++;
		}
	}
	int* temp = d.pateintsVisited;
	d.pateintsVisited = new int[size + 1];
	for (int i = 0; i < size; i++) {
		d.pateintsVisited[i] = temp[i];
	}
	d.pateintsVisited[size] = -1;
	return fin;
}
doctor::~doctor() {
	if (specialization != NULL) {
		delete[]specialization;
		specialization = NULL;
	}	
	if (pateintsVisited != NULL) {
		delete[]pateintsVisited;
		pateintsVisited = NULL;
	}
}

#endif // !doctor_H
