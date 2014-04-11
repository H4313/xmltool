#include "commun.h"
#include "model/document.h"
#include "maintools.h"
#include "validationxsd.h"

#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

extern FILE * xmlin;
int xmlparse(Document **);
extern int xmldebug;

int main(int argc, char ** argv)
{
#ifdef XMLDEBUG
	xmldebug = 1;
#endif
	if(argc >= 2)
	{
		if(strcmp(argv[1],"-p") == 0)
		{
			if(argc == 3)
			{	
				FILE * fid = open("-p",argv[2]);
				if (!fid) return 1;
				xmlin = fid;
				Document * document;
				int retour = xmlparse(&document);
				if (!retour)
				{
				  document->display();
				  delete document;
				  return 0;
				}
				else
				{
					cerr<<"No root markup"<<endl;
					return 1;
				}
			}
			else
			{
				cerr<<"You must provide an argument to the command -p"<<endl;
			}
		}
		else if(strcmp(argv[1],"-v") == 0)
		{
			if(argc == 4)
			{
				FILE * fid = open("-v",argv[2]);
				if (!fid) return 1;
				xmlin = fid;
				Document * xml;
				int retour = xmlparse(&xml);
				if (!retour)
				{
					FILE * fid2 = open("-v",argv[3]);
					if (!fid2) 
					{
						delete xml;
						return 1;
					}
					xmlin = fid2;
					Document * xsd;
					int retourXsd = xmlparse(&xsd);
					if (!retourXsd)
					{
						//// Validation du XML avec le XSD
						ValidationXSD * validationXSD = new ValidationXSD(xml, xsd);

						cout << "The file " << argv[2];
						if(validationXSD->XmlIsValid())
						{
							cout << " is valid wrt ";
						}
						else
						{
							cout << " is not valid wrt ";
						}
						cout << argv[3] << endl;

						delete xml;
						delete xsd;
						return 0;
					}
					else
					{
						cerr<<"No root markup"<<endl;
						return 1;
					}
				}
				else
				{
					cerr<<"No root markup"<<endl;
					return 1;
				}
			}
			else
			{
				cerr<<"You must provide two arguments to the command -v: an xml file and an xsd file"<<endl;
			}
		}
		else if(strcmp(argv[1],"-t") == 0)
		{
			//tranformation xls
			if(argc == 4)
			{
				FILE * fid = open("-t",argv[2]);
				if (!fid) return 1;
				xmlin = fid;
				Document * docXML;
				int retour = xmlparse(&docXML);
				if (!retour)
				{
					FILE * fid2 = open("-t",argv[3]);
					if (!fid2)
					{
						delete docXML;
						return 1;
					}
					xmlin = fid2;
					Document * docXLS;
					int retourXsd = xmlparse(&docXLS);
					if (!retourXsd)
					{
						//Step 0: construction du catalog des templates
						//-pour l'instant direct dans l'arbre

						//Step1 trouver le template correpondant
						string rootStr = "/";
					  	Element *templ = docXLS->getElement()->getTemplateMatching(&rootStr);
						//if templ = null chercher par docXML->element->name 
						//templ->display();
						
						//params :  elemXML, racineXLS, racineXML
						Element *racineXML = docXML->getElement();
						Element *docTransf = templ->traiterTemplate(racineXML, docXLS->getElement(), racineXML);
						docTransf->displayResultatTransf();
						
						delete docXML;
						delete docXLS;
						return 0;
					}
					else
					{
						cerr<<"No root markup"<<endl;
						return 1;
					}
				}
				else
				{
					cerr<<"No root markup"<<endl;
					return 1;
				}
			}
			else
			{
				cerr<<"You must provide two arguments to the command -t: an xml file and an xsl file"<<endl;
			}
			
		}
		else if(strcmp(argv[1],"-h") == 0)
		{
			displayHelp();
		}
		else
		{
			cout<<"La commande n'a pas été reconnue"<<endl;
			displayHelp();
		}
	}
	else
	{
		cerr<<"No argument given"<<endl;
		displayHelp();
	}

	return 1;
}
