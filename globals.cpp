#include "globals.h"



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

int Entervalue(string text, int max, int min) // дурнестійке введення цифр 
//(нецифрові символи не призводять до збою програми, а змушують користувача ввести заново)
//мінімум для наших задач зазвичай буде 1
{
	char buff[10]; int value;
	cout << text << endl;
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
			if (value > max) cout << "Value shoud not exceed  " << max << endl;
			if (value < min) cout << "Value shoud not be less than " << min << endl;
		}
	} while (value > max || value < min);
	return value;
}


float Entervalue(string text, float max, float min) // дурнестійке введення цифр 
//(нецифрові символи не призводять до збою програми, а змушують користувача ввести заново)
//мінімум для наших задач зазвичай буде 1
{
	char buff[10]; int value;
	cout << text << endl;
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
			if (value > max) cout << "Value shoud not exceed  " << max << endl;
			if (value < min) cout << "Value shoud not be less than " << min << endl;
		}
	} while (value > max || value < min);
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