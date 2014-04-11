#include "document.h"
#include "element.h"
#include "attribute.h"
#include "item.h"
#include "donnees.h"

#include <string>
#include <vector>
#include <typeinfo>
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

/// Validation XSD ///
string Element::GetChildrenTag()
{
	Element * child;
	string * str = new string();
	for(int i = 0 ; i < items->size() ; i++)
	{
		if( typeid((*(*items)[i])) == typeid(Element) )
		{
			child = dynamic_cast<Element*>((*items)[i]);

			str->append("<" + child->GetName() + ">");

			if(child->GetChildren()->size() == 0)
			{
				str->append(child->GetValue());
				str->append("</" + child->GetName() + ">");
			}
		}
	}

	return (*str);
}

// Element doit etre un element XSD
string Element::GetRule()
{
	string * str = new string();
	if((this->GetName()).compare("xsd:element") == 0)
	{
		vector<Element *> * xsdTypes = this->GetChildren();
		if(xsdTypes->size() == 1
				&& (*xsdTypes)[0]->GetName().compare("xsd:complexType") == 0)
		{
			Element * xsdType = (*xsdTypes)[0];
			vector<Element *> * xsdRulesTypes = xsdType->GetChildren();
			if(xsdRulesTypes->size() == 1)
			{
				Element * xsdRuleType = (*xsdRulesTypes)[0];
				string * regexSeparator = new string();
				if(xsdRuleType->GetName().compare("xsd:choice") == 0)
				{
					regexSeparator->append("|");
				}
				else if(xsdRuleType->GetName().compare("xsd:sequence") == 0)
				{
					regexSeparator->append("");
				}
				else
				{
					cerr << "Wrong XSD syntax 3" << endl;
				}

				str->append("^(");
				Attribute * attributeName = NULL;
				Attribute * attributeType = NULL;
				Attribute * attributeRef = NULL;
				Attribute * attributeMaxOccus = NULL;
				Attribute * attributeMinOccus = NULL;
				vector<Element *> * xsdRules = xsdRuleType->GetChildren();
				for(int i = xsdRules->size()-1 ; i >= 0; i--)
				{
					attributeName = (*xsdRules)[i]->GetAttributeByName("name");
					attributeType = (*xsdRules)[i]->GetAttributeByName("type");
					attributeRef = (*xsdRules)[i]->GetAttributeByName("ref");
					attributeMaxOccus = (*xsdRules)[i]->GetAttributeByName("maxOccurs");
					attributeMinOccus = (*xsdRules)[i]->GetAttributeByName("minOccurs");
					if(attributeName != NULL && attributeType != NULL)
					{
						str->append("((<" + attributeName->GetValue() + ">)|");
						if((attributeType->GetValue()).compare("xsd:string") == 0)
						{
							str->append("((<" + attributeName->GetValue() + ">).*(<\\/" + attributeName->GetValue() + ">)))");
						}
						else if((attributeType->GetValue()).compare("xsd:date") == 0)
						{
							str->append("((<" + attributeName->GetValue() + ">)[0-9]{4}-[0-9]{2}-[0-9]{2}(<\\/" + attributeName->GetValue() + ">)))");
						}
						str->append((*regexSeparator));
					}
					else if(attributeRef != NULL
							&& (attributeMinOccus != NULL || attributeMaxOccus != NULL))
					{
						str->append("(<" + attributeRef->GetValue() + ">){"
								+ ((attributeMinOccus != NULL) ? attributeMinOccus->GetValue() : "0")
								+ ","
								+ ((attributeMaxOccus != NULL) ? attributeMaxOccus->GetValue() : "") + "}"
								+ (*regexSeparator));
					}
				}
				delete xsdRules;
				if(regexSeparator->length() > 0) str->erase(str->length()-1, 1);
				str->append(")$");
			}
			else
			{
				cerr << "Wrong XSD syntax 2" << endl;
			}
		}
		else
		{
			cerr << "Wrong XSD syntax 1" << endl;
		}
	}
	else
	{
		cerr << "Element is not a xsd element" << endl;
	}

	return (*str);
}

vector<Element *> * Element::GetChildren()
{
	vector<Element *> * children = new vector<Element *>();
	for(int i = 0 ; i < items->size() ; i++)
	{
		if( typeid((*(*items)[i])) == typeid(Element) )
		{
			children->insert(children->begin(), dynamic_cast<Element*>((*items)[i]));
		}
	}

	return children;
}

Attribute * Element::GetAttributeByName(string name)
{
	Attribute * attribute = NULL;
	bool found = false;
	int i = 0;

	do
	{
		if((*attributes)[i]->GetName().compare(name) == 0)
		{
			attribute = (*attributes)[i];
			found = true;
		}
		i++;
	}
	while(i < attributes->size()
			&& !found);

	return attribute;
}

vector<Item *> * Element::GetItems()
{
	return items;
}

string Element::GetName()
{
	return (*name);
}

string Element::GetValue()
{
	for(int i = 0 ; i < items->size() ; i++)
	{
		if( typeid((*(*items)[i])) == typeid(Donnees) )
		{
			return (dynamic_cast<Donnees*>((*items)[i]))->GetData();
		}
	}

	return "";
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
				if((*attributes)[i] && (*(*attributes)[i]->getName()).compare(atrName) ==0 )  
				{
					return (*attributes)[i]->getValue();				
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

/* Algorithme de tranformation d'arbre */
Element* Element::traiterTemplate(Element* elemXML,Element *racineXLS){

 if(items)
 { 
    vector<Item *> * newChildren = new std::vector<Item *>();
    Element *el = new Element(name, attributes, newChildren);	 
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
					}else if ((*(elemXLS->name)).compare("xsl:for-each") == 0)
						{
							//TODO traiter cas for-each
						}else
						{   
							Element *res = elemXLS->traiterTemplate(elemXML, racineXLS);
							el->traiterResultat(res);
						}
			}else
			{  // n'est pas element 
				newChildren->push_back((*items)[i]); 
			}
		} 
    }
    return el;
 }

  //No items
  return new Element(name, attributes, 0);

}

/* Methode pour appliquer un template */
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

/* Methode pour traiter le cas valueOf*/
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

/* Methode pour traiter un resultat intermediaire
-> un noeud du template peut entrainer l'application d'un autre template*/
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
		//delete res;
	}else
	{ 	
		items->push_back(res);
	}	
}
