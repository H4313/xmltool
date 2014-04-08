#include "commun.h"
#include "model/document.h"
#include "maintools.h"

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
				Document * document;
				int retour = xmlparse(&document);
				if (!retour)
				{
					FILE * fid2 = open("-v",argv[3]);
					if (!fid2) return 1;
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
						if(argc == 4)
			{
				FILE * fid = open("-t",argv[2]);
				if (!fid) return 1;
				xmlin = fid;
				Document * document;
				int retour = xmlparse(&document);
				if (!retour)
				{
					FILE * fid2 = open("-t",argv[3]);
					if (!fid2) return 1;
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
				cerr<<"You must provide an argument to the command -t"<<endl;
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
