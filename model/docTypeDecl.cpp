#include "docTypeDecl.h"

#include <string>
#include <iostream>

using namespace std;

DocTypeDecl::DocTypeDecl(string * n, string * i, string * d) : name(n), externalID(i), data(d)
{}

DocTypeDecl::DocTypeDecl(DocTypeDecl * d)
{
	name = new string(d->getName());
	externalID = new string(d->getExternalID());
	data = new string(d->getData());
}

DocTypeDecl::~DocTypeDecl()
{
	if(name) delete name;
	if(externalID) delete externalID;
	if(data) delete data;
}

void DocTypeDecl::display()
{
	if(name && externalID && data)
		cout<<"<!DOCTYPE "<<*name<<" "<<*externalID<<" \""<<*data<<"\">"<<endl;
}

string DocTypeDecl::getName()
{
	return (*name);
}

string DocTypeDecl::getExternalID()
{
	return (*externalID);
}

string DocTypeDecl::getData()
{
	return (*data);
}