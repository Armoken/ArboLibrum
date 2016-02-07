/*****************************************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████  (c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************************************/

#include "../include/writeorg.h"

//****************************************************************************************************

void WriteOrg::writeNote(Note* note) {
	const string orgDir = "./Org/";

	if (note != NULL && note->getType() == tRoot)
	{
		string filename = orgDir + note->getPath();
		ofstream out(filename, ios_base::trunc);

		string level = "*";
		string text = WriteOrg::addSpaces(note->getText(), level);
		out << level << " " << text << endl;
		if (note->getCount() != 0)
		{
			write(note, filename, level);
		}
		out.close();
	}
}

void WriteOrg::write(Note* note, string filename, string level)
{
	ofstream out(filename, ios_base::app);
	string text = "";
	level += "*";

	for (int i = 0; i < note->getCount(); i++)
	{
		text = WriteOrg::addSpaces(note->getNote(i)->getText(), level);
		out << level << " " << text << endl;
		string content = WriteOrg::loadContent(note->getNote(i));
		out << content;
		if (note->getNote(i)->getCount() != 0)
		{
			WriteOrg::write(note->getNote(i), filename, level);
		}
	}
	out.close();
}

//****************************************************************************************************

string WriteOrg::loadContent(Note* note)
{
	string content = "";

	if (note->getType() == tText)
	{
		content = "";
	}
	else if (note->getType() == tPicture)
	{
		content = note->getPath();
	}
	return content;
}

//****************************************************************************************************

string WriteOrg::addSpaces(string content, string level)
{
	string result = content;
	string spaces = "";
	string endl = "\n";
	size_t found;

	for (int i = 0; i < level.size() + 1; i++)
		spaces += " ";
	found = result.find(endl);
	while (found != string::npos)
	{
		result.replace(found, endl.length(), endl + spaces);
		found = result.find(endl.c_str(), found + 1);
	}
	return result;
}

//****************************************************************************************************
