#include "../include/writeorg.h"

void WriteOrg::writeNote(Note* note) {
	if (note != NULL && note->getType() == tRoot)
	{
		string filename = note->getText();
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
	level += "*";
	for (int i = 0; i < note->getCount(); i++)
	{
		out << level << " " << note->getNote(i)->getText() << endl;
		string content = WriteOrg::loadContent(note->getNote(i));
		out << content << endl;
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

	if (note-> getType() == tText)
	{
		ifstream in(note->getPath().c_str());
		string line;

		while (getline(in, line))
		{
			content += line + "\n";
		}
	}
	else if (note->getType() == tPicture)
	{
		content = note->getPath();
	}
	return content;
}
