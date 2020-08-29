#ifndef Appointment_H
#define Appointment_H

#include<iostream>
#include<string>
#include"date.h"
#include"time.h"
#include<windows.h>

using namespace std;

class Appointment {
private:
	char* DiseaseType; // store patient problem
	int pId; // store patient id
	int dId; // store doctor id
	date appDate; // appointment date
	time appTime; // appointment time
	int token_Number; // assigning token number to that patirnt 
	float fee; // patient paid fee
	int x; // control cursor position
	int y; // control cursor postion along y axis
	bool status; // false for pending, true if complete
	BOOL setxy(int x, int y);// this will set cursor position
public:
	Appointment();
	Appointment(char* disease, int pid, int did, date& d, time& t, int token, float fee, bool is_check);
	Appointment(Appointment& p);
	void setAppointment(char* disease, int pid, int did, date& d, time& t, int token, float fee, bool is_check);
	void setStatus(bool); //set is patient chek or not by doctor
	void setxyValues(int x, int y); // set value of x and y cordinate of cursor
	int getY();
	date& getappDate();
	int getTokenNumber();
	char* getDisease(); // return patient problem
	float getFee(); // return checkup fee
	bool getStatus(); // return appointment current status
	int getPatientId();
	int getDoctorId();
	friend ostream& operator<<(ostream& out, Appointment& p);
	friend ofstream& operator<<(ofstream& fout, Appointment& p);
	friend ifstream& operator>>(ifstream& fin, Appointment& p);
	~Appointment();
};
Appointment::Appointment() {
	DiseaseType = NULL;
	token_Number = 0;
	fee = 0;
	status = false;
}
Appointment::Appointment(char* disease, int pid, int did, date& d, time& t, int token, float fee, bool is_check) {
	setAppointment(disease, pid, did, d, t, token, fee, is_check);
}
Appointment::Appointment(Appointment& p) {
	int size = strlen(p.DiseaseType);
	this->DiseaseType = new char[size + 1];
	DiseaseType[size] = '\0';
	strcpy(DiseaseType, p.DiseaseType); // string copy
	this->pId = p.pId;
	this->dId = p.dId;
	appTime = p.appTime;
	appDate = p.appDate;
	this->token_Number = p.token_Number;
	this->fee = p.fee;
	this->status = p.status;
}
void Appointment::setAppointment(char* disease, int pid, int did, date& d, time& t, int token, float fee, bool is_check) {
	int size = strlen(disease);
	this->DiseaseType = new char[size + 1];
	DiseaseType[size] = '\0';
	strcpy(DiseaseType, disease);
	this->pId = pid;
	this->dId = did;
	appTime = t;
	appDate = d;
	this->token_Number = token;
	this->fee = fee;
	this->status = is_check;
}
void Appointment::setStatus(bool s) {
	status = s;
}

void Appointment::setxyValues(int x, int y) {
	this->x = x;
	this->y = y;
}
int Appointment::getY() {
	return y;
}
date& Appointment::getappDate() {
	return appDate;
}
int Appointment::getTokenNumber() {
	return token_Number;
}

BOOL Appointment::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
char* Appointment::getDisease() {
	return DiseaseType;
}

bool Appointment::getStatus() {
	return status;
}

float Appointment::getFee() {
	return this->fee;
}

int Appointment::getPatientId() {
	return pId;
}
int Appointment::getDoctorId() {
	return dId;
}
ostream& operator<<(ostream& out, Appointment& p) {
	int horizontal = 16;
	p.setxy(p.x, p.y); p.y++;
	for (int i = 0; i < 60; i++) { // top boarder line
		cout << char(176);
	}
	for (int i = 0; i < horizontal; i++) { // left boarder line
		p.setxy(p.x, p.y + i); cout << char(176);
	}
	for (int i = 0; i < horizontal; i++) { // right boarder line
		p.setxy(p.x + 59, p.y + i); cout << char(176);
	}
	p.setxy(p.x, p.y + horizontal);
	for (int i = 0; i < 60; i++) { // bottom boarder line
		cout << char(176);
	}
	p.setxy(p.x + 14, p.y); cout << ">>>>>>>PENDING APPOINTMENT<<<<<<<"; p.y += 2;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Token Number : " << p.token_Number; 
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Patient Id number : "<<p.pId;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Doctor Id number : " << p.dId;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Disease Type of patient : " << p.DiseaseType;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Appointment date of patient : " << p.appDate;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Appointment time of patient: " << p.appTime;
	p.setxy(p.x + 1, p.y); p.y += 2;
	cout << "Checkup fee : " << p.fee;
	return out;
}
Appointment::~Appointment() {
	if (DiseaseType != NULL) {
		delete[] DiseaseType;
		DiseaseType = NULL;
	}
}
ofstream& operator<<(ofstream& fout, Appointment& p) {
	for (int i = 0; p.DiseaseType[i] != '\0'; i++) {
		if (p.DiseaseType[i] == ' ') {
			fout << "_";
		}
		else {
			fout << p.DiseaseType[i];
		}
	}
	fout << "\t" << p.pId;
	fout << "\t" << p.dId;
	fout << p.appDate;
	fout << p.appTime;
	fout << "\t" << p.token_Number;
	fout << "\t" << p.fee;
	fout << "\t" << p.status;
	return fout;
}

ifstream& operator>>(ifstream& fin, Appointment& p) {
	p.DiseaseType = new char[36];
	fin >> p.DiseaseType;
	fin >> p.pId;
	fin >> p.dId;
	fin >> p.appDate;
	fin >> p.appTime;
	fin >> p.token_Number;
	fin >> p.fee;
	fin >> p.status;
	return fin;
}


#endif // !Appointment
