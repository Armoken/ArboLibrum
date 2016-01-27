#include "writeorg.h"

void WriteOrg::writeNote(Note* &note) {

}

string WriteOrg::loadContent(Note* &note) {
	string content = "";

	if (note->getType() == Note::types::text) {
		ifstream in(note->getPath());
		string line;

		while (getline(in, line))
		{
			content += line + "\n";
		}
	}
	else if (note->getType() == Note::types::pic) {
		content = note->getPath();
	}
	return content;
}
