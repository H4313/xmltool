#include "document.h"
#include "element.h"
#include "attribute.h"
#include "cdSect.h"
#include "pi.h"
#include "item.h"
#include "comment.h"
#include "donnees.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>

using namespace std;

Element::Element(string * n, vector<Attribute *> * a, vector<Item *> * i) : name(n), attributes(a), items(i)
{}

Element::Element(Element * e)
{
	name = new string(e->GetName());
	vector<Attribute *> * a = e->getAttributes();
	if(a)
	{	
		attributes = new vector<Attribute *>();
		for(int i = 0 ; i < a->size() ; i++)
		{
			attributes->push_back(new Attribute((*a)[i]));
		}
	}else
	{
		attributes = 0;
	}	
	vector<Item *> * it = e->getItems();
	if(it) //else : segmentation fault
	{	
		items = new vector<Item *>();
		for(int i = 0 ; i < it->size() ; i++)
		{
			items->push_back((*it)[i]->clone());
		}
	}else
	{
		items = 0;
	}
}

Element::Element(string * n, vector<Attribute *> * a)
{
	name = new string(*n);
	if(a)
	{
		attributes = new vector<Attribute *>();
		for(int i = 0 ; i < a->size() ; i++)
		{
			attributes->push_back(new Attribute((*a)[i]));
		}
	}else
	{
		attributes = 0;
	}
	items = new vector<Item *>();
}

Element * Element::clone()
{	
	return new Element(this);
}

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
string Element::GetChildrenTag(	string * str )
{
	if(this->GetValue() != NULL)
	{
		str->append(*this->GetValue());
	}
	else
	{
		vector<Element *> * xmlChildren = new vector<Element *>();
		xmlChildren = this->GetChildren(xmlChildren);
		for(int i = 0 ; i < xmlChildren->size(); i++)
		{
			str->append("<" + (*xmlChildren)[i]->GetName() + ">");
		}
		delete xmlChildren;
	}

	return (*str);
}

// Element doit etre un element XSD
string Element::GetRule(string * str)
{
	str->append("^(");

	if((this->GetName()).compare("xsd:element") == 0)
	{
		string * regexSeparator = new string("");
		string * eltrule = new string();
		str->append(this->GetXsdElementRule(this, regexSeparator, eltrule, true));
		delete eltrule;
		delete regexSeparator;
	}
	else if((this->GetName()).compare("xsd:complexType") == 0)
	{
		string * complexrule = new string();
		str->append(this->GetXsdComplexTypeRule(this, complexrule));
		delete complexrule;
	}
	else
	{
		cerr << "Element is not a xsd element" << endl;
	}

	str->append(")$");

	return (*str);
}

string Element::GetXsdElementRule(Element * element, string * regexSeparator, string * str, bool getChildren)
{
	vector<Element *> * xsdChildren = new vector<Element *>();
	xsdChildren = element->GetChildren(xsdChildren);
//	cout << xsdChildren->size() << " " << element->GetName() << " = "
//			<< ((element->GetAttributeByName("name") != NULL) ? element->GetAttributeByName("name")->GetValue() : "") << endl;

	if(xsdChildren->size() > 0 && getChildren)
	{
//		for(int i = 0 ; i < xsdChildren->size(); i++)
//		{
			int i = 0;
			if((*xsdChildren)[i]->GetName().compare("xsd:complexType") == 0)
			{
				string * rule = new string();
				str->append(this->GetXsdComplexTypeRule((*xsdChildren)[i], rule));
				delete rule;
			}
			else
			{
				cerr << "Le fils de element inconnu : " << (*xsdChildren)[i]->GetName() << endl;
			}
//		}
	}
	else
	{
		Attribute * attributeName = element->GetAttributeByName("name");
		Attribute * attributeType = element->GetAttributeByName("type");
		Attribute * attributeRef = element->GetAttributeByName("ref");
		Attribute * attributeMaxOccus = element->GetAttributeByName("maxOccurs");
		Attribute * attributeMinOccus = element->GetAttributeByName("minOccurs");

		if(attributeName != NULL && attributeType != NULL && getChildren)
		{
			if((attributeType->GetValue()).compare("xsd:string") == 0)
			{
				str->append(".*");
			}
			else if((attributeType->GetValue()).compare("xsd:int") == 0)
			{
				str->append("(\\+|\\-)?[0-9]*");
			}
			else if((attributeType->GetValue()).compare("xsd:decimal") == 0)
			{
				str->append("(\\+|\\-)?[0-9]*((\\.|\\,)[0-9]+)?");
			}
			else if((attributeType->GetValue()).compare("xsd:date") == 0)
			{
				str->append("[0-9]{4}-[0-9]{2}-[0-9]{2}");
			}
			str->append((*regexSeparator));
		}
		else if((attributeRef != NULL || attributeName != NULL)
				&& (attributeMinOccus != NULL || attributeMaxOccus != NULL))
		{
			str->append("(<" + ((attributeRef != NULL) ? attributeRef->GetValue() : attributeName->GetValue()) + ">){"
					+ ((attributeMinOccus != NULL) ? attributeMinOccus->GetValue() : "1")
					+ ","
					+ ((attributeMaxOccus != NULL)
							? ((attributeMaxOccus->GetValue().compare("unbounded") != 0)
									? attributeMaxOccus->GetValue()
									: ""
								)
							: "") + "}"
					+ (*regexSeparator));
		}
		else if(xsdChildren->size() == 0 && !getChildren && attributeName != NULL)
		{
			str->append("(<" + element->GetAttributeByName("name")->GetValue() + ">)");
			str->append((*regexSeparator));
		}
	}

	delete xsdChildren;

	return (*str);
}

string Element::GetXsdComplexTypeRule(Element * complexType, string * str)
{
	if(complexType->GetName().compare("xsd:complexType") == 0)
	{
		vector<Element *> * xsdRulesTypes = new vector<Element *>();
		xsdRulesTypes = complexType->GetChildren(xsdRulesTypes);
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

			vector<Element *> * xsdRules = new vector<Element *>();
			xsdRules = xsdRuleType->GetChildren(xsdRules);
			for(int i = 0 ; i < xsdRules->size(); i++)
			{
				if((*xsdRules)[i]->GetName().compare("xsd:element") == 0)
				{
					string * eltrule = new string();
					str->append(this->GetXsdElementRule((*xsdRules)[i], regexSeparator, eltrule, false));
					delete eltrule;
				}
			}
			delete xsdRules;

			if(regexSeparator->length() > 0)
			{
				str->erase(str->length()-1, 1);
			}
			delete regexSeparator;
		}
		else
		{
			cerr << "Wrong XSD syntax 2" << endl;
		}

		delete xsdRulesTypes;
	}
	else
	{
		cerr << "Wrong XSD syntax 1" << endl;
	}

	return (*str);
}

vector<Element *> * Element::GetChildren(vector<Element *> * children)
{
	if(items != NULL)
	{
		for(int i = 0 ; i < items->size() ; i++)
		{
			if( typeid((*(*items)[i])) == typeid(Element) )
			{
				children->push_back(dynamic_cast<Element*>((*items)[i]));
			}
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

string * Element::GetValue()
{
	string * str = NULL;

	for(int i = 0 ; i < this->items->size() ; i++)
	{
		if( typeid((*(*items)[i])) == typeid(Donnees) )
		{
			return (dynamic_cast<Donnees*>((*items)[i]))->GetData();
		}
	}

	return str;
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
					if ((*matchAtrValue).compare(*matchName) == 0){
						return elem;					
					}
				}
			} 
		}
	}
	cout << "No Template found for : " << *matchName <<endl;
	return 0;
}

/* Algorithme de tranformation d'arbre */
//racineXML pour le cas for-each
Element* Element::traiterTemplate(Element* elemXML,Element *racineXLS, Element *racineXML){

 if(items)
 { 
    Element *el = new Element(name, attributes);	 
    for(int i = 0 ; i < items->size() ; i++)
    {
		if((*items)[i])
		{	
			Element* elemXLS = dynamic_cast<Element*>((*items)[i]);
			if(elemXLS != 0) //est un element, pas donnee ou cdSect
			{	 
				if ((*(elemXLS->name)).compare("xsl:apply-templates") == 0)
				{
					el->traiterApplyTemplate(elemXLS, elemXML, racineXLS, racineXML);
				}else if ((*(elemXLS->name)).compare("xsl:value-of") == 0)
					{
						el->traiterValueOf(elemXLS, elemXML);
					}else if ((*(elemXLS->name)).compare("xsl:for-each") == 0)
						{
							//!!! Le foreach called for the first time with RACINE XML !!!
							string* chemin = elemXLS->getAttributeValue("select");
							el->traiterForEach(*chemin, elemXLS, racineXML, racineXLS, racineXML);
						}else
						{   
							Element *res = elemXLS->traiterTemplate(elemXML, racineXLS, racineXML);
							el->traiterResultat(res);
						}
			}else
			{  // n'est pas element 
				el->addChild((*items)[i]->clone()); 
			}
		} 
    }
    return el;
 }
  //No items
  return this->clone();
}

/* Methode pour traiter le cas for-each */
void Element::traiterForEach(string chemin,Element *elemXLS,Element *elemXML, Element *racineXLS, Element *racineXML)
{
  size_t idx = chemin.find("/");
  string first, second;
  if ( idx != string::npos)
  {   
	first = chemin.substr (0, idx);     
    	second = chemin.substr (idx+1);	
  }else	{ first = chemin; second = ""; 	}

  if((*elemXML->name).compare(first) == 0)
  {
	if(second.compare("") != 0)
	{ //il faut encore descendre
		if(elemXML->items)
		{
			for(int j = 0 ; j < elemXML->items->size() ; j++)
			{
				Item *it = (*(elemXML->items))[j];
				if(it)
				{
					Element* elCh = dynamic_cast<Element*>(it);
					if(elCh)
					{ 
						traiterForEach(second, elemXLS, elCh, racineXLS, racineXML);
					}
				}
			}
		}
	}else
	{
		Element *res = elemXLS->traiterTemplate(elemXML,racineXLS, racineXML);
		traiterResultat(res);
	}
  }
}

/* Methode pour traiter le cas applyTemplate */
void Element::traiterApplyTemplate(Element *elemXLS,Element *elemXML, Element *racineXLS, Element *racineXML)
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
					Element *res = templ->traiterTemplate(childElemXML,racineXLS, racineXML);
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
		addChild((*(elemXML->items))[0]->clone()); 
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
						addChild((*(elCh->items))[0]->clone());
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
	if((*res->name).compare("xsl:template") == 0 || (*res->name).compare("xsl:for-each") == 0 )
	{
		if(res->items)
		{
			for(int resIt = 0 ; resIt < res->items->size() ; resIt++)
			{
				if((*res->items)[resIt]) 
				{	
					Item *t =(*res->items)[resIt]; 
					addChild(t->clone());
				}
			}
		}
		delete res;
	}else
	{ 	
		addChild(res);
	}	
}

vector<Attribute *> * Element::getAttributes()
{
	return attributes;
}

vector<Item *> * Element::getItems()
{
	return items;
}
