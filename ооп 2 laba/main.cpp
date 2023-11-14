#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "function.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>
using namespace std;





void next2(const HuberD* HD)
{
	ofstream selection1;
	ofstream selection2;
	ofstream params;
	vector<pair<double, double>> table;
	char option;
	int n;
	double x = 0;

	cout << "1. Вывести параметры распределения на экран" << endl;

	cout << "v = " << HD->get_v() << endl;
	cout << "K = " << HD->get_k() << endl;
	cout << "Scale = " << HD->get_scale() << endl;
	cout << "Shift = " << HD->get_shift() << endl;
	cout << "M[X] = " << HD->Mksi_huber() << endl;
	cout << "D[X] = " << HD->Dksi_huber() << endl;
	cout << "As[X] = " << HD->asymmetry_huber() << endl;
	cout << "Kurt[X] = " << HD->kurtosis_huber() << endl;
	cout << "P = " << HD->P() << endl;
	cout << "Huber(0) = " << HD->Huber(0) << endl;

	cout << "2. Вычислить значение плотности распределения в произвольной точке" << endl;

	cout << "Введите x: ";
	cin >> x;
	cout << endl << "Huber(" << x << ") = " << HD->Huber(x) << endl;

	cout << "3. Получить выборку для анализа" << endl;

	selection1.open("selection1.txt");
	selection2.open("selection2.txt");
	cout << "Введите размерность выборки n: ";
	cin >> n;
	table = HD->generate_pair(n);
	for (const pair<double, double>& pr : table)
	{
		selection1 << pr.first << endl;
		selection2 << pr.second << endl;
	}

	selection1.close();
	selection2.close();

	cout << endl << "Значения выборки записаны в файлы selection1.txt и selection2.txt" << endl;

	cout << "4. Вывести параметры распределения в файл" << endl << endl;

	HD->save_file(params);
}

void next()
{
	char option;
	double v, scale, shift;
	HuberD* HD;
	ifstream file;

	cout << "Выберите опцию: " << endl;
	cout << "1. Стандартное распределение Хьюбера" << endl;
	cout << "2. Ввести произвольные параметры с клавиатуры" << endl;
	cout << "3. Считать параметры из файла" << endl << endl;

	cin >> option;
	cout << endl;

	switch (option)
	{
	case '1':
		cout << "Введите параметр v: ";
		cin >> v;
		cout << endl;
		try
		{
			HD = new HuberD(v);
		}
		catch (exception e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
			exit(1);
		}

		next2(HD);
		break;

	case '2':
		cout << "Введите v lambda mu: ";
		cin >> v >> scale >> shift;
		cout << endl;
		try
		{
			HD = new HuberD(v, scale, shift);
		}
		catch (exception e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
			exit(1);
		}

		next2(HD);
		break;

	case '3':
		try
		{
			HD = new HuberD(file);
		}
		catch (exception e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
			exit(1);
		}

		next2(HD);
		break;

	default:
		cerr << endl << "Ошибка: Некорректный параметр" << endl;
		exit(1);
	}
}


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	int n = 1000;
	int result = Catch::Session().run(argc, argv);
	return result;

	next();

}

