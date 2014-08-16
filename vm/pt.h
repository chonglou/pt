
struct symbol {
	char* name;
	double value;
	struct ast* func;
	struct symlist* syms;
};

#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol* lookup(char* sym);

struct symlist {
	struct symbol* sym;
	struct symlist* next;
};

struct symlist* new_symlist(struct symbol* sym, struct symlist* next);
void free_symlist(struct symlist* sl);

/**
 * 节点类型
 * + - * / |
 * 0-7 比较符， 04= 02< 01>
 * M 负号
 * L 表达式或语句
 * I IF语句
 * W WHILE语句
 * N 符号引用
 * = 赋值
 * S 符号列表
 * F 内置函数调用
 * C 用户函数调用
 */

enum bifs {
	B_sqrt = 1,
	B_exp,
	B_log,
	B_print
};

struct ast {
	int t;
	struct ast* l;
	struct ast* r;
};

struct fncall {
	int nt;
	struct ast* l;
	enum bifs ft;
};

struct ufncall {
	int t;
	struct ast* l;
	struct symbol* s;
};

struct flow {
	int t; //I or W
	struct ast* cond;
	struct ast* tl;
	struct ast* el;
};

struct numval {
	int t; // L
	double v;
};

struct symref {
	int t; //N
	struct symbol* s;
};

struct symasgn {
	int t; //=
	struct symbol* s;
	struct ast* v;	
};

struct ast* new_ast(int type, struct ast* l, struct ast* r);
struct ast* new_cmp(int type, struct ast* l, struct ast* r);
struct ast* new_func(int type, struct ast* l);
struct ast* new_call(struct symbol* s, struct ast* l);
struct ast* new_ref(struct symbol* s);
struct ast* new_asgn(struct symbol* s, struct ast* v);
struct ast* new_num(double number);
struct ast* new_flow(int type, struct ast* cond, struct ast* tl, struct ast* tr);

void do_def(struct symbol* name, struct symlist* syms, struct ast* stmts);

double eval(struct ast* a);

void free_tree(struct ast* a);

extern int yylineno;
void yyerror(char*s, ...);


