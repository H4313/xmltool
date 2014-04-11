#include "attribute.h"

#include <string>
#include <iostream>

using namespace std;

Attribute::Attribute(string * n, string *  v) : name(n), value(v)
{}

Attribute::~Attribute()
{
	if(name) delete name;
	if(value) delete value;
}

string Attribute::GetName()
{
	return (*name);
}

string Attribute::GetValue()
{
	return (*value);
}

void Attribute::display()
{
	if(name && value)
		cout<<" "<<*name<<" = \""<<*value<<"\"";
}

