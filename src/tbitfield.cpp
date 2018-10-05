// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП 
// 
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001 
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015) 
// 
// Битовое поле 

#include "tbitfield.h" 
#include <cmath> 

TBitField::TBitField(int len)
{
	if (len < 0) throw 0;
	BitLen = len;
	MemLen = int(ceil(float(BitLen) / 32.0));
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования 
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	MemLen = NULL;
	pMem = NULL;
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n 
{
	return int(float(BitLen) / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{
	return 0;
}

// доступ к битам битового поля 

int TBitField::GetLength(void) const // получить длину (к-во битов) 
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит 
{
	if (n < 0 || n > BitLen) throw 0;
	int i = int(float(n) / 32);
	int k = int(n - i * 32);
	int m = 1 << k;
	pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // очистить бит 
{
	if (n < 0 || n > BitLen) throw 0;
	int i = int(float(n) / 32);
	int k = int(n - i * 32);
	pMem[i] = pMem[i] & !(1 << k);
}

int TBitField::GetBit(const int n) const // получить значение бита 
{
	if (n < 0 || n > BitLen) throw 0;
	int i = int(float(n) / 32);
	int k = int(n - i * 32);
	int m = 1 << k;
	if ((pMem[i] & m) == 0)
		return 0;
	else
		return 1;
}

// битовые операции 

TBitField& TBitField::operator=(const TBitField &bf) // присваивание 
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение 
{
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение 
{
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или" 
{
	TBitField tempBF(*this);
	for (int i = 0; i < MemLen; i++)
		tempBF.pMem[i] = tempBF.pMem[i] | bf.pMem[i];
	return tempBF;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и" 
{
	TBitField tempBF(*this);
	for (int i = 0; i < MemLen; i++)
		tempBF.pMem[i] = tempBF.pMem[i] & bf.pMem[i];
	return tempBF;
}

TBitField TBitField::operator~(void) // отрицание 
{
	TBitField tempBF(*this);
	for (int i = 0; i < MemLen; i++)
		pMem[i] = !pMem[i];
	for (int i = BitLen; i < MemLen * 32; i++)
		ClrBit(i);
	return tempBF;
}

// ввод/вывод 

istream &operator>>(istream &istr, TBitField &bf) // ввод 
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод 
{
	return ostr;
}