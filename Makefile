all: commun
commun: *.l *.y *.cpp *.h
	flex -Pxml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -DXMLDEBUG=1 -o xmltool main.cpp xml.tab.c lex.xml.c model/attribute.cpp model/cdSect.cpp model/comment.cpp model/docTypeDecl.cpp model/document.cpp model/donnees.cpp model/element.cpp model/pi.cpp model/prolog.cpp

clean:
	-rm -rf xml.tab.c lex.xml.c xml.tab.h xml.output xmltool commun
test:
	cd Tests; ./mktest.sh
