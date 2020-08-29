#include<iostream>
#include"clinic.h"
#include<conio.h>
#include<fstream>

using namespace std;
int mainmenu() { // display main menu
	int x = 30; // control x cordinante
	int y = 3; // control y cordinante
	clinic c; 
	int operation = -1;
	system("CLS");
	c.boarder(21); // make boarder
	y++;
	c.setxy(x + 15, y); cout << ">>>>>>>>>>>>>> MENU <<<<<<<<<<<<<<"; y += 2;
	c.setxy(x + 1, y); cout << "0 : Exist "; y += 2;
	c.setxy(x + 1, y); cout << "1 : Admit patient in case of emergency"; y += 2;
	c.setxy(x + 1, y); cout << "2 : Add Doctor"; y += 2;
	c.setxy(x + 1, y); cout << "3 : Make an appointment for new patient "; y += 2;
	c.setxy(x + 1, y); cout << "4 : Checkup of new patient appointment "; y += 2;
	c.setxy(x + 1, y); cout << "5 : Make appointment for already existing patient "; y += 2;
	c.setxy(x + 1, y); cout << "6 : Checkup of existing patient appoiuntment"; y += 2;
	c.setxy(x + 1, y); cout << "7 : Print Detail"; y += 2;
	c.setxy(x + 10, y); cout << "Enter choice : ";
	c.setxy(x + 25, y); operation = _getche() ;
	getch();
	operation -= 48;
	while (operation <= -1 || operation >= 8) { //untill operation is not present in given operation
		operation = mainmenu();
	}
	y++;
	return operation;
}
int printMenu() { // print sub menu of print Menu
	int x = 30;
	int y = 3;
	clinic c;
	int operation = -1;
	system("CLS");
	c.boarder(19); // make boarder around information
	y++;
	c.setxy(x + 12, y); cout << ">>>>>>>>>>> Print MENU <<<<<<<<<<<"; y += 2;
	c.setxy(x + 1, y); cout << "0 : back "; y += 2;
	c.setxy(x + 1, y); cout << "1 : Doctor visited patients on a particular date"; y += 2;
	c.setxy(x + 1, y); cout << "2 : Patients who visited same doctor on different days."; y += 2;
	c.setxy(x + 1, y); cout << "3 : Pending appointments of a particular date."; y += 2;
	c.setxy(x + 1, y); cout << "4 : Pending appointments of a particular doctor."; y += 2;
	c.setxy(x + 1, y); cout << "5 : Complete history of a patient"; y += 2;
	c.setxy(x + 1, y); cout << "6 : Complete history of a doctor"; y += 2;
	c.setxy(x + 10, y); cout << "Enter choice : ";
	c.setxy(x + 25, y); operation = _getche();
	getch();
	operation -= 48;
	while (operation <= -1 || operation >= 7) {
		operation = mainmenu();
	}
	y++;
	return operation;
}

int main() {
	clinic c;
	int opetion = -1; // get data from menu
	while (opetion) { // untill operaion not equal to zero
		ifstream fin;
		fin >> c;
		opetion = mainmenu();
		if (opetion == 1){ // add patient in emergency
			c.addPatient();
		}
		else if (opetion == 2) { // add doctor
			c.addDoctor();
		}
		else if (opetion == 3) { // appointment of new person
			c.npAppointment();
		}

		else if (opetion == 4) { // check up for new patient
			c.checkUp();
		}
		else if (opetion == 5) { //appointment of already existing patient
			c.aEPAppointment();
		}
		else if (opetion == 6) { //checkup of already existing patient
			c.cFEPatient();
		}
		else if (opetion == 7) { // if user want to print detail
			int operation = -1; 
			while (operation) {
				operation = printMenu();
				if (operation == 1) {
					c.printPVOPDate();
				}
				else if (operation == 2) {
					c.printPatientSameDoctor();
				}
				else if (operation == 3) {
					c.printparticularDatePanAPP();
				}
				else if (operation == 4) {
					c.PerticularDPAppointment();
				}
				else if (operation == 5) {
					c.patientHistory();
				}
				else if (operation == 6) {
					c.doctorHistory();
				}
			}
		}
		ofstream fout;
		fout << c;
	}
	system("PAUSE");
	return 0;
}