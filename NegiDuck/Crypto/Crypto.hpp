#pragma once
#include <Siv3D.hpp>
#include <secblock.h>

class Crypto
{
public:
	static std::string Encrypt(const std::string& plain);
	static std::string Decrypt(const std::string& cipher);


private:
	Crypto();

	static Optional<CryptoPP::SecByteBlock> GetKey();
};
