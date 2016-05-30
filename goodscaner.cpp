#include"goodscaner.h"
GoodScaner::GoodScaner(string goodsfilename):
	m_strGoodFileName(goodsfilename),
	m_nGoodCount(0),
	m_nGoodIdx(0),
	m_bInitFlag(false)
{
	m_vecGoodList.clear();
	if(!m_bInitFlag)
		InitGoodList();
}
void GoodScaner::InitGoodList()
{
	ifstream fin;
	fin.open(m_strGoodFileName.c_str());
	if(!fin)
	{
		cout<<"Open Goods List Error!"<<endl;
		m_bInitFlag=false;
		return;
	}
	string goodItem;
	while(getline(fin,goodItem))
	{
		unsigned posB = goodItem.find("barcode");/////////////???
		unsigned posN = goodItem.find("name");
		unsigned posU = goodItem.find("unit");
		unsigned posC = goodItem.find("category");
		unsigned posS = goodItem.find("subCategory");
		unsigned posP = goodItem.find("price");
		if(posB == string::npos)
			continue;
		if(posN == string::npos)
			continue;
		if(posU == string::npos)
			continue;
		if(posC == string::npos)
			continue;
		if(posS == string::npos)
			continue;
		if(posP == string::npos)
			continue;
		string barcode = goodItem.substr(posB+sizeof("barcode"),posN-posB-sizeof("barcode")-1);
		string name = goodItem.substr(posN+sizeof("name"),posU-posN-sizeof("name")-1);
		string unit = goodItem.substr(posU+sizeof("unit"),posC-posU-sizeof("unit")-1);
		string category = goodItem.substr(posC+sizeof("category"),posS-posC-sizeof("category")-1);
		int a=posS+sizeof("subCategory");
		int b=posP-posS-sizeof("subCategory")-1;
		string subCategory = goodItem.substr(posS+sizeof("subCategory"),posP-posS-sizeof("subCategory")-1);
		string subCategory1 = goodItem.substr(a,b);
		string price =goodItem.substr(posP+sizeof("price"),sizeof(goodItem)-posP-sizeof("price")-1);
		double Price = atof(price.c_str());
		bool onsale = false;

		Goods item(barcode,name,unit,category,subCategory,Price,onsale);
		m_vecGoodList.push_back(item);

		m_nGoodCount ++;
	}
	m_bInitFlag = true;
	fin.close();
}
int GoodScaner::getNextGood(Goods& goodPlate)
{
	if(m_nGoodIdx>=m_nGoodCount)
		return -1;
	goodPlate=m_vecGoodList[m_nGoodIdx];
	m_nGoodIdx ++;
	return m_nGoodIdx;
}
int GoodScaner::getGoodCount()
{
	return m_nGoodCount;
}
void GoodScaner::setGoods(int i,Goods good)
{
	m_vecGoodList[i]=good;
}
void GoodScaner::setIdx()
{
	m_nGoodIdx=0;
}
