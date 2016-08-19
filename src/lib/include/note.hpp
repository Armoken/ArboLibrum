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

#ifndef NOTE_HPP
#define NOTE_HPP

//****************************************************************************

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

//****************************************************************************

// Available note types
enum NoteTypes
{
	tRoot,
	tText,
	tPicture,
	tCheckbox
};

class Note
{
private:
	string text;
	string path; /* Path to note's content */
	NoteTypes noteType;  /* Meaning of the text block */
	bool checkState; /* State for checkbox */
	Note* parentNote; /* Reference to a parent note */

public:
	vector<Note*> notes; /* Array of notes */

	Note(string text, NoteTypes noteType);
	~Note();

	// Get inner note by number
	Note* operator[](int i)
	{
		return notes[i];
	}

	// Set/get note's content
	bool setText(string text);
	string getText();

	// Set/get path to note's content file
	bool setPath(string path);
	string getPath();

	// Returns notes' size
	int getCount();

	// Get type of current note
	NoteTypes getType();

	// Add new note to inner array
	// The path to the Note is an array of int, which show position of Note in notes array
	bool addNote(Note* note);
	bool addNote(string text, NoteTypes noteType);
	bool addNote(string text, string path, NoteTypes noteType);
	bool addNote(string text, NoteTypes noteType, list<int> pathToNote);
	bool addNote(string text, string path, NoteTypes noteType, list<int> pathToNote);

	// Get note from inner array by it's number
	Note* getNote(int number);
	Note* getNote(int number, list<int> pathToNote);

	// Remove current note and additional content file
	bool removeNote(int number);
	bool removeNote(int number, list<int> pathToNote);
	bool removeNote(list<int> pathToNote);
};

#endif // NOTE_HPP

//****************************************************************************
