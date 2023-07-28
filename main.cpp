#include "Student.h"
#include "globals.h"


int Menu(int type)
{
	int choice;
	if (type == 1)
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
	else if (type == 2)
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
		cout << "\n9 - Insert random faculties";
		cout << "\n10 - Reset all marks";
		cout << "\n11 - Add student";
		cout << "\n12 - Delete student";
		cout << "\n13 - Edit marks";
		cout << "\n14 - Sort by average marks";
		cout << "\n15 - Statistics";
		cout << "\n0 - Exit\n";

	}
	else Message(12, "Error in choosing type");
	cin >> choice;

	return choice;
}




int main()
{
	setlocale(LC_ALL, "ukr"); // для відображення кирилиці
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int type = Entervalue("Choose mode. 1 - one student. 2 - group of students.", 2);
	int choice;
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
			case 0: cout << "thank you for exploring"; break;
			defalult: cout << "wrong choice"; break;
			}
		} while (choice);
	}
	

	// робота з групами студентів


	if (type == 2)
	{
		Message(10, "\nExploring default group\n");
		int size = Entervalue("enter group size", INT_MAX);// кількість студентів у групі

		Student* group = new Student[size];
		for (int i = 0; i < size; i++)
			group[i] = Student(); // Викликаємо конструктор за замовченням для кожного об'єкту

		do
		{
			int index;
			choice = Menu(2); // вибір меню
			switch (choice)
			{
			case 1: group[size].Show(group, size); break;
			case 2: index = Entervalue("Enter student's ID you want to edit", size);
				group[index - 1].Edit(index - 1); break;
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
					group[i].SetMarks(rand() % bestmark + 1, rand() % bestmark + 1, rand() % bestmark + 1); break;
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
					group[i].RandFaculty(); break;
			case 10: 
				for (int i = 0; i < size; i++)
					group[i].ResetMarks(); break;
			case 11: group[0].Add(group, size); break;
			case 12: group[0].Delete(group, size, Entervalue("Enter Student's ID you wnat to delete", size)); break;
			case 13: 
				index = Entervalue("Enter Student's ID you wnat to edit", size);
				group[index].EditMarks(index - 1); break;
			case 14: group[0].Sort(group, size); group[0].Show(group, size); break;//проблеми з дестркутором
			case 15: group[0].Stats(group, size); break;
			case 0: cout << "thank you for exploring"; break;
			default: cout << "wrong choice"; break;
			}
		} while (choice);
	}


	cout << "\nThanks for your patience!";
}

/* ----------------------------- */



