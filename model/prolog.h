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
		DocTypeDecl * docTypeDecl;
		vector<Misc *> * miscs;
		
	public :
		Prolog(DocTypeDecl * d, vector<Misc *> * m);
		~Prolog();
};

#endif