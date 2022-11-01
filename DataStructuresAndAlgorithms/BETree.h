///////////////////////////////////////////////////////////
//  BETree.h
//  ���ʽ������
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
* @brief �������ڵ�
* 
* �ɱ��ʽ�����������㷨�����ö�������ʾ��
*/
typedef struct node
{
	struct node *left;			/**< ���� */
	struct node *right;			/**< �Һ��� */
	unsigned char operatorStr;  /**< ����� */
	float value;			    /**< (�ٷֱȣ�����ֵ) */
	std::string  paramName;		            /**< (������) */
}NODE;
typedef NODE* BTree; /** @brief ����������ṹ */


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
	std::string m_definition;		/**< ���ʽ�ִ� */
	int position;					/**< ��ǰ������λ�� */
	BTree m_BTree;					/**< �ɱ��ʽ���ɵĶ����� */
	int m_varNo;                    /**< ������������Ӧ���ݴ����������еĲ������� */

};

#endif // _BETREE_H