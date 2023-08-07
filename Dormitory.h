#pragma once
#pragma warning (disable:4996)
#include <cstring>
#include "globals.h"
#include "Student.h"

struct Room
{
	int roomnumber;
	Student settler[beds];
};

class Dormitory 
{
private:
    char address[50];
    int numberofrooms;
	Room* room;

public:
	Dormitory();
	Dormitory(int numnumberofrooms, const char* dormAddress);
	Dormitory(const Dormitory& obj);
	~Dormitory();
	void Show();
	void ShowRoom();
	void Build(int num);
	void SettleAll(Student* students, int size);
	void SettleByGender(Student* students, int size);
	//void SetRoomNumber(int num);
	void Evict(int id);
	void EvictAll();



	int Getnumberofrooms();
 
};

