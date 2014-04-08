/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_XML_XML_TAB_H_INCLUDED
# define YY_XML_XML_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int xmldebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EGAL = 258,
     SLASH = 259,
     SUP = 260,
     SUPSPECIAL = 261,
     DOCTYPE = 262,
     COLON = 263,
     INFSPECIAL = 264,
     INF = 265,
     CDATABEGIN = 266,
     VALEUR = 267,
     DONNEES = 268,
     COMMENT = 269,
     NOM = 270,
     CDATAEND = 271
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 37 "xml.y"

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


/* Line 2053 of yacc.c  */
#line 92 "xml.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE xmllval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int xmlparse (void *YYPARSE_PARAM);
#else
int xmlparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int xmlparse (Document ** document);
#else
int xmlparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_XML_XML_TAB_H_INCLUDED  */
