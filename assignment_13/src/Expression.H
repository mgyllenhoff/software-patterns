#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>

// Interpreter Pattern: Context
struct Context {};

// Interpreter Pattern: AbstractExpression
class Expression
{
public:
	virtual ~Expression() {}
	virtual int	interpret(Context & context) = 0;
};

// Interpreter Pattern: TerminalExpression
class ValueExpression : public Expression
{
	int	value;
public:
	explicit	ValueExpression(int v);
	int		interpret(Context & context) override;
};

// Interpreter Pattern: NonterminalExpression
class OperationExpression : public Expression
{
	char				op; // +  -  *  /
	std::vector<Expression *>	operands; // R1..Rn
public:
	explicit	OperationExpression(char op);
	~OperationExpression();
	void		addOperand(Expression * e);
	int		interpret(Context & context) override;
};

#endif // EXPRESSION_H
