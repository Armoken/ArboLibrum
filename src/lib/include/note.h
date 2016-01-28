#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Note
{
private:
	string title; /*Note's title*/
	string path; /*Path to note's content*/
	bool isCheckbox; /*If note contain checkboxes*/
	bool isRootNote; /*If note is not located in vector*/
	int noteType; /*Type of note*/
	Note* parentNote; /*Reference to a parent note*/
	vector<Note*> notes; /*Array of notes*/

public:
	enum types /*Available note types*/
	{
		root = 1, // Note is root
		text = 2, // Note contains text
		pic = 3 // Note contains picture
	};
	Note(string _path, types _noteType); /*Constructor*/
	~Note(); /*Destructor*/
	bool setTitle(string _title); /*Set note's title*/
	string getTitle(); /*Get note's title*/
	bool setPath(string _path); /*Set path to note's content*/
	string getPath(); /*Get path to note's content*/
	types getType(); /*Get type of current note*/
	Note* getNote(int _number); /*Get note from inner array by it's number*/
	void addNote(string _title, string _path, types _noteKind); /*Add new note to inner array*/
	void removeNote(); /*Remove current note and additional content file*/
	static void loadContent(Note* &note); /*Load content from file into note*/
	static void showNote(Note* &note); /*Print title and content (for debugging)*/
};
#endif // NOTE_H
