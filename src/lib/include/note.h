#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
  vector<Note*> notes; /*Array of notes*/

 public:
  Note(string _text, NoteTypes _noteType);
  ~Note();

  Note* operator[](int i)
  {
	return notes[i];
  }

  bool setText(string _title);
  string getText();

  bool setPath(string _path);
  string getPath();

  int getCount(); /* Return vector notes size */
  NoteTypes getType(); /*Get type of current note*/

  /* Add new note to inner array. The _path to the Note is an array of int, which show position of Note in notes array. */
  void addNote(string _text, NoteTypes _noteType);
  void addNote(string _text, string _path, NoteTypes _noteType);
  void addNote(string _text, NoteTypes _noteType, vector<int> _pathToNote);
  void addNote(string _text, string _path, NoteTypes _noteType, vector<int> _pathToNote);

  Note* getNote(int _number); /*Get note from inner array by it's number*/
  Note* getNote(int _number, vector<int> _pathToNote);

  void removeNote(); /*Remove current note and additional content file*/

  static void loadContent(Note* &note); /*Load content from file into note*/
  static void showNote(Note* &note); /*Print title and content (for debugging)*/
};
#endif // NOTE_H
