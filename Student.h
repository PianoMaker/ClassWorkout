// Student.h
#ifndef STUDENT_H
#define STUDENT_H
class Student
{
private:
	int lessons; // місяці навання
	char name[30];
	char surname[30];
	char gender;
	char faculty[30];
	int admission_year;
	int* c_prog = new int[lessons]; // оцінки помісячно
	int* hardware = new int[lessons];
	int* uml = new int[lessons];
	float ave_prog;
	float ave_hardware;
	float ave_uml;
	float ave_global;

public:
	
	Student(int lessons = 0); // конструктор за замовченням
	// конструктор з усіма параметрами
	Student(int lessons, char* name, char* surname, char* faculty, int admission_year, int* c_prog, int* hardware, int* uml);
	/*
	Student(const Student& obj);// копіювання
	~Student();// деструктор;
	*/

	// іменний сеттер 
	void SetName(char* name, char* surname);
	void SetGender();


	// геттери
	char* GetName();
	char* GetSurname();
	char* GetFaculty();
	int GetAdmission_year();
	int GetProgramming();
	int GetHardware();
	int Getuml();
	char GetGender();

	/* редактор */

	void Edit(int index = 1);	//для одного студента

	// виставлення нових оцінок по кожному з предметів

	void SetMarks(int c_prog, int hardware, int uml);
	void EditMarks(int index = 0);



	// Інший варіант. Працює як мультисеттер 
	void Fill(Student* students, int size);


	/* Виведення на екран */

	void Show(int index = 0);
	void ShowMarks(int index = 0);
	void Show(Student* students, int size);

	/* створення екземплярів з випадковими параметрами */

	void RandSurnames();
	void RandNames();
	void RandFaculty();

	// Статистика 
	void CountAverage();
	void Stats(Student*& students, int size);

	// Сортування
	void Sort(Student*& students, int size);
	void SwapStudents(Student* students, int index1, int index2);

	// очищення оцінок
	void ResetMarks();

	// додавання і вилучення
	void Add(Student*& students, int& size);
	void Delete(Student*& students, int& size, int index);


};

#endif