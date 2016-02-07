#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

enum NoteTypes /*Available note types*/
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
	string path; /*Path to note's content*/
	NoteTypes noteType;  /*Meaning of the text block*/
	bool checkState; /* State for checkbox */
	Note* parentNote; /*Reference to a parent note*/

public:
	vector<Note*> notes; /*Array of notes*/

	Note(string _text, NoteTypes _noteType);
	~Note();

	Note* operator[](int i)
	{
		return notes[i];
	}

	bool setText(string _text);
	string getText();

	bool setPath(string _path);
	string getPath();

	int getCount(); /* Return vector notes size */
	NoteTypes getType(); /*Get type of current note*/

	/* Add new note to inner array. The _path to the Note is an array of int, which show position of Note in notes array. */
	void addNote(string _text, NoteTypes _noteType);
	void addNote(string _text, string _path, NoteTypes _noteType);
	void addNote(string _text, NoteTypes _noteType, list<int> _pathToNote);
	void addNote(string _text, string _path, NoteTypes _noteType, list<int> _pathToNote);

	Note* getNote(int _number); /*Get note from inner array by it's number*/
	Note* getNote(int _number, list<int> _pathToNote);

	void removeNote(int _number); /*Remove current note and additional content file*/
	void removeNote(int _number, list<int> _pathToNote);
};
#endif // NOTE_H
