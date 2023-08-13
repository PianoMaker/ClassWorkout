#include "Student.h"
#include "globals.h"
#include "Dormitory.h"
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
		cout << "\n4 - Add...";
		cout << "\n5 - Delete...";
		cout << "\n6 - Explore all marks";
		cout << "\n7 - Sort...";
		cout << "\n8 - Search...";
		cout << "\n9 - Statistics";
		cout << "\n10 - Settle...";
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
	else if (type == 5) // dormitories
	{
		cout << "\n1 - Show Settled students info";
		cout << "\n2 - Show dormitories info";
		cout << "\n3 - Build new rooms";
		cout << "\n4 - Settle all";
		cout << "\n5 - Settle manually";
		cout << "\n6 - Settle all using gender segregation";
		cout << "\n7 - Show info for each room";
		cout << "\n8 - Evict all students";
		cout << "\n9 - Set an address";
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
		Dormitory dormhouse; 

		do
		{
			int index, min, max, amount, id, counter=0;
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
						cout << "Student " << group[i].GetName() << " " << group[i].GetSurname() << endl;
						prog = Entervalue("enter prog mark\n", bestmark);
						uml = Entervalue("enter uml mark\n", bestmark);
						hardware = Entervalue("enter hardware mark\n", bestmark);
						group[i].SetMarks(prog, hardware, uml);
					}
					break;
				case 4:
					for (int i = 0; i < size; i++)
						group[i].ResetMarks(); break;

				case 5:
					index = Entervalue("Enter Student's # you want to edit", size);
					group[index].EditMarks(index - 1); break;
					ZEROCHOICE
				}break;
			// RANDOMS
			case 3: editchoice = Menu(4); 
				switch (editchoice) {
				case 1:
					for (int i = 0; i < size; i++)
						if(!strcmp(group[i].GetSurname(),"Unknown"))group[i].RandSurnames(); 
					break;
				case 2:
					for (int i = 0; i < size; i++)
						if (!strcmp(group[i].GetName(), "Unknown"))group[i].RandNames(); 
					break;
				case 3:
					for (int i = 0; i < size; i++)
						if (!strcmp(group[i].GetFaculty(), "Unknown"))group[i].RandFaculty(); 
					break;
				case 4:
					for (int i = 0; i < size; i++)
						group[i].SetMarks(rand() % bestmark + 1, rand() % bestmark + 1, rand() % bestmark + 1); 
					break;
				case 5:
					for (int i = 0; i < size; i++)
					{
						if (!strcmp(group[i].GetSurname(), "Unknown"))group[i].RandSurnames();
						if (!strcmp(group[i].GetName(), "Unknown"))group[i].RandNames();
						if (!strcmp(group[i].GetFaculty(), "Unknown"))group[i].RandFaculty();
						group[i].RandMarks();
					}
					break;
					ZEROCHOICE
				}break;
			//ADD
			case 4: 
				amount = Entervalue("How many students to add?", INT16_MAX, 0);
				for (int i = 0; i < amount; i++)
					group[0].Add(group, size);
				break;
			//DELETE
			case 5: editchoice = Entervalue("Choose mode. \n1- Delete by #\n2 - Delete by ID\n3 - Delete unsuccessful students \n4 - Delete all students\n0 - exit",3, 0);
				switch (editchoice)
				{
				case 1: index = Entervalue("Enter Student's # you wnat to delete", size); index--;
					dormhouse.Evict(group[index].GetID()); group[0].Delete(group, size, index); break;
				case 2: id = Entervalue("Enter Student's ID you wnat to delete", size);
					dormhouse.Evict(id);
					for (int i = 0; i < size; i++)
						if (group[i].GetID() == id) 
						{ 
							group[i].Delete(group, size, i); 
							break; 
						}
					break;
				case 3: amount = Entervalue("Enter the worse average mark allowable", 12, 1);
					for (int i = 0; i < size; i++)
					{
						if(group[i].GetAveMarks()<amount)
						{
							counter++;
							group[i].Delete(group, size, i);
							dormhouse.Evict(i);						
						}
					}
					cout << counter << " students have been deleted\n";
					break;
				case 4:
					for (int i = 0; i < size; i++)
					{
						group[i].Delete(group, size, i); 
						dormhouse.EvictAll();
					}
					ZEROCHOICE
				}break;
			
			//MARKS
			case 6:
				for (int i = 0; i < size; i++)
					group[i].ShowMarks(); break;
			//SORT
			case 7: editchoice = Entervalue("Choose mode. \n1 - Sort by average marks, \n2 - Sort by ID, \n3 - Sort by surnames,\4 - Sort by names", 4, 0);
				switch (editchoice) {
				case 1:
					group[size].Sort(group, size); break;
				case 2:
					group[size].SortByID(group, size); break;
				case 3:  group[size].SortBySurname(group, size); break; 
				case 4:  group[size].SortByName(group, size); break; 
					ZEROCHOICE
				}
				break;
			//SEARCH
			case 8: editchoice = Entervalue("Choose mode. \n1 - Search by name, \n2 - Search by marks, \n3 - Search by ID\n4 - Search by room", 4, 0);
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
				case 4:
					int room;
					room = Entervalue("\nenter room", INT16_MAX);
					group[0].SearchByRoom(group, size, room); break;
					ZEROCHOICE
				}
				break;

			//STATS
			case 9: group[0].Stats(group, size); break;

			//DORMITORY
			case 10: 
				do
				{
					editchoice = Menu(5);
					switch (editchoice) {
					case 1: group[size].ShowSettleInfo(group, size); break;
					case 2: dormhouse.Show(); break;
					case 3: amount = Entervalue("How many rooms to build?", INT16_MAX, 0);
						dormhouse.Build(amount); break;
					
						//cout << "\n3 - Build new rooms";
					case 4: dormhouse.SettleAll(group, size); break;
						//cout << "\n4 - Settle one-by-one";
						//cout << "\n5 - Settle manually";
					case 5: index = Entervalue("Enter student's ID", size); 
						 dormhouse.SettleManually(group, size, index); break;
						//cout << "\n6 - Settle using gender segregation
					case 6: dormhouse.SettleByGender(group, size); break;
						// cout << "\n7 - Show info for each room"
					case 7: dormhouse.ShowRoom(); break;
						//cout << "\n8 - Evict all students";
					case 8: dormhouse.EvictAll(); 
						for (int i = 0; i < size; i++)
							group[i].SetRoom(0);
						break;
					case 9: dormhouse.SetAdress();
						break;
						//cout << "\n0 - Exit\n";
						ZEROCHOICE
					}
				} while (editchoice != 0);
			}
		} while (choice);
	}


	Message(11, "Thanks for your patience!");
}

/* ----------------------------- */



