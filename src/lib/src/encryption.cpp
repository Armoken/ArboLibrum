/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#include "../include/encryption.h"

//****************************************************************************************************

void Encryption::setKey(string _key)
{
	if (!_key.empty()) key = _key;
	else key = "default";
}

//****************************************************************************************************

string Encryption::encrypt(string data)
{
	if (data.empty())
		return data;

	const char* byteData = data.c_str();
	const char* byteKey = key.c_str();
	char* result = new char[data.length()];
	string encryptedData = "";
	encryptedData.resize(data.length());

	for (int i = 0; i < data.length(); i++)
		result[i] = (char)(byteData[i] ^ key[i % key.length()]);

	for (int i = 0; i < encryptedData.length(); i++)
		encryptedData[i] = result[i];

	return encryptedData;
}

string Encryption::decrypt(string encodedData)
{
	if (encodedData.empty())
		return encodedData;

	const char* byteEncodedData = encodedData.c_str();
	const char* byteKey = key.c_str();
	char* result = new char[encodedData.length()];
	string data = "";

	for (int i = 0; i < encodedData.length(); i++)
		result[i] = (char)(byteEncodedData[i] ^ key[i % key.length()]);

	for (int i = 0; i < encodedData.length(); i++)
		data += result[i];

	return data;
}

//****************************************************************************************************