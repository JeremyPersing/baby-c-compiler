#include "my_code.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ASTNode* head = NULL;
int counter = 0;
int offset = 0;

int GetNextReg() {
  return counter++;
}

// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_NUM;
        node->num = num;
        return node;
}


ASTNode* CreateIdentNode(char* name)
{
        ASTNode* curr = head;
        while (curr != NULL) {
             if (strcmp(curr->name, name) == 0) {
                  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
                  node->type = ASTNODE_IDENT;
                  return node;
             }
             curr = curr->next;
        }
       yyerror("Ident not declared"); // yyerror exits the program so no return val needed
}

ASTNode* CreateAssignNode(ASTNode* lhs, ASTNode* expr)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_ASSIGN;
        node->left = lhs;
        node->right = expr;
        return node;
}

ASTNode* CreateAddNode(ASTNode* expr, ASTNode* term)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_ARITH_OP;
        node->op = ADD_OP;
        node->left = expr;
        node->right = term;
        return node;
}

ASTNode* CreateSubNode(ASTNode* expr, ASTNode* term)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_ARITH_OP;
        node->op = SUB_OP;
        node->left = expr;
        node->right = term;
        return node;
}

ASTNode* CreateMultNode(ASTNode* term, ASTNode* factor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_ARITH_OP;
        node->op = MULT_OP;
        node->left = term;
        node->right = factor;
        return node;
}

ASTNode* CreateDivNode(ASTNode* term, ASTNode* factor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_ARITH_OP;
        node->op = DIV_OP;
        node->left = term;
        node->right = factor;
        return node;
}

ASTNode* CreateWhileNode(ASTNode* condition, ASTNode* stList)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_WHILE;
        node->left = condition;
        node->right = stList;
        return node;
}

ASTNode* CreateIfNode(ASTNode* condition, ASTNode* stList)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_IF;
        node->left = condition;
        node->right = stList;
        return node;
}

ASTNode* CreateIfElseNode(ASTNode* condition, ASTNode* thenStList, ASTNode* elseStList)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_IF;
        node->left = condition;
        node->center = thenStList;
        node->right = elseStList;
        return node;
}

ASTNode* CreateCompareList(ASTNode* conditionList, ASTNode* compareTerm)
{
        if (conditionList == NULL) {
                printf("ConditionList was null\n");
                ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
                node->type = ASTNODE_COMPARELIST;
        }
        conditionList->next = compareTerm;
        return conditionList;
}

ASTNode* CreateOrNode(ASTNode* compareTerm, ASTNode* compareFactor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_LOGIC_OP;
        node->left = compareTerm;
        node->right = compareFactor;
        node->op = OR_OP;
        return node;
}

ASTNode* CreateAndNode(ASTNode* compareOne, ASTNode* compareTwo)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_LOGIC_OP;
        node->left = compareOne;
        node->right = compareTwo;
        node->op = AND_OP;
        return node;
}

ASTNode* CreateCompareNode(ASTNode* op, ASTNode* exprOne, ASTNode* exprTwo)
{
        //ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        ASTNode*  node = op;
        node->right = exprTwo;
        node->left = exprOne;
        node->type = ASTNODE_COMPARE;
        return node;
}

ASTNode* CreateLessThanNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = LT_OP;
        return node;
}

ASTNode* CreateLessThanOrEqualNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = LE_OP;
        return node;
}

ASTNode* CreateGreaterThanNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = GT_OP;
        return node;
}

ASTNode* CreateGreaterThanOrEqualNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = GE_OP;
        return node;
}

ASTNode* CreateEqualNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = EQ_OP;
        return node;
}

ASTNode* CreateNotEqualNode(char* op)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = NE_OP;
        return node;
}

// Returns an identifier node that has already been added to the table
ASTNode* GetValidIdentNode(char* name)
{
        ASTNode* curr = head;
        while (curr != NULL) {
                if (strcmp(curr->name, name) == 0) {
                        return curr;
                }
                curr = curr->next;
        }
        yyerror("Ident not declared"); // yyerror exits the program so no return val needed
}


// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
        if (stList == NULL) {
                stList = (ASTNode*)malloc(sizeof(ASTNode));
                stList->type = ASTNODE_STLIST;
        }
        stList->next = st;
        return stList;
}


void AddDeclaration(char* name)
{
       // Check if the variable has already been declared
       ASTNode* curr = head;
       while(curr != NULL) {
               if (strcmp(curr->name, name) == 0) {
                    // The variable has been declared already
                    char errorMsg [] = "Multiple declarations of '";
                    strncat(errorMsg, name, 1);
                    char ending = '\'';
                    strncat(errorMsg, &ending, 1);
                    yyerror(errorMsg);
               }
               curr = curr->next;
       }

       // Variable has not been declared
       ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
       newNode->name = name;
       newNode->offset = offset;
       offset += 4;
       printf("Node %s has the offset of %d", name, offset);


       newNode->next = head;
       head = newNode;
}


// Commented out in this assignment
void GenerateILOC(ASTNode* node);
{
        printf("Generating ILOC \n");
}

int ExprILOC(ASTNode* node)
{
  switch (node->type) {
    int reg;
    case ASTNODE_NUM:
      reg = GetNextReg();
      EmitNum(node->num, reg);
      break;
    case ASTNODE_IDENT
      reg = GetNextReg();
      EmitVar(node->offset, reg);
      break;
    case: ASTNODE_ARITH_OP:

  }
}

void IfILOC(ASTNode* node);

void EmitNum(int num, int destination) {
  printf("loadI %d -> r%d\n", num, destination);
}

void EmitVar(int offset, int destination)
{
  printf("loadAI rarp, %d -> r%d", offset, destination);
}
