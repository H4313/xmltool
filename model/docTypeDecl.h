#ifndef __DOCTYPEDECL_H
#define __DOCTYPEDECL_H

#include <iostream>
#include <string>

using namespace std;

class DocTypeDecl
{
	private :
		string * name;
		int externalID;
		
	public :
		DocTypeDecl(string * n, int i);
		~DocTypeDecl();
};

#endif