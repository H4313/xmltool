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
map<string, string> * Document::GetValidator()
{
	map<string, string> * validationMap = new map<string, string>();

	if((this->element->GetName()).compare("xsd:schema") == 0)
	{

		vector<Element *> * rules = this->element->GetChildren();
		for(int i = 0 ; i < rules->size() ; i++)
		{
			validationMap->insert (
					pair<string,string>(
							((*rules)[i])->GetAttributeByName("name")->GetValue(),
							((*rules)[i])->GetRule()
					)
			);
		}

//		cout << validationMap->size() << endl;
	}
	else
	{
		// ERROR
		cerr << "Invalid XSD" << endl;
	}

	return validationMap;
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
