#include "../include/writeorg.h"

void WriteOrg::writeNote(Note* note) {
	if (note != NULL && note->getType() == tRoot)
	{
		string filename = note->getPath();
		ofstream out(filename, ios_base::trunc);

		string level = "*";
		out << level << " " << note->getText() << endl;
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
		text = note->getNote(i)->getText();
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
