#include "document.h"
#include "element.h"
#include "attribute.h"
#include "item.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Element::Element(string * n, vector<Attribute *> * a, vector<Item *> * i) : name(n), attributes(a), items(i)
{}

Element::~Element()
{
	if(name) delete name;
	if(attributes)
	{
		for(int i = 0 ; i < attributes->size() ; i++)
		{
			if((*attributes)[i]) delete (*attributes)[i];
		}
		delete attributes;
	}
	if(items)
	{
		for(int i = 0 ; i < items->size() ; i++)
		{
			if((*items)[i]) delete (*items)[i];
		}
		delete items;
	}
}



void Element::GetXmlChildren()
{
	string * str = new string("^(");
	for(int i = 0 ; i < items->size() ; i++)
	{
		if( typeid((*(*items)[i])) == typeid(Element) )
		{
			str->append("(<" + (dynamic_cast<Element*>((*items)[i]))->GetName() + ">)|");
		}
	}
	str->erase(str->length()-1, 1);
	str->append(")$");

	validationMap[this->GetName()] = str;
}

string Element::GetName()
{
	return (*name);
}

void Element::display()
{
	if(name)
	{
		cout<<endl<<"<"<<*name;
		if(attributes)
		{
			for(int i = 0 ; i < attributes->size() ; i++)
			{
				if((*attributes)[i]) (*attributes)[i]->display();
			}
		}
		if(items)
		{
			cout<<">"<<endl;
			for(int i = 0 ; i < items->size() ; i++)
			{
				if((*items)[i]) (*items)[i]->display();
			}
			cout<<endl<<"</"<<*name<<">"<<endl;
		}
		else
		{
			cout<<"/>"<<endl;
		}
	}
}
