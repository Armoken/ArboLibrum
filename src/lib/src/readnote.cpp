/*****************************************************************************

███████████████████████████████████████████████████
█────█────█────██────█─███───█────██────█─█─█─███─█
█─██─█─██─█─██──█─██─█─████─██─██──█─██─█─█─█──█──█
█────█────█────██─██─█─████─██────██────█─█─█─█─█─█
█─██─█─█─██─██──█─██─█─████─██─██──█─█─██─█─█─███─█
█─██─█─█─██────██────█───█───█────██─█─██───█─███─█
███████████████████████████████████████████████████

(c) ArboLibrum, 2016. All rights reserved.

*****************************************************************************/

#include "../include/serialization.hpp"

//****************************************************************************

string Serializer::findFile(string filename)
{
	if (ifstream(filename))
	{
		return filename;
	}
	else if (ifstream("./Notes/" + filename))
	{
		return "./Notes/" + filename;
	}
	else
	{
		return string();
	}
}

string Serializer::loadNoteFile(string filename)
{
	string fullPathToFile = Serializer::findFile(filename);
	if (fullPathToFile.empty())
	{
		cout << "Such note does not exists!" << endl;
		return string();
	}

	ifstream inputFile(fullPathToFile);
	stringstream strStream;
	strStream << inputFile.rdbuf();
	return strStream.str();
}

Note* Serializer::parseNoteFile(string filename)
{
	// Just for test
	filename += "kek.arbml";

	auto content = Serializer::loadNoteFile(filename);
	if (content.empty())
	{
		return NULL;
	}
	content = clearWhitespace(content);
	Serializer::Cursor* cursor = new Serializer::Cursor();
	cursor = Serializer::getTag(content, cursor);
	if (cursor->tag != "note" | cursor->isClosing)
		return NULL;

	cursor = Serializer::getTag(content, cursor);
	if (cursor->tag != "root" |  cursor->isClosing)
		return NULL;

	Note* rootNote;

	cursor = Serializer::getTag(content, cursor);
	if (cursor->tag != "title" | cursor->isClosing)
		return NULL;
	else
	{
		pair<string, Serializer::Cursor*> title = Serializer::getContent(content, cursor);
		rootNote = new Note(Serializer::undecorateSymbols(title.first), tRoot);
		cursor = title.second;

		cursor = Serializer::getTag(content, cursor);
		if (cursor->tag != "title" | !cursor->isClosing)
			return NULL;
	}

	cursor = Serializer::getTag(content, cursor);
	if (cursor->tag == "nodes" & !cursor->isClosing)
	{
		//TODO: Parsing inner notes
		cursor = Serializer::getTag(content, cursor);
	}

	if (cursor->tag != "root" | !cursor->isClosing)
		return NULL;

	cursor = Serializer::getTag(content, cursor);
	if (cursor->tag != "note" | !cursor->isClosing)
		return NULL;

	return rootNote;
}

pair<string, Serializer::Cursor*> Serializer::getContent(string arbml_doc, Serializer::Cursor* cursor)
{
	if (arbml_doc[cursor->pos] != '>')
		return make_pair(nullptr, nullptr);

	int cur_pos = cursor->pos;
	while (arbml_doc[cur_pos] != '<') cur_pos++;
	string content = arbml_doc.substr(cursor->pos + 1, cur_pos - cursor->pos - 1);
	
	cursor->pos = cur_pos;

	pair<string, Serializer::Cursor*> result;
	result.first = content;
	result.second = cursor;

	return result;
}

Serializer::Cursor* Serializer::getTag(string arbml_doc, Serializer::Cursor* cursor)
{
	if (arbml_doc[cursor->pos] != '<')
		cursor->pos++;
	if (arbml_doc[cursor->pos] != '<')
		return NULL;
	int cur_pos = cursor->pos;
	while (arbml_doc[cur_pos] != '>') cur_pos++;
	string tag = arbml_doc.substr(cursor->pos + 1, cur_pos - cursor->pos - 1);
	
	cursor->pos = cur_pos;
	cursor->isClosing = tag[0] == '/' ? true : false;
	cursor->tag = cursor->isClosing ? tag.substr(1, tag.length()) : tag;

	return cursor;
}

Note* Serializer::parse(string content)
{
	return NULL;
}

string Serializer::undecorateSymbols(string line)
{
	line = replaceSubstr(line, string("&nbsp;"), string(" "));
	line = replaceSubstr(line, string("&lt;"), string("<"));
	line = replaceSubstr(line, string("&gt;"), string(">"));
	line = replaceSubstr(line, string("&nl;"), string("\n"));
	line = replaceSubstr(line, string("&tb;"), string("\t"));
	line = replaceSubstr(line, string("&rr;"), string("\r"));
	return line;
}

string Serializer::clearWhitespace(string content)
{
	content.erase(remove_if(content.begin(), content.end(), RemoveDelimiter()), content.end());
	return content;
}
