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

void WriteOrg::writeNote(Note* note, Encryption encryptor)
{
	const string orgDir = "./Org/";
	string content = "";

	if (note != NULL && note->getType() == tRoot)
	{
		string level = "*";
		string text = WriteOrg::addSpaces(note->getText(), level);

		content += level + " " + text + "\n";

		if (note->getCount() != 0)
		{
			content = write(note, content, level);
		}

		if (!content.empty())
		{
			string filename = orgDir + note->getPath();
			ofstream out(filename, ios_base::trunc);
			string encryptedContent = encryptor.encrypt(content);

			out << encryptedContent;
			out.close();
		}
	}
}

string WriteOrg::write(Note* note, string oldcontent, string level)
{
	if (note != NULL && note->getType() == tText)
	{
		string text = "";
		level += "*";

		for (int i = 0; i < note->getCount(); i++)
		{
			text = WriteOrg::addSpaces(note->getNote(i)->getText(), level);
			oldcontent += level + " " + text + "\n";
			string content = WriteOrg::loadContent(note->getNote(i)); // Maybe now it is useless
			oldcontent += content;
			if (note->getNote(i)->getCount() != 0)
			{
				oldcontent += WriteOrg::write(note->getNote(i), oldcontent, level);
			}
		}
	}
	else if (note != NULL && note->getType() == tPicture)
	{
		string pictureLink = "";
		level += "*";

		for (int i = 0; i < note->getCount(); i++)
		{
			pictureLink = "[[" + note->getNote(i)->getText + "][" + note->getNote(i)->getPath + "]";
			oldcontent += level + " " + pictureLink + "\n";
			if (note->getNote(i)->getCount() != 0)
			{
				oldcontent += WriteOrg::write(note->getNote(i), oldcontent, level);
			}
		}
	}

	return oldcontent;
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
