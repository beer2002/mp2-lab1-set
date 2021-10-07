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
    if (&s == this) {
        return *this;
    }

    MaxPower = s.GetMaxPower();
    BitField = s.BitField;

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.GetMaxPower()) {
        return 0;
    }
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet set(MaxPower > s.GetMaxPower() ? MaxPower : s.GetMaxPower());
    set.BitField = BitField | s.BitField;

    return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet set(*this);
    set.InsElem(Elem);

    return set;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet set(*this);
    set.DelElem(Elem);

    return set;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet set(MaxPower > s.GetMaxPower() ? MaxPower : s.GetMaxPower());
    set.BitField = BitField & s.BitField;

    return set;
}

TSet TSet::operator~(void) // дополнение
{
    BitField = ~BitField;
    return *this;
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
    int i;
    for (i = 0; i < s.GetMaxPower(); i++) {
        if (s.BitField.GetBit(i)) {
            os << i;
            break;
        }
    }
    
    for (i = i + 1; i < s.GetMaxPower(); i++) {
        if (s.BitField.GetBit(i)) {
            os << ", " << i;
        }
    }

    os << "}";

    return os;
}
