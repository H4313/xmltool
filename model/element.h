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
	private : 
		string * name;
		vector<Attribute *> * attributes;
		vector<Item *> * items;

		// Transformation XSL
		string* getAttributeValue(string atrName);
		
	public :
		Element(string * n, vector<Attribute *> * a, vector<Item *> * i);
		Element(Element * e);
		Element * clone();
		~Element();
		void display();
		string GetName();
		string GetValue();
		vector<Attribute *> * getAttributes();
		vector<Item *> * getItems();
		vector<Element *> * GetChildren(vector<Element *> * children);
		Attribute * GetAttributeByName(string name);
		vector<Item *> * GetItems();

		// Validation XSD
		string GetChildrenTag(string * str);
		// Element doit etre un element XSD
		string GetRule(string * str);
		string GetXsdComplexTypeRule(Element * complexType, string * str);
		string GetXsdElementRule(Element * element, string * regexSeparator, string * str);

		/*  Transformation de l'arbre */
		//traiter le template sur un element XML recu en entree
		Element* traiterTemplate(Element* elemXML,Element *racineXLS, Element *racineXML);
		// retrouver le template (pour l'instant direct dans l'arbre XLS)
		Element* getTemplateMatching(string* matchName);

		private:
			void traiterResultat(Element *res);
			void traiterValueOf(Element *elemXLS,Element *elemXML);
			void traiterApplyTemplate(Element *elemXLS,Element *elemXML, Element *racineXLS, Element *racineXML);
			void traiterForEach(string chemin,Element *elemXLS,Element *elemXML, Element *racineXLS, Element *racineXML);
		public: 
			void displayResultatTransf(){
				(*items)[0]->display();
			}
};

#endif
