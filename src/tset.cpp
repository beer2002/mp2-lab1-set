// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"


// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

TSet::TSet(const TSet &s) : BitField(s.BitField)
// конструктор копирования
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) :MaxPower(bf.GetLength()), BitField(bf)
{

}

TSet::operator TBitField()
{
    return BitField;// вызов в main (TBitField()Set)
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
    return FAKE_SET;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return FAKE_INT;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return FAKE_INT;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return BitField | s.BitField;//MaxPower изменять не нужно. т.к в приведении типа будет присваиваться MaxPover
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    return FAKE_SET;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    return FAKE_SET;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return FAKE_SET;
}

TSet TSet::operator~(void) // дополнение
{
    return FAKE_SET;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{
    int num;
    char ch;

    do {
        is >> ch;
    } while (ch != '{');


    do {
        is >> num;
        s.InsElem(num);
        do {
            is >> s;
        } while (ch != ',' && ch != '}');
    } while (ch != '}');

    return is;
}

ostream& operator<<(ostream &os, const TSet &s) // вывод
{
    os << "{";
    
    for (int i = 0; i < s.GetMaxPower(); i++) {
        os << i << ", ";
    }

    os << "}";

    return os;
}
