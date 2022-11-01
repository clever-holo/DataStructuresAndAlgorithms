#include "BETree.h"


BETreeAnalysor::BETreeAnalysor(void)
{
	m_BTree = NULL;
	m_definition = "";
	position = 0;
	m_varNo = 0;
}


BETreeAnalysor::~BETreeAnalysor(void)
{
	ClearBTree (m_BTree);
}



void BETreeAnalysor::SetParam(const std::string& param, float val/* = INVALID_DATA*/)
{
	m_mp_param[param] = val;
}

/** 
* @brief 验证表达式的正确性
* 
* Detailed description.
* @param[in] expression 表达式字符串
* @return int  错误位置，正确时返回-1,同时返回该表达式的涉及的所有参数号
*/
int BETreeAnalysor::InitExp(const std::string& str_exp)
{
	m_definition = str_exp + '\0' + '\0' +'\0'; // to make sure definition[position+N] safe
	return UpdateBTree();
}

float BETreeAnalysor::Value()
{
	return Calculate(m_BTree);
}

int BETreeAnalysor::UpdateBTree()
{
	if (m_definition == "") //表达式为空，则构造一个值为0(FALSE)的二叉树
	{
		m_BTree = new NODE;
		m_BTree->left = NULL;
		m_BTree->right = NULL;
		m_BTree->operatorStr = '~';
		m_BTree->value = 0;
		return -1;
	}

	m_BTree = NULL;
	position = 0;
	m_BTree = OrOp();  //start from the lowest level operation
	if (m_definition[position] != '\0') 
	{
		ClearBTree(m_BTree);
		m_BTree = NULL;
	}

	return m_BTree ? -1 : 0;
}

BTree BETreeAnalysor::OrOp()
{	
	BTree leftBTree = AndOp();
	if (leftBTree == NULL)
		return NULL;

	SkipSpaces();
	while ((m_definition[position]=='|') && (m_definition[position+1]=='|'))
	{
		BTree node;
		node = new NODE;
		node->left = leftBTree;
		node->operatorStr = OR;
		position += 2;
		node->right = AndOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL; 
		}
		leftBTree = node;
		SkipSpaces();
	}
	return leftBTree;
}

BTree BETreeAnalysor::AndOp()
{
	BTree leftBTree = LogicalOp();
	if (leftBTree == NULL)
		return NULL;

	SkipSpaces();
	while ((m_definition[position]=='&') && (m_definition[position+1]=='&'))
	{
		BTree node = new NODE;
		node->left = leftBTree;
		node->operatorStr = AND;
		position += 2;
		node->right = LogicalOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;  
		}

		leftBTree = node;
		SkipSpaces();
	}
	return leftBTree;
}

BTree BETreeAnalysor::LogicalOp()
{
	BTree leftBTree = AddSubOp();
	if  (leftBTree == NULL) 
		return NULL; 

	SkipSpaces();
	while ((m_definition[position]=='<') 
		|| (m_definition[position]=='>') 
		|| ((m_definition[position]=='!')&&(m_definition[position+1]=='='))
		|| ((m_definition[position]=='=')&&(m_definition[position+1]=='=')) /* || another same priority operations*/) 
	{
		BTree node = new NODE;
		node->left=leftBTree;
		if(m_definition[position+1] == '=')
		{
			if(m_definition[position] == '<')
			{// For "<=" occasion
				node->operatorStr = SMALLEQUAL;		
			}
			else if(m_definition[position] == '>')
			{// For ">=" occasion
				node->operatorStr = BIGEQUAL;
			}
			else if(m_definition[position] == '=')
			{// For "==" occasion
				node->operatorStr = EQUAL;
			}
			else if(m_definition[position] == '!')
			{// For "!=" occasion
				node->operatorStr = NOTEQUAL;
			}
			position++;
		}
		else
		{// For ">" or "<" occasion
			node->operatorStr = m_definition[position];
		}
		position++;
		node->right = AddSubOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;  
		}

		leftBTree = node;
		SkipSpaces();
	}
	return leftBTree;
}

BTree BETreeAnalysor::AddSubOp()
{
	BTree leftBTree = DivisionOp();
	if  (leftBTree == NULL) 
		return NULL;

	SkipSpaces();
	while ((m_definition[position]=='-') || (m_definition[position]=='+')) 
	{
		BTree node = new NODE;
		node->left = leftBTree;
		node->operatorStr = m_definition[position];
		position++;
		node->right = DivisionOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;  
		}
		leftBTree = node;
		SkipSpaces();
	}
	return leftBTree;
}

BTree BETreeAnalysor::DivisionOp()
{
	BTree leftBTree = PowerOp();
	if  (leftBTree == NULL) 
		return NULL; 

	SkipSpaces();
	while ((m_definition[position]=='*') 
		|| (m_definition[position]=='/') 
		|| (m_definition[position]=='%'))
	{
		BTree node = new NODE;
		node->left = leftBTree;
		node->operatorStr = m_definition[position];
		position++;
		node->right = PowerOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;  
		}
		leftBTree = node;
		SkipSpaces();
	}
	return leftBTree;
}

BTree BETreeAnalysor::PowerOp()
{
	BTree leftBTree = NonOp();
	if  (leftBTree == NULL) 
		return NULL;  // 

	SkipSpaces();
	while (m_definition[position] == '^') 
	{
		BTree node=new NODE;
		node->left = leftBTree;
		node->operatorStr = m_definition[position];
		position++;
		node->right = NonOp();
		if  (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;  // 
		}
		leftBTree = node;
	}
	return leftBTree;
}

BTree BETreeAnalysor::NonOp()
{
	SkipSpaces();

	BTree node = NULL;
	if ((m_definition[position]=='!') /* || another same priority operations*/) 
	{
		node=new NODE;
		node->right=NULL;
		node->operatorStr = m_definition[position];
		position++;
		node->left = NonOp();
		if  (node->left == NULL) 
		{
			ClearBTree(node);
			return NULL;  // 
		}
	}
	else 
		node = SinOp();
	return node;
}

/** 
* @brief 匹配三角函数
* 
* 
* @return BTree  子二叉树
*/
BTree BETreeAnalysor::SinOp()
{
	SkipSpaces();

	BTree node = NULL;
	int pos = position;
	if(isalpha(m_definition[position]))		
	{
		while  ((isalpha(m_definition[position])))
			position++;

		std::string strOp = m_definition.substr(pos, position-pos);
		unsigned char uch = 0;
		if (strOp == "sin")
			uch = SIN;
		else if(strOp == "cos")
			uch = COS;
		
		if (uch != 0)
		{
			node = new NODE;
			node->operatorStr = uch;
			node->right = NULL;
			node->left = Factor();
			if (node->left == NULL)
			{
				ClearBTree(node);
				return NULL;
			}
		}
		else
		{
			// 回退
			position = pos;
		}
	}

	node = Factor();
	
	return node;
}

/** 
* @brief 匹配子部分运算
* 
* 匹配括号，取反，求绝对值操作。
* @return BTree  子二叉树
*/
BTree BETreeAnalysor::Factor()
{
	SkipSpaces();
	if (m_definition[position]=='-' || m_definition[position]=='+')
	{
		BTree left = new NODE;
		left->right = NULL;
		left->left = NULL;
		left->operatorStr = '~';
		left->value = m_definition[position]=='-' ? -1.0f : 1.0f;

		BTree node = new NODE;
		node->left=left;
		node->operatorStr = '*';
		position++;
		node->right = Factor();
		if (node->right == NULL) 
		{
			ClearBTree(node);
			return NULL;
		}
		return node;   
	}
	
	if (m_definition[position]=='(')
	{
		position++;
		BTree node = OrOp();
		if (node == NULL) 
			return NULL;
		if (m_definition[position]!=')')
		{
			ClearBTree(node);
			return NULL;
		}
		position++;
		return node;
	}

	return Identifier();
}

/** 
* @brief 匹配变量和常数
*
* @return BTree  子二叉树
*/
BTree BETreeAnalysor::Identifier()
{
	SkipSpaces();
	if (m_definition[position]=='\0') 
		return NULL;

	int pos = position;

	// 变量：数字与字母的组合，允许数字在前
	if(isalnum(m_definition[position]))		
	{
		while  ((isalnum(m_definition[position])))
			position++;

		float val = -1;
		if(GetParam(m_definition.substr(pos, position - pos), val))
		{
			BTree node = new NODE;
			node->left = NULL; 
			node->right = NULL;
			node->operatorStr = '@';
			node->paramName = m_definition.substr(pos, position - pos);
			SkipSpaces();
			return node;
		}
		else
		{
			// 不是变量，可能是数字，位置回退
			position = pos;
		}
	}

	// 常数：允许是浮点数
	if (isdigit(m_definition[position]))	
	{
		int dotCnt = 0;
		while  ((isdigit(m_definition[position]) || (m_definition[position]=='.')))
		{
			if(m_definition[position]=='.')
				dotCnt++;

			if(dotCnt >= 2)
				return NULL;

			position++;
		}
	
		BTree node = new NODE;
		node->left = NULL; 
		node->right = NULL;
		node->operatorStr = '~';
		node->value = (float)atof(m_definition.substr(pos,position-pos).c_str());
		return node;
	}

	return NULL;

}

float BETreeAnalysor::Calculate(BTree a)
{
	if(a == NULL)
		return INVALID_DATA;

	float left_val = Calculate(a->left);
	float right_vale = Calculate(a->right);

	float ret = INVALID_DATA;
	unsigned char opStr = a->operatorStr;
	if (opStr == '+' || opStr == '-' || opStr == '*' || opStr == '/' || opStr == '%' || opStr == '^')
	{
		if(left_val == INVALID_DATA || right_vale == INVALID_DATA)
			return INVALID_DATA;

		switch(opStr)
		{
		case '+':
			ret = left_val + right_vale;
			break;
		case '-':
			ret = left_val - right_vale;
			break;
		case '*':
			ret = left_val * right_vale;
			break;
		case '/':
			ret = left_val / right_vale;
			break;
		case '%':
			ret = (float) ((int)left_val % (int)right_vale);
			break;
		case '^':
			ret = float((int)left_val ^ (int)right_vale);
			break;
		}
		return ret;
	}
	else if (opStr == AND || opStr == OR || opStr == '>' || opStr == '<' || opStr == SMALLEQUAL || opStr == BIGEQUAL || opStr == EQUAL || opStr == NOTEQUAL) 
	{
		if(left_val == INVALID_DATA || right_vale == INVALID_DATA)
			return INVALID_DATA;

		switch(opStr)
		{
		case AND:
			ret = left_val && right_vale;
			break;
		case OR:
			ret = left_val || right_vale;
			break;
		case '>':
			ret = left_val > right_vale;
			break;
		case '<':
			ret = left_val < right_vale;
			break;
		case SMALLEQUAL:
			ret = left_val <= right_vale;
			break;
		case BIGEQUAL:
			ret = left_val >= right_vale;
			break;
		case EQUAL:
			ret = left_val == right_vale;
			break;
		case NOTEQUAL:
			ret = left_val != right_vale;
			break;
		}
		return ret;
	}
	else if (opStr == '!' || opStr == SIN || opStr == COS) 
	{
		if(left_val == INVALID_DATA)
			return INVALID_DATA;

		switch(opStr)
		{
		case '!':
			ret = !left_val;
			break;
		case SIN:
			ret = sin(left_val);
			break;
		case COS:
			ret = cos(left_val);
			break;
		}
		return ret;
	}
	else if (opStr == '~') /** @brief 为常数构造值区 */ 
	{
		return a->value;
	}
	else if (opStr == '@') /** @brief 为参数构造值区(重新复制内存数据，以保护原始数据不被修改) */ 
	{
		if (GetParam(a->paramName, ret))
			return ret;
		else 
			return INVALID_DATA;
	}
	else /** @brief 无匹配运算符 */	 
	{
		return INVALID_DATA;
	}
}

bool BETreeAnalysor::GetParam(const std::string& str_param, float& val)
{

	if (m_mp_param.find(str_param) != m_mp_param.end())
	{
		val = m_mp_param[str_param];
		return true;
	}

	return false;
}

void BETreeAnalysor::ClearBTree(BTree a)
{
	if (a==NULL) 
		return;

	if (a->left!=NULL) 
		ClearBTree(a->left);

	if (a->right!=NULL) 
		ClearBTree(a->right);

	delete a;
	a = NULL;
}

void BETreeAnalysor::SkipSpaces()
{
	while (m_definition[position]==' ' && m_definition[position]!='\0')
		position ++;
}