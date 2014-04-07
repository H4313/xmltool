#include "donnees.h"

#include <string>

using namespace std;

Donnees::Donnees(string * d) : data(d)
{}

Donnees::~Donnees()
{
	if(data) delete data;
}
