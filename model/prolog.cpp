#include "prolog.h"
#include "docTypeDecl.h"
#include "misc.h"

#include <vector>
#include <iostream>

using namespace std;

Prolog::Prolog(vector<Misc *> * m1, DocTypeDecl * d, vector<Misc *> * m2) : miscsBeginning(m1), docTypeDecl(d), miscsEnd(m2)
{}

Prolog::~Prolog()
{
	if(miscsBeginning)
	{
		for(int i = 0 ; i < miscsBeginning->size() ; i++)
		{
			if((*miscsBeginning)[i]) delete (*miscsBeginning)[i];
		}
		delete miscsBeginning;
	}
	if(docTypeDecl) delete docTypeDecl;
	if(miscsEnd)
	{
		for(int i = 0 ; i < miscsEnd->size() ; i++)
		{
			if((*miscsEnd)[i]) delete (*miscsEnd)[i];
		}
		delete miscsEnd;
	}
}

void Prolog::display()
{
	if(miscsBeginning)
	{
		for(int i = 0 ; i < miscsBeginning->size() ; i++)
		{
			if((*miscsBeginning)[i]) (*miscsBeginning)[i]->display();
		}
	}
	if(docTypeDecl)
	{
		docTypeDecl->display();
		if(miscsEnd)
		{
			for(int i = 0 ; i < miscsEnd->size() ; i++)
			{
				if((*miscsEnd)[i]) (*miscsEnd)[i]->display();
			}
		}
	}
}
