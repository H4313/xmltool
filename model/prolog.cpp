#include "prolog.h"
#include "docTypeDecl.h"
#include "misc.h"

#include <vector>

using namespace std;

Prolog::Prolog(DocTypeDecl * d, vector<Misc *> * m) : docTypeDecl(d), miscs(m)
{}

Prolog::~Prolog()
{
	if(docTypeDecl) delete docTypeDecl;
	if(miscs)
	{
		for(int i = 0 ; i < miscs->size() ; i++)
		{
			if((*miscs)[i]) delete (*miscs)[i];
		}
		delete miscs;
	}
}

