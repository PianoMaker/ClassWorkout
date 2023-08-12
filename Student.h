// Student.h
#ifndef STUDENT_H
#define STUDENT_H

extern int IDCounter;

class Student
{
private:
	int ID; // ідентифікатор
	int lessons; // кількість уроків, за які виставляються оцінки
	char name[30];
	char surname[30];
	char gender;
	char faculty[30];
	int admission_year;
	int* c_prog = new int(lessons); // оцінки за кожен урок
	int* hardware = new int(lessons);
	int* uml = new int(lessons);
	/* ALARM!!! Дає глюк при сортуванні!!! 
	int* c_prog; 
	int* hardware;
	int* uml;
	*/
	float ave_prog; // середні оцінки
	float ave_hardware;
	float ave_uml;
	float ave_global;
	int room;// кімната в гуртожитку "Dormitory"

public:
	// конструктор за замовченням
	Student(); 

	// конструктор з усіма параметрами
	Student(int lessons, char* name, char* surname, char* faculty, int admission_year, int* c_prog, int* hardware, int* uml);
/*
  //ALARM!!! При включеному конструкторі-копіювання + деструктор збивається алгоритм сортування!!!.
  */
	Student(const Student& obj);// копіювання  
	~Student();// деструктор;                         
	/*
	*/ 


	// геттери
	char* GetName();
	char* GetSurname();
	char* GetFaculty();
	int GetAdmission_year();
	float GetProgramming();
	float GetHardware();
	float GetAveMarks();
	float Getuml();
	int Getroom();
	int GetID();
	char GetGender();

	// сеттери 
	void SetName(char* name, char* surname);
	void SetGender();
	void SetID(int id);
	void SetRoom(int room);
	void SetMarks(int c_prog, int hardware, int uml);
	void Fill(Student* students, int size);	// Інший варіант. Працює як мультисеттер 
	
	/* редактори */

	void Edit(int index = 1);	//імена і ф-т
	void EditMarks(int index = 0); 	// для нових оцінок по кожному з предметів

	/* ID - індекс*/
	int IDtoIndex(Student* students, int size, int id);//для операцій за ID


	/* Виведення на екран */

	void Show(int index = 0);// для моделі в один екземпляр
	void Show(const Student* students, int size); // показати весь список 
	void Show(const Student* students, int size, int ID_min, int ID_max); // показати діапазон в заданих межах
	void ShowMarks(int index = 0); // детально відображає всі оцінки
	void ShowSettleInfo(const Student* students, int size); // показує розселення в гуртожитку

	/* створення екземплярів з випадковими параметрами */

	void RandSurnames();
	void RandNames();
	void RandFaculty();

	// Статистика 
	void CountAverage();
	void Stats(Student*& students, int size);

	// Сортування
	void Sort(Student*& students, int size);
	void SortByID(Student*& students, int size);
	void SwapStudents(Student* students, int index1, int index2);
	void SortBySurname(Student*& students, int size);
	void SortByName(Student*& students, int size);

	// очищення оцінок
	void ResetMarks();

	// пошук
	void SearchByName(Student* students, int size, char* name);
	void SearchByMarks(Student* students, int size, float mark);
	void SearchByID(Student* students, int size, int ID);
	void SearchByRoom(Student* students, int size, int room);

	// додавання і вилучення
	void Add(Student*& students, int& size);
	void Delete(Student*& students, int& size, int index);


};

#endif