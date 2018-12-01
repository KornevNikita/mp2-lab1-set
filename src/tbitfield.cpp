// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "Len isn't correct";
  BitLen = len;
  int size = sizeof(TELEM) * 8;
  MemLen = BitLen / size + 1;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;		
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
	pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[] pMem;
  pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n / (sizeof(TELEM) * 8) ;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen)
	throw 1;
  int index = GetMemIndex(n);
  pMem[index] = pMem[index] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > BitLen)
	throw "index isn't correct";
  int index = GetMemIndex(n);
  pMem[index] = pMem[index] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > BitLen)
	throw "index isn't correct";
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % (sizeof(TELEM) * 8));
 }

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
	return *this;
  pMem = NULL;
  delete[] pMem;
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
	pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
	return 0;
  for (int i = 0; i < MemLen; i++)
    if (pMem[i] != bf.pMem[i])
	  return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
	return 1;
  for (int i = 0; i < MemLen; i++)
	if (pMem[i] != bf.pMem[i])
	  return 1;
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int len;
  if (BitLen < bf.BitLen)
	len = bf.BitLen;
  else
	len = BitLen;
  TBitField result(len);
  for (int i = 0; i < result.MemLen; i++)
	result.pMem[i] = pMem[i] | bf.pMem[i];
  return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int len;
  if (BitLen < bf.BitLen)
	len = bf.BitLen;
  else
	len = BitLen;
  TBitField result(len);
  for (int i = 0; i < result.MemLen; i++)
	result.pMem[i] = pMem[i] & bf.pMem[i];
  return result;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField result(BitLen);
  for (int i = 0; i < BitLen; i++)
	if (GetBit(i) == 0)
	  result.SetBit(i);
  return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int k;
  for (int i = 0; i < bf.GetLength(); i++)
  {
	istr >> k;
	if (k == 1)
	  bf.SetBit(i);
	else if (k == 0)
	{
	  bf.ClrBit(i);
	}
	else break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
    ostr << bf.GetBit(i) << endl;
  return ostr;
}
 