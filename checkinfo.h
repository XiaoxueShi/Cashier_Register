#ifndef CHECKINFO_H
#define CHECKINFO_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
#include"goodscaner.h"
#include"salescaner.h"
#include"shopinglist.h"
#include<algorithm>
#include"calcu.h"
struct shoping
{
public:
	string barcode;
	int num;
};
class CheckInfo
{
public:
	CheckInfo();
	~CheckInfo();
	void setScaner(GoodScaner* Gscaner,SaleScaner* Sascaner,ShopingList* Spscaner);
	void checkOnsale(Goods& goods);
	void getShopingInfo();
	void Calcu();
private:
	GoodScaner* m_pGoodScaner;
	SaleScaner* m_pSaleScaner;
	ShopingList* m_pShopingScaner;
	vector<shoping> m_vecShopInfo;
};
#endif
