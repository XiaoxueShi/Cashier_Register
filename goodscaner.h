#ifndef GOODSCANER
#define GOODSCANER

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
#include"goods.h"

class GoodScaner
{
public:
	GoodScaner(string goodsfilename);
	int getNextGood(Goods& goodPlate);
	string getGoodFileName();
	int getGoodCount();
	void setGoods(int i,Goods good);
	void setIdx();
protected:
	void InitGoodList();
private:
	vector<Goods> m_vecGoodList;

	string m_strGoodFileName;
	int m_nGoodCount;
	int m_nGoodIdx;
	bool m_bInitFlag;
};

#endif
