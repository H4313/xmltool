#include "cdSect.h"

#include <string>
#include <iostream>

using namespace std;

CDSect::CDSect(string * d) : data(d)
{}

CDSect::CDSect(CDSect * c)
{
	data = new string(c->getData());
}

CDSect * CDSect::clone()
{
	return new CDSect(this);
}

string CDSect::getData()
{
	return (*data);
}

CDSect::~CDSect()
{
	if(data) delete data;
}

void CDSect::display()
{
	if(data)
		cout<<"<![CDATA["<<*data<<"]]>"<<endl;
}

