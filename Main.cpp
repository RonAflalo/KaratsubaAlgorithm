#include <iostream>
#include <math.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <cmath>
#include <string>
#include "Stack.h"


using namespace std;
using namespace NumArr;

#define START 0
#define AFTER_FIRST 1
#define AFTER_SECOND 2
#define AFTER_THIRD 3

long ConvertStringToNum(string string);

//void karatsuba(Array* arrX, Array* arrY, long n, Array** Res);

Array* karatsubaReq(Array* arrX, Array* arrY, long n);

Array* karatsubaIter(Array* arrX, Array* arrY, long n);

Array* Multpy(Array* arrX, Array* arrY, long n);


int main(void)
{
	string n;
	Array *arrMult, *arrKarReq, *arrKarIter;

	// get number of points and initialize module
	cin >> n;
	if (n[0] == '0')
		cout << " wrong output";
	else
	{
		long newN = ConvertStringToNum(n);
		if (newN == 0)
			cout << " wrong output ";
		else
		{
			string Xs;
			string Ys;

			Array* arrX = new Array(newN);
			Array* arrY = new Array(newN);

			cin >> Xs;
			cin >> Ys;

			arrX = arrX->ConvertNumToArray(Xs);
			arrY = arrY->ConvertNumToArray(Ys);

			if (!arrX || !arrY)
				cout << " wrong output ";
			else
			{
				//cout << "i get Over Here!" << endl;

				auto start = chrono::high_resolution_clock::now();
				// unsync the I/O of C and C++.
				ios_base::sync_with_stdio(false);
				// Here you put the name of the function you wish to measure
				arrMult = Multpy(arrX, arrY, newN);
				auto end = chrono::high_resolution_clock::now();
				// Calculating total time taken by the program.
				double time_taken =
					chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				time_taken *= 1e-9;
				auto start2 = chrono::high_resolution_clock::now();
				// unsync the I/O of C and C++.
				ios_base::sync_with_stdio(false);
				// Here you put the name of the function you wish to measure
				arrKarReq = karatsubaReq(arrX, arrY, newN);
				auto end2 = chrono::high_resolution_clock::now();
				// Calculating total time taken by the program.
				double time_taken2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
				time_taken2 *= 1e-9;
				auto start3 = chrono::high_resolution_clock::now();
				// unsync the I/O of C and C++.
				ios_base::sync_with_stdio(false);
				// Here you put the name of the function you wish to measure
				arrKarIter = karatsubaIter(arrX, arrY, newN);
				auto end3 = chrono::high_resolution_clock::now();
				// Calculating total time taken by the program.
				double time_taken3 = chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count();
				time_taken3 *= 1e-9;
				ofstream myfile("Measure.txt"); // The name of the file
				myfile << "Time taken by function <Multpy> is : " << fixed
					<< time_taken << setprecision(9);
				myfile << " sec" << endl;
				myfile << "Time taken by function <KaratsubaReq> is : " << fixed
					<< time_taken2 << setprecision(9);
				myfile << " sec" << endl;
				myfile << "Time taken by function <KaratsubaIter> is : " << fixed
					<< time_taken3 << setprecision(9);
				myfile << " sec" << endl;
				myfile.close();

				cout << "Long multiplication: x * y = ";
				arrMult->print();
				cout << "Karatsuba (recursive): x * y = ";
				arrKarReq->print();
				cout << "Karatsuba (iterative): x * y = ";
				arrKarIter->print();
			}
		}
	}
}

//void karatsuba(Array* arrX, Array* arrY, long n, Array** Res)
//{
//	*Res = karatsubaReq(arrX, arrY, n);
//}

Array* karatsubaReq(Array* arrX, Array* arrY, long n)
{
	long size = 0;
	int s = 0, c = 0;
	if (n == 1)
	{
		Array* arr = new Array(2 * n);
		s = arrX->get(0) * arrY->get(0);
		if (s > 9)
			c = s / 10;
		else
			c = 0;
		arr->set(1, s % 10);
		arr->set(0, c);
		arr = arr->RemoveZero();
		return arr;
	}
	size = (int)ceil(n / 2.0);
	if (arrX->getSize() > arrY->getSize())
		arrY = arrY->balanceSize(arrY, arrX->getSize());

	if (arrX->getSize() < arrY->getSize())
		arrX = arrX->balanceSize(arrX, arrY->getSize());
	
	Array* arra = new Array(n - size);
	arra->SpiltArr(arrX, n - size, 0);

	Array* arrb = new Array(size);
	arrb->SpiltArr(arrX, n, n - size);

	Array* arrc = new Array(n - size);
	arrc->SpiltArr(arrY, n-size, 0);

	Array* arrd = new Array(size);
	arrd->SpiltArr(arrY, n, n - size);

	Array* ac = new Array(2 * (n - size));
	ac = karatsubaReq(arra, arrc, n - size);
	ac = ac->RemoveZero();


	Array* bd = new Array(2 * (size));
	bd = karatsubaReq(arrb, arrd, size);
	bd = bd->RemoveZero();

	
	Array* aPb = arra->Sum(arra, arrb, arra->getSize(), arrb->getSize());
	aPb = aPb->RemoveZero();

	Array* cPd = arrc->Sum(arrc, arrd, arrc->getSize(), arrd->getSize());
	cPd = cPd->RemoveZero();

	int MaxSize = std::max(aPb->getSize(), cPd->getSize());
	Array* abcd = new Array(MaxSize);
	abcd = karatsubaReq(aPb, cPd, abcd->getSize());
	abcd = abcd->RemoveZero();

	abcd = abcd->Sub(abcd, ac, abcd->getSize(), ac->getSize());
	abcd = abcd->Sub(abcd, bd, abcd->getSize(), bd->getSize());

	Array* arrR = new Array();
	ac = ac->MoveToLeft(ac, 2*size);
	abcd = abcd->MoveToLeft(abcd, size);
	abcd = abcd->RemoveZero();

	arrR = arrR->Sum(abcd, ac, abcd->getSize(), ac->getSize());

	arrR = arrR->Sum(arrR, bd, arrR->getSize(), bd->getSize());

	arrR = arrR->RemoveZero();

	return arrR;
}

Array* Multpy(Array* arrX, Array* arrY, long n)
{
	long b = 0, Y = 0, X = 0, s = 0, c = 0;
	Array* Sum = new Array(2 * n);
	for (int i = (n - 1); i >= 0; i--)
	{
		X = arrX->get(i);
		for (int j = (n - 1); j >= 0; j--)
		{
			Y = arrY->get(j);
			s = X * Y + c;
			c = s / 10;
			s = s % 10;
			Sum->add(j + i + 1, s);
		}
		if (c > 0)
			Sum->add(i, c % 10);
		c = 0;
	}
	Sum->equal();
	return Sum;
}

Array* karatsubaIter(Array* arrX, Array* arrY, long n)
{
	long size = 0;
	int s = 0, c = 0, MaxSize;
	Array* arrR = nullptr, *arrc = nullptr,
		*arrb = nullptr, *arrd = nullptr, *arra = nullptr,
		*arrac = nullptr, *arrbd = nullptr, *arrabcd = nullptr,
		*arr = nullptr, *aPb = nullptr, *cPd = nullptr, *Temp = nullptr;
	ItemT Curr(arrX, arrY, nullptr, nullptr, nullptr, nullptr, n, size, START);
	ItemT Next;
	Stack st;

	//Curr = buildItem(arrX, arrY, nullptr, nullptr, nullptr, n, size, START, nullptr);
	st.Push(Curr);

	while (!st.isEmpty())
	{
		Curr = st.getTop();
		Curr.setARR(arrR);
		st.Pop();
		if (Curr.getline() == START)
		{
			if (Curr.getn() == 1)
			{
				arrR = new Array(2);
				s = Curr.getArrX()->get(0) * Curr.getArrY()->get(0);
				if (s > 9)
					c = s / 10;
				else
					c = 0;
				arrR->set(1, s % 10);
				arrR->set(0, c);
				arrR = arrR->RemoveZero();
				if (!st.isEmpty())
					Curr.setARR(arrR);
				else
					return arrR;
			}
			else
			{
				Curr.setSize((int)ceil(Curr.getn() / 2.0));
				if (Curr.getArrX()->getSize() > Curr.getArrY()->getSize())
					Curr.setArrY(Curr.getArrY()->balanceSize(Curr.getArrY(), Curr.getArrX()->getSize()));
				if (Curr.getArrX()->getSize() < Curr.getArrY()->getSize())
					Curr.setArrX(Curr.getArrX()->balanceSize(Curr.getArrX(), Curr.getArrY()->getSize()));

				arra = new Array(Curr.getn() - Curr.getsize());
				arra->SpiltArr(Curr.getArrX(), Curr.getn() - Curr.getsize(), 0);
				arrc = new Array(Curr.getn() - Curr.getsize());
				arrc->SpiltArr(Curr.getArrY(), Curr.getn() - Curr.getsize(), 0);
				
				//arrac = new Array(2 * (Curr.getn() - Curr.getsize()));
			    Curr.setline(AFTER_FIRST);
				Next.set(arra, arrc, nullptr, nullptr, nullptr, nullptr, Curr.getn() - Curr.getsize(), 0, START);

				st.Push(Curr);
				st.Push(Next);

				//check
				//cout << "Curr in start: " << endl;
				//PrintItem(Curr);
				//cout << "Next in start: " << endl;
				//PrintItem(Next);
			}
		}
		else if (Curr.getline() == AFTER_FIRST)
		{
			arrb = new Array(Curr.getsize());
			arrb->SpiltArr(Curr.getArrX(), Curr.getn(), Curr.getn() - Curr.getsize());
			arrd = new Array(Curr.getsize());
			arrd->SpiltArr(Curr.getArrY(), Curr.getn(), Curr.getn() - Curr.getsize());

			arrac = Curr.getARR();
			arrac = arrac->RemoveZero();
			Curr.setArrac(arrac);

			//Curr.setArrbd(new Array(2 * (Curr.getsize())));
			Curr.setline(AFTER_SECOND);
			Next.set(arrb, arrd, nullptr, nullptr, nullptr, nullptr, Curr.getsize(), 0, START);

			st.Push(Curr);
			st.Push(Next);

			//check
			//PrintItem(Curr);
			//PrintItem(Next);
		}
		else if (Curr.getline() == AFTER_SECOND)
		{
			arra = new Array(Curr.getn() - Curr.getsize());
			arra->SpiltArr(Curr.getArrX(), Curr.getn() - Curr.getsize(), 0);
			arrc = new Array(Curr.getn() - Curr.getsize());
			arrc->SpiltArr(Curr.getArrY(), Curr.getn() - Curr.getsize(), 0);
			arrb = new Array(Curr.getsize());
			arrb->SpiltArr(Curr.getArrX(), Curr.getn(), Curr.getn() - Curr.getsize());
			arrd = new Array(Curr.getsize());
			arrd->SpiltArr(Curr.getArrY(), Curr.getn(), Curr.getn() - Curr.getsize());

			arrbd = Curr.getARR();
			arrbd = arrbd->RemoveZero();
			Curr.setArrbd(arrbd);

			aPb = aPb->Sum(arra, arrb, arra->getSize(), arrb->getSize());
			aPb = aPb->RemoveZero();
			cPd = cPd->Sum(arrc, arrd, arrc->getSize(), arrd->getSize());
			cPd = cPd->RemoveZero();

			MaxSize = std::max(aPb->getSize(), cPd->getSize());

			Curr.setline(AFTER_THIRD);
			Next.set(aPb, cPd, nullptr, nullptr, nullptr, nullptr, MaxSize, 0, START);
			st.Push(Curr);
			st.Push(Next);

			//check
			//PrintItem(Curr);
			//PrintItem(Next);
		}
		else if (Curr.getline() == AFTER_THIRD)
		{
			arrabcd = Curr.getARR();
			arrac = Curr.getArrac();
			arrbd = Curr.getArrbd();
			arrabcd = arrabcd->RemoveZero();

			arrabcd = arrabcd->Sub(arrabcd, arrac, arrabcd->getSize(), arrac->getSize());
			arrabcd = arrabcd->Sub(arrabcd, arrbd, arrabcd->getSize(), arrbd->getSize());

			arrac = arrac->MoveToLeft(arrac, 2 * Curr.getsize());
			arrabcd = arrabcd->MoveToLeft(arrabcd, Curr.getsize());
			arrabcd = arrabcd->RemoveZero();

			arrR = arrR->Sum(arrabcd, arrac, arrabcd->getSize(), arrac->getSize());
			arrR = arrR->Sum(arrR, arrbd, arrR->getSize(), arrbd->getSize());
			arrR = arrR->RemoveZero();

			Curr.setArrabcd(arrabcd);
			Curr.setARR(arrR);

			//check
			//Curr.aRR->print();
		}
	}
	return Curr.getARR();
}

long ConvertStringToNum(string _string) {
	int size = _string.size(), num = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		if (_string[i] < 48 || _string[i] > 57)
			return 0;
		else
			num += (_string[i] - '0') * (int)pow(10, size - i - 1);
	}
	return num;
}