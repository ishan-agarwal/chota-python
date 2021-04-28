%{
#include<stdio.h> 
#include<stdlib.h> 
#include "y.tab.h"
#include<string.h>
#define MAXQUADS 250



FILE *fp_icg, *fp_quad;
char temp_var[100];
int m = 0;        //string length for temp_var
int unop =0;
int paramno=0;
char final_out[1024];

typedef struct Node
{
  struct Node *parent;
  struct Node *sibling;
  struct Node *child;
  char *token;
  int leaf;
}Node;

typedef struct tree
{
  Node *node;
}tree;

typedef struct Quad
{
  char *Res;
  char *A1;
  char *A2;
  char *Op;
  int I;
  
} Quad;

Quad* allQuads=NULL;
int qIndex = 0; // quadruple entry no
//allQuads = 


tree *tree_init();
Node* create_node(Node *parent, char *token, int leaf);
void push(Node* node);
void printTree(tree* T);
void print(Node* node);


tree *tree_init()
{
  tree *temp= (tree*)malloc(sizeof(tree));
  temp->node = NULL;
  return(temp);
}

void makeQuad(char *Op, char *A1, char *A2, char *Res)
  {
    
    allQuads[qIndex].Res = (char*)malloc(strlen(Res)+1);
    allQuads[qIndex].Op = (char*)malloc(strlen(Op)+1);
    allQuads[qIndex].A1 = (char*)malloc(strlen(A1)+1);
    allQuads[qIndex].A2 = (char*)malloc(strlen(A2)+1);
    
    strcpy(allQuads[qIndex].Res, Res);
    strcpy(allQuads[qIndex].A1, A1);
    strcpy(allQuads[qIndex].A2, A2);
    strcpy(allQuads[qIndex].Op, Op);
    allQuads[qIndex].I = qIndex;
 
    qIndex++;
    
    return;
  }


Node* create_node(Node *parent, char *token, int leaf) 
{
  Node *newnode = (Node*)malloc(sizeof(Node));
  newnode->token = (char*)malloc(strlen(token)*sizeof(char));
  strcpy(newnode->token, token);
  newnode->parent = parent;
  newnode->sibling = NULL;
  newnode->child = NULL;
  newnode->leaf=leaf;
  return(newnode);
}

void print(Node* node) 
{ 
    if(node == NULL) 
        return; 

    printf("%s ",node->token);
    print(node->child);  
    print(node->sibling); 
}

void printTree(tree* T)
{
  print(T->node);
  printf("\n");
}

void first_val(char *first, char *temp)
{
    int i=0;int n=strlen(first);
    while(i<n && first[i]!=',')
    {
      temp[i]=first[i];i++;
    }
}

void expand(char *str, char *temp)
{
  char *pt;int a=0,b=0,c=0,i=0; char buffer[1024]="";
  pt = strtok(str,",");
  if(pt==NULL)
  {
    if(strlen(str)==0)
    {
    strcat(temp,"");
    return;
    }
  }
  a=atoi(pt);
  pt = strtok(NULL,",");
  if(pt==NULL)
  {
    i=0;
    while(i<a-1)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i++;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return;
  }
  b=atoi(pt);
  pt = strtok (NULL,",");
  if(pt==NULL)
  {
    i=a;
    while(i<b-1)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i++;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return;
  }  
  c=atoi(pt);
  i=a;
  if(c>0)
  {
  while(i<b-c)
  {
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);strcat(temp,",");
    i+=c;
  }
  sprintf(buffer,"%d",i);
  strcat(temp,buffer);
  return;
  }
  else 
  {

    while(i>b-c)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i+=c;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return; 
  }

}

void len(char *val,char *temp)
{
  int t=strlen(val);
  t=t-t/2;
  sprintf(temp,"%d",t);
}

tree *head = NULL;

void add_child(Node* parent, Node* child)
{
  if(parent==NULL)
    return;
  
  if(parent->child==NULL)
  {
    parent->child = child;
  }
  else
  {
    Node *n = parent->child;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    n->sibling = child;
  }
  child->parent = parent;
}

void add_sibling(Node* left, Node* new)
{
  if(left==NULL)
  {
    left = new;
    return;
  }
  
  if(left->sibling==NULL)
  {
    left->sibling = new;
  }
  else
  {
    Node *n = left;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    n->sibling = new;
  }
}

Node* end_node(Node* left)
{
  if(left==NULL)
    return NULL;
  
  if(left->sibling==NULL)
  {
    return left;
  }
  else
  {
    Node *n = left;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    return n;
  }
}



int tempno = 0, ln = 0; //temp variable no, label no
int exprno = -1; //expr no

%} 

%union{ struct{char value[1024]; int type;struct Node *node;char lhs[1024]  ;char code[1024];char begin[1024]; char end[1024];}ctype; char val[1024]; };
%token DOT LINE FALSE NONE TRUE LAND BREAK CONTINUE ELIF DEL ELSE FOR IF IN NOT LOR WHILE INPUT PRINT INT FLOAT STR LIST SPLIT MAP APPEND POP INSERT LEN ID CINT CFLOAT SEMI COMMA CSTR EPOP MUL DIV FDIV MOD ADD SUB ASOP G L GE LE EOP NEOP XOR BAND BOR LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET RANGE COLON
%type <ctype> Exp Const Or_Exp And_Exp In_Exp Eq_Exp Rel_Exp Bit_Exp Add_Exp Mul_Exp Pow_Exp Unary_Exp Primary_Exp ID Iterable Param_list Translation_unit Stmt Assignment_stmt Simple_stmt Compound_stmt Jump_stmt Print_stmt If_stmt Elif_stmt Else_stmt While_stmt For_stmt Expression_stmt Start
%type<val> DOT LINE FALSE NONE TRUE LAND BREAK CONTINUE ELIF DEL ELSE FOR IF IN NOT LOR WHILE INPUT PRINT INT FLOAT STR LIST SPLIT MAP APPEND POP INSERT LEN  CINT CFLOAT SEMI COMMA CSTR EPOP MUL DIV FDIV MOD ADD SUB ASOP G L GE LE EOP NEOP XOR BAND BOR LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET RANGE COLON 
%% 
Start: Translation_unit
{
  /*add_child(head->node,create_node(NULL,"Translation_unit",0));
  add_child(head->node->child,$1.node);*/
  printf("%s",$1.code);
}
;
Translation_unit: Stmt Translation_unit 
{
  /*$$.node = create_node(NULL,"Stmt",0);
  add_child(end_node($$.node),$1.node);
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$2.node);*/
  //printf("TU\n%s",$1.code);
  //printf("TU2\n%s",$2.code);
  sprintf($$.code,"%s\n%s",$1.code,$2.code);
}
| Stmt
{
  /*$$.node = create_node(NULL,"Stmt",0);
  add_child(end_node($$.node),$1.node);*/
  strcpy($$.code,$1.code);
  //printf("%s",$1.code);
}
;
Stmt: Simple_stmt SEMI 
{
  /*$$.node=create_node(NULL,"Simple_stmt",0);
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,";",0));*/
  strcpy($$.code,$1.code);
  //printf("simp%s",$1.code);
}
| Compound_stmt 
{
  /*$$.node=create_node(NULL,"Compound_stmt",0);
  add_child($$.node,$1.node);*/
  strcpy($$.code,$1.code);
  //printf("cmp%s",$1.code);
}
| Assignment_stmt SEMI 
{
  /*$$.node=create_node(NULL,"Assignment_stmt",0);
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,";",0));*/
  //printf("assg%s",$1.code);
  strcpy($$.code,$1.code);

}
;
Assignment_stmt: ID ASOP Exp 
{
  char buff[3]="";
  sprintf(buff,"%d",$3.type);
  insert("ID",$1.value,buff,$3.value,-1);
  /*$$.node=create_node(NULL,"ID",0);
  add_child($$.node,create_node(NULL,$1.value,0));
  add_sibling($$.node,create_node(NULL,"=",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf($$.code,"%s\n=\t%s\t\t%s\n",$3.code,$3.lhs,$1.value);

  


}
Simple_stmt: Expression_stmt 
{
  //$$.node=create_node(NULL,"Expression_stmt",0);add_child($$.node,$1.node);
  strcpy($$.code,$1.code);
}
| Print_stmt 
{
  paramno=0;
  //$$.node=create_node(NULL,"Print_stmt",0);add_child($$.node,$1.node);
  strcpy($$.code,$1.code);
}
| Jump_stmt 
{
  //$$.node=create_node(NULL,"Jump_stmt",0);add_child($$.node,$1.node);
  strcpy($$.code,$1.code);

}
;
Compound_stmt: If_stmt 
{
  //$$.node=create_node(NULL,"If_stmt",0);add_child($$.node,$1.node);
  //printf("IF STATEMENT\n%s",$1.code);
  strcpy($$.code,$1.code);
}
| While_stmt 
{
  
  //$$.node=create_node(NULL,"While_stmt",0);add_child($$.node,$1.node);
  //printf("WHILE STATEMENT%s",$1.code);
  strcpy($$.code,$1.code);
}
| For_stmt 
{
  //$$.node=create_node(NULL,"For_stmt",0);add_child($$.node,$1.node);

}
;
Jump_stmt: BREAK 
{
  //$$.node=create_node(NULL,"BREAK",0);
  sprintf($$.code,"goto\t \t \tL%d",ln);

}
| CONTINUE 
{
  //$$.node=create_node(NULL,"CONTINUE",0);
}
;
Print_stmt: PRINT LPAREN Param_list RPAREN 
{
  /*$$.node=create_node(NULL,"PRINT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
  //printf("call\t \tprint\t%d\n",paramno);
  sprintf($$.code,"%s\ncall\t \tprint\t%d\n",$3.code,paramno);
}
;
Param_list: Param_list COMMA Exp  
{
  $$.type=50+$3.type;strcat($$.value,",");
  strcat($$.value,$3.value);
  /*$$.node = create_node(NULL,"Param_list",0);
  add_child(end_node($$.node),$1.node);
  add_sibling($$.node,create_node(NULL,",",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf($$.lhs,$1.lhs);
  //printf("param\t \t%s\n",$3.lhs);
  sprintf($$.code,"%s\n\t%s\nparam\t \t \t%s\n",$1.code,$3.code,$3.lhs);
  paramno++;
}
| Exp 
{  
  /*$$.node = create_node(NULL,"EXP",0);
  add_child(end_node($$.node),$1.node);*/
  //strcpy($$.code,$1.code);
  sprintf($$.lhs,"%s",$1.lhs);
  //printf("%s\nparam\t \t%s\n",$1.code,$1.lhs);
  sprintf($$.code,"%s\nparam\t \t \t%s\n",$1.code,$1.lhs);
  paramno++;



} 
;
If_stmt: IF Exp COLON LBRACE Translation_unit RBRACE Elif_stmt Else_stmt 
{
  /*$$.node = create_node(NULL,"IF",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));
  add_sibling($$.node,create_node(NULL,"Elif_stmt",0));
  add_child(end_node($$.node),$7.node);
  add_sibling($$.node,create_node(NULL,"Else_stmt",0));
  add_child(end_node($$.node),$8.node);*/

  
  //strcpy($$.code,$2.code);
  //////printf("code is:\n If False %s goto L%d\n",$$.code,ln++);
  //printf("IfFalse\t%s\t \tL%d\n",$$.code,ln);

  sprintf($$.begin,"L%d",ln++);
  sprintf($$.end,"L%d",ln++);
  strcpy($$.end,$8.end);
  sprintf($$.code,"Label\t \t \t%s\n%sIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\n%s\n%s\n",$$.begin,$2.code,$2.lhs,$7.begin,$5.code,$8.end,$7.code,$8.code);

  

}
;
Elif_stmt: ELIF Exp COLON LBRACE Translation_unit RBRACE Elif_stmt
{
  /*$$.node = create_node(NULL,"ELIF",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));
  add_sibling($$.node,create_node(NULL,"Elif_stmt",0));
  add_child(end_node($$.node),$7.node);*/
  int l=ln;
  ln++;
  ////printf("code is:\n L%d\n",l);
  //printf("Label\t \t \tL%d\n",l);
  sprintf($$.begin,"L%d",ln++);
  sprintf($$.end,"L%d",ln++);
  //sprintf($$.code,"elif code");
  sprintf($$.code,"Label\t \t \t%s\n%sIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\n%s\n",$$.begin,$2.code,$2.lhs,$7.begin,$5.code,final_out,$7.code);
} 
| {int l=ln;
  //ln++;
  sprintf($$.begin,"L%d",ln);
  sprintf($$.end,"L%d",ln);
  sprintf($$.code,"Label\t \t \t%s\n",$$.end);

  }
;
Else_stmt: ELSE COLON LBRACE Translation_unit RBRACE
{
  /*$$.node = create_node(NULL,"ELSE",0);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$4.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/

  //int l=ln;
  //ln++;
  ////printf("code is:\n L%d\n",l);
  //printf($$.code,"Label\t \t \tL%d\n",l);


  int l=ln;
  ln++;
  ////printf("code is:\n L%d\n",l);
  //printf("Label\t \t \tL%d\n",l);
  sprintf($$.begin,"L%d",ln++);
  sprintf($$.end,"L%d",ln++);
  strcpy(final_out,$$.end);
  //sprintf($$.code,"else code");
  //sprintf($$.code,"Label\t \t \t%s\n%s\ngoto\t \t \t%s\nLabel\t \t \t%s\n",$$.begin,$4.code,$$.end,$$.end);
  sprintf($$.code,"%s\ngoto\t \t \t%s\nLabel\t \t \t%s",$4.code,$$.end,$$.end);

} 
| {
  int l=ln;
  //ln++;
  sprintf($$.begin,"L%d",ln);
  sprintf($$.end,"L%d",ln);
  ////printf("code is:\n L%d\n",l);
  //sprintf($$.code,"Label\t \t \tL%d\n",l);
  //sprintf($$.code,"Label\t \t \t%s\n",$$.end);

  }
;
While_stmt: WHILE Exp COLON LBRACE Translation_unit RBRACE 
{
  /*$$.node = create_node(NULL,"WHILE",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/

  ////printf("code is : \nL%d:\n", ln);
  //printf("Label\t \t \tL%d\n",ln); //quad format: op =label a1=null a2=null res=l<ln>
  //ln++;
  //strcpy($$.code,$2.code);
  ////printf("code is If False %s goto L%d\n",$$.code,ln);
  ////printf("code is : \nL%d:\n", ln);


  sprintf($$.begin,"L%d",ln++);
  sprintf($$.end,"L%d",ln++);

  sprintf($$.code,"Label\t \t \t%s\n %s \nIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\nLabel\t \t \t%s \n",$$.begin,$2.code,$2.lhs,$$.end,$5.code,$$.begin,$$.end);

  //printf("%s",$$.code);
  /*printf("code is : \nL%d:\n", ln);
  //printf("Quadruple is:\n \tLabel\t  \t L%d\n\n", ln); //quad format: op =label a1=null a2=null res=l<ln>
  //ln++;
  //strcpy($$.code,$2.code);
  //printf("code is If False %s goto L%d\n",$$.code,ln);
  //printf("code is : \nL%d:\n", ln);*/




}
;
For_stmt: FOR ID IN Iterable COLON LBRACE Translation_unit RBRACE 
{
  char temp[1024]="";
  first_val($4.value,temp);
  char buff[3]="";
  sprintf(buff,"%d",$4.type%10);
  insert("ID",$2.value,buff,temp,-1);
  /*$$.node = create_node(NULL,"FOR",0);
  add_sibling($$.node,create_node(NULL,"ID",0));
  add_child(end_node($$.node),create_node(NULL,$2.value,0));
  add_sibling($$.node,create_node(NULL,"in",0));
  add_sibling($$.node,create_node(NULL,"Iterable",0));
  add_child(end_node($$.node),$4.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$7.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/


  ////printf("code is : \nL%d:\n", ln);
  printf("Label\t \t \tL%d\n",ln);//quad format: op =label a1=null a2=null res=l<ln>
  ln++;

  strcpy($$.code,$2.code);
  ////printf("code is If False %s goto L%d\n",$$.code,ln);
  ////printf("code is : \nL%d:\n", ln);
}
;
Iterable: LBRACKET Param_list RBRACKET  
{
  $$=$2;
  /*$$.node = create_node(NULL,"[",0);
  add_sibling($$.node,create_node(NULL,"Param_list",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,"]",0));*/
}
| RANGE LPAREN Param_list RPAREN 
{
  $$.type=51;
  char temp[1024]="";
  expand($3.value,temp);strcpy($$.value,temp);
  /*$$.node = create_node(NULL,"RANGE",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"Param_list",0));
  add_child(end_node($$.node),$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
}
; 
Expression_stmt: Exp 
{
 /* $$.node = create_node(NULL,"Exp",0);
  add_child($$.node,$1.node);*/
  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);


}
;
Exp: Or_Exp 
{
  /*$$.node = create_node(NULL,"Or_Exp",0);
  add_child($$.node,$1.node);*/
  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);

  
}
;
Const: CINT 
{
  $$.type=1;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"CINT",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //printf("in const cint %s\n",$1);
  //strcpy($$.lhs,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;
}
| CFLOAT 
{
  $$.type=2;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"CFLOAT",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;
}
| CSTR 
{
  $$.type=3;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"CSTR",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;
}
| TRUE 
{
  $$.type=4;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"TRUE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/
  //strcpy($$.code,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;

}
| FALSE 
{
  $$.type=4;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"FALSE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;
}
| NONE 
{
  $$.type=5;
  strcpy($$.value,$1);
  /*$$.node = create_node(NULL,"NONE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/
  //strcpy($$.code,$1);
  sprintf($$.lhs,"%s",$1);
  exprno=0;

  //tempno++;
}
| INPUT LPAREN RPAREN 
{
  $$.type=3;
  strcpy($$.value,"");
  /*$$.node = create_node(NULL,"INPUT",0);
  add_child($$.node,create_node(NULL,$$.value,0));
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,")",0));*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  //sprintf($$.code,temp_var);
  printf("call\t%s\tinput\t0\n",temp_var);
  sprintf($$.lhs,"%s",temp_var);
}
;
Primary_Exp: ID 
{
 
  $$=$1; 
  /*$$.node = create_node(NULL,"ID",0); 
  add_child($$.node,create_node(NULL,$1.value,0));*/

  //strcpy($$.code,$1.value);
  //printf("in id %s\n",$1.value);

  sprintf($$.lhs,"%s",$1.value);
  exprno=0;
  //tempno++;

 


}
| Const 
{
  $$=$1;  
  /*$$.node = create_node(NULL,"Const",0); 
  add_child($$.node,$1.node);*/

  
}
| LPAREN Exp RPAREN 
{
  $$=$2;
  /*$$.node = create_node(NULL,"(",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$2.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/

  strcpy($$.code,$2.code);
  sprintf($$.lhs,"%s",temp_var);
  exprno=1;
}
| Iterable 
{
  $$=$1;
  /*$$.node = create_node(NULL,"Iterable",0);
  add_child($$.node,$1.node);*/
}
| LEN LPAREN Iterable RPAREN 
{
  $$.type=1;
  char buffer[10]="";
  len($3.value,buffer) ;
  strcpy($$.value,buffer);
  /*$$.node = create_node(NULL,"LEN",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"Iterable",0));
  add_child(end_node($$.node),$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
}
| INT LPAREN Exp RPAREN 
{
  $$.type=1;
  strcpy($$.value,$3.value);
  /*$$.node = create_node(NULL,"INT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
| FLOAT LPAREN Exp RPAREN 
{
  $$.type=2;
  strcpy($$.value,$3.value);
  /*$$.node = create_node(NULL,"FLOAT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
| STR LPAREN Exp RPAREN 
{
  $$.type=3;
  strcpy($$.value,$3.value);
  /*$$.node = create_node(NULL,"STR",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
;
Unary_Exp: SUB Primary_Exp 
{
  $$.type=$2.type;
  char buffer[1024]="-";
  strcat(buffer,$2.value);
  strcpy($$.value,buffer);
  /*$$.node = create_node(NULL,"-",0); 
  add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  add_child(end_node($$.node),$2.node);*/

  tempno++;
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  //printf($$.code,"hi %s = - %s ",$2.lhs,$2.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("Uminus\t%s\t \t%s\n",$2.lhs,$$.lhs);
  sprintf($$.code,"Uminus\t%s\t \t%s\n",$2.lhs,$$.lhs);

  strcpy($$.lhs,$2.lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=1;
}
| ADD Primary_Exp 
{
  //$$=$2;
  /*$$.node = create_node(NULL,"+",0); 
  //add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  //add_child(end_node($$.node),$2.node);*/

  //strcpy($$.code,$2.code);

  strcpy($$.code,$2.lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=0;
  //tempno++;

  tempno++;
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  sprintf($$.code,"%s = %s ",$$.lhs,$2.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("Uplus\t%s\t \t%s\n",$2.lhs,$$.lhs);

  
  exprno=2;

}
| NOT Primary_Exp 
{
  $$.type=$2.type;
  char buffer[1024]="-";
  strcat(buffer,$2.value);
  strcpy($$.value,buffer);
  /*$$.node = create_node(NULL,"!",0); 
  add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  add_child(end_node($$.node),$$.node);*/
  

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);
  sprintf($$.code,"%s = not %s ",temp_var,$2.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("not\t%s\t\t%s\n",$2.lhs,$$.lhs);


  strcpy($$.code,$2.lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=2;

}
| Primary_Exp 
{
  /*$$.node = create_node(NULL,"Primary_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
;
Pow_Exp: Unary_Exp 
{
  /*$$.node = create_node(NULL,"Unary_Exp",0); 
  add_child($$.node,$1.node);*/
  strcpy($$.code,$1.code);

  }
| Pow_Exp EPOP Unary_Exp 
{
  /*$$.node = create_node(NULL,"Pow_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"**",0));
  add_sibling($$.node,create_node(NULL,"Unary_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n**\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  
  //printf("**\t%s\t%s\t%s\n",$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"** \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
;
Mul_Exp: Pow_Exp 
{
  /*$$.node = create_node(NULL,"Pow_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| Mul_Exp MUL Pow_Exp 
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"*",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n*\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("*\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //fprintf(fp_quad,"* \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;

}
| Mul_Exp DIV Pow_Exp 
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"/",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n/\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("/\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //fprintf(fp_quad,"/ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
| Mul_Exp FDIV Pow_Exp 
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"//",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n//\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("//\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);
}
| Mul_Exp MOD Pow_Exp
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"%",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);
  sprintf($$.code,"%s = %s % %s",temp_var,$1.lhs,$3.code);


  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("%\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);
}
;
Add_Exp: Mul_Exp 
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| Add_Exp ADD Mul_Exp 
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"+",0));
  add_sibling($$.node,create_node(NULL,"Mul_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);
  //sprintf($$.code,"hello%s = %s + %s",temp_var,$1.lhs,$3.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("+\t%s\t%s\t%s\n",$1.lhs,$3.lhs,temp_var);
  sprintf($$.code,"%s%s\n+\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"+ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
| Add_Exp SUB Mul_Exp
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"-",0));
  add_sibling($$.node,create_node(NULL,"Mul_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n-\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("-\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //fprintf(fp_quad,"- \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
;
Bit_Exp: Add_Exp 
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| Bit_Exp XOR Add_Exp 
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"^",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  //sprintf($$.code,"^\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf($$.code,"%s\n%s\n^\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"^ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;


}
| Bit_Exp BAND Add_Exp 
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"&",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  //sprintf($$.code,"%s\n%s\n&\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf($$.code,"%s\n%s\n&\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"& \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
| Bit_Exp BOR Add_Exp
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"|",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf($$.lhs,temp_var);
  //sprintf($$.code,"%s\n%s\n|\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf($$.code,"%s\n%s\n|\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"| \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
;
Rel_Exp: Bit_Exp 
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| Rel_Exp G Bit_Exp 
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,">",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s > %s\n",temp_var, $1.lhs, $3.lhs);
  //printf(">\t%s\t%s\t%s\n", $1.lhs, $3.lhs, temp_var);
  sprintf($$.code,">\t%s\t%s\t%s\n", $1.lhs, $3.lhs, temp_var);
  strncpy($$.lhs, temp_var, m+1);
}
| Rel_Exp GE Bit_Exp 
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,">=",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s >= %s\n",temp_var, $1.code, $3.code);
  //printf(">=\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);

  sprintf($$.code,"%s\n%s\n>=\t%s\t%s\t%s\n", $1.code, $3.code,$1.lhs,$3.lhs, temp_var);
  strncpy($$.lhs, temp_var, m+1);
}
| Rel_Exp L Bit_Exp 
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"<",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s < %s\n",temp_var, $1.code, $3.code);
  //printf("<\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);
  sprintf($$.code,"%s\n%s\n<\t%s\t%s\t%s\n", $1.code, $3.code,$1.lhs,$3.lhs, temp_var);
  strncpy($$.lhs, temp_var, m+1);
}
| Rel_Exp LE Bit_Exp
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"<=",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s <= %s\n",temp_var, $1.code, $3.code);
  //printf("<=\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);
  sprintf($$.code,"<=\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);
  strncpy($$.lhs, temp_var, m+1);
}
;
Eq_Exp: Rel_Exp 
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
}
| Eq_Exp EOP Rel_Exp 
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"==",0));
  add_sibling($$.node,create_node(NULL,"Rel_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s == %s\n", temp_var, $1.code, $3.code);
  //printf("==\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);

  //strncpy($$.code, temp_var, m+1);   //check out
  strcpy($$.lhs,temp_var);
  sprintf($$.code,"%s\n%s\n==\t%s\t%s\t%s\n", $1.code, $3.code,$1.lhs,$3.lhs, temp_var);
}
| Eq_Exp NEOP Rel_Exp 
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"!=",0));
  add_sibling($$.node,create_node(NULL,"Rel_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s != %s\n", temp_var, $1.code, $3.code);
  sprintf("%s\n%s\n!=\t%s\t%s\t%s\n", $1.code, $3.code,$1.lhs,$3.lhs, temp_var);

  strncpy($$.lhs, temp_var, m+1);   //check out
}
;
In_Exp: Eq_Exp 
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| Eq_Exp IN In_Exp   
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"in",0));
  add_sibling($$.node,create_node(NULL,"In_Exp",0));
  add_child(end_node($$.node),$3.node);*/
}
;
And_Exp: In_Exp 
{
  /*$$.node = create_node(NULL,"In_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| In_Exp LAND And_Exp   
{
  /*$$.node = create_node(NULL,"In_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"and",0));
  add_sibling($$.node,create_node(NULL,"And_Exp",0));
  add_child(end_node($$.node),$3.node);*/
  
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);

  sprintf($$.code,"%s%s\nand\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);


}
;
Or_Exp: And_Exp 
{
  $$=$1;  
  /*$$.node = create_node(NULL,"And_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy($$.code,$1.code);
  strcpy($$.lhs,$1.lhs);
}
| And_Exp LOR Or_Exp 
{
  $$=$1;  
  /*$$.node = create_node(NULL,"And_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"or",0));
  add_sibling($$.node,create_node(NULL,"Or_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy($$.lhs,temp_var);

  sprintf($$.code,"%s%s\nor\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);



}
;

%% 
int yyerror(char *msg) 
{ 
  printf("Syntax Error\n"); 
  return 1;
} 
 
int main() 
{ 
  Quad *allQuads = (Quad*)malloc(sizeof(Quad));

  // head = tree_init();
  // head->node = create_node(NULL,"Start",0);
  yyparse(); 
  // printf("Symbol Table\n");
  // display_symbol();
  // printf("\n\nAbstract Syntax Tree\n\n");
  // printTree(head);
  
  return 0;
}
