#ifndef __DOCTYPEDECL_H
#define __DOCTYPEDECL_H

#include <iostream>
#include <string>

using namespace std;

class DocTypeDecl
{
	private :
		string * name;
		string * externalID;
		string * data;
		
	public :
		DocTypeDecl(string * n, string * i, string * d);
		DocTypeDecl(DocTypeDecl * d);
		~DocTypeDecl();
		void display();
		string getName();
		string getExternalID();
		string getData();
};

#endif