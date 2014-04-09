#include "element.h"
#include "attribute.h"
#include "item.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Element::Element(string * n, vector<Attribute *> * a, vector<Item *> * i) : name(n), attributes(a), items(i)
{}

Element::~Element()
{
	if(name) delete name;
	if(attributes)
	{
		for(int i = 0 ; i < attributes->size() ; i++)
		{
			if((*attributes)[i]) delete (*attributes)[i];
		}
		delete attributes;
	}
	if(items)
	{
		for(int i = 0 ; i < items->size() ; i++)
		{
			if((*items)[i]) delete (*items)[i];
		}
		delete items;
	}
}

void Element::display()
{
	if(name)
	  {	cout<<endl<<"<"<<*name;
		if(attributes)
		{
			for(int i = 0 ; i < attributes->size() ; i++)
			{
				if((*attributes)[i]) (*attributes)[i]->display();
			}
		}
		if(items)
		{
			cout<<">"<<endl;
			for(int i = 0 ; i < items->size() ; i++)
			{
				if((*items)[i]) (*items)[i]->display();
			}
			cout<<endl<<"</"<<*name<<">"<<endl;
		}
		else
		{
			cout<<"/>"<<endl;
		}
	   }
}

string* Element::getAttributeValue(string atrName){
	if(attributes)
		{
			for(int i = 0 ; i < attributes->size() ; i++)
			{
				if((*attributes)[i] && (*(*attributes)[i]->name).compare(atrName) ==0 )  
				{
					return (*attributes)[i]->value;				
				}
			}
		}
	return 0;
}

Element* Element::getTemplateMatching(string* matchName)
{
	if(items)
	{
		for(int i = 0 ; i < items->size() ; i++)
		{
			if((*items)[i])
			{
				Element* elem = dynamic_cast<Element*>((*items)[i]);
				if(elem != 0) //is an element
				{ 	
					string *matchAtrValue = elem->getAttributeValue("match");
					//cout <<"compare" << *matchAtrValue <<"ET"<<*matchName;
					if ((*matchAtrValue).compare(*matchName) == 0){
						//cout << ": true" << endl;
						return elem;					
					}//else cout << ": false" << endl;
				}
			} 
		}
	}
	cout << "No Template found for : " << *matchName <<endl;
	return 0;
}

Element* Element::traiterTemplate(Element* elemXML,Element *racineXLS){

 vector<Item *> * newChildren = new std::vector<Item *>();
 Element *el = new Element(name, attributes, newChildren);	

 if(items)
 {  
    for(int i = 0 ; i < items->size() ; i++)
    {
		if((*items)[i])
		{	
			Element* elemXLS = dynamic_cast<Element*>((*items)[i]);
			if(elemXLS != 0) //est un element, pas donnee ou cdSect
			{	 
				if ((*(elemXLS->name)).compare("xsl:apply-templates") == 0)
				{
					el->traiterApplyTemplate(elemXLS, elemXML, racineXLS);
				}else if ((*(elemXLS->name)).compare("xsl:value-of") == 0)
					{
						el->traiterValueOf(elemXLS, elemXML);
					}else
					{   
						Element *res = elemXLS->traiterTemplate(elemXML, racineXLS);
						//cout << *name << " push_back " << *(res->name) <<endl;
						el->traiterResultat(res);
					}
			}else
			{  // n'est pas element 
				newChildren->push_back((*items)[i]); 
			}
		} 
    }
 }

 return el;
}

void Element::traiterApplyTemplate(Element *elemXLS,Element *elemXML, Element *racineXLS)
{
	//parcurir les enfants directs d'element XML
	string* selectOptVal = elemXLS->getAttributeValue("select");
	for(int k = 0 ; k < elemXML->items->size() ; k++)
	{
		if((*(elemXML->items))[k])
		{
			Element* childElemXML = dynamic_cast<Element*>((*(elemXML->items))[k]);
			if(childElemXML != 0 && (selectOptVal==0 || (*childElemXML->name).compare(*selectOptVal) == 0))
			{
				//on reprends les etapes du debut : 1. on trouve le bon template
				Element *templ = racineXLS->getTemplateMatching(childElemXML->name);
				if(templ != 0) //2.traiter le template sur l'enfant
				{
					Element *res = templ->traiterTemplate(childElemXML,racineXLS);
					// cout << *name << " push_back " << *(res->name) <<endl;
					traiterResultat(res);	
				}
			} 
		}
	}
}

void Element::traiterValueOf(Element *elemXLS,Element *elemXML)
{
	string* selectOptVal = elemXLS->getAttributeValue("select");
	if((*selectOptVal).compare(".") == 0)
	{
		items->push_back((*(elemXML->items))[0]);
	}else
	{ //recherche de l'element parmi les items
		if(elemXML->items)
		{
			for(int j = 0 ; j < elemXML->items->size() ; j++)
			{
				Item *it = (*(elemXML->items))[j];
				if(it)
				{
					Element* elCh = dynamic_cast<Element*>(it);
					if(elCh && (*(elCh->name)).compare(*selectOptVal) == 0)
					{ 
						items->push_back((*(elCh->items))[0]);
						break;
					}
				}
			}
		}
	}
}

//eliminate recursion
void Element::traiterResultat(Element *res)
{
	if((*res->name).compare("xsl:template") == 0)
	{
		if(res->items)
		{
			for(int resIt = 0 ; resIt < res->items->size() ; resIt++)
			{
				if((*res->items)[resIt]) 
				{
					items->push_back((*res->items)[resIt]);
				}
			}
		}
		//detele res
	}else
	{ 
		items->push_back(res);
	}	
}
