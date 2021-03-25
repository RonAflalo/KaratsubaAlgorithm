#ifndef arr_
#define arr_
#include <string>
#include <iostream>
using namespace std;

namespace NumArr {
	class Array
	{
	private:
		int* arr;
		int size;
	public:
		Array(int size = 1);
		Array(const Array&);
		~Array();

		const int& get(int idx) const;

		const int& getSize(void) const;

		void set(int idx, const int& digit);

		void add(int idx, const int& digit);

		Array* ConvertNumToArray(string _string);

		void SpiltArr(Array* fullArr, int _size, int counter);

		Array* RemoveZero(void);

		Array* Sub(Array* a, Array* b, int sizeA, int sizeB);

		Array* Sum(Array* a, Array* b, int sizeA, int sizeB);

		Array* MoveToLeft(Array* a, int num);

		Array* balanceSize(Array* a, int size);

		void equal(void);

		void print(void) const;
	};
};

#endif


