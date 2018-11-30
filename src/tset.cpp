// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp): BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  if(this == &s)
	return *this;
  MaxPower = s.MaxPower;
  BitField = s.BitField;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if(MaxPower != s.MaxPower)
	return 0;
  if (BitField != s.BitField)
	return 0;
  return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if (MaxPower != s.MaxPower)
	return 1;
  if (BitField != s.BitField)
	return 1;
  return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  if (this == &s)
	return *this;
  if (MaxPower >= s.MaxPower) 
  {
	TSet result(MaxPower);
	result.BitField = BitField | s.BitField;
	return result;
  }
  else 
  {
  TSet result(s.MaxPower);
  result.BitField = BitField | s.BitField;
  return result;
  }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if ((Elem < MaxPower) || (Elem > -1))
  {
    TSet result(BitField);
    result.BitField.SetBit(Elem);
	return result;
  }
  else 
	return 1;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if ((Elem < MaxPower) || (Elem > -1))
  {
	TSet result(BitField);
	result.BitField.ClrBit(Elem);
	return result;
  }
  else
	return 1;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  if (this == &s)
	return *this;
  if (MaxPower >= s.MaxPower) 
  {
	TSet result(MaxPower);
	result.BitField = BitField & s.BitField;
	return result;
  }
  else 
  {
	TSet result(s.MaxPower);
	result.BitField = BitField & s.BitField;
	return result;
  }
}

TSet TSet::operator~(void) // дополнение
{
  TSet A(MaxPower);
  A.BitField = ~BitField;
  return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int i;
  cin >> i;
  for (; ((i > -1) && (i < s.MaxPower)); cin >> i)
    s.bitField.SetBit(i);
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << s.bitField << ' ';
  return ostr;
}