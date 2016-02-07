#ifndef WRITEORG_H
#define WRITEORG_H

#include <iostream>
#include <fstream>
#include "note.h"

using namespace std;

class WriteOrg
{
public:
	static void writeNote(Note* note);
	static void write(Note* note, string filename, string level);
	static string loadContent(Note* note);
};

#endif // WRITEORG_H
