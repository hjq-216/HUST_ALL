flex Vector.l

bison -d -v parser.y

gcc -o parser lex.yy.c parser.tab.c ast.c semantic.c

./parser test.c > result.log