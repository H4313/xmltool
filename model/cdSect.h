#ifndef __CDSECT_H
#define __CDSECT_H

#include "item.h"

#include <iostream>
#include <string>

using namespace std;

class CDSect : public Item
{
	private :
		string * data;
	
	public :
		CDSect(string * d);
		CDSect(CDSect * c);
		CDSect * clone();
		~CDSect();
		void display();
		string getData();
};

#endif