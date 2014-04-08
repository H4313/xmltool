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
			cout<<"La commande n'a pas été reconnue"<<endl;
		}
	}
	else if(strcmp(argv[1],"-v") == 0)
	{
	}
	else if(strcmp(argv[1],"-t") == 0)
	{
	}
	else
	{
		cout<<"La commande n'a pas été reconnue"<<endl;
	}
	return 0;
}
