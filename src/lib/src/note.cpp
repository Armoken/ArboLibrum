#include "../include/note.h"

using namespace std;

Note::Note(string _text, NoteTypes _noteType)
{
	text = _text;
	noteType = _noteType;
}

Note::~Note()
{
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

void Note::addNote(string _text, NoteTypes _noteType, vector<int> _pathToNote)
{
	if (_pathToNote.size() != 0)
	{
		int firstNodeOfPath = _pathToNote[0];
		_pathToNote.erase(_pathToNote.begin());
		notes[firstNodeOfPath]->addNote(_text, _noteType, _pathToNote);
	}
	else
	{
		notes.push_back(new Note(_text, _noteType));
	}
}

void Note::addNote(string _text, string _path, NoteTypes _noteType, vector<int> _pathToNote)
{
	Note *nodeForNote = this;
	for (int i = 0; i < _pathToNote.size(); i++)
	{
		nodeForNote = nodeForNote->getNote(_pathToNote[i]);
	}
	nodeForNote->addNote(_text, _path, _noteType);
}




Note* Note::getNote(int _number)
{
	return notes[_number];
}

Note* Note::getNote(int _number, vector<int> _pathToNote)
{
	Note *returnNote = this;
	for (int i = 0; i < _pathToNote.size(); i++)
	{
		returnNote = returnNote->getNote(_pathToNote[i]);
	}
	return returnNote;
}

void Note::removeNote()
{
	remove(this->path.c_str());
	this->~Note();
}
