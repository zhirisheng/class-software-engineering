#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像的路径
	char* srcPath = "54.jpg";
	//输出图像的路径
	char* dstPath = "res.tif";
	//图像的内存存储
	GByte* buffTmp, *buffTmp2;
    //图像波段数
	int i , bandNum;

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);

    //获得图像宽度，高度和波段数量
    imgXlen = poSrcDS->GetRasterXSize();
    imgYlen = poSrcDS->GetRasterYSize();
    bandNum = poSrcDS->GetRasterCount();

    //根据图像的宽度和高度分配内存
    buffTmp2 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
    //创建输出图像
    poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
            dstPath, imgXlen, imgYlen,bandNum, GDT_Byte, NULL);


    //一个个波段的输入，然后一个个波段的输出
    for (i = 0; i < bandNum; i++)
    {
        poSrcDS->GetRasterBand(i+1)->RasterIO(GF_Read,
            0, 0, imgXlen, imgYlen, buffTmp2, imgXlen, imgYlen, GDT_Byte, 0, 0);
        poDstDS->GetRasterBand(i+1)->RasterIO(GF_Write,
            0, 0, imgXlen, imgYlen, buffTmp2, imgXlen, imgYlen, GDT_Byte, 0, 0);
        printf("... ... band %d processing ... ...\n", i);
    }


    //图像处理
    //起始的位置坐标
    int StartX = 500;
    int StartY = 500;
    //区域的宽度和高度
    int tmpXlen = 100;
    int tmpYlen = 50;
    //分配内存
    for(int k = 3; k > 0; k--){

    buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
    //读取红色通道缓存在bufftmp中
    poSrcDS ->GetRasterBand(k)->RasterIO(GF_Read,
        StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
    //遍历区域，逐像素置为255
    for (int j = 0; j <tmpYlen; j++)
        for(int i = 0; i <tmpXlen; i++)
        {
            buffTmp[j*tmpXlen+i] = (GByte)0;
        }
    //数据写入poDstDs
    poDstDS ->GetRasterBand(k)->RasterIO(GF_Write,
        StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
    CPLFree(buffTmp);
}
//图像处理
    //起始的位置坐标
    StartX = 300;
    StartY = 300;
    //区域的宽度和高度
    tmpXlen = 50;
    tmpYlen = 100;
    //分配内存
    for(int k = 3; k > 0; k--){

    buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
    //读取红色通道缓存在bufftmp中
    poSrcDS ->GetRasterBand(k)->RasterIO(GF_Read,
        StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
    //遍历区域，逐像素置为255
    for (int j = 0; j <tmpYlen; j++)
        for(int i = 0; i <tmpXlen; i++)
        {
            buffTmp[j*tmpXlen+i] = (GByte)255;
        }
    //数据写入poDstDs
    poDstDS ->GetRasterBand(k)->RasterIO(GF_Write,
        StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
    CPLFree(buffTmp);
}
    //清楚内存

	CPLFree(buffTmp2);
    //关闭dataset
    GDALClose(poDstDS);
    GDALClose(poSrcDS);

    //system("PAUSE");
	return 0;
}