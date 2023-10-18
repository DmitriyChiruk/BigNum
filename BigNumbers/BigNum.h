#pragma once

#include <vector>
#include <bitset>
#include <string>

class BigNum
{
private:
	std::vector<uint64_t> data_int;

public:
	BigNum();
	BigNum(std::vector<uint64_t> BlocksOfData);

	~BigNum();

	int GetNumOfBlocks();
	std::vector<uint64_t> GetDataBlocks();

	void SetHex(std::string HexString);
	std::string GetHex();

	BigNum AND(BigNum *Other);
	BigNum OR(BigNum *Other);
	BigNum XOR(BigNum *Other);
	BigNum Inv();
	void ShiftL(int NumOfBits);
	void ShiftR(int NumOfBits);

	BigNum ADD(BigNum* Other);
	BigNum SUB(BigNum* Other);
};