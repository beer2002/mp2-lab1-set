// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw len;
    }
    BitLen = len;
    MemLen = (len - 1) / 32 + 1;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    BitLen = -1;
    MemLen = -1;
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    return 1 << n % 32;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) {
        throw n;
    }

    return pMem[GetMemIndex(n)] & GetMemMask(n) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf == this) {
        return *this;
    }

    BitLen = bf.BitLen;

    if (MemLen != bf.MemLen) {
        MemLen = bf.MemLen;

        delete[] pMem;
        pMem = new TELEM[MemLen];
    }

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.MemLen != MemLen) {
        return 0;
    }

    for (int i = 0; i < MemLen; i++) {
        if (bf.pMem[i] != pMem[i]) {
            return 0;
        }
    }

    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField bitField(BitLen > bf.BitLen ? BitLen : bf.BitLen);
    if (BitLen > bf.BitLen) {
        for (int i = 0; i < bf.MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i] | pMem[i];
        }

        for (int i = bf.MemLen; i < MemLen; i++) {
            bitField.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = 0; i < MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i] | pMem[i];
        }

        for (int i = MemLen; i < bf.MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i];
        }
    }
   
    return bitField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    
    TBitField bitField(BitLen > bf.BitLen ? BitLen : bf.BitLen);
    if (BitLen > bf.BitLen) {
        for (int i = 0; i < bf.MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i] & pMem[i];
        }

        for (int i = bf.MemLen; i < MemLen; i++) {
            bitField.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = 0; i < MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i] & pMem[i];
        }

        for (int i = MemLen; i < bf.MemLen; i++) {
            bitField.pMem[i] = bf.pMem[i];
        }
    }

    return bitField;
}

TBitField TBitField::operator~(void) // отрицание
{   
    for (int i = 0; i < MemLen - 1; i++) {
        pMem[i] = ~pMem[i];
    }

    for (int i = 32 * (MemLen - 1); i < BitLen; i++) {
        if (GetBit(i)) {
            ClrBit(i);
        } else {
            SetBit(i);
        }
    }

    return *this;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
    char ch;
    cout << "Input BitField: ";

    for (int i = 0; i < bf.BitLen; i++) {
        is >> ch;
        if (ch == '1') {
            bf.SetBit(i);
        }
    }
    return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
    os << "BitField: ";

    for (int i = 0; i < bf.BitLen; i++) {
        os << bf.GetBit(i);
    }

    return os;
}
