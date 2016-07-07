/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█  
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

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

//****************************************************************************************************

int treeTravel(Note* rootNote, int level)
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

//****************************************************************************************************

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

//****************************************************************************************************

int main() /* Pseudo UI */
{
	Note* rootNote;
	bool isAlive = true;
	bool isInit = false;
	while (isAlive)
	{
		int selection;

		cout << "\n\n\n" << endl;
		if (isInit)
		{
			treeTravel(rootNote, 0);
		}

		cout << "\n" << endl;
		cout << "0) Quit" << endl;
		cout << "1) Create note" << endl;
		cout << "2) Rename note" << endl;
		cout << "3) Create new node" << endl;
		cout << "4) Delete node" << endl;
		cout << "5) Save note to file" << endl;
		cout << "\n" << endl;

		cin >> selection;

		string name;
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
			if (!isInit)
			{
				cout << "Please, enter name: ";
				cin.ignore();
				getline(cin, name);
				rootNote = new Note(name, tRoot);
				filename = name + ".org";
				rootNote->setPath(filename);
				isInit = true;
			}
			else
			{
				cout << "This is already init!" << endl;
			}
			break;
		case 2:
			if (isInit)
			{
				cout << "Please, enter new filename: ";
				cin.ignore();
				getline(cin, name);
				rootNote->setText(name);
				filename = name + ".org";
				rootNote->setPath(filename);
			}
			else
			{
				cout << "Please, create new note!" << endl;
			}
			break;
		case 3:
			if (isInit)
			{
				cout << "Please, enter path to new note: ";
				cin.ignore();
				getline(cin, textPath);
				path = parseTextPath(textPath);
				if (!rootNote->addNote("This is example of text for testing work of the NEW STEP in world's notes editor direction!\nTRY AND ENJOY IT!!!\n________ArboLibrum________\n...\nIt's goddamn cool!", tText, path))
				{
					cout << "Wrong path!" << endl;
				}
			}
			else
			{
				cout << "Please, create new note!" << endl;
			}
			break;
		case 4:
			if (isInit)
			{
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
					cout << "Can't convert!" << endl;
					break;
				}

				if (selectedElement == -1)
				{
					string filepath = "./Org/" + rootNote->getPath();
					if (remove(filepath.c_str()))
					{
						cout << "File " << rootNote->getText() << " does not exists!";
					}
					delete rootNote;
					isInit = false;
				}
				else if (!rootNote->removeNote(selectedElement, path))
				{
					cout << "This note is absent." << endl;
				}
			}
			else
			{
				cout << "Please, create new note!" << endl;
			}
			break;
		case 5:
			if (isInit)
			{
				WriteOrg::writeNote(rootNote);
			}
			else
			{
				cout << "Please, create new note!" << endl;
			}
			break;
		}
	}
	return 0;
}

//****************************************************************************************************
