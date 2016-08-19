/******************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████

(c) ArboLibrum, 2016. All rights reserved.

******************************************************************************/

#include <map>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "lib/include/note.hpp"
#include "lib/include/readnote.hpp"
#include "lib/include/writenote.hpp"

using namespace std;

typedef pair<bool, Note *> (*actionFunc)(Note *note);

string input(bool isNeedEndline)
{
	string text;
	getline(cin, text);
	if (isNeedEndline)
	{
		cout << endl;
	}
	return text;
}

void treeTravel(Note* rootNote, int level)
{
	if (rootNote != NULL)
	{
		cout << string(level, '*') << " " << rootNote->getText() << endl;
		for (auto note: rootNote->notes)
		{
			treeTravel(note, level + 1);
		}
	}
}

list<int> tokensToNumbers(vector<string> tokens)
{
	list<int> numbers;
	for (auto token: tokens)
	{
		try
		{
			numbers.push_back(boost::lexical_cast<int>(token));
		}
		catch(boost::bad_lexical_cast const&)
		{
			cout << "Error: input string was not valid" << endl;
			break;
		}
	}
	return numbers;
}

list<int> parseTextPath(string textPath)
{
	textPath = boost::trim_copy(textPath);
	if (textPath == "")
	{
		return list<int>();
	}
	else
	{
		vector<string> tokens;
		boost::iter_split(tokens, textPath, boost::first_finder(" "));
		return tokensToNumbers(tokens);
	}
}

pair<bool, Note *> createNote(Note *note)
{
	cout << "Please, enter name: ";
	string name = input(true);
	note = new Note(name, tRoot);
	return make_pair(false, note);
}

pair<bool, Note *> quitProgram(Note *note)
{
	return make_pair(false, note);
}

pair<bool, Note *> readNoteFromFile(Note *note)
{
	cout << "Enter note's filename: ";
	note = ReadNote::parseNoteFile(input(true));
	if (note != nullptr)
	{
		cout << "Note loaded!" << endl;
		return make_pair(true, note);
	}
	cout << "Wrong path!" << endl;
	return make_pair(false, note);
}

pair<bool, Note *> renameNote(Note *note)
{
	cout << "Please, enter new filename: ";
	string name = input(true);
	note->setText(name);
	return make_pair(true, note);
}

pair<bool, Note *> createNode(Note *note)
{
	cout << "Please, enter path to new note: ";
	string textPath = input(true);
	auto path = parseTextPath(textPath);

	cout << "Please, enter node's text: ";
	string text = input(true);
	if (not note->addNote(text, tText, path))
	{
		cout << "Wrong path!" << endl;
	}
	return make_pair(true, note);
}

pair<bool, Note *> removeNode(Note *note)
{
	cout << "Please, enter path to note, where"
		" last element is number to delete: ";
	string textPath = input(true);
	auto path = parseTextPath(textPath);

	if (path.size() != 0)
	{
		return make_pair(note->removeNote(path), note);
	}

	cout << "You can't delete root node!" << endl;
	return make_pair(true, note);
}

pair<bool, Note *> saveNoteToFile(Note *note)
{
	cout << "Please, input path for note saving: " << endl;
	if (WriteNote::writeNote(note, input(true)))
	{
		cout << "Note was successfully written!" << endl;
	}
	else
	{
		cout << "Note wasn't written!" << endl;
	}
	return make_pair(true, note);
}

pair<bool, Note *> callActionFunc(Note *note, map<int, actionFunc> actionDict)
{
	string actionNum = boost::trim_copy(input(true));
	try
	{
		auto selectedOption = boost::lexical_cast<unsigned int>(actionNum);
		if (actionDict.find(selectedOption) != actionDict.end())
		{
			return actionDict[selectedOption](note);
		}

		return make_pair(true, nullptr);
	}
	catch(boost::bad_lexical_cast const&)
	{
		cout << "Error: input string was not valid" << endl;
	}
}

Note* UI(map<int, actionFunc> actionDict, void (*UIFunc)(), Note *rootNote)
{
	bool isAlive = true;
	while (isAlive)
	{
		treeTravel(rootNote, 0);
		UIFunc();
		auto resultPair = callActionFunc(rootNote, actionDict);
		rootNote = resultPair.second;
		isAlive = resultPair.first;
	}
	return rootNote;
}

void printStartUI()
{
	cout << endl;
	cout << "0) Quit" << endl;
	cout << "1) Create note" << endl;
	cout << "2) Read note from file" << endl;
}

map<int, actionFunc> initStartActionDict()
{
	map<int, actionFunc> interfaceFunctions;
	interfaceFunctions[0] = &quitProgram;
	interfaceFunctions[1] = &createNote;
	interfaceFunctions[2] = &readNoteFromFile;
	return interfaceFunctions;
}

void printMainUI()
{
	cout << endl;
	cout << "0) Quit" << endl;
	cout << "1) Rename note" << endl;
	cout << "2) Create new node" << endl;
	cout << "3) Delete node" << endl;
	cout << "4) Save note to file" << endl;
}

map<int, actionFunc> initMainActionDict()
{
	map<int, actionFunc> interfaceFunctions;
	interfaceFunctions[0] = &quitProgram;
	interfaceFunctions[1] = &renameNote;
	interfaceFunctions[2] = &createNode;
	interfaceFunctions[3] = &removeNode;
	interfaceFunctions[4] = &saveNoteToFile;
	return interfaceFunctions;
}

int main()
{
	auto rootNote = UI(initStartActionDict(), &printStartUI, NULL);
	if (rootNote)
	{
		rootNote = UI(initMainActionDict(),&printMainUI, rootNote);
	}
	return 0;
}
