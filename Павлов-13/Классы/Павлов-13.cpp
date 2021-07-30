#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "..\\..\\myfunctions.h"
#include "..\\..\\myclasses.h"
using namespace std;
struct point2 { double x; double y; };
struct stCircle { point2 center; double radius; };
void crcnd(stCircle *pc, double x0, double x1, double y0, double y1, double r0, double r1);
void crcout(stCircle crc);

class AB {
	int a, b;
public:
	AB() {
		a = 5; b = 8;
		cout << "CONSTRUCTOR 1" << endl;
	};
	AB(int x, int y = 25) {
		a = x; b = y;
		cout << "CONSTRUCTOR 2" << endl;
	};
	void set() {
		cout << "Введите значение полей а, b: ";
		//cin >> a >> b;
		cout << (a = 2) << " " << (b = 5);
	};
	int sum() {
		return a + b;
	};
	int mult() {
		return a * b;
	};
	void get() {
		cout << "a = " << a << ", b = " << b << endl;
	};
	void set(int amin, int amax, int bmin, int bmax) {
		a = rand() % (amax - amin + 1) + amin;
		b = rand() % (bmax - bmin + 1) + bmin;
	};
};
class clCircle {
	stCircle crc;
public:
	clCircle(double x = 0, double y = 0, double r = 1) {
		crc.center.x = x; crc.center.y = y; crc.radius = r;
	};
	void set() {
		cin >> crc.center.x >> crc.center.y >> crc.radius;
	};
	void set(const char*s) {
		double x[3];
		str2num(x, s);
		crc.center.x = x[0];
		crc.center.y = x[1];
		crc.radius = x[2];
	};
	double angsize() {
		return 2 * asin(crc.radius / (sqrt(crc.center.x*crc.center.x + crc.center.y*crc.center.y)));
	};
	void set(double x, double y, double r) {
		crc.center.x = x; crc.center.y = y; crc.radius = r;
	};
	void set(double x0, double x1, double y0, double y1, double r0, double r1) {
		crcnd(&crc, x0, x1, y0, y1, r0, r1);
	};
	double len() {
		return 2 * acos(-1)*crc.radius  ;
	};
	double area() {
		return  acos(-1)*crc.radius*crc.radius;
	};
	double dist(double a, double b) {
		a -= crc.center.x; b -= crc.center.y;
		a = sqrt(a*a - b*b) - crc.radius;
		return (a > 0 ? a : 0);
	};
	double rast() {
		return sqrt(crc.center.x*crc.center.x + crc.center.y*crc.center.y)- crc.radius;
	};
	void get() {
		crcout(crc);
	};
	void get(int sw, int sp, bool addText) {
		if (addText == true)
			cout << fixed << setprecision(sp) << "x =" << setw(sw) << crc.center.x << " y =" << setw(sw) << crc.center.y << " r =" << setw(sw)<<crc.radius;
		else cout<<fixed<<setprecision(sp)<< setw(sw) << crc.center.x << setw(sw) << crc.center.y << setw(sw) << crc.radius;
	};
};
int main()
{
	
	setlocale(LC_CTYPE, "rus");
	{cout << "=== Задание 1 =================\n";
	AB ab1;
	ab1.set();
	cout << "\nСумма полей = " << ab1.sum() << endl;
	cout << "Произведение полей = " << ab1.mult() << endl;
	ab1.set(-99, 99, -99, 99);
	cout << "Значение полей объекта ab1: "; ab1.get(); ;
	cout << "Сумма полей = " << ab1.sum() << endl;
	cout << "Произведение полей = " << ab1.mult() << endl;
	AB ab2;
	cout << "Значение полей объекта ab2: "; ab2.get();
	AB ab3(12, -10);
	cout << "Значение полей объекта ab3: "; ab3.get();
	AB ab4(30);
	cout << "Значение полей объекта ab4: "; ab4.get();
	}

	{cout << "\n=== Задание 2 =================\n";
	int nx = 50; cout << "Размер массива: " << nx << endl;
	arD D1(nx);
	cout << "Массив случайных чисел:\n";
	D1.set(-99, 99);
	D1.get(5);
	cout << "Диапазон массива = " << *D1.min_() << ".." << *D1.max_() << endl;
	cout << "Отсортированный массив:\n";
	D1.srt(1);
	D1.get(5);
	}
	{cout << "\n=== Задание 3 =================\n";
	int nc = 20;
	clCircle *arC = new clCircle[nc];
	cout << "Динамический массив из " << nc << " объектов clCircle:\n";
	for (int i = 0; i < nc; i++) {
		arC[i].set(-10, 10, -10, 10, 0, 10);
		arC[i].get();
		if (((i + 1) % 5) == 0)
			cout << endl;
	}
	clCircle *pmax = arC;
	double maxlen = pmax->dist(0, 0);
	for (clCircle *p = arC + 1, *end = arC + nc; p < end; p++) {
		double len = p->dist(0, 0);
		if (len > maxlen) {
			maxlen = len;
			pmax = p;
		}
	}
	cout << "\nСамый удаленный от начала координат круг "; pmax->get();
	cout << " имеет площадь " << pmax->area() << endl;
	}
	{cout << "\n=== Задание 4 =================\n";
	int nc = strcount("13.4b.txt");
	clCircle *arC = new clCircle[nc];
	char**S = new char*[nc];
	myinput(S, "13.4b.txt");

	for (int i = 0; i < nc; i++) {
		arC[i].set(S[i]);
		if (arC[i].rast() > 80) {
			arC[i].get(7, 2, 1);
			cout << "    угловой размер = " << setprecision(4) << arC[i].angsize() << endl;	
		}
	}
	}

	system("pause");
	return 0;
}
void crcnd(stCircle *pc, double x0, double x1, double y0, double y1, double r0, double r1) {
	int n1 = (x0 - x1) * 10 + 1;
	pc->center.x = (rand() % n1) / 10. + x0;
	int n2 = (y0 - y1) * 10 + 1;
	pc->center.y = (rand() % n2) / 10. + y0;
	int n3 = (r0 - r1) * 10 + 1;
	pc->radius = (rand() % n3) / 10. + r0;
}
void crcout(stCircle crc) {
	cout << "(" << fixed << setprecision(1) << (crc.center.x >= 0 ? " " : "") << crc.center.x << "," << (crc.center.y >= 0 ? " " : "") << crc.center.y << ","
		<< (crc.radius >= 0 ? " " : "") << crc.radius << ")";
}