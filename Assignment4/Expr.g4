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

AND	: 'and' ;
ARRAY   : 'array' ;
ASM	: 'asm' ;
BEGIN	: 'begin' ;
BREAK	: 'break' ;
CASE	: 'case' ;
CONST	: 'const' ;
CONSTRUCTOR	: 'constructor' ;
CONTINUE	: 'continue' ;
DESTRUCTOR	: 'destructor' ;
DIV	: 'div' ;
DO	: 'do' ;
DOWNTO	: 'downto' ;
ELSE	: 'else' ;
END	: 'end' ;
FALSE	: 'false' ;
FILE	: 'file' ;
FOR	: 'for' ;
FUNCTION	: 'function' ;
GOTO	: 'goto' ;
IF	: 'if' ;
IMPLEMENTATION	: 'implementation' ;
IN	: 'in' ;
INLINE	: 'inline' ;
INTERFACE	: 'interface' ;
LABEL	: 'label' ;
MOD	: 'mod' ;
NIL	: 'nil' ;
NOT	: 'not' ;
OBJECT	: 'object' ;
OF	: 'of' ;
ON	: 'on' ;
OPERATOR	: 'operator' ;
OR	: 'or' ;
PACKED	: 'packed' ;
PROCEDURE: 'procedure' ;
PROGRAM : 'program' ;
RECORD	: 'record' ;
REPEAT	: 'repeat' ;
SET	: 'set' ;
SHL	: 'shl' ;
SHR	: 'shr' ;
STRING	: 'string' ;
THEN	: 'then' ;
TO	: 'to' ;
TRUE	: 'true' ;
TYPE	: 'type' ;
UNIT	: 'unit' ;
UNTIL	: 'until' ;
USES	: 'uses' ;
VAR	: 'var' ;
WHILE	: 'while' ;
WITH	: 'with' ;
XOR	: 'xor' ;
INTEGER   : [0-9]+ ;
REAL	:
IDENTIFER : [a-zA-Z]+ ; 
PLUSOP	: '+' ;
MINUSOP	: '-' ;
MULTOP	: '*' ;
DIVOP	: '/' ;
ASSIGN	: ':=' ;
EQUAL	: '=' ;
NE	: '<>' ;
LTEQ	: '<=' ;
GTEQ	: '>=' ;
LT	: '<' ;
GT	: '>' ;
PLUSEQUAL	: '+=' ;
MINUSEQUAL	: '-=' ;
MULTEQUAL	: '*=' ;
DIVEQUAL	: '/=' ;
CARAT	: '^' ;
SEMICOLOR	: ';' ;
COMMA	: ',' ;
LPAREN	: '(' ;
RPAREN	: ')' ;
LBRACKET	: '[' ;
RBRACKET	: ']' ;
LBRACE	: '{' ;
RBRACE	: '}' ;
LCOMMENT	: '(*' ;
RCOMMENT	: '*)' ;

NEWLINE   : '\r'? '\n' ;

WS : [ \t]+ -> skip ; 