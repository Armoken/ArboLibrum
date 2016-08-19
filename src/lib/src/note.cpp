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

#include "../include/note.hpp"

//****************************************************************************

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

bool Note::setText(string text)
{
	if (text != "")
	{
		text = text;
		return true;
	}
	return false;
}

string Note::getText()
{
	return text;
}

bool Note::setPath(string path)
{
	if (path != "")
	{
		path = path;
		return true;
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

bool Note::addNote(string text, NoteTypes noteType)
{
	notes.push_back(new Note(text, noteType));
	return true;
}

bool Note::addNote(string text, string path, NoteTypes noteType)
{
	Note* newNote = new Note(text, noteType);
	newNote->setPath(path);
	notes.push_back(newNote);
	return true;
}

bool Note::addNote(string text, NoteTypes noteType, list<int> pathToNote)
{
	if (pathToNote.size() == 0)
	{
		notes.push_back(new Note(text, noteType));
		return true;
	}

	int firstNodeOfPath = pathToNote.front();
	pathToNote.pop_front();
	if (getCount() - 1 < firstNodeOfPath)
	{
		return false;
	}
	return notes[firstNodeOfPath]->addNote(text, noteType, pathToNote);
}

bool Note::addNote(string text, string path,
	NoteTypes noteType, list<int> pathToNote)
{
	if (pathToNote.size() != 0)
	{
		notes.push_back(new Note(text, noteType));
		notes.back()->setPath(path);
		return true;
	}

	int firstNodeOfPath = pathToNote.front();
	pathToNote.pop_front();
	if (getCount() - 1 < firstNodeOfPath)
	{
		return false;
	}
	return notes[firstNodeOfPath]->addNote(text, path, noteType, pathToNote);
}

Note* Note::getNote(int number)
{
	return notes[number];
}

Note* Note::getNote(int number, list<int> pathToNote)
{
	if (pathToNote.size() == 0)
	{
		return notes[number];
	}

	int firstNodeOfPath = pathToNote.front();
	pathToNote.pop_front();
	if (getCount() - 1 < firstNodeOfPath)
	{
		return NULL;
	}
	return notes[firstNodeOfPath]->getNote(number, pathToNote);
}

bool Note::removeNote(int number)
{
	if (getCount() - 1 < number)
	{
		return false;
	}

	notes.erase(notes.begin() + number);
	return true;
}

bool Note::removeNote(int number, list<int> pathToNote)
{
	if (pathToNote.size() == 0)
	{
		return removeNote(number);
	}

	int firstNodeOfPath = pathToNote.front();
	pathToNote.pop_front();
	if (getCount() - 1 < firstNodeOfPath)
	{
		return false;
	}
	return notes[firstNodeOfPath]->removeNote(number, pathToNote);
}

bool Note::removeNote(list<int> pathToNote)
{
	if (pathToNote.size() == 1)
	{
		return removeNote(pathToNote.front());
	}

	int firstNodeOfPath = pathToNote.front();
	pathToNote.pop_front();
	if (getCount() - 1 < firstNodeOfPath)
	{
		return false;
	}
	return notes[firstNodeOfPath]->removeNote(pathToNote);
}
