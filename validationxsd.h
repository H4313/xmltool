#ifndef __VALIDATION_XSD_H
#define __VALIDATION_XSD_H

#include "model/document.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

class ValidationXSD
{
	private :
		map<string, string> * validator;
		bool xmlIsValid;
		bool validation(Element * element);

	public :
		ValidationXSD(Document * xml, Document * xsd);
		~ValidationXSD();
		bool XmlIsValid();
};

#endif
