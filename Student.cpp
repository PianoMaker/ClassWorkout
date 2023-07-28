﻿#include "Student.h"
#include "globals.h"

#pragma warning (disable:4996)
#define HEADER cout << "#\tName\t\tSurname\t\tGener\tFaculty\t\tAdm.Year\tC++\tHardw.\tUML.\t global\n";

using namespace std;


Student::Student(int lessons) : lessons(lessons)
{
	strcpy(name, "Unknown");
	strcpy(surname, "Unknown");
	strcpy(faculty, "Unknown");
	admission_year = 2023;
	CountAverage();
}
// конструктор з усіма параметрами
Student::Student(int lessons, char* name, char* surname, char* faculty, int admission_year, int* c_prog, int* hardware, int* uml)
{
	this->lessons = lessons;
	strcpy(this->name, name);
	strcpy(this->surname, surname);
	strcpy(this->faculty, faculty);
	this->admission_year = admission_year;
	for (int i = 0; i < lessons; i++)
	{
		this->c_prog[i] = c_prog[i];
		this->hardware[i] = hardware[i];
		this->uml[i] = uml[i];
	}
	ave_prog = Average(c_prog, lessons);
	ave_hardware = Average(hardware, lessons);
}
/*
Student::Student(const Student& obj)// копіювання
{
	this->lessons = obj.lessons;
	strcpy(this->name, obj.name);
	strcpy(this->surname, obj.surname);
	strcpy(this->faculty, obj.faculty);
	this->gender = obj.gender;
	this->admission_year = obj.admission_year;
	for (int i = 0; i < lessons; i++)
	{
		this->c_prog[i] = obj.c_prog[i];
		this->hardware[i] = obj.hardware[i];
		this->uml[i] = obj.uml[i];
	}
}
Student::~Student()// деструктор
{
	delete[] c_prog;
	delete[] hardware;
	delete[] uml;
}
*/


// іменний сеттер 
void Student::SetName(char* name, char* surname)
{
	strcpy(this->name, name);
	strcpy(this->surname, surname);
}

// виставлення нових оцінок по кожному з предметів

void Student::SetMarks(int c_prog, int hardware, int uml)
{

	int* temp = new int[lessons + 1];
	for (int i = 0; i < lessons; i++)
	{
		temp[i] = this->c_prog[i];
	}
	temp[lessons] = c_prog;
	this->c_prog = temp;
	//delete[] temp;

//предмет hardware
	int* temp2 = new int[lessons + 1];
	for (int i = 0; i < lessons; i++)
	{
		temp2[i] = this->hardware[i];
	}
	temp2[lessons] = hardware;
	this->hardware = temp2;
	//delete temp2;

	//предмет winconfig
	int* temp3 = new int[lessons + 1];
	for (int i = 0; i < lessons; i++)
	{
		temp3[i] = this->uml[i];
	}
	temp3[lessons] = uml;
	this->uml = temp3;

	lessons++;
	//delete temp3;
}

void Student::EditMarks(int index)
{
	if (!lessons) Message(12, "\nStudents don't have marks yet");
	else {
		bool job = EnterPass();


		if (job)
		{
			Message(11, "\ncurrent marks:\n");
			ShowMarks();

			Message(11, "\ninsert new marks:\n");
			if (ToDoOrNotToDo("c_programming"))
			{
				for (int i = 0; i < lessons; i++)
				{
					c_prog[i] = Entervalue("", bestmark);
				}
			}
			if (ToDoOrNotToDo("hardware"))
			{
				for (int i = 0; i < lessons; i++)
				{
					hardware[i] = Entervalue("", bestmark);
				}
			}
			if (ToDoOrNotToDo("UML"))
			{
				for (int i = 0; i < lessons; i++)
				{
					uml[i] = Entervalue("", bestmark);
				}
			}
		}
		else cout << Message(12, "Wrong password, nothing has been edited");
	}
}

// геттери
char* Student::GetName() { return name; }
char* Student::GetSurname() { return surname; }
char* Student::GetFaculty() { return faculty; }
char Student::GetGender() { return gender; }
int Student::GetAdmission_year() { return admission_year; }
int Student::GetProgramming() { return ave_prog; }
int Student::GetHardware() { return ave_hardware; }
int Student::Getuml() { return ave_uml; }


// Інший варіант. Працює як мультисеттер 
void Student::Fill(Student* students, int size)
{
	for (int i = 0; i < size; i++)
	{
		CINIGNORE;
		Message(11, "Exploring student #");
		cout << i + 1 << ":\n";
		cout << "enter name\n"; CINIGNORE; cin.getline(students[i].name, 30);
		cout << "enter surname\n"; CINIGNORE; cin.getline(students[i].surname, 30);
		cout << "enter faculty\n"; CINIGNORE; cin.getline(students[i].faculty, 30);
		cout << "enter admission year\n"; CINIGNORE; cin >> students[i].admission_year;
		if (lessons > 0) cout << "enter marks:\n";
		for (int j = 0; j < lessons; j++)
		{
			CINIGNORE; students[i].c_prog[j] = Entervalue("C++ programming:\n", bestmark);
			CINIGNORE; students[i].hardware[j] = Entervalue("Hardware:\n", bestmark);
			CINIGNORE; students[i].uml[j] = Entervalue("Windows configuration:\n", bestmark);
		}
	}
}


void Student::CountAverage() // рахує середнє з округленням до 0,1
{
	if (lessons == 0)
	{
		ave_prog = 0;
		ave_hardware = 0;
		ave_uml = 0;
		ave_global = 0;
	}
	else
	{
		ave_prog = round(Average(c_prog, lessons) * 10.0) / 10.0;
		ave_hardware = round(Average(hardware, lessons) * 10.0) / 10.0;
		ave_uml = round(Average(uml, lessons) * 10.0) / 10.0;
		ave_global = round((ave_prog + ave_hardware + ave_uml) / 3 * 10.0) / 10.0;
	}

}

/* Виведення на екран */

void Student::Show(int index) // для одного студента
{
	HEADER;
	CountAverage();
	cout << setw(150) << setfill('_') << " \n";
	cout << "1\t" << setfill(' ')
		<< setw(12) << name << "\t\t"
		<< setw(12) << surname << "\t\t"
		<< setw(1) << gender << "\t"
		<< setw(12) << faculty << "\t\t"
		<< setw(5) << admission_year << "\t\t"
		<< setw(2) << ave_prog << "\t"
		<< setw(2) << ave_hardware << "\t"
		<< setw(2) << ave_uml << "\t"
		<< setw(2) << ave_global << "\n";
}

void Student::ShowMarks(int index) // для одного студента
{
	CountAverage();
	cout << "\nStudent " << name << " " << surname << " has got the following marks:";
	cout << "\n   C++ programming:\t";
	for (int i = 0; i < lessons; i++)
	{
		cout << right << setw(2) << c_prog[i] << " ";
	}
	cout << "\t Average: " << ave_prog;
	cout << "\n\t  Hardware: \t";
	for (int i = 0; i < lessons; i++)
	{
		cout << right << setw(2) << hardware[i] << " ";
	}
	cout << "\t Average: " << ave_hardware;
	cout << "\n\t\tUML: \t";
	for (int i = 0; i < lessons; i++)
	{
		cout << right << setw(2) << uml[i] << " ";
	}
	cout << "\t Average: " << ave_uml;
}

void Student::Show(Student* students, int size)//для групи студентів
{
	HEADER;
	cout << setw(80) << setfill('_') << " \n";
	for (int i = 0; i < size; i++)
	{
		students[i].CountAverage();
		cout << i + 1 << "\t"
			<< left <<  setfill(' ')
			<< setw(12) << students[i].name << "\t"
			<< setw(12) << students[i].surname << "\t"
			<< setw(1) << students[i].gender << "\t"
			<< setw(12) << students[i].faculty << "\t"
			<< setw(5) << students[i].admission_year << "\t\t"
			<< right 
			<< setw(2) << students[i].ave_prog << "\t"
			<< setw(2) << students[i].ave_hardware << "\t"
			<< setw(2) << students[i].ave_uml << "\t"
			<< setw(2) << students[i].ave_global << "\n";

	}
}

/* створення екземплярів з випадковими параметрами */

void Student::RandSurnames()
{
	char root[5][10] = { "Ivan", "Dmytr", "Petr", "Pavl", "Grygor" };
	char ending[3][10] = { "uk", "iv", "enko" };
	strcpy(surname, root[rand() % 5]);
	strcat(surname, ending[rand() % 3]);
}

void Student::RandNames()
{
	int const numberofnames = 22;
	char name[numberofnames][10] = { "Ivan", "Dmytro", "Petro", "Pavlo", "Mykola", "Volodymyr", "Danylo", "Stepan", "Fedir", "Oksana", "Ivanka", "Olena", "Kateryna", "Olha", "Karina", "Myroslava", "Anna", "Orysia", "Nadia", "Natalie", "Alina", "Sofia"};
	int random = rand() % numberofnames;
	strcpy(this->name, name[random]);
	if (random < 9) gender = 'm';
	else gender = 'f';	
}

void Student::RandFaculty()
{
	int const numberoffacs = 2;
	char faculty[numberoffacs][30] = { "Devops", "Sysadmin" };
	strcpy(this->faculty, faculty[rand() % numberoffacs]);

}


/* редактор */
//для одного студента

void Student::Edit(int index)
{
	bool oncemore, choice;
	char buff[30];
	do
	{
		Show(index);

		cout << "enter name  (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
		if (strcmp(buff, "0")) strcpy(name, buff);

		cout << "enter surname (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
		if (strcmp(buff, "0")) strcpy(surname, buff);

		cout << "enter faculty (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
		if (strcmp(buff, "0")) strcpy(faculty, buff);

		cout << "enter admission_year (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
		if (strcmp(buff, "0")) admission_year = atoi(buff);

		SetGender();
		
		Show(index);
		oncemore = ToDoOrNotToDo("edit more");
	} while (oncemore);
}
//для групи студентів

void Student::SetGender()
{
	char buff;
	cout << "\nEnter gender. (m - male, f - female, 0 - skip this step)\n";
	do
	{
		cin >> buff;
		if (buff == '0') break;
		else if (buff != 'm' && buff != 'f')
			cout << "We accept only two genders. Try once more";
	} while (buff != 'm' && buff != 'f');
	if (buff != '0') gender = buff;
}

// очищення оцінок

void Student::ResetMarks()
{
	lessons = 0;
	delete[] c_prog;
	delete[] hardware;
	delete[] uml;
}


void Student::Add(Student*& students, int& size)
{
	Student* temp = new Student[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = students[i];

	temp[size] = Student();

	//delete[] students; // Видалення попереднього масиву
	students = temp;   // Перенаправлення вказівника на новий масив
	size++;            // Збільшення розміру масиву на 1
}

void Student::Delete(Student*& students, int& size, int index)
{
	index--;
	Student* temp = new Student[size - 1];
	for (int i = 0; i < index; i++)
		temp[i] = students[i];
	for (int i = index; i < size; i++)
		temp[i] = students[i + 1];

	//delete[] students; // Видалення попереднього масиву
	students = temp;   // Перенаправлення вказівника на новий масив
	size--;            // Збільшення розміру масиву на 1
}


void Student::SwapStudents(Student* students, int index1, int index2) {
	Student temp = students[index1];
	students[index1] = students[index2];
	students[index2] = temp;
}

void Student::Sort(Student*& students, int size)
{
	for (int j = 0; j < size; j++)
		for (int i = 1; i < size; i++)
			if (students[i - 1].ave_global < students[i].ave_global)
				SwapStudents(students, i - 1, i);
}


void Student::Stats(Student*& students, int size)
{
	
	int females = 0, males = 0, unknown = 0;
	for (int i = 0; i < size; i++)
	{
		students[i].CountAverage();
		if (students[i].GetGender() == 'f') females++;
		else if (students[i].GetGender() == 'm') males++;
		else unknown++;
	}
	Message(11, "\n===============Statstics=============\n");
	cout << "\nMales - " << males;
	cout << "\nFemales - " << females;
	cout << "\nUnknown - " << unknown;
	
	float fmarks = 0, mmarks = 0;
	for (int i = 0; i < size; i++)
	{
		if (students[i].GetGender() == 'f') fmarks+= students[i].ave_global;
		else if (students[i].GetGender() == 'm') mmarks+= students[i].ave_global;
	}
	
	cout << "\nAverage males marks - " << mmarks / males;
	cout << "\nAverage females marks - " << fmarks / females << endl;
}






