#include "donnees.h"

#include <string>
#include <iostream>

using namespace std;

Donnees::Donnees(string * d) : data(d)
{}

Donnees::~Donnees()
{
	if(data) delete data;
}

void Donnees::display()
{
	if(data)
		cout<<*data;
}