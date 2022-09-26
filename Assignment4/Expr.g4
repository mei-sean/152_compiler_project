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

fragment A  :   [Aa];
fragment B  :   [Bb];
fragment C  :   [Cc];
fragment D  :   [Dd];
fragment E  :   [Ee];
fragment F  :   [Ff];
fragment G  :   [Gg];
fragment H  :   [Hh];
fragment I  :   [Ii];
fragment J  :   [Jj];
fragment K  :   [Kk];
fragment L  :   [Ll];
fragment M  :   [Mm];
fragment N  :   [Nn];
fragment O  :   [Oo];
fragment P  :   [Pp];
fragment Q  :   [Qq];
fragment R  :   [Rr];
fragment S  :   [Ss];
fragment T  :   [Tt];
fragment U  :   [Uu];
fragment V  :   [Vv];
fragment W  :   [Ww];
fragment X  :   [Xx];
fragment Y  :   [Yy];
fragment Z  :   [Zz];

AND	: 'A N D' ;
ARRAY   : 'A R R A Y' ;
ASM	: 'A S M' ;
BEGIN	: 'B E G I N' ;
BREAK	: 'B R E A K' ;
CASE	: 'C A S E' ;
CONST	: 'C O N S T' ;
CONSTRUCTOR	: 'C O N S T R U C T O R' ;
CONTINUE	: 'C O N T I N U E' ;
DESTRUCTOR	: 'D E S T R U C T O R' ;
DIV	: 'D I V' ;
DO	: 'D O' ;
DOWNTO	: 'D O W N T O' ;
ELSE	: 'E L S E' ;
END	: 'E N D' ;
FALSE	: 'F A L S E' ;
FILE	: 'F I L E' ;
FOR	: 'F O R' ;
FUNCTION	: 'F U N C T I O N' ;
GOTO	: 'G O T O' ;
IF	: 'I F' ;
IMPLEMENTATION	: 'I M P L E M E N T A T I O N' ;
IN	: 'I N' ;
INLINE	: 'I N L I N E' ;
INTERFACE	: 'I N T E R F A C E' ;
LABEL	: 'L A B E L' ;
MOD	: 'M O D' ;
NIL	: 'N I L' ;
NOT	: 'N O T' ;
OBJECT	: 'O B J E C T' ;
OF	: 'O F' ;
ON	: 'O N' ;
OPERATOR	: 'O P E R A T O R' ;
OR	: 'O R' ;
PACKED	: 'P A C K E D' ;
PROCEDURE: 'P R O C E D U R E' ;
PROGRAM : 'P R O G R A M' ;
RECORD	: 'R E C O R D' ;
REPEAT	: 'R E P E A T' ;
SET	: 'S E T' ;
SHL	: 'S H L' ;
SHR	: 'S H R' ;
STRING	: 'S T R I N G' ;
THEN	: 'T H E N' ;
TO	: 'T O' ;
TRUE	: 'T R U E' ;
TYPE	: 'T Y P E' ;
UNIT	: 'U N I T' ;
UNTIL	: 'U N T I L' ;
USES	: 'U S E S' ;
VAR	: 'V A R' ;
WHILE	: 'W H I L E' ;
WITH	: 'W I T H' ;
XOR	: 'X O R' ;
INTEGER   : [0-9]+ ;
REAL	: (MINUSOP)? INTEGER;
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