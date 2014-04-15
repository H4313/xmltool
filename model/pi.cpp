#include "pi.h"
#include "attribute.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

PI::PI(string * t, vector<Attribute *> * a) : target(t), attributes(a)
{}

PI::PI(PI * p)
{
	target = new string(p->getTarget());
	attributes = new vector<Attribute *>();
	vector<Attribute *> * a = p->getAttributes();
	for(int i = 0 ; i < a->size() ; i++)
	{
		(*attributes)[i] = new Attribute((*a)[i]);
	}
}

PI * PI::clone()
{
	return new PI(this);
}

PI::~PI()
{
	if(target) delete target;
	if(attributes)
	{
		for(int i = 0 ; i < attributes->size() ; i++)
		{
			if((*attributes)[i]) delete (*attributes)[i];
		}
		delete attributes;
	}
}

void PI::display()
{
	if(target)
	{
		cout<<"<? "<<*target;
		if(attributes)
		{
			for(int i = 0 ; i < attributes->size() ; i++)
			{
				if((*attributes)[i]) (*attributes)[i]->display();
			}
		}
		cout<<" ?>"<<endl;
	}
}

string PI::getTarget()
{
	return (*target);
}

vector<Attribute *> * PI::getAttributes()
{
	return attributes;
}
