/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#ifndef NOTE_H
#define NOTE_H

//****************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

//****************************************************************************************************

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

	Note(string _text, NoteTypes _noteType);
	~Note();

	// Get inner note by number
	Note* operator[](int i)
	{
		return notes[i];
	}

	// Set/get note's content
	bool setText(string _text);
	string getText();

	// Set/get path to note's content file
	bool setPath(string _path);
	string getPath();

	// Returns notes' size
	int getCount();

	// Get type of current note
	NoteTypes getType();

	// Add new note to inner array
	// The _path to the Note is an array of int, which show position of Note in notes array
	bool addNote(string _text, NoteTypes _noteType);
	bool addNote(string _text, string _path, NoteTypes _noteType);
	bool addNote(string _text, NoteTypes _noteType, list<int> _pathToNote);
	bool addNote(string _text, string _path, NoteTypes _noteType, list<int> _pathToNote);

	// Get note from inner array by it's number
	Note* getNote(int _number); 
	Note* getNote(int _number, list<int> _pathToNote);

	// Remove current note and additional content file
	bool removeNote(int _number);
	bool removeNote(int _number, list<int> _pathToNote);
};
#endif // NOTE_H

//****************************************************************************************************
