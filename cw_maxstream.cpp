// cw_maxstream.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include "list_funcs.h"
#include "Ford_Falkerson.h"
#include "unit.h"

using namespace std;

template <class T>
void alg_ini(List<T> *ini_list);
int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;
	test_all();

	ifstream in("input.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);

	}
	alg_ini(rec_list);
	//int list_len = rec_list->get_size();
	//for (int i=0; i< list_len; i++)

}
template <class T>
void alg_ini(List<T> *ini_list) {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	ford_falkerson finding(ini_list);
	cout << "\n" << finding.maxflow;
	_getch();
}
