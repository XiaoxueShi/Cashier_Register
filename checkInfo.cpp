#include"checkInfo.h"

CheckInfo::CheckInfo()
{

}
CheckInfo::~CheckInfo()
{

}
void CheckInfo::setScaner(GoodScaner* Gscaner,SaleScaner* Sascaner,ShopingList* Spscaner)
{
	this->m_pGoodScaner=Gscaner;
	this->m_pSaleScaner=Sascaner;
	this->m_pShopingScaner=Spscaner;
}
void CheckInfo::checkOnsale(Goods& Gitem)
{
	Sales Sitem;
	m_pSaleScaner->setIdx();
	while(m_pSaleScaner->getNextSale(Sitem)!=-1)
	{
		if(Gitem.getBarcode()==Sitem.getBarcode())
			Gitem.setOnsale(Sitem.getType());
	}
}

void CheckInfo::getShopingInfo()
{
	shoping list;

	string currItem;
	string nextItem;
	int num;
	vector<string> shopList=m_pShopingScaner->getShopingList();
	sort(shopList.begin(),shopList.end());
	m_pShopingScaner->setList(shopList);
	int p_c=m_pShopingScaner->getNextShoping(currItem);
	while(true)
	{
		int p_n=m_pShopingScaner->getNextShoping(nextItem);
		if(currItem!=nextItem)
		{
			if(p_n!=-1)
				num=p_n-p_c;
			else
				num=m_pShopingScaner->getShopingCount()-p_c+1;
			list.barcode=currItem;
			list.num=num;
			currItem=nextItem;
			p_c=p_n;
			m_vecShopInfo.push_back(list);
		}
		if(p_n==-1)
			break;

	}
}
bool Flag=false;
void CheckInfo::Calcu()
{
	ofstream fout;
	string outName = "receipt.txt";
	fout.open(outName.c_str(),ios::out);
	if(!fout)
	{
		cout<<"Creat Result File Error!"<<endl;
		return;
	}
	double discount=0;
	double total=0;
	double reduce=0;
	string disInfo;
	string s1="  名称：";
	string s2=",折扣：";
	string Type1;
	fout<<"*<没钱赚商店>购物清单*"<<endl<<endl;
	for(unsigned i=0;i<m_vecShopInfo.size();i++)
	{
		Goods Item;
		m_pGoodScaner->setIdx();
		while(m_pGoodScaner->getNextGood(Item)!=-1)
		{
			if(Item.getBarcode()==m_vecShopInfo[i].barcode)
			{

				fout<<"  名称："<<Item.getName()<<",数量："<<m_vecShopInfo[i].num<<Item.getUnit()
					<<",单价："<<Item.getPrice()<<"(元)"<<",小计：";
				if(Item.Onsale())
				{
					Flag=true;
					string Type=Item.getDiscountType();
					if(Type=="FIVE_PERCENT_DISCOUNT")
					{discount=0.05;Type1="九五折  ";}
					if(Type=="TEN_PERCENT_DISCOUNT")
					{discount=0.10;Type1="九折  ";}
					CalcuSale calS(discount);
					fout<<calS.CalcuCost(Item.getPrice(),m_vecShopInfo[i].num);
					total+=calS.CalcuCost(Item.getPrice(),m_vecShopInfo[i].num);
					fout<<",优惠："<<calS.CalcuReduce(Item.getPrice(),m_vecShopInfo[i].num)<<endl;
					reduce+=calS.CalcuReduce(Item.getPrice(),m_vecShopInfo[i].num);
					disInfo=disInfo+s1+Item.getName()+s2+Type1;
				}
				else
				{
					CalcuNormal calN;
					fout<<calN.CalcuCost(Item.getPrice(),m_vecShopInfo[i].num)<<endl;
					total+=calN.CalcuCost(Item.getPrice(),m_vecShopInfo[i].num);
				}

				break;
			}

		}
	}
	if(Flag)
		fout<<endl<<"单品打折商品： "<<endl<<disInfo<< endl;
	fout<<endl<<"总计："<<total<<"(元)";
	if(Flag)
		fout<<"  节省："<<reduce<<endl;
}
