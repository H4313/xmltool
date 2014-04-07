#include "pi.h"
#include "attribute.h"

#include <vector>
#include <string>

using namespace std;

PI::PI(string * t, vector<Attribute *> * a) : target(t), attributes(a)
{}

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
