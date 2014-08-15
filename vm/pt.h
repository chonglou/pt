//接口
extern int yylineno;
void yyerror(char*s, ...);

//ast节点
struct ast {
	int type;
	struct ast *left;
	struct ast *right;
};

struct num_node {
	int type;
	double val;
};

//构造ast
struct ast* new_ast(int type, struct ast* left, struct ast* right);
struct ast* new_num(double val);

//计算ast
double eval(struct ast* a);

//删除和释放ast
void tree_free(struct ast* a);

