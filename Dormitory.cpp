                                     #pragma once
#include <cstring>
#include "globals.h"
#include "Student.h"
#include "Dormitory.h"
#define ROW cout << "\t" \
<< right << setfill('0') << setw(log10(numberofrooms * 4) + 1) \
<< room[i].settler[j].GetID() << "\t"\
<< left << setfill(' ') \
<< setw(12) << room[i].settler[j].GetName() << "\t" \
<< setw(12) << room[i].settler[j].GetSurname() << endl; 


// Constructor to initialize the number of numberofrooms and allocate memory

Dormitory::Dormitory() : numberofrooms(0)
{
	room = new Room[numberofrooms]; // Allocate memory for numberofrooms
	strcpy(address, "Unknown str, 0"); // Copy the address to the class member
	for (int i = 0; i < numberofrooms; i++)
		for (int j = 0; j < places; j++)
			room[i].settler[j];
}


Dormitory::Dormitory(int numnumberofrooms, const char* dormAddress) : numberofrooms(numnumberofrooms)
{
	room = new Room[numberofrooms]; // Allocate memory for numberofrooms
	strcpy(address, dormAddress); // Copy the address to the class member
	for (int i = 0; i < numberofrooms; i++)
		for (int j = 0; j < places; j++)
			room[i].settler[j];
}


Dormitory::Dormitory(const Dormitory& obj)
{
	this->numberofrooms = obj.numberofrooms;
	strcpy(this->address, obj.address);
	this->room = obj.room;
}


Dormitory::~Dormitory()     // Деструктор
{
	delete[] room; // Deallocate the dynamically allocated memory
}

int Dormitory::Getnumberofrooms() { return numberofrooms; }



void Dormitory::Show()
{
	Message(11, "Dormitory info");
	cout << "\nAdress: " << address;
	cout << "\nrooms built:  " << numberofrooms << endl;
	cout << "\ncapacity:  " << numberofrooms*places<< endl;
	cout << "\nstudents settled: " << Settled() << endl;
	cout << "\nplaces aailable: " << numberofrooms * places- Settled() << endl;
}

void Dormitory::ShowRoom()
{
	if (numberofrooms == 0) cout << "No rooms are built yet\n";
	else
	{
		cout << "#\tSt. ID\tName\tSurname\n";
		for (int i = 0; i < numberofrooms; i++)
		{
			cout << "room #" << room[i].roomnumber << "\n";
			for (int j = 0; j < places; j++)
				if (room[i].settler[j].GetID() > 0) ROW
				else cout << "\t" << "no settler yet\n";

		}
	}
}


void Dormitory::Build(int num)
{
	Room *temp = new Room[numberofrooms + num];
	for (int i = 0; i < numberofrooms; i++)
		temp[i] = room[i];
	for (int i = numberofrooms; i < numberofrooms + num; i++)
	{
		temp[i].roomnumber = i + 1;
		for (int j = 0; j < places; j++)
		{
			temp[i].settler[j].SetID(0); 
			IDCounter--;
		}
	}
	
	delete[] room;
	room = temp;
	numberofrooms += num;
}



void Dormitory::SettleAll(Student *students, int size)
{
	int id = 0;
	for (int i = 0; i < numberofrooms && id < size; i++)
	{
		room[i].roomnumber = i + 1;
		for (int j = 0; j < places; j++)
		{
			if (room[i].settler[j].GetID()) continue;
			while (students[id].Getroom() && id<size) id++;
			if(id<size)
			{
				students[id].SetRoom(i + 1);
				room[i].settler[j] = students[id];
				IDCounter--;
			}
		}
	}
}

void Dormitory::SettleByGender(Student* students, int size)
{
	int index = 0; int gendergap;
	for (int i = 0; i < numberofrooms && index < size; i++)
	{
		gendergap = 0;
		room[i].roomnumber = i + 1;
		for (int j = 0; j < places; j++)
		{
			if (room[i].settler[j].GetID()) continue;
			while (students[index].Getroom() && index < size) { index++; gendergap++; }
			while (j>0 && students[index].GetGender() != room[i].settler[0].GetGender() && index < size)
				// якщо інший претендент не співпав за статтю з першим поседенцем
			{ gendergap++; index++;	}
			if (index < size)
			{
				students[index].SetRoom(i + 1);
				room[i].settler[j] = students[index];
				IDCounter--;
			}
		}
		index -= gendergap;
	}
}

void Dormitory::Evict(int id)
{
	
	for (int i = 0; i < numberofrooms; i++)
		for (int j = 0; j < places; j++)
		{
			if (room[i].settler[j].GetID() == id)
			{
				room[i].settler[j].~Student();
				room[i].settler[j].SetID(0);
			}
			
		}

}

void Dormitory::EvictAll()
{
	for (int i = 0; i < numberofrooms; i++)
		for (int j = 0; j < places; j++)
		{
			room[i].settler[j].~Student();
			room[i].settler[j].SetID(0);
		}
}

int Dormitory::Settled()
{
	int settled = 0;
	for (int i = 0; i < numberofrooms; i++)
		for (int j = 0; j < places; j++)
		{
			if (room[i].settler[j].GetID() > 0)
				settled++;
		}
	return settled;
}


