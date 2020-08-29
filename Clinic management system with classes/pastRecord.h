#ifndef pastRecord_H

#define pastRecord_H

#include<iostream>
#include<string.h>
#include"time.h"
#include"date.h"
#include<windows.h>
using namespace std;

class pastRecord {
private:
	char* DiseaseType; // store patient disease type
	date visDate; // patient visited date to the doctor
	time visTime; // stor patient visited time to the doctor
	int AssignedDoc; // Contain Doctor ID
	float feepaid; // fee paid by patient
	BOOL setxy(int x, int y);// this will set cursor position
public:
	pastRecord();
	pastRecord(char*, date&, time&, int, float);
	int getAssignedDoc();
	date& getDate();// return date
	void operator = (pastRecord& );
	void setPastRecord(char*, date&, time&, int, float); // input record in formation
	void output(int, int& ); // display output by getting initially xy cordinates
	friend ofstream& operator <<(ofstream&, pastRecord&);
	friend ifstream& operator >>(ifstream&, pastRecord&);

};
pastRecord::pastRecord() {
	DiseaseType = NULL;
	AssignedDoc = 0;
	feepaid = 0;
}
pastRecord::pastRecord(char* arr, date& d, time& t, int Did, float fee) {
	setPastRecord(arr, d, t, Did, fee);
}
int pastRecord::getAssignedDoc() {
	return AssignedDoc;
}

void pastRecord :: operator = (pastRecord& p) {
	setPastRecord(p.DiseaseType, p.visDate, p.visTime, p.AssignedDoc, p.feepaid);
}

void pastRecord::setPastRecord(char* arr, date& d, time& t, int Did, float fee) {
	int size = strlen(arr);
	DiseaseType = new char[size + 1];
	DiseaseType[size] = '\n';
	strcpy(DiseaseType, arr);
	this->visDate = d;
	this->visTime = t;
	this->AssignedDoc = Did;
	this->feepaid = fee;
}

date& pastRecord::getDate() {
	return visDate;
}
void pastRecord:: output(int x, int& y) {
	setxy(x + 1, y); y += 2;
	cout << "Diseases type : " << DiseaseType;
	setxy(x + 1, y); y += 2;
	cout << "Visit date of patient: " << visDate;
	setxy(x + 1, y); y += 2;
	cout << "Visit time of patient : " << visTime;
	setxy(x + 1, y); y += 2;
	cout << "fee paid : " << feepaid;
}
ofstream& operator <<(ofstream& fout, pastRecord& p) {
	for (int i = 0; p.DiseaseType[i] != '\0'; i++) {
		if (p.DiseaseType[i] == ' ') { // output disease type in file and put_ where space present
			fout << "_";
		}
		else {
			fout << p.DiseaseType[i];
		}
	}
	fout << p.visDate;
	fout << p.visTime;
	fout << "\t" << p.AssignedDoc;
	fout << "\t" << p.feepaid;
	return fout;
}

ifstream& operator >>(ifstream& fin, pastRecord& p) {
	p.DiseaseType = new char[36];
	fin >> p.DiseaseType;
	fin >> p.visDate;
	fin >> p.visTime;
	fin >> p.AssignedDoc;
	fin >> p.feepaid;
	return fin;
}

BOOL pastRecord::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

#endif // !pastRecord_H
