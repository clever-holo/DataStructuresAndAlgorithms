///////////////////////////////////////////////////////////
//  BETree.h
//  表达式二叉树
///////////////////////////////////////////////////////////

#ifndef _BETREE_H
#define _BETREE_H

#include <string>
#include <vector>
#include <map>

#define INVALID_DATA	((float)0xFFFFFFFF)

//DEFINE Trigonometric
#define SIN                    150
#define COS                    151
#define EXP                    152

//DEFINE Logic operation
#define AND                    160
#define OR                     161

#define SMALLEQUAL             162
#define BIGEQUAL               163
#define EQUAL                  164
#define NOTEQUAL               165


/** 
* @brief 二叉树节点
* 
* 由表达式解析出来的算法过程用二叉树表示。
*/
typedef struct node
{
	struct node *left;			/**< 左孩子 */
	struct node *right;			/**< 右孩子 */
	unsigned char operatorStr;  /**< 运算符 */
	float value;			    /**< (百分比，单个值) */
	std::string  paramName;		            /**< (参数号) */
}NODE;
typedef NODE* BTree; /** @brief 定义二叉树结构 */


class BETreeAnalysor
{
public:
	BETreeAnalysor(void);
	~BETreeAnalysor(void);


public:
	void SetParam(const std::string& param, float val = INVALID_DATA);
	bool GetParam(const std::string& str_param, float& val);
	int InitExp(const std::string& str_exp);
	float Value();

protected:
	int UpdateBTree();
	
	BTree OrOp();
	BTree AndOp();
	BTree LogicalOp();
	BTree AddSubOp();
	BTree DivisionOp();
	BTree PowerOp();
	BTree NonOp();
	BTree SinOp();
	BTree Factor();
	BTree Identifier();

	float Calculate (BTree a);

	
	void SkipSpaces();
	void ClearBTree(BTree a);

private:
	std::map<std::string, float> m_mp_param;
	std::string m_definition;		/**< 表达式字串 */
	int position;					/**< 当前解析的位置 */
	BTree m_BTree;					/**< 由表达式生成的二叉树 */
	int m_varNo;                    /**< 参数个数，对应数据处理点参数表中的参数个数 */

};

#endif // _BETREE_H