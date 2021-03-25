#include "ItemT.h"



namespace NumArr {
	ItemT::ItemT(Array* _arrX, Array* _arrY, Array* _arrac, Array* _arrbd, Array* _arrabcd, Array* _aRR, long _n, long _size, int _line) {
		arrX = _arrX;
		arrY = _arrY;
		arrac = _arrac;
		arrbd = _arrbd;
		arrabcd = _arrabcd;
		n = _n;
		size = _size;
		line = _line;
		aRR = _aRR;
	}
	ItemT::ItemT()
	{
		arrX = nullptr;
		arrY = nullptr;
		arrac = nullptr;
		arrbd = nullptr;
		arrabcd = nullptr;
		n = 0;
		size = 0;
		line = 0;
		aRR = nullptr;
	}

	ItemT::~ItemT(){
	}

	Array* ItemT::getArrX(void) {
		return arrX;
	}
	Array* ItemT::getArrY(void) {
		return arrY;
	}
	Array* ItemT::getArrac(void) {
		return arrac;
	}
	Array* ItemT::getArrbd(void) {
		return arrbd;
	}
	Array* ItemT::getArrabcd(void) {
		return arrabcd;
	}
	Array* ItemT::getARR(void) {
		return aRR;
	}
	int ItemT::getsize(void) {
		return size;
	}
	int ItemT::getn(void) {
		return n;
	}
	int ItemT::getline(void) {
		return line;
	}

	void ItemT::setArrX(Array* _arrX){
		arrX = _arrX;
	}
	void ItemT::setArrY(Array* _arrY) {
		arrY = _arrY;
	}
	void ItemT::setArrac(Array* _arrac) {
		arrac = _arrac;
	}
	void ItemT::setArrbd(Array* _arrbd) {
		arrbd = _arrbd;
	}
	void ItemT::setArrabcd(Array* _arrabcd) {
		arrabcd = _arrabcd;
	}
	void ItemT::setARR(Array* _aRR) {
		aRR = _aRR;
	}
	void ItemT::setSize(long _size) {
		size = _size;
	}
	void ItemT::setn(long _n) {
		n = _n;
	}
	void ItemT::setline(int _line) {
		line = _line;
	}

	void ItemT::set(Array* _arrX, Array* _arrY, Array* _arrac, Array* _arrbd, Array* _arrabcd, Array* _aRR, long _n, long _size, int _line) {
		setArrX(_arrX);
		setArrY(_arrY);
		setArrac(_arrac);
		setArrbd(_arrbd);
		setArrabcd(_arrabcd);
		setARR(_aRR);
		setn(_n);
		setSize(_size);
		setline(_line);
	}
	void ItemT::set(ItemT _item) {
		setArrX(_item.getArrX());
		setArrY(_item.getArrY());
		setArrac(_item.getArrac());
		setArrbd(_item.getArrbd());
		setArrabcd(_item.getArrabcd());
		setARR(_item.getARR());
		setn(_item.getn());
		setSize(_item.getsize());
		setline(_item.getline());
	}
};