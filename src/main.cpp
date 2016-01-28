#include <iostream>
#include "lib/include/note.h"

using namespace std;

int main()
{
  Note* note = new Note("1.txt", Note::root);
  note->setTitle("NOTTTTEE");
  note->addNote("KEK", "2.txt", Note::text);
  Note* newNote = note->getNote(0);
  return 0;
}
