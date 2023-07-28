/*1. Написати клас "Студент".Поля стандартні.Методи:
вивод на екран
сеттер
геттери
редактор
*/

#include <iostream>
#include <iomanip>
#include <windows.h>
#pragma warning (disable:4996)
#define HEADER cout << "#\tName\t\tSurname\t\tFaculty\t\tAdm.Year\tC++\tHardw.\tUML.\n";
#define IFAVERAGE if (ToDoOrNotToDo("count success rate"))cout << "\nAverage success rate = " << 
#define CINIGNORE if (cin.rdbuf()->in_avail() > 0) { cin.clear(); cin.ignore(INT_MAX, '\n'); }
using namespace std;


// СИГНАТУРИ ФУНКЦІЙ 

bool ToDoOrNotToDo(string text); /* перемикач для юзерів на кшталт автора цієї програми,
який промахується по клавіатурі */
float Average(int* nums, int size); // рахує середнє 
int Entervalue(int max); // дурнестійке введення значення до максимального
bool EnterPass(); // введення пароля
void Color(int color); // колір повідомлень
string Message(int color, string message);


const char teacher[8] = "teacher"; // використовується як пароль.

//КЛАС

class Student
{
private:
	int months; // місяці навання
	char name[30];
	char surname[30];
	char faculty[30];
	int admission_year;
	int* c_prog = new int[months]; // оцінки помісячно
	int* hardware = new int[months];
	int* uml = new int[months];
	float ave_prog;
	float ave_hardware;
	float ave_uml;

public:
	// конструктор за замовченням
	Student(int months = 0) : months(months)
	{
		strcpy(name, "Unknown");
		strcpy(surname, "Unknown");
		strcpy(faculty, "Unknown");
		admission_year = 2023;
		CountAverage();
	}
	// конструктор з усіма параметрами
	Student(int months, char* name, char* surname, char* faculty, int admission_year, int* c_prog, int* hardware, int* uml)
	{
		this->months = months;
		strcpy(this->name, name);
		strcpy(this->surname, surname);
		strcpy(this->faculty, faculty);
		this->admission_year = admission_year;
		for (int i = 0; i < months; i++)
		{
			this->c_prog[i] = c_prog[i];
			this->hardware[i] = hardware[i];
			this->uml[i] = uml[i];
		}
		ave_prog = Average(c_prog, months);
		ave_hardware = Average(hardware, months);
	}
	Student(const Student& obj)// копіювання
	{
		this->months = obj.months;
		strcpy(this->name, obj.name);
		strcpy(this->surname, obj.surname);
		strcpy(this->faculty, obj.faculty);
		this->admission_year = obj.admission_year;
		for (int i = 0; i < months; i++)
		{
			this->c_prog[i] = obj.c_prog[i];
			this->hardware[i] = obj.hardware[i];
			this->uml[i] = obj.uml[i];
		}
	}
	~Student()// деструктор
	{
		delete[] c_prog;
		delete[] hardware;
		delete[] uml;
	}


	// іменний сеттер 
	void SetName(char* name, char* surname)
	{
		strcpy(this->name, name);
		strcpy(this->surname, surname);
	}

	// виставлення нових оцінок по кожному з предметів

	void SetMarks(int c_prog, int hardware, int uml)
	{
		
		int *temp = new int[months + 1];   
		for (int i = 0; i < months; i++)
		{
			temp[i] = this->c_prog[i];
		}
		temp[months] = c_prog;
		this->c_prog = temp;
		//delete[] temp;
		
 //предмет hardware
		int* temp2 = new int[months + 1];   
		for (int i = 0; i < months; i++)
		{
			temp2[i] = this->hardware[i];
		}
		temp2[months] = hardware;
		this->hardware = temp2;

		
//предмет winconfig
		int* temp3 = new int[months + 1];   
		for (int i = 0; i < months; i++)
		{
			temp3[i] = this->uml[i];
		}
		temp3[months] = uml;
		this->uml = temp3;

		months++;
	}

	void EditMarks(int index = 0)
	{
		bool job = EnterPass();

		if (job)
		{
			Message (11, "\ncurrent marks:\n");
			ShowMarks();

			Message(11, "\ninsert new marks:\n");
			if (ToDoOrNotToDo("c_programming"))
			{
				for (int i = 0; i < months; i++)
				{
					c_prog[i] = Entervalue(12);
				}
			}
			if (ToDoOrNotToDo("hardware"))
			{
				for (int i = 0; i < months; i++)
				{
					hardware[i] = Entervalue(12);
				}
			}
			if (ToDoOrNotToDo("UML"))
			{
				for (int i = 0; i < months; i++)
				{
					uml[i] = Entervalue(12);
				}
			}
		}
		else cout << Message(12, "Wrong password, nothing has been edited");
	}

	// геттери
	char* GetName() { return name; }
	char* GetSurname() { return surname; }
	char* GetFaculty() { return faculty; }
	int GetAdmission_year() { return admission_year; }
	int GetProgramming() { return ave_prog; }
	int GetHardware() { return ave_hardware; }
	int Getuml() { return ave_uml; }


	// Інший варіант. Працює як мультисеттер 
	void Fill(Student* students, int size)
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
			if(months > 0) cout << "enter marks:\n";
			for (int j = 0; j < months; i++)
			{
				cout << "C++ programming:\n"; CINIGNORE; students[i].c_prog[j] = Entervalue(12);
				cout << "Hardware:\n"; CINIGNORE; students[i].hardware[j] = Entervalue(12);
				cout << "Windows configuration:\n"; CINIGNORE; students[i].uml[j] = Entervalue(12);
			}
		}
	}


	void CountAverage()
	{
		if (months==0)
		{
			ave_prog = 0;
			ave_hardware = 0;
			ave_uml = 0;
		}
		else
		{
			ave_prog = Average(c_prog, months);
			ave_hardware = Average(hardware, months);
			ave_uml = Average(uml, months);
		}
	}

	/* Виведення на екран */

	void Show(int index = 0) // для одного студента
	{
		HEADER;
		CountAverage();
		cout << setw(100) << setfill('_') << " \n";
		cout << "1\t" << setfill(' ')
			<< setw(7) << name << "\t\t"
			<< setw(7) << surname << "\t\t"
			<< setw(7) << faculty << "\t\t"
			<< setw(5) << admission_year << "\t\t"
			<< setw(2) << ave_prog << "\t"
			<< setw(2) << ave_hardware << "\t"
			<< setw(2) << ave_uml << "\n";
	}

	void ShowMarks(int index = 0) // для одного студента
	{
		CountAverage();
		cout << "\nStudent " << name << " " << surname << " has got the following marks:";
		cout << "\n   C++ programming:\t";
		for (int i = 0; i < months; i++)
		{
			cout << right << setw(2) << c_prog[i] << " ";
		}
		cout << "\t Average: " << ave_prog;
		cout << "\n\t  Hardware: \t";
		for (int i = 0; i < months; i++)
		{
			cout << right << setw(2) << hardware[i] << " ";
		}
		cout << "\t Average: " << ave_hardware;
		cout  << "\n\t\tUML: \t";
		for (int i = 0; i < months; i++)
		{
			cout << right << setw(2) <<  uml[i] << " ";
		}
		cout << "\t Average: " << ave_uml;
	}

	void Show(Student* students, int size)//для групи студентів
	{
		HEADER;
		cout << setw(80) << setfill('_') << " \n";
		for (int i = 0; i < size; i++)
		{
			students[i].CountAverage();
			cout << i + 1 << "\t"
				<< left << setfill(' ')
				<< setw(12) << students[i].name << "\t"
				<< setw(12) << students[i].surname << "\t"
				<< setw(12) << students[i].faculty << "\t"
				<< setw(5) << students[i].admission_year << "\t\t"
				<< right
				<< setw(2) << students[i].ave_prog << "\t\t"
				<< setw(2) << students[i].ave_hardware << "\t\t"
				<< setw(2) << students[i].ave_uml << "\n";

		}
	}

	/* створення екземплярів з випадковими параметрами */

	void RandSurnames()
	{
		char root[4][10] = { "Ivan", "Dmytr", "Petr", "Pavl" };
		char ending[4][10] = { "uk", "iv", "enko" };
		strcpy(surname, root[rand() % 4]);
		strcat(surname, ending[rand() % 3]);
	}

	void RandNames()
	{
		char name[7][10] = { "Ivan", "Dmytro", "Petro", "Pavlo", "Mykola", "Volodymyr", "Danylo" };
		strcpy(this->name, name[rand() % 7]);
	}


	/* редактор */
	//для одного студента

	void Edit()
	{
		int index;
		bool oncemore, choice;
		do
		{
			Show();

			if (ToDoOrNotToDo("edit name")) {
				cout << "enter name\n"; /* cin.ignore()*/; cin.getline(name, 30);
			}
			if (ToDoOrNotToDo("edit surname")) {
				cin.ignore(); cout << "enter surname\n"; /* cin.ignore()*/; cin.getline(surname, 30);
			}
			if (ToDoOrNotToDo("edit faculty")) {
				cout << "enter faculty\n"; /* cin.ignore()*/; cin.getline(faculty, 30);
			}
			if (ToDoOrNotToDo("edit admission year")) {
				cout << "enter admission year\n"; cin >> admission_year;
			}
			Show();
			oncemore = ToDoOrNotToDo("edit more");
		} while (oncemore);
	}
	//для групи студентів


	void Edit(Student* students, int size)
	{
		int index;
		bool oncemore, choice;
		do
		{
			cout << "\nenter student # you want to edit\n";
			index = Entervalue(size);
			index--; // оскільки # відображаються від 1
			students[index].Show(index);
			char buff[30];

			cout << "enter name  (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
			if (strcmp(buff, "0")) strcpy(students[index].name, buff);

			cout << "enter surname (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
			if (strcmp(buff, "0")) strcpy(students[index].surname, buff);
			
			cout << "enter faculty (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
			if (strcmp(buff, "0")) strcpy(students[index].surname, buff);
			 
			cout << "enter admission_year (0 - no changes)\n";  CINIGNORE; cin.getline(buff, 30);
			if (strcmp(buff, "0")) strcpy(students[index].surname, buff);
			

			Show(students, size);
			CINIGNORE;
			cout << "\nedit more? 1-yes, 0-no\n";
			cin >> oncemore;
		} while (oncemore);
	}

	// очищення оцінок

	void ResetMarks()
	{ months = 0; 
	delete[] c_prog;
	delete[] hardware;
	delete[] uml;
	}
};


int Menu(bool stdefault, bool stgroup)
{
	int choice;
	if (stdefault)
	{
		cout << "\n+++++++++++++Enter choice+++++++++++++";
		cout << "\n1 - Show";  // Один екземпляр, всі параметри за замовченням
		cout << "\n2 - Edit default student (no marks yet)";
		cout << "\n3 - Enter name and surname only";
		cout << "\n4 - Enter new marks";
		cout << "\n5 - Enter random marks";
		cout << "\n6 - Explore all marks\n";
		cout << "\n7 - Edit marks (only for teachers)\n";
		cout << "\n0 - Exit\n";
	}
	if (stgroup)
	{
		cout << "\n+++++++++++++Enter choice+++++++++++++";
		cout << "\n1 - Show";  // Один екземпляр, всі параметри за замовченням
		cout << "\n2 - Edit student by index";
		cout << "\n3 - Fill the group step-by-step";
		cout << "\n4 - Enter new marks";
		cout << "\n5 - Enter random marks";
		cout << "\n6 - Explore all marks";
		cout << "\n7 - Insert random surnames";
		cout << "\n8 - Insert random names";
		cout << "\n9 - Reset all marks";
		cout << "\n10 - Add student";
		cout << "\n11 - Delete student";
		cout << "\n12 - Edit marks";
		cout << "\n0 - Exit\n";

	}
	cin >> choice;

	return choice;
}

void Add(Student*& students, int& size)
{
	Student* temp = new Student[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = students[i];

	temp[size] = Student();

	//delete[] students; // Видалення попереднього масиву
	students = temp;   // Перенаправлення вказівника на новий масив
	size++;            // Збільшення розміру масиву на 1
}

void Delete (Student*& students, int& size, int index)
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


int main()
{
	setlocale(LC_ALL, "ukr"); // для відображення кирилиці
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	bool stdefault = false; 
	bool stgroup = false;
	int choice;
	srand(time(NULL));

	cout << "\nExploring default student\n";
	if (ToDoOrNotToDo("try test"))
	{
		Student stud_default; stdefault = true; stgroup = false;
		do
		{
			choice = Menu(stdefault, stgroup); // вибір меню
			switch (choice)
			{
				// Один екземпляр, всі параметри за замовченням
			case 1: stud_default.Show();  break;
			case 2: stud_default.Edit(); break;
			case 3: char name[30], surname[30];
				cout << "enter name\n";
				cin >> name;
				cout << "enter surname\n";
				cin >> surname;
				stud_default.SetName(name, surname); break;
			case 4: int prog, uml, hardware;
				cout << "enter prog mark\n";
				cin >> prog;
				cout << "enter hardware mark\n";
				cin >> hardware;
				cout << "enter uml mark\n";
				cin >> uml;
				stud_default.SetMarks(prog, hardware, uml); break;
			case 5: stud_default.SetMarks(rand() % 12 + 1, rand() % 12 + 1, rand() % 12 + 1); break;
			case 6: stud_default.ShowMarks(); break;
			case 7: stud_default.EditMarks(); break;
			case 0: cout << "thank you for exploring"; break;
			defalult: cout << "wrong choice"; break;
			}
		} while (choice);
	}
	

	// робота з групами студентів

	cout << "\nExploring default group\n";
	if (ToDoOrNotToDo("try test"))
	{
		int size = Entervalue(INT_MAX);// кількість студентів у групі

		Student* group = new Student[size];
		for (int i = 0; i < size; i++)
			group[i] = Student(); // Викликаємо конструктор за замовченням для кожного об'єкту

		stdefault = false; stgroup = true;
		do
		{
			int index;
			choice = Menu(stdefault, stgroup); // вибір меню
			switch (choice)
			{
			case 1: group[size].Show(group, size); break;
			case 2: group[size].Edit(group, size); break;
			case 3: group[size].Fill(group, size); break;
			case 4: int prog, uml, hardware;
				for (int i = 0; i < size; i++)
				{
					cout << "Student " << group[i].GetName() << " " << group[i].GetName() << endl;
					cout << "enter prog mark\n";
					cin >> prog;
					cout << "enter uml mark\n";
					cin >> uml;
					cout << "enter hardware mark\n";
					cin >> hardware;
					group[i].SetMarks(prog, hardware, uml);
				}
				break;
			case 5:
				for (int i = 0; i < size; i++)
					group[i].SetMarks(rand() % 12 + 1, rand() % 12 + 1, rand() % 12 + 1); break;
			case 6:
				for (int i = 0; i < size; i++)
					group[i].ShowMarks(); break;

			case 7:
				for (int i = 0; i < size; i++)
					group[i].RandSurnames(); break;
			case 8:
				for (int i = 0; i < size; i++)
					group[i].RandNames(); break;
			case 9: 
				for (int i = 0; i < size; i++)
					group[i].ResetMarks(); break;
			case 10: Add(group, size); break;
			case 11: Delete(group, size, Entervalue(size)); break;
			case 12: cout << "\nEnter Student's ID you wnat to edit\n";
				index = Entervalue(size);
				group[index].EditMarks(index); break;
			case 0: cout << "thank you for exploring"; break;
			default: cout << "wrong choice"; break;
			}
		} while (choice);
	}


	cout << "\nThanks for your patience!";
}

/* ----------------------------- */


float Average(int* nums, int size)
{
	float sum = 0.0;
	for (int i = 0; i < size; i++)
		sum += nums[i];
	return sum / size;
}



bool ToDoOrNotToDo(string text) // захист від випадково невірно введенних символів для змінної bool
{
	char choice[3];
	cout << text << "? 1-yes, 0-no\n";
	while (true)
	{
		CINIGNORE;
		cin.getline(choice, 3);
		if (strcmp(choice, "1") == 0) return true;
		else if (strcmp(choice, "0") == 0) return false;
		else cout << "try once more!1 or 0!\n";
	}
}

int Entervalue(int max) // дурнестійке введення цифр 
//(нецифрові символи не призводять до збою програми, а змушують користувача ввести заново)
{
	char buff[10]; int value;
	cout << "\nEnter value\n";
	do
	{
	cin >> buff;
	value = atoi(buff);
	bool job = true;
	for (int i = 0; i < strlen(buff); i++)
	{
		if (!isdigit(buff[i])) {
			cout << "\nPlease enter digits, not letters!\n";
			job = false; break;
		}
	}
	if (job)
	{
		if (value > max) cout << "Value shoud be less than size\n";
		if (value < 1) cout << "Value shoud be more than 0\n";
	}
	} while (value > max || value < 1);
		return value;
}

bool EnterPass()
{
	char password[100];
	cout << "\nEnter password\n";
	cin >> password;
	if (strcmp(password, teacher) == 0) return true;
	else return false;
}

void Color(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

string Message(int color, string message)
{
	Color(color);
	cout << message;
	Color(7);
	return message;
}
