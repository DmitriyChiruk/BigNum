#include <iostream>

#include "BigNum.h"

using namespace std;

int main() {
	BigNum A, B, C;
	A.SetHex("51bf60");
	B.SetHex("403db8");
	string TestRes = "Failed";

	// Binary operators tests
	cout << "A: " << A.GetHex() << endl << "B: " << B.GetHex() << endl << endl;

	cout << "And: ";
	C = A.AND(&B);
	TestRes = C.GetHex() == "0x403d20" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;
	
	cout << "Or: " ;
	C = A.OR(&B);
	TestRes = C.GetHex() == "0x51bff8" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;
	
	cout << "Xor: ";
	C = A.XOR(&B);
	TestRes = C.GetHex() == "0x1182d8" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;
	
	cout << "Inv: ";
	C = A.Inv();
	TestRes = C.GetHex() == "0xffffffffffae409f" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;

	cout << "LShift: ";
	C = A;
	C.ShiftL(4);
	TestRes = C.GetHex() == "0x51bf600" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;

	cout << "RShift: ";
	C = A;
	C.ShiftR(4);
	TestRes = C.GetHex() == "0x51bf6" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl;

	// Arithmetical operations test
	cout << endl;

	cout << "Add: ";
	A.SetHex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
	B.SetHex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
	cout << endl << "A: " << A.GetHex() << endl << "B: " << B.GetHex() << endl;
	C = A.ADD(&B);
	TestRes = C.GetHex() == "0x1fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl << endl;

	cout << "Add: ";
	A.SetHex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
	B.SetHex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
	cout << endl << "A: " << A.GetHex() << endl << "B: " << B.GetHex() << endl;
	C = A.ADD(&B);
	TestRes = C.GetHex() == "0xa78865c13b14ae4e25e90771b54963ee2d68c0a64d4a8ba7c6f45ee0e9daa65b" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl << endl;

	cout << "Sub: ";
	A.SetHex("30962951c10e57032");
	B.SetHex("22e9629510e57032");
	cout << endl << "A: " << A.GetHex() << endl << "B: " << B.GetHex() << endl;
	C = A.SUB(&B);
	TestRes = C.GetHex() == "0x2e679328700000000" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl << endl;
	
	cout << "Sub: ";
	A.SetHex("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
	B.SetHex("22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
	cout << endl << "A: " << A.GetHex() << endl << "B: " << B.GetHex() << endl;
	C = A.SUB(&B);
	TestRes = C.GetHex() == "0x10e570324e6ffdbc6b9c813dec968d9bad134bc0dbb061530934f4e59c2700b9" ? " Passed" : " Failed";
	cout << C.GetHex() << " : " << TestRes << endl << endl;

	return 0;
}