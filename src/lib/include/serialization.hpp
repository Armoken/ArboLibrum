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
	struct RemoveDelimiter
	{
		bool operator()(char c)
		{
			return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
		}
	};

	class Cursor
	{
	public:
		int pos = 0;
		string tag = "";
		bool isClosing = false;
	};

	static Cursor* getTag(string arbml_doc, Cursor* cursor);
	static pair<string, Cursor*> getContent(string arbml_doc, Cursor* cursor);

	// Replacing one substring to another
	static string replaceSubstr(string str, const string& from, const string& to);

	// Replace special symbols to their mnemonics
	static string decorateSymbols(string line);

	// Replace mnemonics to according special symbols
	static string undecorateSymbols(string line);

	/*---SAVING---*/

	// Save a note to .arbml file
	static bool writeNote(Note* note, string path);

	// Get text representation of note's type for arbml tag
	static string getTagType(NoteTypes type);

	// Converting note into an arbml format
	static string serialize(Note* rootNote);
	static string serialize(Note* note, NoteTypes type, string level);

	/*---LOADING---*/

	// File can be in current dir or in ./Org dir or somewhere else
	static string findFile(string filename);

	static string loadNoteFile(string filename);

	// Reading note from html-like file
	static Note* parseNoteFile(string noteOrg);
	static Note* parse(string content);

	static string clearWhitespace(string content);
};

#endif // SERIALIZATION_HPP

//****************************************************************************
