#ifndef __ELEMENT_H
#define __ELEMENT_H

#include "attribute.h"
#include "item.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Element : public Item
{
	public : //temporary(sorana)
		string * name;
		vector<Attribute *> * attributes;
		vector<Item *> * items;
		
	public :
		Element(string * n, vector<Attribute *> * a, vector<Item *> * i);
		~Element();
		void display();

		/*  Transformation de l'arbre */
		//traiter le template sur un element XML recu en entree
		Element* traiterTemplate(Element* elemXML,Element *racineXLS);
		// retrouver le template (pour l'instant direct dans l'arbre XLS)
		Element* getTemplateMatching(string* matchName);

		private:
			string* getAttributeValue(string atrName);
			void traiterResultat(Element *res);
			void traiterValueOf(Element *elemXLS,Element *elemXML);
			void traiterApplyTemplate(Element *elemXLS,Element *elemXML, Element *racineXLS);
};

#endif
