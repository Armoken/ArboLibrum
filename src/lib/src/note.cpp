/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#include "../include/note.h"

using namespace std;

//****************************************************************************************************

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
}

//****************************************************************************************************

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

//****************************************************************************************************

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

//****************************************************************************************************

int Note::getCount()
{
	return notes.size();
}

//****************************************************************************************************

NoteTypes Note::getType()
{
	return (NoteTypes)this->noteType;
}

//****************************************************************************************************

bool Note::addNote(string _text, NoteTypes _noteType)
{
	notes.push_back(new Note(_text, _noteType));
	return true;
}

bool Note::addNote(string _text, string _path, NoteTypes _noteType)
{
	Note* newNote = new Note(_text, _noteType);
	newNote->setPath(_path);
	notes.push_back(newNote);
	return true;
}

bool Note::addNote(string _text, NoteTypes _noteType, list<int> _pathToNote)
{
	if (_pathToNote.size() == 0)
	{
		notes.push_back(new Note(_text, _noteType));
		return true;
	}
	else
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		if ((int)notes.size() - 1 < firstNodeOfPath) // Compare number of last element of array with number of node of path
		{
			return false;
		}
		else
		{
			return notes[firstNodeOfPath]->addNote(_text, _noteType, _pathToNote);
		}
	}
}

bool Note::addNote(string _text, string _path, NoteTypes _noteType, list<int> _pathToNote)
{
	if (_pathToNote.size() != 0)
	{
		notes.push_back(new Note(_text, _noteType));
		notes.back()->setPath(_path);
		return true;
	}
	else
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		if ((int)notes.size() - 1 < firstNodeOfPath)
		{
			return false;
		}
		else
		{
			return notes[firstNodeOfPath]->addNote(_text, _path, _noteType, _pathToNote);
		}
	}
}

//****************************************************************************************************

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
		if ((int)notes.size() - 1 < firstNodeOfPath)
		{
			return NULL;
		}
		else
		{
			return notes[firstNodeOfPath]->getNote(_number, _pathToNote);
		}
	}
}

//****************************************************************************************************

bool Note::removeNote(int _number)
{
	if ((int)notes.size() - 1 < _number)
	{
		return false;
	}
	else
	{
		notes.erase(notes.begin() + _number);
		return true;
	}
}

bool Note::removeNote(int _number, list<int> _pathToNote)
{
	if (_pathToNote.size() == 0)
	{
		return removeNote(_number);
	}
	else
	{
		int firstNodeOfPath = _pathToNote.front();
		_pathToNote.pop_front();
		if ((int)notes.size() - 1 < firstNodeOfPath)
		{
			return false;
		}
		else
		{
			return notes[firstNodeOfPath]->removeNote(_number, _pathToNote);
		}
	}
}

//****************************************************************************************************