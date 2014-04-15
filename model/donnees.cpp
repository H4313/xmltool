#include "donnees.h"

#include <string>
#include <iostream>

using namespace std;

Donnees::Donnees(string * d) : data(d)
{}

Donnees::Donnees(Donnees * d)
{
	data = new string(*d->GetData());
}

Donnees * Donnees::clone()
{
	return new Donnees(this);
}

Donnees::~Donnees()
{
	if(data) delete data;
}

void Donnees::display()
{
	if(data)
		cout<<*data;
}

string * Donnees::GetData()
{
	return data;
}
