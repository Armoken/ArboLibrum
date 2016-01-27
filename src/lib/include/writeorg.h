#ifndef WRITEORG_H
#define WRITEORG_H

#include "note.h"

class WriteOrg
{
 public:
	 static void writeNote(Note* &note);
	 static string loadContent(Note* &note);
};

#endif // WRITEORG_H
