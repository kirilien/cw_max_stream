#pragma once
#include <assert.h>
#include "pch.h"
#include "list_funcs.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "list_funcs.h"
#include "edge.h"
#include "Ford_Falkerson.h"
#include <fstream>
using namespace std;
void test_ordinary() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;

	ifstream in("input2.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);

	}
	ford_falkerson finding(rec_list);
	assert(15 == finding.maxflow);
	cout << "test_ordinary - succeed\n";

}

void test_stress() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;

	ifstream in("input1.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);

	}
	ford_falkerson finding(rec_list);
	assert(2000 == finding.maxflow);
	cout << "test_stress - succeed\n";
}

void test_double_dir() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;

	ifstream in("input_dd.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);

	}
	ford_falkerson finding(rec_list);
	assert(6 == finding.maxflow);
	cout << "test_double_dir - succeed\n";
}
void test_all() {
	test_ordinary();

	test_stress();

	test_double_dir();
	cout << "All tests are succeed\n\n\n";
}