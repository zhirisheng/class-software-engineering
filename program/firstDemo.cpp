// firstDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	GDALDataset* poSrcDS;
	GDALDataset* poDstDS;
	int imgXlen,imgYlen;
	char* srcPath="trees.jpg";
	char* dstPath="res.tif";
	GByte* buffTmp;
	int i,bandNum;
	GDALAllRegister();
	poSrcDS=(GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);
	imgXlen=poSrcDS->GetRasterXSize();
	imgYlen=poSrcDS->GetRasterYSize();
	bandNum=poSrcDS->GetRasterCount();
	cout<<"X Length:"<<imgXlen<<endl;
	cout<<"Y Length:"<<imgYlen<<endl;
	cout<<"Band number:"<<bandNum<<endl;
	buffTmp=(GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
	poDstDS=GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
	for(int i=0; i<bandNum; i++)
	{
		poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
		poDstDS->GetRasterBand(i+1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
	}
	CPLFree(buffTmp);
	GDALClose(poSrcDS);
	GDALClose(poDstDS);
	system("PAUSE");
	return 0;
}

