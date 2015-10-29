#include "stdafx.h"

LPBITMAPINFO  lpBitsInfo = NULL;

BOOL LoadBmpFile (char* BmpFileName)
{
	FILE* fp;
	if (NULL == (fp = fopen(BmpFileName, "rb"))) 
		return FALSE;
	
	BITMAPFILEHEADER   bf;       //文件头结构
	BITMAPINFOHEADER   bi;       //信息头结构
	
	//将文件头BITMAPFILEHEADER结构从文件中读出，填写到bf中
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	
	//将信息头BITMAPINFOHEADER结构从文件中读出，填写到bi中
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
	
	//计算图像中每一行像素共占多少字节LineBytes
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;
	
	//计算实际图象数据占用的字节数ImgSize
	DWORD ImgSize=LineBytes * bi.biHeight;
	
	DWORD NumColors;  //实际用到的颜色数，即调色板数组中的颜色个数
	if (bi.biClrUsed != 0)
		NumColors = bi.biClrUsed; //如果bi.biClrUsed不为零，就是本图象实际用到的颜色数
	else {
		switch(bi.biBitCount)	{
		case 1:
			NumColors=2;
			break;
		case 4:
			NumColors=16;
			break;
		case 8:
			NumColors=256;
			break;
		case 24:
			NumColors=0; //对于真彩色图，没用到调色板
			break;
		}
	}
	//分配内存，大小为BITMAPINFOHEADER结构长度+调色板+实际位图数据
	LONG size= sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;
	
	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	
	//将文件内容读入lpBitsInfo
	fread((char*)lpBitsInfo, size, 1, fp);
	lpBitsInfo->bmiHeader.biClrUsed = NumColors;


	return FALSE;
}

void Gray()
{
	int w = lpBitsInfo->bmiHeader.biWidth;	//宽度
	int h = lpBitsInfo->bmiHeader.biHeight;	//高度
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//每一行所占用字节数
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//调色板指针
	//新图像内存大小
	int new_LineBytes =(w * 8 + 31)/32 * 4;
	LONG size = 40 + 1024 + new_LineBytes * h;
	LPBITMAPINFO new_lpBitsInfo = (LPBITMAPINFO) malloc(size);
	//填写文件信息头
	memcpy(new_lpBitsInfo, lpBitsInfo, 40);
	new_lpBitsInfo->bmiHeader.biBitCount = 8;
	new_lpBitsInfo->bmiHeader.biClrUsed = 256;
	//调色板
	int i,j;
	for (i = 0; i < 256; i ++)
	{
		new_lpBitsInfo->bmiColors[i].rgbBlue = i;
		new_lpBitsInfo->bmiColors[i].rgbGreen = i;
		new_lpBitsInfo->bmiColors[i].rgbRed = i;
		new_lpBitsInfo->bmiColors[i].rgbReserved = 0; 
	}
	//位图数据
	BYTE* pixel;
	BYTE *R,*G,*B;
	BYTE* new_lpBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j++)
		{
			B = lpBits + LineBytes * i + j * 3; 
			G = B + 1;
			R = G + 1;
			pixel = new_lpBits + new_LineBytes * i + j;
			*pixel = (BYTE)((*R + *G + *B)/3);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;	
}


void ShowDetail(CPoint point){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE* Pixel;
	int val;
	int R, G, B;
	CString value;
	
	switch(lpBitsInfo->bmiHeader.biBitCount){
		case 1:
			val = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/8)&(1<<(7-point.x%8));
			Pixel = lpBits + LineBytes * (h - 1 - point.y) + point.x/8;
			*Pixel = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/8)&(1<<(7-point.x%8));
			//*Pixel = *Pixel >> (7-point.x%8)&1;

			if (*Pixel == 0)
			{
				AfxMessageBox("0");
			}else{
				AfxMessageBox("1");
			}
			break;
		case 4:
		case 8:
			Pixel = lpBits + LineBytes * (h - 1 - point.y) + point.x;
			R = lpBitsInfo->bmiColors[*Pixel].rgbRed;
			G = lpBitsInfo->bmiColors[*Pixel].rgbGreen;
			B = lpBitsInfo->bmiColors[*Pixel].rgbBlue;
			value.Format("R:%d G:%d B:%d", R, G, B);
			AfxMessageBox(value);
			break;
		case 24:
			Pixel = lpBits + LineBytes * (h - 1 - point.y) + point.x;
			//value.Format("%d", *Pixel);
			AfxMessageBox(value);
			break;

	}
}

void statisticsGrey(){

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//每行字节
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//实际位图数据
	
	int statistics[255];	//储存统计数据
	BYTE* Pixel;	//存储像素值
	CString str = "", val = "";
	int R, G, B;
	for (int i = 0; i <=1 ; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Pixel = lpBits + LineBytes*1 +j;
			R = lpBitsInfo->bmiColors[*Pixel].rgbRed;
			G = lpBitsInfo->bmiColors[*Pixel].rgbGreen;
			B = lpBitsInfo->bmiColors[*Pixel].rgbBlue;
			str.Format("R:%d G:%d B:%d", R, G, B);
			val += str;
		}
	}
	AfxMessageBox(val);


}

