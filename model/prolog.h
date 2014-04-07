#ifndef __PROLOG_H
#define __PROLOG_H

#include "docTypeDecl.h"
#include "misc.h"

#include <iostream>
#include <vector>

using namespace std;

class Prolog
{
	private :
		vector<Misc *> * miscsBeginning;
		DocTypeDecl * docTypeDecl;
		vector<Misc *> * miscsEnd;
		
	public :
		Prolog(vector<Misc *> * m1, DocTypeDecl * d, vector<Misc *> * m2);
		~Prolog();
		void display();
};

#endif