/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#ifndef READORG_H
#define READORG_H

//****************************************************************************************************

#include <iostream>
#include <fstream>
#include "note.h"

using namespace std;

//****************************************************************************************************

class ReadOrg
{
 public:

	 // Reading note from orgmode-like file
	 static Note* readNote(string noteOrg);

	 // Loading orgmode-like file's content
	 static string loadOrgFile(string filename);

	 // Splitting strings by delimiters
	 static vector<string> split(const string& s, const string& delim, const bool keep_empty = true);

	 // Trimming strings
	 static string trim(string &str);
};

#endif // READORG_H

//****************************************************************************************************
