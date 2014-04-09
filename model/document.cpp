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

// XSD
void Document::Validation()
{
	if((this->element->GetName()).compare("xsd:schema") == 0)
	{
		//map<string, string> validationMap;

		vector<Element *> * rules = this->element->GetChildren();
		for(int i = 0 ; i < rules->size() ; i++)
		{
			cout << ((*rules)[i])->GetRule() << endl;
		}

		//cout << validationMap.count() << endl;
	}
	else
	{
		// ERROR
		cerr << "Invalid XSD" << endl;
	}
}

void Document::display()
{
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
