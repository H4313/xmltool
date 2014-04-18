all: commun
commun: *.l *.y *.cpp *.h
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -o ./Tests/xmltool main.cpp validationxsd.cpp xml.tab.c lex.xml.c model/attribute.cpp model/cdSect.cpp model/comment.cpp model/docTypeDecl.cpp model/document.cpp model/donnees.cpp model/element.cpp model/pi.cpp model/prolog.cpp maintools.cpp

clean:
	-rm -rf xml.tab.c lex.xml.c xml.tab.h xml.output xmltool.dSYM ./Tests/results.csv ./Tests/xmltool ./Tests/xmltool.exe ./Tests/xmltool.dSYM commun

prez: *.l *.y *.cpp *.h
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -DXSDPRINT=1 -o ./Tests/xmltool main.cpp validationxsd.cpp xml.tab.c lex.xml.c model/attribute.cpp model/cdSect.cpp model/comment.cpp model/docTypeDecl.cpp model/document.cpp model/donnees.cpp model/element.cpp model/pi.cpp model/prolog.cpp maintools.cpp

test:
	cd Tests; ./mktest.sh
	
test1:
	cd Tests/; ./xmltool -p files/simple_no_att.xml

test2:
	cd Tests/; ./xmltool -v files/book_good.xml files/book.xsd;
		
test3:
	cd Tests/; ./xmltool -t files/catalog.xml files/catalog_foreach.xsl

debug: *.l *.y *.cpp *.h
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -DXMLDEBUG=1 -o ./Tests/xmltool main.cpp validationxsd.cpp xml.tab.c lex.xml.c model/attribute.cpp model/cdSect.cpp model/comment.cpp model/docTypeDecl.cpp model/document.cpp model/donnees.cpp model/element.cpp model/pi.cpp model/prolog.cpp maintools.cpp
