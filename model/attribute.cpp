#include "attribute.h"

#include <string>

using namespace std;

Attribute::Attribute(string * n, string *  v) : name(n), value(v)
{}

Attribute::~Attribute()
{
	if(name) delete name;
	if(value) delete value;
}

