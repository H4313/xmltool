#include "maintools.h"
#include <iostream>
//#include <stdio.h>
//#include <cstring>
#include <string>

using namespace std;

void displayHelp(){
	cerr<<"Available commands are:"<<endl;
	cerr<<"../xmltool -p file.xml : parse and display the xml file"<<endl;
	cerr<<"../xmltool -v file.xml file.xsd : parse both xml and xsd files and display the validation result"<<endl;
	cerr<<"../xmltool -t file.xml file.xsl : parse both xml and xsl files and display de transformation result of file.xml by the stylesheet file.xsl"<<endl;
	cerr<<"../xmltool -h : displays this help"<<endl;
}

FILE * open(string param, string fileName){
	FILE * fid = fopen(fileName.c_str(),"r");
	if (!fid)
	{
		if (param.compare("-v")==0 || param.compare("-t")==0){
			cerr<<"Unable to open file "<<fileName<<endl;
		}
		else{
			cerr<<"Unable to open "<<fileName<<endl;
		}
		return NULL;
	}
	return fid;
}
