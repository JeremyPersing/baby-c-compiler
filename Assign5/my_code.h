#ifndef YOUR_CODE_H
#define YOUR_CODE_H

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT,
	ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE, ASTNODE_STLIST, ASTNODE_COMPARELIST} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{ADD_OP, MULT_OP, DIV_OP, SUB_OP, OR_OP, AND_OP, EQ_OP, NE_OP, LT_OP, GT_OP, LE_OP, GE_OP} ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type;
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	int offset;
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child

	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list
    ASTNode* center; // pointer for the if-else ASTNode
// Depending on your implementation, you may need to add other fields to this struct
};

// Add functions to create the different kinds of ASTNodes
// These functions are called by the code embedded in the grammar.
// Here are some samples:
ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* CreateAssignNode(ASTNode* lhs, ASTNode* expr);
ASTNode* CreateAddNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateSubNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateMultNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateDivNode(ASTNode* term, ASTNode* factor);
ASTNode* GetValidIdentNode(char* name);

ASTNode* CreateWhileNode(ASTNode* condition, ASTNode* stList);
ASTNode* CreateIfNode(ASTNode* condition, ASTNode* stList);
ASTNode* CreateIfElseNode(ASTNode* condition, ASTNode* thenStList, ASTNode* elseStList);
ASTNode* CreateCompareList(ASTNode* condition, ASTNode* compareTerm);
ASTNode* CreateOrNode(ASTNode* compareTerm, ASTNode* compareFactor);
ASTNode* CreateAndNode(ASTNode* compareOne, ASTNode* compareTwo);
ASTNode* CreateCompareNode(ASTNode* op, ASTNode* exprOne, ASTNode* exprTwo);
ASTNode* CreateLessThanNode(char* op);
ASTNode* CreateLessThanOrEqualNode(char* op);
ASTNode* CreateGreaterThanNode(char* op);
ASTNode* CreateGreaterThanOrEqualNode(char* op);
ASTNode* CreateEqualNode(char* op);
ASTNode* CreateNotEqualNode(char* op);
// Need a function to add a declaration to your symbol table
void AddDeclaration(char* name);

// This is the function that generates ILOC code after the construction of the AST
void GenerateILOC(ASTNode* node);
int ExprILOC(ASTNode* node);
void IfILOC(ASTNode* node);
void EmitNum(int num, int destination);
void EmitVar(int offset, int destination);
#endif
