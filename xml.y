%{

#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
#include "commun.h"
#include "model/document.h"

extern char xmltext[];

int xmllex(void);  

void xmlerror(Document ** doc, const char * msg)
{
   fprintf(stderr,"%s\n",msg);
}

%}

%union {
   char * s;
}

%token EGAL SLASH SUP SUPSPECIAL DOCTYPE COLON INFSPECIAL INF CDATABEGIN
%token <s> VALEUR DONNEES COMMENT NOM CDATAEND

%parse-param {Document ** document}

%%

document
 : prolog element miscstar {*document = new Document(0,0,0);}
 ;
 
 prolog
 : miscstar prologend
 ;
 
 prologend
 : doctypedecl miscstar
 | /* vide */
 ;
 
 doctypedecl
 : DOCTYPE NOM SUP
 | DOCTYPE NOM NOM SUP
 | DOCTYPE NOM NOM VALEUR SUP
 ;
 
 miscstar
 : miscstar misc
 | /* vide */
 ;
 
 misc
 : COMMENT
 | pi
 ;

element
 : INF NOM COLON NOM attributestar SLASH SUP
 | INF NOM COLON NOM attributestar SUP content INF SLASH NOM COLON NOM SUP  
 | INF NOM attributestar SLASH SUP
 | INF NOM attributestar SUP content INF SLASH NOM SUP    
 ;
 
 attributestar
 : attributestar attribute
 | /* vide */
 ;
 
 attribute
 : NOM EGAL VALEUR
 | NOM COLON NOM EGAL VALEUR
 ;

content
 : content item          
 | /* vide */              
 ;
 
 item
 : element
 | cdsect
 | pi
 | COMMENT
 | DONNEES
 ;
 
 cdsect
 : CDATABEGIN CDATAEND
 ;
 
 pi
 : INFSPECIAL NOM attributestar SUPSPECIAL
 ;
