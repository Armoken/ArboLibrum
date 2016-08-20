/*****************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████

(c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************/

#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

//****************************************************************************

#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "note.hpp"

using namespace std;

//****************************************************************************

class Serializer
{
public:
	static bool writeNote(Note* note, string path);

	// File can be in current dir or in ./Org dir or somewhere else
	static string findFile(string filename);

	static string loadNoteFile(string filename);

	// Reading note from html-like file
	static Note* parseNoteFile(string noteOrg);
};

#endif // SERIALIZATION_HPP

//****************************************************************************
