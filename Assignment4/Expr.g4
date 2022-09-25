grammar Expr;

program: statement+ ;  // at least one statement

statement : expr NEWLINE                
          | IDENTIFER '=' expr NEWLINE        
          | NEWLINE                   
          ;

expr: expr ('*'|'/') expr   
    | expr ('+'|'-') expr   
    | INTEGER                    
    | IDENTIFER                  
    | '(' expr ')'         
    ;

AND	:
ARRAY   :
ASM	:
BEGIN	:
BREAK	:
CASE	:
CONST	:
CONSTRUCTOR	:
CONTINUE	:
DESTRUCTOR	:
DIV	:
DO	:
DOWNTO	:
ELSE	:
END	:
FALSE	:
FILE	:
FOR	:
FUNCTION	:
GOTO	:
IF	:
IMPLEMENTATION	:
IN	:
INLINE	:
INTERFACE	:
LABEL	:
MOD	:
NIL	:
NOT	:
OBJECT	:
OF	:
ON	:
OPERATOR	:
OR	:
PACKED	:
PROCEDURE:

RECORD	:
REPEAT	:
SET	:
SHL	:
SHR	:
STRING	:
THEN	:
TO	:
TRUE	:
TYPE	:
UNIT	:
UNTIL	:
USES	:
VAR	:
WHILE	:
WITH	:
XOR	:
INTEGER   : [0-9]+ ;
REAL	:
IDENTIFER : [a-zA-Z]+ ; 
PLUSOP	:
MINUSOP	:
MULTOP	:
DIVOP	:
ASSIGN	:
EQUAL	:
NE	:
LTEQ	:
GTEQ	:
LT	:
GT	:
PLUSEQUAL	:
MINUSEQUAL	:
MULTEQUAL	:
DIVEQUAL	:
CARAT	:
SEMICOLOR	:
COMMA	:
LPAREN	:
RPAREN	:
LBRACKET	:
RBRACKET	:
LBRACE	:
RBRACE	:
LCOMMENT	:
RCOMMENT	:

NEWLINE   : '\r'? '\n' ;

WS : [ \t]+ -> skip ; 