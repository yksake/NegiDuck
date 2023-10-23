#include "Crypto.hpp"
#include <rijndael.h>
#include <modes.h>
#include <files.h>
#include <osrng.h>
#include <hex.h>

using namespace CryptoPP;


Crypto::Crypto()
{

}


std::string Crypto::Encrypt(const std::string& plain)
{
	SecByteBlock key(AES::DEFAULT_KEYLENGTH);
	SecByteBlock iv(AES::BLOCKSIZE);

	{
		const auto tempKey = GetKey();
		if (not tempKey)
		{
			return "";
		}

		key = tempKey.value();
	}

	AutoSeededRandomPool prng;
	prng.GenerateBlock(iv, iv.size());

	std::string plainText = "0123456789ABCDEF" + plain;
	std::string cipher = "";

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, key.size(), iv);

		StringSource s(plainText, true,
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			)
		);
	}
	catch (const Exception& e)
	{
		const String text = U"暗号化に失敗しました";

		System::MessageBoxOK(text, MessageBoxStyle::Error);
	}

	return cipher;
}

std::string Crypto::Decrypt(const std::string& cipher)
{
	SecByteBlock key(AES::DEFAULT_KEYLENGTH);
	SecByteBlock iv(AES::BLOCKSIZE);

	{
		const auto tempKey = GetKey();
		if (not tempKey)
		{
			return "";
		}

		key = tempKey.value();
	}

	AutoSeededRandomPool prng;
	prng.GenerateBlock(iv, iv.size());

	std::string recovered = "";

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key, key.size(), iv);

		StringSource s(cipher, true,
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			)
		);
	}
	catch (const Exception& e)
	{
		std::string error = e.GetWhat();
		Clipboard::SetText(Unicode::FromUTF8(error));

		const String text = U"復号化に失敗しました";

		System::MessageBoxOK(text, MessageBoxStyle::Error);
	}

	if (recovered.size() <= 16)
	{
		return "";
	}

	recovered = recovered.substr(16, recovered.size() - 16);

	return recovered;
}


Optional<SecByteBlock> Crypto::GetKey()
{
	SecByteBlock key(AES::DEFAULT_KEYLENGTH);

	const FilePath path = Resource(U"data/key");
	BinaryReader reader{ path };
	if (not reader)
	{
		return none;
	}

	for (uint8 i = 0; i < key.size(); i++)
	{
		uint8 byte = 0;

		if (not reader.read(byte))
		{
			return none;
		}

		key[i] = byte;
	}

	return key;
}
