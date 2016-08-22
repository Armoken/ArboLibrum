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

#include "../include/serialization.hpp"

//****************************************************************************

string indent = "    ";

bool Serializer::writeNote(Note* note, string path)
{
	// Just for test
	path = "./Notes/" + note->getText() + ".arbml";
	string content = Serializer::serialize(note);

	if (!content.empty())
	{
		ofstream out(path, ios_base::trunc);
		//TODO: Add encryption before saving
		out << content;
		out.close();

		return true;
	}

	return false;
}

string Serializer::getTagType(NoteTypes type)
{
	if (type == tRoot) return "root";
	else if (type == tText) return "text";
	else if (type == tPicture) return "picture";
	else return "unknown";
}

string Serializer::replaceSubstr(string str, const string& from, const string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

string Serializer::decorateSymbols(string line)
{
	line = replaceSubstr(line, string(" "), string("&nbsp;"));
	line = replaceSubstr(line, string("<"), string("&lt;"));
	line = replaceSubstr(line, string(">"), string("&gt;"));
	line = replaceSubstr(line, string("\n"), string("&nl;"));
	line = replaceSubstr(line, string("\t"), string("&tb;"));
	line = replaceSubstr(line, string("\r"), string("&rr;"));
	return line;
}

string Serializer::serialize(Note* rootNote)
{
	if (rootNote->getType() != tRoot)
		return string();

	string arbml_doc("");
	string level(indent + indent);

	arbml_doc += "<note>\n";
	arbml_doc += indent + "<" + getTagType(rootNote->getType()) + ">\n";

	arbml_doc += level + "<title>\n";
	arbml_doc += level + indent + Serializer::decorateSymbols(rootNote->getText()) + "\n";
	arbml_doc += level + "</title>\n";

	if (rootNote->getCount() != 0)
	{
		arbml_doc += level + "<nodes>\n";

		for (auto note : rootNote->notes)
		{
			arbml_doc += Serializer::serialize(note, note->getType(), level);
		}

		arbml_doc += level + "</nodes>\n";
	}

	arbml_doc += indent + "</" + getTagType(rootNote->getType()) + ">\n";
	arbml_doc += "</note>";

	return arbml_doc;
}

string Serializer::serialize(Note* note, NoteTypes type, string level)
{
	string arbml_doc("");
	string innerLevel = level + indent;

	arbml_doc += innerLevel + "<" + getTagType(type) + ">\n";

	innerLevel += indent;

	arbml_doc += innerLevel + "<content>\n";
	arbml_doc += innerLevel + indent + Serializer::decorateSymbols(note->getText()) + "\n";
	arbml_doc += innerLevel + "</content>\n";

	if (note->getCount() != 0)
	{
		arbml_doc += innerLevel + "<nodes>\n";

		for (auto innerNote : note->notes)
		{
			arbml_doc += serialize(innerNote, innerNote->getType(), innerLevel);
		}

		arbml_doc += innerLevel + "</nodes>\n";
	}

	arbml_doc += level + indent + "</" + getTagType(type) + ">\n";

	return arbml_doc;
}
