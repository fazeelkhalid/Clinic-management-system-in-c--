#ifndef clinic_H
#define clinic_H

#include<iostream>

#include"date.h"
#include"time.h"
#include"name.h"
#include"pastRecord.h"
#include"patient.h"
#include"doctor.h"
#include"Appointment.h"
#include<Windows.h> //consist a function that set cursor position on console

using namespace std;

class clinic {
private:
	int pId; // patient id
	int dId; // doctor id
	int Token; // token given to patient at the time of appointmen
	int totalPatient; // how many patient have been checked
	Appointment* App; // store appointment
	patient* pat; // store patient
	doctor* doc; // store doctor
	
	int docMenu(int, doctor*); // display doctor menue
	
public:
	clinic();
	void addPatient(); // add new patient in case of emergency
	void npAppointment(); // appointment for new patient
	void boarder(int); // making outer boarder
	void addDoctor(); // add doctor in doc array
	BOOL setxy(int, int);// this will set cursor position
	void checkUp(); // check up for new patient appointment
	void aEPAppointment(); // appointment for already exicting patient
	void cFEPatient(); // checkup for already existing patient
	
	void printPVOPDate(); // Print details of all patients, whom a doctor has visited on a particular date
	void printPatientSameDoctor(); //Print details of all patients who visited same doctor but on different days.
	void printparticularDatePanAPP();//Print details of all pending appointments of a particular
	void PerticularDPAppointment(); //Print details of all pending appointments of a particular doctor
	void patientHistory();// Print complete history of a patient
	void doctorHistory();// Print complete history of a doctor

	friend ofstream& operator <<(ofstream&, clinic&); // input data in file
	friend ifstream& operator >>(ifstream&, clinic&); // read data from file
	~clinic();
};

clinic::clinic() { // default constructor
	pId = 0;
	dId = 0;
	Token = 0;
	totalPatient = 0;
	App = NULL;
	pat = NULL;
	doc = NULL;
}
void clinic::addPatient() {
	int x = 30, y = 3; // control x and y component of cursor position
	char disease[36]; // store disease type
	int fee = -1; //checkup fee
	int sId; // store doctor id that selected for patient;
	int k = y; // control x component of right line
	int j = x + 59; // control y component of line
	date arrDate; // store admit date
	time arrtime; // stor admit time
	patient* temp = pat;

	system("CLS");
	boarder(21); // making boarder
	y++;
	setxy(x + 12, y); cout << ">>>>>>>ADD pATIENT IN EMERGENCY<<<<<<<";
	pat = new patient[totalPatient + 1]; // memory assing to pat
	for (int i = 0; i < totalPatient; i++) { // copy data
		pat[i] = temp[i];
	}

	pat[totalPatient].setInput(30, y); // input person information
	y++;
	setxy(x + 1, y);
	cout << "Admit date and pattern is DD/MM/YYYY -> ";
	arrDate.setInput(x + 41, y); y++; // input date from user 
	setxy(x + 1, y);
	cout << "Admit time and pattern is SS:MM:HH -> ";
	arrtime.setInput(x + 39, y); y++; y++; //input time from user

	cin.ignore();
	setxy(x + 1, y); y++;
	cout << "DiseaseType : "; // get disease from the operator
	cin.getline(disease, 36);
	y++;
	sId = docMenu(dId, doc); // store doctor id according to patient disease
	while (fee < 0) { // get admit fee
		setxy(x + 1, y);
		cout << "Admit fee : ";
		setxy(x + 13, y); cout << "    "; // put spaces after print "Admit fee : "
		setxy(x + 13, y);
		cin >> fee;
	}
	pastRecord patRecord(disease, arrDate, arrtime, sId, fee); // input in past record
	pat[totalPatient].newPatientRec(pId + 1, patRecord); // adding patient in pat array
	doc[sId - 1].setPatienVisited(pId + 1); // add patient id in doctor data
	pId++;
	totalPatient++;
}

void clinic::npAppointment() {
	int x = 30; // control cursor x component
	int y = 3; // control cursor y component
	char disease[36];
	int fee = -1; // store appointment fee
	int sDId; //store selected doctor id
	time arrTime; // appointment time
	date arrDate; // appointment date
	Appointment* temp = App;
	App = new Appointment[Token + 1];
	system("CLS");
	boarder(17); //make boarder when this function call
	y++;
	setxy(x + 12, y); cout << ">>>>>>>> NEW PATIENT APPOINTMENT <<<<<<<<"; y += 2;
	for (int i = 0; i < Token; i++) { // copy data from patient temp array
		App[i] = temp[i];
	}
	setxy(x + 1, y); y += 2;
	cout << "Patient token number : " << Token + 1;
	setxy(x + 1, y); y += 2;
	cout << "Patient Id number : " << pId + 1;
	setxy(x + 1, y);
	cout << "Arrival date and pattern is DD/MM/YYYY -> ";
	arrDate.setInput(x + 43, y); y++; // input appointment date
	setxy(x + 1, y);
	cout << "Arrival time and pattern is SS:MM:HH -> ";
	arrTime.setInput(x + 41, y); y += 2; // input appointment time
	cin.ignore();
	setxy(x + 1, y); y += 2;
	cout << "Enter Disease : ";
	cin.getline(disease, 36);
	sDId = docMenu(dId, doc); // show doctor menu
	while (fee < 0) {
		setxy(x + 1, y);
		cout << "Enter checkup fee : ";
		setxy(x + 21, y); cout << "      ";// print spaces after "Enter checkup fee : "
		setxy(x + 21, y);
		cin >> fee;
	}
	y += 2;
	App[Token].setAppointment(disease, pId + 1, dId, arrDate, arrTime, Token + 1, fee, 0); //add data in aapointment array
	Token++;
	pId++;
	setxy(x + 1, y);
	cout << "press any key to continue";
	_getch();
}
void clinic::addDoctor() {
	int x = 30, y = 3; // control cursor position
	char spacility[36]; // store doctor spacilization
	doctor* temp = doc;
	doc = new doctor[dId + 1];
	for (int i = 0; i < dId; i++) { // copy data from temp to doctor array
		doc[i] = temp[i];
	}
	dId++;
	system("CLS");
	boarder(19); //make boarder
	y++;
	setxy(x + 17, y); y += 2;
	cout << ">>>>>>>>>> ADD DOCTOR <<<<<<<<<<";
	setxy(x + 1, y);
	cout << "Doctor Id : " << dId;
	doc[dId - 1].setInput(x, y); y++; // input person info in doctor array from console
	cin.ignore();
	setxy(x + 1, y); y += 2;
	cout << "Enter doctor spacility : ";
	cin.getline(spacility, 36);
	setxy(x + 1, y);
	cout << "Press any key for continue";
	_getch();
	doc[dId - 1].setDoctor(dId, spacility); // enter and save data in doctor file
}

void clinic::checkUp() {
	int x = 30, y = 3;// control x and y componrnt of cursor
	patient* temp = pat;
	int token = 0; 
	date arrDate; // store admit date
	time arrtime; // store admit time
	system("CLS");
	boarder(21); // draw boarder
	y++;
	setxy(x + 16, y); cout << ">>>>>>>>>> CheckUP <<<<<<<<<<"; y += 2;
	while (token <= 0) {
		setxy(x + 1, y);
		cout << "Enter token number : ";
		setxy(x + 22, y); cout << "          "; // print spaces after "Enter token between 0 to <<token+1 :  "
		setxy(x + 22, y);
		cin >> token;
	}
	if (App[token - 1].getStatus() == false&& token <= Token) {
		App[token - 1].setStatus(1); // change status of current appointment
		pat = new patient[totalPatient + 1]; //add in patient array
		for (int i = 0; i < totalPatient; i++) { // copy data
			pat[i] = temp[i];
		}
		pat[totalPatient].setInput(x, y); // input person data
		y++;
		setxy(x + 1, y);
		cout << "current date and pattern is DD/MM/YYYY -> ";
		arrDate.setInput(x + 43, y); y++; //input date
		setxy(x + 1, y);
		cout << "current time and pattern is SS:MM:HH -> ";
		arrtime.setInput(x + 41, y); y += 2; // input time
		setxy(x + 1, y);
		cout << "Press any key to continue";
		_getch();
		pastRecord patRecord(App[token - 1].getDisease(), arrDate, arrtime, App[token - 1].getDoctorId(), App[token - 1].getFee());
		pat[totalPatient].newPatientRec(App[token - 1].getPatientId(), patRecord);
		doc[App[token - 1].getDoctorId() - 1].setPatienVisited(App[token - 1].getPatientId());
		totalPatient++;
	}
	else {
		setxy(x + 1, y + 2);
		cout << "Token not exist! ";
		getch();
	}
}

void clinic::aEPAppointment() { // already existing patient appointment
	int x = 30;
	int y = 3;
	int pID = -1; // store patient Id
	bool IDCPresent = false; // check patient id present or not
	int index = 0;//store index of that perticular patient
	char disease[36];
	int fee = -1; // store appointment fee
	int sDId; //store selected doctor id
	time arrTime;
	date arrDate;
	Appointment* temp = App;

	system("CLS");
	boarder(17);
	y++;
	setxy(x + 3, y); cout << ">>>>>>> ALREADY EXISTING PATIENT APPOINTMENT <<<<<<<"; y += 2;
	while (pID < 0) {
		setxy(x + 1, y);
		cout << "Patient Id card number : ";
		setxy(x + 25, y); cout << "     "; //print spaces after "Patient Id card number : "
		setxy(x + 25, y);
		cin >> pID;
	}
	y += 2;
	for (int i = 0; i < totalPatient; i++) {
		index = i;
		if (pID == pat[i].getPid()) { //patient id found
			IDCPresent = true; 
			i = totalPatient; // store last index
		}
	}
	App = new Appointment[Token + 1];
	for (int i = 0; i < Token; i++) { // copy data from patient temp array
		App[i] = temp[i];
	}
	setxy(x + 1, y); y += 2;
	cout << "Patient token number : " << Token + 1;
	setxy(x + 1, y);
	cout << "Current date and pattern is DD/MM/YYYY -> ";
	arrDate.setInput(x + 43, y); y++; // input date
	setxy(x + 1, y);
	cout << "Current time and pattern is SS:MM:HH -> ";
	arrTime.setInput(x + 41, y); y += 2; // input time
	cin.ignore();
	setxy(x + 1, y); y += 2;
	cout << "Enter Disease : ";
	cin.getline(disease, 36);
	sDId = docMenu(dId, doc); // show doctor menu
	while (fee < 0) {
		setxy(x + 1, y);
		cout << "Enter checkup fee : ";
		setxy(x + 21, y); cout << "        "; //print spaces after "Enter checkup fee : "
		setxy(x + 21, y);
		cin >> fee;
	}
	y += 2;
	setxy(x + 1, y);
	cout << "Press any key to continue : ";
	_getch();
	App[Token].setAppointment(disease, pat[index].getPid(), dId, arrDate, arrTime, Token + 1, fee, 0);
	Token++;
}

void clinic::cFEPatient() { // checkup for existing patient
	int x = 30, y = 3; // control x and y cordinates of cursor
	int pID = -1; // store patient id
	patient* temp = pat;
	int token = 0;
	date arrDate; // admit dat
	time arrtime; // admit time
	system("CLS");
	boarder(13);
	y++;
	setxy(x + 18, y); cout << ">>>>>>>>> CHECKUP <<<<<<<<<<"; y += 2;
	while (token <= 0) {
		setxy(x + 1, y);
		cout << "Enter token number : ";
		setxy(x + 22, y); cout << "        "; // print spaces after"Enter token between 0 to " << Token + 1 << " : "
		setxy(x + 22, y);
		cin >> token;
	}
	y += 2;
	while (pID <= 0) {
		setxy(x + 1, y);
		cout << "Enter patient Id : ";
		setxy(x + 20, y); cout << "        "; // print spaces after "Enter patient Id : "
		setxy(x + 20, y);
		cin >> pID;
	}
	y += 2;
	if (pID == App[token - 1].getPatientId() && App[token - 1].getStatus() == false) {
		App[token - 1].setStatus(1); // change appointment status
		setxy(x + 1, y);
		cout << "Current date and pattern is DD/MM/YYYY -> ";
		arrDate.setInput(x + 42, y); y++; // input date
		setxy(x + 1, y);
		cout << "Current time and pattern is SS:MM:HH -> ";
		arrtime.setInput(x + 40, y); y += 2; // input time
		pastRecord patRecord(App[token - 1].getDisease(), arrDate, arrtime, App[token - 1].getDoctorId(), App[token - 1].getFee());
		pat[token - 1].addPatientRec(patRecord);
		doc[App[token - 1].getDoctorId() - 1].setPatienVisited(App[token - 1].getPatientId());
	}
	else {
		setxy(x + 1, y); y += 2;
		cout << "Token not found : ";
	}
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
}

void clinic::printPVOPDate() { // Print details of all patients, whom a doctor has visited on a particular date
	date d; // store date
	bool recordFound = false; 
	int x = 30, y = 3; // control coursor
	system("CLS");
	boarder(7); // draw board
	y++;
	setxy(x + 1, y); cout << ">>>>>> DOCTOR VISITED PATIENTS ON A PARTICULAR DATE <<<<<<"; y += 2;
	setxy(x + 1, y);
	cout << "Enter Date and pattern is DD/MM/YYYY -> ";
	d.setInput(x + 41, y); y++; // input date
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	for (int i = 0; i < totalPatient; i++) {
		if (pat[i].datePresent(d)) { // if any patient found according to that date
			recordFound = true;
			pat[i].setxyValues(x, y); 
			cout << pat[i]; // output pof that perticular patient
			y = pat[i].getY();
		}
	}
	if (!recordFound) { // if record not found then if statement execute
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "No record found!";
	}
	setxy(x + 1, y); cout << "Press any key for continue";
	_getch();
}

void clinic::printPatientSameDoctor() {//Print details of all patients who visited same doctor but on different days.
	int x = 30, y = 3; // control xy component of coursor
	system("CLS");
	boarder(7); // draw boarder
	y++;
	setxy(x + 1, y); cout << ">>PATIENT WHO VISITED SAME DOCTOR BUT ON DIFFERENT DATE<<"; y += 2;
	int doctorId = 0;
	bool recordFound = false;
	while (doctorId <= 0) {
		setxy(x + 1, y);
		cout << "Enter doctor ID : ";
		setxy(x + 19, y); cout << "         "; // print spaces after"Enter doctor ID : "
		setxy(x + 19, y);
		cin >> doctorId;
	}
	y += 2;
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	for (int i = 0; i < totalPatient; i++) {
		if (pat[i].doctorIdPresent(doctorId)) { // check that doctor id is found in any patient record
			pat[i].setxyValues(x, y);
			cout << pat[i]; // print record of that perticular patient
			y = pat[i].getY();
			recordFound = true;
		}
	}
	if (!recordFound) { // if no record found
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "No record found!";
	}
	setxy(x + 1, y); cout << "Press any key for continue";
	_getch();
}
void clinic::printparticularDatePanAPP() { //Print details of all pending appointments of a particular date.
	int x = 30, y = 3; // control x and y component ofcursor
	system("CLS");
	boarder(7); // draw board
	y++;
	setxy(x + 17, y); cout << ">>>>>>> PENDING APPOINTMENT<<<<<<<"; y += 2;
	date d; // stor date
	bool recordFound = false;
	setxy(x + 1, y);
	cout << "Enter Date and pattern is DD/MM/YYYY -> ";
	d.setInput(x + 40, y); y++; // input date
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	for (int i = 0; i < Token; i++) {
		if (d == App[i].getappDate() && !App[i].getStatus()) { // check any record found according to that perticular record
			recordFound = true;
			App[i].setxyValues(x, y);
			cout << App[i]; // print record of that perticular appointment
			y = App[i].getY();
		}
	}
	if (!recordFound) { // if no record found
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "Record not found!";
	}
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();

}

void clinic::PerticularDPAppointment() {//Print details of all pending appointments of a particular doctor
	int x = 30, y = 3; // control xy component of coursor
	int doctorId = 0;
	bool recordFound = false;
	system("CLS");
	boarder(7); // draw boarder
	y++;
	setxy(x + 17, y); cout << ">>>>>>> PENDING APPOINTMENT<<<<<<<"; y += 2;

	while (doctorId <= 0) {
		setxy(x + 1, y);
		cout << "Enter doctor ID : ";
		setxy(x + 19, y); cout << "          "; //print spaces after "Enter doctor ID : "
		setxy(x + 19, y);
		cin >> doctorId;
	}
	y += 2;
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	for (int i = 0; i < Token; i++) {
		if (doctorId == App[i].getDoctorId() && !App[i].getStatus()) {
			App[i].setxyValues(x, y);
			cout << App[i]; // if any record in panding appointment according to that doctor Id
			y = App[i].getY();
			recordFound = true;
		}
	}
	if (!recordFound) { //if no record found
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "Record not found!";
	}
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
}

void clinic::patientHistory() {
	int x = 30, y = 3; // control xy component of coursor
	int patientId = -1;
	bool historyFound = false;
	system("CLS");
	boarder(7); // draw boarder
	y++;
	setxy(x + 17, y); cout << ">>>>>>> PATIENT HISTORY <<<<<<<"; y++;
	while (patientId <= 0) {
		setxy(x + 1, y);
		cout << "Enter patient Id : ";
		setxy(x + 20, y); cout << "          "; // print spaces after "Enter patient Id : "
		setxy(x + 20, y);
		cin >> patientId;
	}
	y += 2;
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	for (int i = 0; i < totalPatient; i++) {
		if (patientId == pat[i].getPid()) { //check any patient present according to that perticular id
			pat[i].setxyValues(x, y);
			cout << pat[i];
			y = pat[i].getY();
			historyFound = true;
		}
	}
	if (!historyFound) { // if no recor found then this will execute
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "Record not found!";
	}
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
}

void clinic::doctorHistory() {
	int x = 30, y = 3; // control xy component of coursor
	int doctorId = -1; // store doctor id enter by user
	bool historyFound = false;
	system("CLS");
	boarder(6); // draw boarder
	y++;
	setxy(x + 17, y); cout << ">>>>>>> Doctor HISTORY <<<<<<<"; y++;
	while (doctorId <= 0) {
		setxy(x + 1, y);
		cout << "Enter patient Id : ";
		setxy(x + 20, y); cout << "         "; // print spaces after "Enter patient Id : "
		setxy(x + 20, y);
		cin >> doctorId;
	}
	y += 2;
	setxy(x + 1, y);
	cout << "Press any key to continue";
	_getch();
	system("CLS");
	y = 3;
	boarder(18);
	for (int i = 0; i < dId; i++) {
		if (doctorId == doc[i].getDid()) { // check any record found according to that doctor id
			cout << doc[i];
			historyFound = true;
		}
	}
	if (!historyFound) { // if no record found
		system("CLS");
		boarder(5); y++;
		setxy(x + 1, y); y += 2;
		cout << "Record not found!";
		setxy(x + 1, y);
		cout << "Press any key to continue";
		_getch();
	}
	else {
		setxy(x + 1, y + 17);
		cout << "Press any key to continue";
		_getch();

	}
}


ofstream& operator <<(ofstream& fout, clinic& c) {
	fout.open("patient.txt");
	fout << c.pId << "\n"; // input patient id in patien file
	fout << c.totalPatient << "\n"; // input total patient in patient file
	for (int i = 0; i < c.totalPatient; i++) {
		fout << c.pat[i] << "\n"; // input patient record in patient file
	}
	fout.close();
	fout.open("Appointment.txt");
	fout << c.Token << "\n"; //input token in appointment file
	for (int i = 0; i < c.Token; i++) {
		fout << c.App[i] << "\n"; // input appointment record in appointment file
	}
	fout.close();
	fout.open("Doctor.txt");
	fout << c.dId << "\n"; // input doctor Id in doctor file
	for (int i = 0; i < c.dId; i++) {
		fout << c.doc[i] << "\n"; // input doctor record in doctor file
	}

	return fout;
}

ifstream& operator >>(std::ifstream& fin, clinic& c) {
	//start input doctor data from file
	fin.open("Doctor.txt");
	fin >> c.dId; // input doctor Id from doctor file
	if (c.dId != 0) {
		c.doc = new doctor[c.dId];
		for (int i = 0; i < c.dId; i++) {
			fin >> c.doc[i]; // input doctor record from doctor file
		}
	}
	fin.close();
	fin.open("Patient.txt");
	fin >> c.pId; // input patient id from patient file
	fin >> c.totalPatient; // input total patient from patient file
	if (c.totalPatient != 0) {
		c.pat = new patient[c.totalPatient];
		for (int i = 0; i < c.totalPatient; i++) {
			fin >> c.pat[i]; // input patient record from patient file
		}
	}
	fin.close();
	fin.open("Appointment.txt");
	fin >> c.Token; // input token number from appointment file
	if (c.Token != 0) {
		c.App = new Appointment[c.Token];
		for (int i = 0; i < c.Token; i++) {
			fin >> c.App[i]; // input appointment record from appointment file
		}
	}
	fin.close();

	return fin;
}

int clinic::docMenu(int docId, doctor* d) { // show available doctor ids plus doctor type
	int x = 91, y = 3; // contorl x and y component of coursor
	int verticalines = 5*docId; // decide verticle line length
	setxy(x, y);
	for (int i = 0; i < 28; i++) { // top boarder
		cout << char(176);
	}
	for (int i = 0; i < verticalines + 3; i++) { // left boarder
		setxy(x, y + i);cout<< char(176);
	}
	setxy(x, y + verticalines + 3);
	for (int i = 0; i < 28; i++) { // bottom boarder
		 cout << char(176);
	}
	for (int i = 0; i < verticalines + 3; i++) { // right boarder
		setxy(x+27, y+i); cout << char(176);
	}
	y++;
	setxy(x + 6, y);
	cout << "Available Doctors";
	int operation = 0;
	for (int i = 0; i < docId; i++) {
		y += 2;
		setxy(x + 1, y);
		cout << "Doctor Id : " << i + 1;
		y += 2;
		setxy(x + 1, y);
		cout << "spacility : " << d[i].getdoctorType(); 
	}
	y += 2;
	while (operation <= 0 || operation > docId) {
		setxy(x + 1, y);
		cout << "Respective doctor Id : ";
		setxy(x + 23, y); cout << "    "; //print spaces after "Respective doctor Id : "
		setxy(x + 23, y);
		cin >> operation;
	}
	return operation;
}
BOOL clinic::setxy(int x, int y) {// this will set cursor position
	COORD c = { x,y };
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clinic:: boarder(int height) {
	int x = 30, y = 3; // control xy component of coursor
	setxy(x, y); // set cursor position
	for (int i = 0; i < 60; i++) { // print top line
		cout << char(176);
	}
	for (int i = 0; i < height; i++) { // print right side line
		setxy(x + 59, y + i); cout << char(176);
	}
	for (int i = 0; i < height; i++) { // print left line
		setxy(x, y + i); cout << char(176);
	}
	setxy(x, y + height); // print bottom line
	for (int i = 0; i < 60; i++) {
		cout << char(176);
	}
	y++;

}

clinic::~clinic(){
	if (App != NULL) {
		delete[]App;
		App = NULL;
	}
	if (pat != NULL) {
		delete[]pat;
		pat = NULL;
	}
	if (doc != NULL) {
		delete[]doc;
		doc = NULL;
	}
}
#endif