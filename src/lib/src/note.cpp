#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "note.h"

using namespace std;

Note::Note(string _path, types _noteType) {
	path = _path;
	noteType = _noteType;
}

bool Note::setTitle(string _title) {
	if (_title != "") {
		title = _title;
		return true;
	}
	return false;
}

string Note::getTitle() {
	return title;
}

bool Note::setPath(string _path) {
	if (_path != "") {
		path = _path;
		return true;
	}
	return false;
}

string Note::getPath() {
	return path;
}

void Note::addNote(string _title, string _path, types _noteKind) {
	Note* newNote = new Note(_path, _noteKind);
	newNote->setTitle(_title);
	notes.push_back(newNote);
}

//Maybe will be relocated to read/write classes
void Note::loadContent(Note* &note) {
	if (note->noteType == types::text || types::root) {
		ifstream in(note->path);
		string s, line;
		while (getline(in, line)) {
			s += line + "\n";
		}
		cout << s;
	}
}

int main() {
	Note* note = new Note("c:\\1.txt", Note::types::root);
	note->setTitle("NOTTTTEE");
	note->addNote("KEK", "", Note::types::text);
	cout << "Title: " << note->getTitle() << endl << endl << "Content:" << endl << endl;
	Note::loadContent(note);
	return 0;
}