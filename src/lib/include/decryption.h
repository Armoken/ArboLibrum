/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#ifndef DECRYPTION_H
#define DECRYPTION_H

#define FD(x) (((x) >> 1) ^ (((x) & 1) ? 0x8d : 0))

//****************************************************************************************************

#include "encryption.h"

//****************************************************************************************************

class Decryption
{
private:
	static uint8_t rj_xtime(uint8_t x);
	static void aes_subBytes_inv(uint8_t* buf);
	static void aes_addRoundKey(uint8_t* buf, uint8_t* key);
	static void aes_addRoundKey_cpy(uint8_t* buf, uint8_t* key, uint8_t* cpk);
	static void aes_shiftRows_inv(uint8_t* buf);
	static void aes_mixColumns_inv(uint8_t* buf);
	static void aes_expandDecKey(uint8_t* k, uint8_t* rc);
public:
	static void aes256_decrypt_ecb(AES256_Context* ctx, uint8_t* buf);
};

#endif // DECRYPTION_H

//****************************************************************************************************
