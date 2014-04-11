#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include "prolog.h"
#include "element.h"
#include "misc.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Document
{
	private : 
		Prolog * prolog;
		Element * element;
		vector<Misc *> * miscs;
		
	public :
		Document(Prolog * p, Element * e, vector<Misc *> * m);
		~Document();
		map<string, string> * GetValidator();
		void display();
		Element* getElement()
		{
			return element;
		}
};

#endif
