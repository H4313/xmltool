#include "document.h"
#include "prolog.h"
#include "element.h"
#include "misc.h"

#include <vector>
#include <iostream>

using namespace std;

Document::Document(Prolog * p, Element * e, vector<Misc *> * m) : prolog(p), element(e), miscs(m)
{}

Document::~Document()
{
	if(prolog) delete prolog;
	if(element) delete element;
	if(miscs)
	{
		for(int i = 0 ; i < miscs->size() ; i++)
		{
			if((*miscs)[i]) delete (*miscs)[i];
		}
		delete miscs;
	}
}

void Document::display()
{
	cout<<"--- AFFICHAGE DU DOCUMENT XML PARSE ---"<<endl<<endl;
	if(prolog && element)
	{
		prolog->display();
		element->display();
		if(miscs)
		{
			for(int i = 0 ; i < miscs->size() ; i++)
			{
				if((*miscs)[i]) (*miscs)[i]->display();
			}
		}
	}
	cout<<endl;
}
