// globals.h
#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#define CINIGNORE if (cin.rdbuf()->in_avail() > 0) { cin.clear(); cin.ignore(INT16_MAX, '\n'); }
using namespace std;

const char teacher[8] = "teacher"; // використовується як пароль.
const int bestmark = 12; // максимальна оцінка судентів
const int maxlist = 20; // максимальна кількість елементів у списку за замовченням
const int places= 4; // кількість місць у кімнаті гуртожитку

float Average(int* nums, int size);
int Entervalue(string text, int max, int min = 1);
float Entervalue(string text, float max, float min = 1.0);
bool EnterPass();
void Color(int color);
string Message(int color, string message);
bool ToDoOrNotToDo(string text);