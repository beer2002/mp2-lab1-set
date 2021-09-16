#include <iostream>
#include "tbitfield.h"

void main() {
	TBitField BitField = TBitField(65);

	BitField.SetBit(0);
	int bit = BitField.GetBit(0);

	BitField.SetBit(10);
	int bit1 = BitField.GetBit(10);

	BitField.ClrBit(10);
	int bit2 = BitField.GetBit(10);
	//system("pause");
}