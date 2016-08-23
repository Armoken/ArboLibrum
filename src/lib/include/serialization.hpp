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

	// String delimiters to remove
	struct RemoveDelimiter
	{
		bool operator()(char c)
		{
			return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
		}
	};

	// Parsing cursor
	class Cursor
	{
	public:
		int pos = 0; /* Position in document (line) */
		string tag = ""; /* The nearest tag, inside of which there is a cursor */
		bool isClosing = false; /* Whether tag is closing */
	};

	// Get next tag in document (line)
	static Cursor* getTag(string arbml_doc, Cursor* cursor);

	// Get note's content enclosed in tags
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

	// Convert note into an arbml format
	static string serialize(Note* rootNote);
	static string serialize(Note* note, NoteTypes type, string level);

	/*---LOADING---*/

	// File can be in current dir or in ./Org dir or somewhere else
	static string findFile(string filename);

	// Load file's content
	static string loadNoteFile(string filename);

	// Read note from html-like file
	static Note* parseNoteFile(string noteOrg);
	static vector<Note*> parse(string arbml_doc, Cursor* cursor);

	// Remove string delimiters
	static string clearWhitespace(string content);
};

#endif // SERIALIZATION_HPP

//****************************************************************************
