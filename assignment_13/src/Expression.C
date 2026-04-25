#include "Expression.H"

ValueExpression::ValueExpression(int v) : value(v) {}

int ValueExpression::interpret(Context &)
{
	return value;
}

OperationExpression::OperationExpression(char op) : op(op) {}

OperationExpression::~OperationExpression()
{
	for (Expression * e : operands)
		delete e;
}

void OperationExpression::addOperand(Expression * e)
{
	operands.push_back(e);
}

int OperationExpression::interpret(Context & context)
{
	if (operands.empty())
		return 0;

	int result = operands[0]->interpret(context);

	if (operands.size() == 1 && op == '-')
		return -result;

	for (size_t i = 1; i < operands.size(); i++)
	{
		int val = operands[i]->interpret(context);
		switch (op)
		{
		case '+': result += val; break;
		case '-': result -= val; break;
		case '*': result *= val; break;
		case '/': result /= val; break;
		}
	}
	return result;
}
