#include "Array.h"
#include <algorithm> 
#include <string>
namespace NumArr {

	Array::Array(int _size){
		this->arr = new int[_size];
		this->size = _size;
		for (int i = 0; i < size; i++)
			arr[i] = 0;
	}
	Array::Array(const Array& other) : size(other.size) {
		for (int i = size - other.size; i < size; i++)
			arr[i] = other.arr[i - other.size];
	}
	Array::~Array() {
	}
	Array* Array::RemoveZero(void) {
		if (size != 1)
		{
			int newSize = 0;
			for (int i = 0; i < size - 1; i++)
			{
				if (this->get(newSize) == 0)
					newSize++;
				else
					break;
			}
			newSize = size - newSize;
			Array* Tarr = new Array(newSize);
			for (int i = 1; i <= newSize; i++)
				Tarr->set(newSize - i, this->get(size - i));
			this->~Array();
			return Tarr;
		}
		else
			return this;
	}

	Array* Array::Sub(Array* a, Array* b, int sizeA, int sizeB) {
		int c = 0, s = 0, Bsize = max(sizeA, sizeB), Ssize = min(sizeA, sizeB);
		Array* arrSub = new Array(Bsize);
		for (int i = 1; i <= Ssize; i++)
		{
			s = a->get(sizeA - i) - b->get(sizeB - i) - c;
			if (s < 0)
			{
				arrSub->set(Bsize - i, s + 10);
				c = 1;
			}
			else
			{
				arrSub->set(Bsize - i, s);
				c = 0;
			}
		}
		for (int i = Ssize + 1; i <= Bsize; i++)
		{
			if (sizeB < sizeA)
				s = a->get(sizeA - i) - c;
			else
				s = b->get(sizeB - i) - c;
			if (s < 0)
			{
				arrSub->set(Bsize - i, s + 10);
				c = 1;
			}
			else
			{
				arrSub->set(Bsize - i, s);
				c = 0;
			}
		}
		return arrSub;
	}
	Array* Array::Sum(Array* a, Array* b, int sizeA, int sizeB) {
		int c = 0, s = 0, Bsize = max(sizeA, sizeB), Ssize = min(sizeA, sizeB);
		Array* arrSum = new Array(Bsize + 1);
		for (int i = 1; i <= Ssize; i++)
		{
			s = a->get(sizeA - i) + b->get(sizeB - i) + c;
			arrSum->set(Bsize - i + 1, s % 10);
			if (s > 9)
				c = s / 10;
			else
				c = 0;
		}
		for (int i = Ssize + 1; i <= Bsize; i++)
		{
			if (sizeB > sizeA)
			{
				s = b->get(sizeB - i) + c;
				arrSum->set(Bsize - i + 1, s % 10);
				if (s > 9)
					c = s / 10;
				else
					c = 0;
			}
			else
			{
				s = a->get(sizeA - i) + c;
				arrSum->set(Bsize - i + 1, s % 10);
				if (s > 9)
					c = s / 10;
				else
					c = 0;
			}

		}
		arrSum->set(0, c);
		a->~Array();
		b->~Array();
		return arrSum;
	}
	Array* Array::balanceSize(Array* a, int size) {
		int oldSize = a->getSize();
		int Diff = size - oldSize;
		Array* Tarr = new Array(size);
		for (int i = 0; i < oldSize; i++)
			Tarr->set(i + Diff, this->get(i));
		this->~Array();
		return Tarr;
	}

	Array* Array::MoveToLeft(Array* a, int num)
	{
		Array* Tarr = new Array(a->getSize() + num);
		for (int i = 1; i <= a->getSize(); i++)
			Tarr->set(Tarr->getSize() - i - num, a->get(a->getSize() - i));
		this->~Array();
		return Tarr;
	}
	void Array::SpiltArr(Array* fullArr, int _size,  int counter) {
		int Pcounter = 0;
		while (counter < _size)
		{
			this->set(Pcounter, fullArr->get(counter));
			counter++;
			Pcounter++;
		}
	}
	const int&  Array::get(int idx) const {
		return arr[idx];
	}
	const int&  Array::getSize(void) const {
		return size;
	}
	void  Array::set(int idx, const int& digit) {
		arr[idx] = digit;
	}
	Array* Array::ConvertNumToArray(string _string) {
		int len = _string.size();
		if (len != size)
			return NULL;
		for (int i = size - 1; i >= 0; i--)
			if (_string[i] < 48 || _string[i] > 57)
				return NULL;
			else
				this->set(i, (_string[i] - '0'));
		return this;
    }

	void Array::add(int idx, const int& digit) {
		arr[idx] += digit;
	}
	void Array::print(void) const {
		bool zero = true;
		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] != 0)
				zero = false;
			if (!zero)
				cout << arr[i];
		}
		cout << arr[size - 1] << "\n";
	}

	void Array::equal(void)
	{
		int c = 0, s = 0;
		for (int i = (size - 1); i > 0; i--)
		{
			c = this->get(i) / 10;
			s = this->get(i) % 10;
			this->add(i - 1, c);
			this->set(i, s);
		}
	}
}

