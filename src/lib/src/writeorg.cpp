#include "../include/writeorg.h"

void WriteOrg::writeNote(Note* &note) {}

string WriteOrg::loadContent(Note* &note)
{
  string content = "";

  if (note-> getType() == Note::text)
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
