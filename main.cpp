#include "Student.h"
#include "globals.h"
#define ZEROCHOICE case 0: break;\
default: cout << "wrong choice"; break;


int Menu(int type)
{
	int choice;
	if (type == 1)
	{
		Message(14, "\n+++++++++++++Enter choice+++++++++++++");
		cout << "\n1 - Show";  // Один екземпляр, всі параметри за замовченням
		cout << "\n2 - Edit default student (no marks yet)";
		cout << "\n3 - Enter name and surname only";
		cout << "\n4 - Enter new marks";
		cout << "\n5 - Enter random marks";
		cout << "\n6 - Explore all marks\n";
		cout << "\n7 - Edit marks (only for teachers)\n";
		cout << "\n0 - Exit\n";
	}
	else if (type == 2) 
	{
		Message(14, "\n+++++++++++++Enter choice+++++++++++++");
		cout << "\n1 - Show...";  // Один екземпляр, всі параметри за замовченням
		cout << "\n2 - Edit...";
		cout << "\n3 - Random fill...";
		cout << "\n4 - Add student";
		cout << "\n5 - Delete student";
		cout << "\n6 - Explore all marks";
		cout << "\n7 - Sort...";
		cout << "\n8 - Search...";
		cout << "\n9 - Statistics";
		cout << "\n0 - Exit\n";
	}
	else if (type == 3) // manual edit
	{
		Message(14,"\n++++++++++++ + Enter choice++++++++++++ + ");
		cout << "\n1 - Edit student by index";
		cout << "\n2 - Fill the group step-by-step";
		cout << "\n3 - Enter new marks";
		cout << "\n4 - Reset all marks";
		cout << "\n5 - Edit marks (password required)";
		cout << "\n0 - Exit\n";
	}
	else if (type == 4) // random fill
	{
		cout << "\n1 - Insert random surnames";
		cout << "\n2 - Insert random names";
		cout << "\n3 - Insert random faculties";
		cout << "\n4 - Enter random marks";
		cout << "\n5 - All fields random";
		cout << "\n0 - Exit\n";
	}
	else Message(12, "Error in choosing type");
	cin >> choice;

	return choice;
}

int IDCounter = 0;


int main()
{
	setlocale(LC_ALL, "ukr"); // для відображення кирилиці
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int type = Entervalue("Choose mode. 1 - one student. 2 - group of students.", 2);
	int choice, editchoice;
	srand(time(NULL));
	

	if (type == 1)
	{
		Message(10, "\nExploring default student\n");
		Student stud_default; 
		do
		{
			choice = Menu(1); // вибір меню
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
			case 5: stud_default.SetMarks(rand() % bestmark + 1, rand() % bestmark + 1, rand() % bestmark + 1); break;
			case 6: stud_default.ShowMarks(); break;
			case 7: stud_default.EditMarks(); break;
				ZEROCHOICE
			}
		} while (choice);
	}
	

	// робота з групами студентів


	if (type == 2)
	{
		Message(10, "\nExploring default group\n");
		int size = Entervalue("enter group size", INT_MAX);// кількість студентів у групі

		Student* group = new Student[size];

		do
		{
			int index, min, max;
			choice = Menu(2); // вибір меню
			switch (choice)
			{
			//SHOW
			case 1: if (size < maxlist) group[size].Show(group, size); // SHOW
				  else {
				editchoice = Entervalue("Choose mode. 1 - Show all, 2 - Show range", 2);//якщо списки завеликі
				if (editchoice == 1)
					group[size].Show(group, size);
				else {
					min = Entervalue("Show from:", size);
					max = Entervalue("up to:", size, min);
					group[size].Show(group, size, --min, --max);
				}
			}
				  break;
			// EDIT
			case 2: editchoice = Menu(3); 
				switch (editchoice) {
				case 1: index = Entervalue("Enter student's ID you want to edit", size);
					group[index - 1].Edit(index - 1); break;
				case 2: group[size].Fill(group, size); break;
				case 3: int prog, uml, hardware;
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
				case 4:
					for (int i = 0; i < size; i++)
						group[i].ResetMarks(); break;

				case 5:
					index = Entervalue("Enter Student's ID you want to edit", size);
					group[index].EditMarks(index - 1); break;
					ZEROCHOICE
				}break;
			// RANDOMS
			case 3: editchoice = Menu(4); 
				switch (editchoice) {
				case 1:
					for (int i = 0; i < size; i++)
						group[i].RandSurnames(); break;
				case 2:
					for (int i = 0; i < size; i++)
						group[i].RandNames(); break;
				case 3:
					for (int i = 0; i < size; i++)
						group[i].RandFaculty(); break;
				case 4:
					for (int i = 0; i < size; i++)
						group[i].SetMarks(rand() % bestmark + 1, rand() % bestmark + 1, rand() % bestmark + 1); break;
				case 5:
					for (int i = 0; i < size; i++)
					{
						group[i].RandSurnames(); 
						group[i].RandNames(); 
						group[i].RandFaculty(); 
						group[i].SetMarks(rand() % bestmark + 1, rand() % bestmark + 1, rand() % bestmark + 1); 
					}
					break;
					ZEROCHOICE
				}break;
			//ADD
			case 4: group[0].Add(group, size); break;
			//DELETE
			case 5: group[0].Delete(group, size, Entervalue("Enter Student's ID you wnat to delete", size)); break;
			//MARKS
			case 6:
				for (int i = 0; i < size; i++)
					group[i].ShowMarks(); break;
			//SORT
			case 7: editchoice = Entervalue("Choose mode. \n1 - Sort by average marks, \n2 - Sort by ID, \n3 - Sort by surnames", 3);
				switch (editchoice) {
				case 1:
					group[size].Sort(group, size); break;
				case 2:
					group[size].SortByID(group, size); break;
				case 3:  group[size].SortBySurname(group, size); break; //проблеми з дестркутором
					ZEROCHOICE
				}
				break;
			//SEARCH
			case 8: editchoice = Entervalue("Choose mode. \n1 - Search by name, \n2 - Search by marks, \n3 - Search by ID", 3);
				switch (editchoice) {
				case 1:
					char name[30];
					cout << "\nenter name or surname"; cin >> name;
					group[0].SearchByName(group, size, name); break;
				case 2:
					float mark;
					mark = Entervalue("\nenter requested average mark", 12);
					group[0].SearchByMarks(group, size, mark); break;
				case 3:
					int ID;
					ID = Entervalue("\nenter ID", INT16_MAX);
					group[0].SearchByID(group, size, ID); break;
					ZEROCHOICE
				}
				break;

			//STATS
			case 9: group[0].Stats(group, size); break;
				ZEROCHOICE
			}
		} while (choice);
	}


	Message(11, "Thanks for your patience!");
}

/* ----------------------------- */



