/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#include "../include/decryption.h"

//****************************************************************************************************

uint8_t Decryption::rj_xtime(uint8_t x)
{
	uint8_t y = (uint8_t)(x << 1);
	return (x & 0x80) ? (y ^ 0x1b) : y;
}

void Decryption::aes_subBytes_inv(uint8_t* buf)
{
	register uint8_t i = 16;

	while (i--)
		buf[i] = rj_sbox_inv(buf[i]);
}

void Decryption::aes_addRoundKey(uint8_t* buf, uint8_t* key)
{
	register uint8_t i = 16;

	while (i--)
		buf[i] ^= key[i];
}

void Decryption::aes_addRoundKey_cpy(uint8_t* buf, uint8_t* key, uint8_t* cpk)
{
	register uint8_t i = 16;

	while (i--)
	{
		buf[i] ^= (cpk[i] = key[i]);
		cpk[16 + i] = key[16 + i];
	}
}

void Decryption::aes_shiftRows_inv(uint8_t* buf)
{
	register uint8_t i, j;

	i = buf[1], buf[1] = buf[13], buf[13] = buf[9], buf[9] = buf[5], buf[5] = i;
	i = buf[2], buf[2] = buf[10], buf[10] = i;

	j = buf[3], buf[3] = buf[7], buf[7] = buf[11], buf[11] = buf[15], buf[15] = j;
	j = buf[6], buf[6] = buf[14], buf[14] = j;
}

void Decryption::aes_mixColumns_inv(uint8_t* buf)
{
	register uint8_t a, b, c, d, e, x, y, z;

	for (uint8_t i = 0; i < 16; i += 4)
	{
		a = buf[i];
		b = buf[i + 1];
		c = buf[i + 2];
		d = buf[i + 3];
		e = a ^ b ^ c ^ d;
		z = rj_xtime(e);
		x = e ^ rj_xtime(rj_xtime(z ^ a ^ c));
		y = e ^ rj_xtime(rj_xtime(z ^ b ^ d));
		buf[i] ^= x ^ rj_xtime(a ^ b);
		buf[i + 1] ^= y ^ rj_xtime(b ^ c);
		buf[i + 2] ^= x ^ rj_xtime(c ^ d);
		buf[i + 3] ^= y ^ rj_xtime(d ^ a);
	}
}

void Decryption::aes_expandDecKey(uint8_t* k, uint8_t* rc)
{
	for (uint8_t i = 28; i > 16; i -= 4)
	{
		k[i + 0] ^= k[i - 4];
		k[i + 1] ^= k[i - 3];
		k[i + 2] ^= k[i - 2];
		k[i + 3] ^= k[i - 1];
	}

	k[16] ^= rj_sbox(k[12]);
	k[17] ^= rj_sbox(k[13]);
	k[18] ^= rj_sbox(k[14]);
	k[19] ^= rj_sbox(k[15]);

	for (uint8_t i = 12; i > 0; i -= 4)
	{
		k[i + 0] ^= k[i - 4];
		k[i + 1] ^= k[i - 3];
		k[i + 2] ^= k[i - 2];
		k[i + 3] ^= k[i - 1];
	}

	*rc = FD(*rc);
	k[0] ^= rj_sbox(k[29]) ^ (*rc);
	k[1] ^= rj_sbox(k[30]);
	k[2] ^= rj_sbox(k[31]);
	k[3] ^= rj_sbox(k[28]);
}

//****************************************************************************************************

void Decryption::aes256_decrypt_ecb(AES256_Context *ctx, uint8_t *buf)
{
	uint8_t i, rcon;

	aes_addRoundKey_cpy(buf, ctx->deckey, ctx->key);
	aes_shiftRows_inv(buf);
	aes_subBytes_inv(buf);

	for (i = 14, rcon = 0x80; --i;)
	{
		if ((i & 1))
		{
			aes_expandDecKey(ctx->key, &rcon);
			aes_addRoundKey(buf, &ctx->key[16]);
		}
		else aes_addRoundKey(buf, ctx->key);
		aes_mixColumns_inv(buf);
		aes_shiftRows_inv(buf);
		aes_subBytes_inv(buf);
	}
	aes_addRoundKey(buf, ctx->key);
}

//****************************************************************************************************

