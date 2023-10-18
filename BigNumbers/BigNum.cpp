#include<iostream>

#include "BigNum.h"

#define BLOCK_BIT_SZ 64

using namespace std;

BigNum::BigNum()
{
	this->data_int = vector<uint64_t>({ 0 });
}

BigNum::BigNum(std::vector<uint64_t> BlocksOfData)
{
	data_int = BlocksOfData;
}

BigNum::~BigNum()
{
	data_int.clear();
}

int BigNum::GetNumOfBlocks()
{
	return data_int.size();
}

std::vector<uint64_t> BigNum::GetDataBlocks()
{
	return data_int;
}

void BigNum::SetHex(string HexString)
{
	this->data_int.clear();

	// Read by blocks of 16 digits from the end 
	for (int i = HexString.size() - 1; i >= 0; i -= (BLOCK_BIT_SZ / 4))
	{
		// If left block is shorter than 16 digits => set ctart reading from 0 element
		int BlockStart = i - (BLOCK_BIT_SZ / 4 - 1) > 0 ? i - (BLOCK_BIT_SZ / 4 - 1) : 0;

		// Select block as a substring
		string SubStr = HexString.substr(BlockStart, i - BlockStart + 1);

		// Insert block data to the beginning, converting it to int64_t
		data_int.insert(data_int.begin(), stoull(SubStr, 0, 16));
	}
}

string BigNum::GetHex()
{
	string HexString = "0x";
	size_t counter = 0;

	// Iterate over each block
	for (auto block : data_int)
	{
		string Substr = "";

		// Convert block to hex
		while (block > 0)
		{
			size_t Rest = block % 16;
			char HexDigit = Rest < 10? '0' + Rest: 'a' + (Rest - 10);
			
			Substr = HexDigit + Substr;
			block /= 16;
		}

		if (Substr.size() != 16 && counter != 0)
		{
			Substr.insert(Substr.begin(), 16 - Substr.size(), '0');
		}

		// Add converted value to output
		HexString += Substr;

		++counter;
	}

	return HexString;
}

void AppendDataToSz(std::vector<uint64_t>* Vec, size_t& NewSz)
{
	if (Vec->size() < NewSz)
	{
		Vec->insert(Vec->begin(), NewSz - Vec->size(), 0);
	}
}

BigNum BigNum::AND(BigNum* Other)
{
	size_t MaxNumOfBlocks = std::max(this->GetNumOfBlocks(), Other->GetNumOfBlocks());
	std::vector<uint64_t> data_fst, data_scnd, data_res;

	data_fst = this->GetDataBlocks();
	data_scnd = Other->GetDataBlocks();

	AppendDataToSz(&data_fst, MaxNumOfBlocks);
	AppendDataToSz(&data_scnd, MaxNumOfBlocks);

	for (int i = 0; i < MaxNumOfBlocks; i++)
	{
		data_res.push_back(data_fst[i] & data_scnd[i]);
	}

	return BigNum(data_res);
}

BigNum BigNum::OR(BigNum *Other)
{
	size_t MaxNumOfBlocks = std::max(this->GetNumOfBlocks(), Other->GetNumOfBlocks());
	std::vector<uint64_t> data_fst, data_scnd, data_res;

	data_fst = this->GetDataBlocks();
	data_scnd = Other->GetDataBlocks();

	AppendDataToSz(&data_fst, MaxNumOfBlocks);
	AppendDataToSz(&data_scnd, MaxNumOfBlocks);

	for (int i = 0; i < MaxNumOfBlocks; i++)
	{
		data_res.push_back(data_fst[i] | data_scnd[i]);
	}

	return BigNum(data_res);
}

BigNum BigNum::XOR(BigNum *Other)
{
	size_t MaxNumOfBlocks = std::max(this->GetNumOfBlocks(), Other->GetNumOfBlocks());
	std::vector<uint64_t> data_fst, data_scnd, data_res;

	data_fst = this->GetDataBlocks();
	data_scnd = Other->GetDataBlocks();

	AppendDataToSz(&data_fst, MaxNumOfBlocks);
	AppendDataToSz(&data_scnd, MaxNumOfBlocks);

	for (int i = 0; i < MaxNumOfBlocks; i++)
	{
		data_res.push_back(data_fst[i] ^ data_scnd[i]);
	}

	return BigNum(data_res);
}

BigNum BigNum::Inv()
{
	std::vector<uint64_t> data_res;

	for (int i = 0; i < data_int.size(); i++)
	{
		data_res.push_back(~data_int[i]);
	}

	return BigNum(data_res);
}

void BigNum::ShiftL(int NumOfBits)
{
	for (int i = 0; i < data_int.size(); i++)
	{
		data_int[i] <<= NumOfBits;
		if (i > 0) {
			// Add first n bits of the previous block
			data_int[i] |= (data_int[i - 1] >> (BLOCK_BIT_SZ - NumOfBits));
		}
	}
}

void BigNum::ShiftR(int NumOfBits)
{
	for (int i = 0; i < data_int.size(); i++)
	{
		data_int[i] >>= NumOfBits;
		if (i > 0) {
			// Add last n bits of the previous block
			data_int[i] |= (data_int[i - 1] << (BLOCK_BIT_SZ - NumOfBits));
		}
	}
}

BigNum BigNum::ADD(BigNum* Other)
{
	size_t MaxNumOfBlocks = std::max(this->GetNumOfBlocks(), Other->GetNumOfBlocks());
	std::vector<uint64_t> data_fst, data_scnd, data_res;

	data_fst = this->GetDataBlocks();
	data_scnd = Other->GetDataBlocks();

	AppendDataToSz(&data_fst, MaxNumOfBlocks);
	AppendDataToSz(&data_scnd, MaxNumOfBlocks);

	bool move = false;

	for (int i = MaxNumOfBlocks - 1; i >= 0; i--)
	{
		uint64_t num_res;
		
		num_res = data_fst[i] + data_scnd[i] + move;
		
		// Set move true if going to next register
		move = ((data_fst[i] >> 1) + (data_scnd[i] >> 1)) >> (BLOCK_BIT_SZ - 1);

		data_res.insert(data_res.begin(), num_res);

		if (i == 0 && move)
		{
			data_res.insert(data_res.begin(), move);
		}
	}

	return BigNum(data_res);
}

BigNum BigNum::SUB(BigNum* Other)
{
	size_t MaxNumOfBlocks = std::max(this->GetNumOfBlocks(), Other->GetNumOfBlocks());
	std::vector<uint64_t> data_fst, data_scnd, data_res;

	data_fst = this->GetDataBlocks();
	data_scnd = Other->GetDataBlocks();

	AppendDataToSz(&data_fst, MaxNumOfBlocks);
	AppendDataToSz(&data_scnd, MaxNumOfBlocks);

	for (int i = MaxNumOfBlocks - 1; i >= 0; i--)
	{
		uint64_t num_res, max_val = 0;
		--max_val;

		if (data_fst[i] < data_scnd[i] && i - 1 >= 0)
		{
			--data_fst[i - 1];
		}
		
		num_res = data_fst[i] - data_scnd[i];

		data_res.insert(data_res.begin(), num_res);
	}

	return BigNum(data_res);
}
