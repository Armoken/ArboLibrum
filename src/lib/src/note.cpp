#include "../include/note.h"

using namespace std;

Note::Note(string _text, NoteTypes _noteType)
{
	text = _text;
	noteType = _noteType;
}

Note::~Note()
{
	if (notes.size() != 0)
	{
		notes.clear();
	}
	delete this;
}

bool Note::setText(string _text)
{
	if (_text != "")
	{
		text = _text;
		return true;
	}
	return false;
}

string Note::getText()
{
	return text;
}

bool Note::setPath(string _path)
{
	if (noteType != tRoot || noteType != tText)
	{
		if (_path != "")
		{
			path = _path;
			return true;
		}
	}
	return false;
}

string Note::getPath()
{
	return path;
}

int Note::getCount()
{
	return notes.size();
}

NoteTypes Note::getType()
{
	return (NoteTypes)this->noteType;
}



void Note::addNote(string _text, NoteTypes _noteType)
{
	notes.push_back(new Note(_text, _noteType));
}

void Note::addNote(string _text, string _path, NoteTypes _noteType)
{
	Note* newNote = new Note(_text, _noteType);
	newNote->setText(_path);
	notes.push_back(newNote);
}

void Note::addNote(string _text, NoteTypes _noteType, list<int> _pathToNote)
{
	if (_pathToNote.size() != 0)
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		notes[firstNodeOfPath]->addNote(_text, _noteType, _pathToNote);
	}
	else
	{
		notes.push_back(new Note(_text, _noteType));
	}
}

void Note::addNote(string _text, string _path, NoteTypes _noteType, list<int> _pathToNote)
{
	if (_pathToNote.size() != 0)
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		notes[firstNodeOfPath]->addNote(_text, _path, _noteType, _pathToNote);
	}
	else
	{
		notes.push_back(new Note(_text, _noteType));
		notes.back()->setPath(_path);
	}
}




Note* Note::getNote(int _number)
{
	return notes[_number];
}

Note* Note::getNote(int _number, list<int> _pathToNote)
{
	if (_pathToNote.size() == 0)
	{
		return notes[_number];
	}
	else
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		return notes[firstNodeOfPath]->getNote(_number, _pathToNote);
	}
}

void Note::removeNote(int _number)
{
	notes.erase(notes.begin() + _number);
}

void Note::removeNote(int _number, list<int> _pathToNote)
{
	if (_pathToNote.size() == 0)
	{
		notes.erase(notes.begin() + _number);
	}
	else
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		notes[firstNodeOfPath]->removeNote(_number, _pathToNote);
	}
}
