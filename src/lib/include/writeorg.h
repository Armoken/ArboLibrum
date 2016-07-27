/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#ifndef WRITEORG_H
#define WRITEORG_H

//****************************************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include "note.h"
#include "encryption.h"

using namespace std;

//****************************************************************************************************

class WriteOrg
{
public:

	// Writing note to file in orgmode-like representation
	static void writeNote(Note* note, Encryption encryptor);
	static string write(Note* note, string oldcontent, string level);

	// Loading content from note
	static string loadContent(Note* note);

	// Adding spaces after new line symbols ("\n")
	static string addSpaces(string line, string level);
};

#endif // WRITEORG_H

//****************************************************************************************************
