#include "commun.h"
#include "model/document.h"

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
				FILE * fid;
				fid = fopen(argv[2],"r");
				if (!fid)
				{
					cerr<<"Unable to open "<<argv[2]<<endl;
					return 1;
				}
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
				FILE * fid;
				fid = fopen(argv[2],"r");
				if (!fid)
				{
					cerr<<"Unable to open file "<<argv[2]<<endl;
					return 1;
				}
				xmlin = fid;
				Document * document;
				int retour = xmlparse(&document);
				if (!retour)
				{
					FILE * fid2;
					fid2 = fopen(argv[3],"r");
					if (!fid2)
					{
						cerr<<"Unable to open file "<<argv[3]<<endl;
						return 1;
					}
					xmlin = fid2;
					Document * document2;
					int retourXsd = xmlparse(&document2);
					if (!retourXsd)
					{
					  //document->display();
					  //document2->display();
					////
						// Validation XSD
					////

					  delete document;
					  delete document2;
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
				cerr<<"You must provide an argument to the command -v"<<endl;
			}
		}
		else if(strcmp(argv[1],"-t") == 0)
		{
		}
		else if(strcmp(argv[1],"-h") == 0)
		{
			cerr<<"Available commands are:"<<endl;
			cerr<<"../xmltool -p file.xml : parse and display the xml file"<<endl;
			cerr<<"../xmltool -v file.xml file.xsd : parse both xml and xsd files and display the validation result"<<endl;
			cerr<<"../xmltool -t file.xml file.xsl : parse both xml and xsl files and display de transformation result of file.xml by the stylesheet file.xsl"<<endl;
			cerr<<"../xmltool -h : displays this help"<<endl;
		}
		else
		{
			cout<<"La commande n'a pas été reconnue"<<endl;
		}
	}
	else
	{
		cerr<<"No argument given"<<endl;
		cerr<<"Available commands are:"<<endl;
		cerr<<"../xmltool -p file.xml : parse and display the xml file"<<endl;
		cerr<<"../xmltool -v file.xml file.xsd : parse both xml and xsd files and display the validation result"<<endl;
		cerr<<"../xmltool -t file.xml file.xsl : parse both xml and xsl files and display de transformation result of file.xml by the stylesheet file.xsl"<<endl;
		cerr<<"../xmltool -h : displays this help"<<endl;
	}

	return 1;
}
