#include <conio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

int m;
int table[100];
int n;
int a[100];
bool overflow;
int collisions;

int HashF(int num)
{
	return num % m;
}

// Создание хеш-таблицы методом линейных проб.
void CreateTable1()
{
	int i;
	for (i = 0; i < m; i++)
		table[i] = 0;
	collisions = 0;
	int h, h0, g;
	for (i = 0; i < n; i++) {
		h = HashF(a[i]);
		h0 = h;
		g = 1;
		while (1) {
			if (table[h] == a[i])
				break;
			if (table[h] == 0) {
				table[h] = a[i];
				break;
			}
			if (g >= m) {
				overflow = true;
				return;
			}
			collisions++;
			h = h0 + g;
			if (h >= m)
				h -= m;
			g++;
		}
	}
	overflow = false;
}

// Создание хеш-таблицы методом квадратичных проб.
void CreateTable2()
{
	int i;
	for (i = 0; i < m; i++)
		table[i] = 0;
	collisions = 0;
	int h, d;
	for (i = 0; i < n; i++) {
		h = HashF(a[i]);
		d = 1;
		while (1) {
			if (table[h] == a[i])
				break;
			if (table[h] == 0) {
				table[h] = a[i];
				break;
			}
			if (d >= m) {
				overflow = true;
				return;
			}
			collisions++;
			h += d;
			if (h >= m)
				h -= m;
			d += 2;
		}
	}
	overflow = false;
}

void ShowTable()
{
	if (m == 11) {
		cout << "------------------------------------------------------------------------\n";
		cout << "| Icheika       |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | \n";
		cout << "------------------------------------------------------------------------\n";
		cout << "| Chilso        | ";
		for (int i = 0; i < m; i++)
			if (table[i] != 0)
				printf("%2d | ", table[i]);
			else
				cout << "   | ";
		cout << "\n------------------------------------------------------------------------\n";
	}
	if (!overflow)
		cout << "Perepolnenie tablici ne bilo\n";
	else
		cout << "Perepolnenie tablici\n";
	cout << "Kolichestvo kollizii: ";
	cout << collisions << endl;
}

// Поиск число в хеш-таблице, построенной методом линейных проб.
bool Search1(int num)
{
	int h, h0, g;
	h = HashF(num);
	h0 = h;
	g = 1;
	while (1) {
		if (table[h] == num)
			return true;
		if (g >= m)
			return false;
		h = h0 + g;
		if (h >= m)
			h -= m;
		g++;
	}
}

// Поиск число в хеш-таблице, построенной методом квадратичных проб.
bool Search2(int num)
{
	int h, d;
	h = HashF(num);
	d = 1;
	while (1) {
		if (table[h] == num)
			return true;
		if (d >= m)
			return false;
		h += d;
		if (h >= m)
			h -= m;
		d += 2;
	}
}

int main(int argc, char* argv[])
{
	system("mode con cols=100 lines=30");
	system("color 0");
	cout << "Vvedite razmer hesh-tablici: ";
	cin >> m;
	cout << "Vvedite kolichestvo ishodnih chisel: ";
	cin >> n;
	int num;
	int i;
	srand(time(0));
	for (i = 0; i < n; i++)
		a[i] = rand() % n + 1;
	cout << "Metod lineinih prob:\n";
	CreateTable1();
	ShowTable();
	cout << "Vvedite chislo dlia poiska: ";
	cin >> num;
	if (Search1(num))
		cout << "Chislo naideno!\n";
	else
		cout << "Chislo ne naideno!\n";
	cout << "\nMetod kvadratichnih prob:\n";
	CreateTable2();
	ShowTable();
	cout << "Vvedite chislo dlia search: ";
	cin >> num;
	if (Search2(num))
		cout << "Chislo naideno!\n";
	else
		cout << "Chislo ne naideno!\n";
	_getch();
	return 0;
}