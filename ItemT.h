#pragma once
#include "Array.h"

namespace NumArr {
	class Array;
	class ItemT
	{
	private:
		Array* arrX;
		Array* arrY;
		Array* arrac;
		Array* arrbd;
		Array* arrabcd;
		Array* aRR;
		long n, size;
		int line;
	public:
		ItemT(Array* _arrX, Array* _arrY, Array* _arrac, Array* _arrbd, Array* _arrabcd, Array* _aRR, long _n, long _size, int _line);
		ItemT();
		~ItemT();

		Array* getArrX(void);
		Array* getArrY(void);
		Array* getArrac(void);
		Array* getArrbd(void);
		Array* getArrabcd(void);
		Array* getARR(void);
		int getsize(void);
		int getn(void);
		int getline(void);

		void setArrX(Array* _arrX);
		void setArrY(Array* _arrY);
		void setArrac(Array* _arrac);
		void setArrbd(Array* _arrbd);
		void setArrabcd(Array* _arrabcd);
		void setARR(Array* _aRR);

		void setSize(long _size);
		void setn(long _n);
		void setline(int _line);

		void set(Array* _arrX, Array* _arrY, Array* _arrac, Array* _arrbd, Array* _arrabcd, Array* _aRR, long _n, long _size, int _line);
		void set(ItemT _item);
	};
};
