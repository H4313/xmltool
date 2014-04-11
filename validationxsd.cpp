#include "validationxsd.h"

#include <string>
#include <regex.h>
//#include <regex>
#include <iostream>

using namespace std;

ValidationXSD::ValidationXSD(Document * xml, Document * xsd)
{
	this->xmlIsValid = false;

	this->validator = xsd->GetValidator();

	this->xmlIsValid = this->validation(xml->getElement());
}

ValidationXSD::~ValidationXSD()
{
}

bool ValidationXSD::validation(Element * element)
{
	map<string,string>::iterator eltRegex = this->validator->find(element->GetName());
	if(eltRegex != this->validator->end())
	{
		regex_t regex;
		int reti;

		// Compile regular expression
		reti = regcomp(&regex, eltRegex->second.c_str(), REG_EXTENDED|REG_ICASE|REG_NOSUB|REG_NEWLINE);
		if( reti != 0 )
		{
			cerr << "Wrong Regex" << endl;
			return false;
		}

		// Execute regular expression
		reti = regexec(&regex, element->GetChildrenTag().c_str(), 0, NULL, 0);
		regfree(&regex);

//		cout << element->GetName() << ":" << eltRegex->second
//				<< "\nMatch : " << reti
//				<< "\n" << element->GetChildrenTag() << endl;

		if( reti != 0 )
		{
			cerr << "Regex match failed" << endl;
			return false;
		}
	}

	// C++ REGEX
//	map<string,string>::iterator eltRegex = this->validator->find(element->GetName());
//	if(eltRegex != this->validator->end())
//	{
//		regex exp(eltRegex->second);
////		cout << element->GetName() << eltRegex->second
////				<< "\n" << regex_match(element->GetChildrenTag(), exp)
////				<< "\n" << element->GetChildrenTag() << endl;
//
//		if(!regex_match(element->GetChildrenTag(), exp))
//		{
//			return false;
//		}
//	}

    // For each children
    bool childIsValid = true;
    vector<Element *> * children = element->GetChildren();
	for(int i = 0 ; i < children->size() ; i++)
	{
		childIsValid = this->validation((*children)[i]);
		if(!childIsValid)
		{
			delete children;
			return false;
		}
	}
	delete children;

	return true;
}

bool ValidationXSD::XmlIsValid()
{
	return this->xmlIsValid;
}
