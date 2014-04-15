%{

#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;

#include "commun.h"
#include "model/document.h"
#include "model/docTypeDecl.h"
#include "model/attribute.h"
#include "model/cdSect.h"
#include "model/comment.h"
#include "model/donnees.h"
#include "model/element.h"
#include "model/misc.h"
#include "model/item.h"
#include "model/pi.h"
#include "model/prolog.h"

extern char xmltext[];

int xmllex(void);  

void xmlerror(Document ** doc, const char * msg)
{
   fprintf(stderr,"%s\n",msg);
}

%}

%union {
   char * s;
   DocTypeDecl * docType;
   Attribute * attribute;
   CDSect * cdSect;
   Comment * comment;
   Donnees * donnees;
   Element * element;
   Misc * misc;
   Item * item;
   PI * pi;
   Prolog * prolog;
   pair<DocTypeDecl *,vector<Misc*> *> * prologEnd;
   vector<Misc *> * miscStar;
   vector<Attribute *> * attributeStar;
   vector<Item *> * content;
}

%token EGAL SLASH SUP SUPSPECIAL DOCTYPE COLON INFSPECIAL INF CDATABEGIN
%token <s> VALEUR DONNEES COMMENT NOM CDATAEND
%type <prolog> prolog
%type <prologEnd> prologend
%type <docType> doctypedecl
%type <attribute> attribute
%type <cdSect> cdsect
%type <miscStar> miscstar
%type <attributeStar> attributestar
%type <misc> misc
%type <pi> pi
%type <element> element
%type <content> content
%type <item> item

%parse-param {Document ** document}

%%

document
 : prolog element miscstar {*document = new Document($1,$2,$3);}
 ;
 
 prolog
 : miscstar prologend {$$ = new Prolog($1,$2->first,$2->second); delete $2;}
 ;
 
 prologend
 : doctypedecl miscstar {$$ = new pair<DocTypeDecl *,vector<Misc*> *>($1,$2);}
 | /* vide */ {$$ = new pair<DocTypeDecl *,vector<Misc*> *>(0,0);}
 ;
 
 doctypedecl
 : DOCTYPE NOM SUP {$$ = new DocTypeDecl(new string($2), 0, 0); free($2);}
 | DOCTYPE NOM NOM SUP {$$ = new DocTypeDecl(new string($2), new string($3), 0); free($2) ; free($3);}
 | DOCTYPE NOM NOM VALEUR SUP {$$ = new DocTypeDecl(new string($2), new string($3), new string($4)); free($2); free($3) ; free($4);}
 ;
 
 miscstar
 : miscstar misc {(*$1)[$1->size()-1] = $2; $$ = $1;}
 | /* vide */ {$$ = new vector<Misc*>();}
 ;
 
 misc
 : COMMENT {$$ = new Comment(new string($1));}
 | pi {$$ = $1;}
 ;

element
 : INF NOM COLON NOM attributestar SLASH SUP {string * buf = new string($2); buf->append(":"); buf->append($4); $$ = new Element(buf,$5,0); free($2) ; free($4);}
 | INF NOM COLON NOM attributestar SUP content INF SLASH NOM COLON NOM SUP {string * buf = new string($2); buf->append(":"); buf->append($4); $$ = new Element(buf,$5,$7); if(strcmp($2,$10)!=0) {cerr<<"Non matching element namespaces "<<$2<<" and "<<$10<<endl;} if(strcmp($4,$12)!=0) {cerr<<"Non matching element names "<<$4<<" and "<<$12<<endl;}free($2) ; free($4) ; free($10) ; free($12);}  
 | INF NOM attributestar SLASH SUP {$$ = new Element(new string($2),$3,0); free($2);}
 | INF NOM attributestar SUP content INF SLASH NOM SUP {$$ = new Element(new string($2),$3,$5); if(strcmp($2,$8)!=0) {cerr<<"Non matching element names "<<$2<<" and "<<$8<<endl;}free($2) ; free($8);}
 ;
 
 attributestar
 : attributestar attribute {$1->push_back($2); $$ = $1;}
 | /* vide */ {$$ = new vector<Attribute *>();}
 ;
 
 attribute
 : NOM EGAL VALEUR {$$ = new Attribute(new string($1), new string($3));free($1); free($3);}
 | NOM COLON NOM EGAL VALEUR {string * buf = new string($1) ; buf->append(":") ; buf->append($3) ; $$ = new Attribute(new string($1), buf);free($1);free($3);free($5);}
 ;

content
 : content item {$1->push_back($2); $$ = $1;}          
 | /* vide */ {$$ = new vector<Item *>();}              
 ;
 
 item
 : element {$$ = $1;}
 | cdsect {$$ = $1;}
 | pi {$$ = $1;}
 | COMMENT {$$ = new Comment(new string($1));}
 | DONNEES {$$ = new Donnees(new string($1));free($1);}
 ;
 
 cdsect
 : CDATABEGIN CDATAEND {$$ = new CDSect(new string($2));}
 ;
 
 pi
 : INFSPECIAL NOM attributestar SUPSPECIAL {$$ = new PI(new string($2),$3);free($2);}
 ;
