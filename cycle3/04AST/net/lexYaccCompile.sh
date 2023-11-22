lex lex.l
bison -d bi.y
gcc lex.yy.c bi.tab.c
./a.out 
