#include "cdSect.h"

#include <string>

using namespace std;

CDSect::CDSect(string * d) : data(d)
{}

CDSect::~CDSect()
{
	if(data) delete data;
}

