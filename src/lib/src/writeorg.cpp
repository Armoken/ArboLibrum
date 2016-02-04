#include "../include/writeorg.h"

void WriteOrg::writeNote(Note* note) {
	if (note != NULL && note->getType() == Note::types::root)
	{
		string filename = note->getPath();
		ofstream out(filename, ios_base::trunc);

		string level = "*";
		out << level << " " << note->getTitle() << endl;
		if (note->notes.size() != 0)
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
	for (int i = 0; i < note->notes.size(); i++)
	{
		out << level << " " << note->notes[i]->getTitle() << endl;
		string content = WriteOrg::loadContent(note->notes[i]);
		out << content << endl;
		if (note->notes[i]->notes.size() != 0)
		{
			write(note->notes[i], filename, level);
		}
	}
	out.close();
}

string WriteOrg::loadContent(Note* note)
{
	string content = "";

	if (note->getType() == Note::text)
	{
		ifstream in(note->getPath().c_str());
		string line;

		while (getline(in, line))
		{
			content += line + "\n";
		}
	}
	else if (note->getType() == Note::pic)
	{
		content = note->getPath();
	}
	return content;
}

