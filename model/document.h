#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include "prolog.h"
#include "element.h"
#include "misc.h"

#include <iostream>
#include <vector>

using namespace std;

class Document
{
	public : //temporaire (sorana)
		Prolog * prolog;
		Element * element;
		vector<Misc *> * miscs;
		
	public :
		Document(Prolog * p, Element * e, vector<Misc *> * m);
		~Document();
		void display();
};

#endif
