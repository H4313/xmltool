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
	{
		cout<<endl<<"<"<<*name;
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

Item* Element::traiterTemplate(Element* elemXML,Element *racineXLS){

 vector<Item *> * newChildren;

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
		//parcurir les enfants directs d'element XML
		string* selectOptVal = elemXLS->getAttributeValue("select");
		for(int k = 0 ; k < elemXML->items->size() ; k++)
		{
		   if((*(elemXML->items))[k])
		   {
		      Element* childElemXML = dynamic_cast<Element*>((*(elemXML->items))[k]);
		      if(childElemXML != 0 && (selectOptVal==0 || (*childElemXML->name).compare(*selectOptVal) == 0))
		      {
			 //on reprends les etapes du debut
			 //on trouve le bon template
		    	Element *templ = racineXLS->getTemplateMatching(childElemXML->name);
		    	//templ->display();
		        //traiter le template sur l'enfant
		    	if(templ != 0)
			{
			  Item *res = templ->traiterTemplate(childElemXML,racineXLS);
			  newChildren->push_back(res);							    
			}
		      } 
	     	   }
	   	   }
	     }else if ((*(elemXLS->name)).compare("xsl:value-of") == 0)
	           {
			//TODO
			elemXML->display();
		   }else
		     {
			//cout << "<"<<*(elemXLS->name) << endl; //copy element(pour l'instant print)
			//affichage sans atributes
			Item *res = elemXLS->traiterTemplate(elemXML, racineXLS);
			
			newChildren->push_back(res);
			//cout<<endl<<"</"<<*(elemXLS->name)<<">"<<endl;
		    }
	   }else{
		// (*items)[i]->display(); //copy element(pour l'instant print)
		 newChildren->push_back((*items)[i]);
	       }
	} 
    }
 }
 Element el(name, attributes, newChildren);
 return &el;
}
