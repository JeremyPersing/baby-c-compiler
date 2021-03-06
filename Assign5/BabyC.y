%{
	#include <stdio.h>
	#include "my_code.h"

// The parser needs to call the scanner to get the next token
	extern int yylex();

// The error function
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here
%initial-action
{

}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...)
%union
{
	struct ASTNode* node; // Most $$ values will be ASTNodes
	int num; // Integer numbers
	char* string; // Strings for identifiers
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM
//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> StatementList
%type <node> LHS
// Add the rest of the types for the grammar's symbols
%type <node> While
%type <node> If
%type <node> Condition
%type <node> CompareTerm
%type <node> CompareFactor
%type <node> Compare
%type <node> Op
%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot=$6;} // Store the AST root node in gASTRoot;

DeclarationList:  | Declaration DeclarationList // Note that a DeclarationList may be empty
;

Declaration: "int" IDENT ';' {AddDeclaration($2); printf("Processing declaration of %s\n", $2);};


StatementList: {$$ = NULL;}
               | Statement StatementList	{$$ = CreateStatementListNode($1,$2); printf("Adding a Statement to a Statement list \n");};

Statement: Assignment {$$ = $1;}
          | If {$$ = $1;}
          | While {$$ = $1;};

While: WHILE '(' Condition ')' '{' StatementList '}' {$$ = CreateWhileNode($3, $6); printf("Creating while loop node\n");};

If: IF '(' Condition ')' '{' StatementList '}' {$$ = CreateIfNode($3, $6); printf("Creating if Statement node\n");}
  | IF '(' Condition ')' '{' StatementList '}' ELSE '{' StatementList '}' {$$ = CreateIfElseNode($3, $6, $10); printf("Creating if-else Statement node\n");};

Condition: Condition CompareTerm {$$ = CreateCompareList($1, $2);}
          | CompareTerm {$$ = $1;};

CompareTerm: CompareTerm OR CompareFactor {$$ = CreateOrNode($1, $3); printf("Create OR node\n");}
            | CompareFactor {$$ = $1;};

CompareFactor: Compare AND Compare  {$$ = CreateAndNode($1, $3); printf("Create AND node\n")}
              | Compare {$$ = $1;};

Compare: Expr Op Expr {$$ = CreateCompareNode($2, $1, $3); printf("Creating Compare node\n");};

Op: EQ
  | NE
  | '<'
  | '>'
  | LE
  | GE

Assignment: LHS '=' Expr ';'  {$$ = CreateAssignNode($1, $3); printf("Creating Assignment node \n");};

LHS: IDENT {$$ = GetValidIdentNode($1); printf("Creating left-hand IDENT node for %s\n", $1);};

Expr: Expr '+' Term {$$ = CreateAddNode($1, $3); printf("Creating Addition node\n");}
     | Expr '-' Term {$$ = CreateSubNode($1, $3); printf("Creating Subtraction node\n");}
     | Term {$$ = $1;};

Term: Term '*' Factor {$$ = CreateMultNode($1, $3); printf("Creating Multiplication node\n");}
      | Term '/' Factor {$$ = CreateDivNode($1, $3); printf("Creating Division node\n");}
                | Factor {$$ = $1;};

Factor: IDENT       {$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
        | NUM       {$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
        | '('Expr')'    {$$ = $2; printf("Creating Expression node in parentheses\n");};


%%
