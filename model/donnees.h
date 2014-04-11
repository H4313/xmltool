#ifndef __DONNEES_H
#define __DONNEES_H

#include "item.h"

#include <iostream>
#include <string>

using namespace std;

class Donnees : public Item
{
	private :
		string * data;
	
	public :
		Donnees(string * d);
		~Donnees();
		void display();
		string GetData();
};

#endif
