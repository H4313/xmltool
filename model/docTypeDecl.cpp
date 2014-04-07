#include "docTypeDecl.h"

#include <string>

using namespace std;

DocTypeDecl::DocTypeDecl(string * n, int i) : name(n), externalID(i)
{}

DocTypeDecl::~DocTypeDecl()
{
	if(name) delete name;
}
