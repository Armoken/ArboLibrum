#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <stdexcept>
#include "lib/include/note.h"
#include "lib/include/writeorg.h"

using namespace std;

int treeTravel (Note *rootNote, int level)
{
	int elCount = rootNote->getCount();
	if (level == 0)
	{
		cout << "\n Filename: " << rootNote->getText() << endl;
	}
	else
	{
		cout << std::string(level, '*') << " " << rootNote->getText() << endl;
	}

	for (int i = 0; i < elCount; i++)
	{
		treeTravel((*rootNote)[i], level + 1);
	}
	return 0;
}

list<int> parseTextPath(string textPath)
{
	list<int> numPath;
	int convertedEl;
    string buf; // Have a buffer string
    stringstream iss(textPath); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words

    while (iss >> buf)
	{
        tokens.push_back(buf);
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		try
		{
			numPath.push_back(stoi(tokens[i]));
		}
		catch (invalid_argument &x)
		{
			cout << "Cant convert!" << endl;
			numPath.clear();
			break;
		}
	}
	return numPath;
}

int main() /* Pseudo UI */
{
	Note *rootNote;
	bool isAlive = true;
	while (isAlive)
	{
		int selection;
		cout << "0) Quit" << endl;
		cout << "1) Create note" << endl;
		cout << "2) Rename note" << endl;
		cout << "3) Create new node" << endl;
		cout << "4) Delete node" << endl;
		cout << "5) Show all notes" << endl;
		cout << "6) Save note to file" << endl;

		cin >> selection;
		string filename;
		string textPath;
		string textSelectedElement;
		int selectedElement;
		list<int> path;
		switch (selection)
		{
		case 0:
			isAlive = false;
			break;
		case 1:
			cout << "Please, enter filename: ";
			cin.ignore();
			getline(cin, filename);
			rootNote = new Note(filename, tRoot);
			break;
		case 2:
			cout << "Please, enter new filename: ";
			cin.ignore();
			getline(cin, filename);
			rootNote->setText(filename);
			break;
		case 3:
			cout << "Please, enter path to new note: ";
			cin.ignore();
			getline(cin, textPath);
			path = parseTextPath(textPath);
			rootNote->addNote("bimbom", tRoot, path);
			break;
		case 4:
			cout << "Please, enter path to note and number of element to delete: ";
			cin.ignore();
			getline(cin, textPath);
			path = parseTextPath(textPath);
			getline(cin, textSelectedElement);
			try
			{
				selectedElement = stoi(textSelectedElement);
			}
			catch (invalid_argument &x)
			{
				cout << "Cant convert!" << endl;
				break;
			}
			rootNote->removeNote(selectedElement, path);
			break;
		case 5:
			if (rootNote != NULL)
			{
				treeTravel(rootNote, 0);
			}
			else
			{
				cout << "Please, create file for note!";
			}
			break;
		case 6:
			WriteOrg::writeNote(rootNote);
			break;
		}
	}
	return 0;
}
