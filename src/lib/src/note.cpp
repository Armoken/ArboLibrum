#include "note.h"

using namespace std;

Note::Note(string _path, types _noteType)
{
	path = _path;
	noteType = _noteType;
}

Note::~Note()
{
//	if (this != NULL)
//		delete this;
}

bool Note::setTitle(string _title)
{
	if (_title != "")
	{
		title = _title;
		return true;
	}
	return false;
}

string Note::getTitle()
{
	return title;
}

bool Note::setPath(string _path)
{
	if (_path != "")
	{
		path = _path;
		return true;
	}
	return false;
}

string Note::getPath()
{
	return path;
}

Note::types Note::getType()
{
	return (Note::types)this->noteType;
}

void Note::addNote(string _title, string _path, types _noteKind)
{
	Note* newNote = new Note(_path, _noteKind);
	newNote->setTitle(_title);
	notes.push_back(newNote);
}

void Note::addNote(Note* newNote)
{
	notes.push_back(newNote);
}

void Note::removeNote()
{
	remove(this->path.c_str());
	this->~Note();
}

Note* Note::getNote(int _number)
{
	return notes[_number];
}
