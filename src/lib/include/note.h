#ifndef NOTE_H
#define NOTE_H
#include <iostream>
#include <vector>

using namespace std;

class Note
{
private:
	string title;
	string path;
	bool isCheckbox;
	bool isRootNote;
	int noteType;
	Note* parentNote;
	vector<Note*> notes;

public:
	enum types
	{
		root = 1,
		text = 2,
		pic = 3
	};
	Note(string _path, types _noteType);
	~Note();
	bool setTitle(string _title);
	string getTitle();
	bool setPath(string _path);
	string getPath();
	int getType();
	Note* getNote(int _number);
	void addNote(string _title, string _path, types _noteKind);
	void removeNote();
	static void loadContent(Note* &note);
	static void showNote(Note* &note);
};
#endif // NOTE_H
