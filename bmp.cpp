#include "stdafx.h"
#include <complex>

#define PI 3.1415926535

using namespace std;

LPBITMAPINFO  lpBitsInfo = NULL;
LPBITMAPINFO  TmplpBitsInfo = NULL;
LPBITMAPINFO  lpBitsInfo1 = NULL;
BITMAPINFO* lpDIB_FFT = NULL;  //快速傅里叶变换
BITMAPINFO* lpDIB_IFFT = NULL;
//LPBITMAPINFO  lpBitsInfo2 = NULL;
int picNum = 0;

complex<double>* gFD;
//BOOL LoadBmpFile (char* BmpFileName, LPBITMAPINFO lpInfo = NULL)
LPBITMAPINFO LoadBmpFile (char* BmpFileName)
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
	if (NULL == (TmplpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;
	
	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	
	//将文件内容读入lpBitsInfo
	fread((char*)TmplpBitsInfo, size, 1, fp);
	TmplpBitsInfo->bmiHeader.biClrUsed = NumColors;
	
	
	return TmplpBitsInfo;
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
	int val,fourBit;
	int R, G, B;
	CString value;
	
	switch(lpBitsInfo->bmiHeader.biBitCount){
	case 1:
		//val = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/8)&(1<<(7-point.x%8));
		//Pixel = lpBits + LineBytes * (h - 1 - point.y) + point.x/8;
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
		//方法一
		//fourBit = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)&(15<<(1-point.x%2)*4);
		//方法二
		if (!point.x%2)//判断点击的是8个字节中的左边还是右边，坐标从0开始
		{
			//点击了左边，取高四位，右移四位即可
			fourBit = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)>>4;
		}else{
			//点击了右边，取低四位，与15（即00001111）相与
			fourBit = (BYTE)*(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)&15;
		}
		//通过调色板获取rgb的值
		R = lpBitsInfo->bmiColors[fourBit].rgbRed;
		G = lpBitsInfo->bmiColors[fourBit].rgbGreen;
		B = lpBitsInfo->bmiColors[fourBit].rgbBlue;
		value.Format("R:%d G:%d B:%d", R, G, B);
		AfxMessageBox(value);
		break;
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
		R = *Pixel;
		G =	*(Pixel+1);
		B = *(Pixel+2);
		value.Format("R:%d G:%d B:%d", R, G, B);
		AfxMessageBox(value);
		break;
		
	}
}


void MovePic(int x, int y){
	AfxMessageBox("还没做");
}
int statistics[256];	//储存统计数据
void GrayStatistics () {
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//每行字节
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//实际位图数据
	
	//初始化统计数据
	for (int k = 0; k<256 ;k++)
	{
		statistics[k] = 0;
	}
	
	
	BYTE* Pixel;	//像素指针
	int R;
	for (int i = 0; i <=h ; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Pixel = lpBits + LineBytes*i +j;
			R = lpBitsInfo->bmiColors[*Pixel].rgbRed;	//因为为256灰色，获取其中一个值即可
			statistics[R]++;
		}
	}
	
	//调试过程，找出最大值，以便画图时确定高度的比例
	/*
	int maxNum = 0;
	CString str = "",a,b;
	for (i = 0; i<256; i++)
	{
	//a.Format("%d: ",i);
	//b.Format("%d; ",statistics[i]);
	//str = str + a + b;
	maxNum =  statistics[i]>maxNum?statistics[i]:maxNum;
	}
	str.Format("%d",maxNum);
	//AfxMessageBox(str);
	*/
}

//线性点运算
void linearity(){
	int w = lpBitsInfo->bmiHeader.biWidth;	//宽度
	int h = lpBitsInfo->bmiHeader.biHeight;	//高度
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//每一行所占用字节数
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//调色板指针
	BYTE *pixel;
	int newVal;
	int a=2,b=10;
	
	for (int i = 0; i < h; i ++)
	{
		for (int j = 0; j < w; j++)
		{
			// pixel = lpBits + LineBytes*(h-1-i)+ j; 
			pixel = lpBits + LineBytes*i+ j; 
			newVal = a*(*pixel)+b;	//计算线性点运算后的结果
			if (newVal > 255){
				*pixel = 255;
			}
			else if (newVal < 0)
			{
				*pixel = 0;
			}else{
				*pixel = newVal;
			}
		}
	}	
}
void equalization(){
	int w = lpBitsInfo->bmiHeader.biWidth;	//宽度
	int h = lpBitsInfo->bmiHeader.biHeight;	//高度
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//每一行所占用字节数
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//调色板指针
	
	int i,j;
	BYTE * pixel;
	float t[256]={0},temp=0;
	int size = w*h;
	int newStatistics[256],mapping[256];//新统计数组跟映射数组
	//灰度统计
	GrayStatistics();
	
	
	int k =0;
	//计算归一化直方图：   statistics/图像大小（w*h）
	for (i = 0; i < 256; i++){
		temp += statistics[i];
		t[i] += temp;	
		t[i]/=size;			//计算累积直方图t
		mapping[i] = int(255*t[i]+0.5); //获取对应灰度值所对应的新的灰度值（手段:计算灰度DB =int(255*t +0.5)）
	}
	
	for(i=0;i<h;i++){
		for(j=0;j<w;j++)
		{
			pixel=lpBits+LineBytes*i+j;
			*pixel=mapping[*pixel];	//获取对应点的灰度值，用其映射的值覆盖掉
		}
	}
		
}

void FT(complex<double>* TD,complex<double>* FD,int m)
{
	int u,x;
	double angle;
	for(u=0;u<m;u++)
	{
		FD[u]=0;//初始化数组的值
		for(x=0;x<m;x++)
		{
			angle=-2*PI*u*x/m;
			FD[u]+=TD[x]*complex<double>(cos(angle),sin(angle));
		}
		
		FD[u]/=m;
	}
	
}

void IFT(complex<double>* FD,complex<double>* TD,int m)
{
	int u,x;
	double angle;
	for(x=0;x<m;x++)
	{
		TD[x]=0;
		for(u=0;u<m;u++)
		{
			angle=2*PI*u*x/m;
			TD[x]+=FD[u]*complex<double>(cos(angle),sin(angle));
		}				
	}	
}


void lowFourier(){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	int new_LineBytes=(w*8+31)/32*4;
	LONG size=40+1024+new_LineBytes*h;
	
	complex<double>* TD=new complex<double>[w*h];
	complex<double>* FD=new complex<double>[w*h];
	
	int i,j;
	BYTE* pixel;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			TD[j+w*i]=complex<double>(*pixel*pow(-1,i+j),0);
		}
	}
	
	for(i=0;i<h;i++)
	{
		FT(&TD[w*i],&FD[w*i],w);
	}
	
	//转置
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			TD[i+h*j]=FD[j+w*i];
		}
	}
	
	for(i=0;i<w;i++)
		FT(&TD[i*h],&FD[i*h],h);
	
	BITMAPINFO* lpDIB_FT=(LPBITMAPINFO) malloc(size);
	if(NULL==lpDIB_FT)
		return;
	memcpy(lpDIB_FT,lpBitsInfo,size);
	
	lpBits= (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
	
	double temp;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++)
		{
			pixel=lpBits+LineBytes*(h-1-i)+j;
			temp=sqrt(FD[j*h+i].real()*FD[j*h+i].real()
				+ FD[j*h+i].imag()*FD[j*h+i].imag())*2000;
			if(temp>255)
				temp=255;
			*pixel=(BYTE)(temp);
			
			
		}
	}
	
	
	delete TD;
	gFD=FD;
	
	free(lpBitsInfo);
	
	lpBitsInfo=lpDIB_FT;
	
}

void lowIFourier()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	DWORD LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];
	
	int i,j;
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			FD[w * i + j] = gFD[i + h * j];
		}
	}
	
	for (i = 0; i < h; i++)
	{
		IFT(&FD[w * i], &TD[w * i], w);
	}
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			FD[i + h * j] = TD[j + w * i];
		}
	}
	
	for (i = 0; i < w; i++)
	{
		IFT(&FD[i * h], &TD[i * h], h);
	}
	
	//新图像内存大小
	LONG size = 40 + 1024 + LineBytes * h;
	
	BITMAPINFO*	lpDIB_FT = (LPBITMAPINFO)malloc(size);
	if (NULL == lpDIB_FT)
	{
		return;
	}
	memcpy(lpDIB_FT, lpBitsInfo, size);
	
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
	
	BYTE* pixel;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			*pixel = (BYTE)(TD[j * h + i].real() / pow(-1, i + j));
		}
	}
	
	delete TD;
	delete gFD;
	
	free(lpBitsInfo);
	lpBitsInfo = lpDIB_FT;
	
}




void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// 计算付立叶变换点数
	LONG count = 1 << r;
	// 计算加权系数
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	
	// 将时域点写入X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	
	// 采用蝶形算法进行快速付立叶变换，输出为频域值X2
	complex<double>* X2 = new complex<double>[count]; 
	
	int k,j,p,size;
	complex<double>* temp;
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	// 重新排序（码位倒序排列）
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	// 释放内存
	delete W;
	delete X1;
	delete X2;
}


void Fourier()
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//指向图像数据指针
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}
	
	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}
	
	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // 行
	{
		for(j = 0; j < FFT_w; j++)  // 列
		{
			// 指向DIB第i行，第j个象素的指针
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			
			// 给时域赋值
			//TD[j + FFT_w * i] = complex<double>(*pixel, 0);
			TD[j + FFT_w * i] = complex<double>(*pixel * pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶变换
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立叶变换
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}
	
	// 删除临时变量
	delete TD;
	
	//生成频谱图像
	//为频域图像分配内存
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return;
	memcpy(lpDIB_FFT, lpBitsInfo, size);
	
	//指向频域图像数据指针
	lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
	
	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			// 计算频谱幅度
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// 判断是否超过255
			if (temp > 255)
			{
				// 对于超过的，直接设置为255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			
			// 更新源图像
			*pixel = (BYTE)(temp);
		}
	}
	
	// 删除临时变量
	// delete FD;
	gFD=FD;
	
}


void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// 付立叶变换点数
	LONG	count;
	// 计算付立叶变换点数
	count = 1 << r;
	
	// 分配运算所需存储器
	complex<double> * X = new complex<double>[count];
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// 求共轭
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// 调用快速付立叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// 释放内存
	delete X;
}

void IFourier()
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	
	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}
	
	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}
	
	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // 行
		for(j = 0; j < FFT_w; j++)  // 列
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
		
		// 沿水平方向进行快速付立叶变换
		for(i = 0; i < FFT_h; i++)
			IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
		
		// 保存中间变换结果
		for(i = 0; i < FFT_h; i++)
			for(j = 0; j < FFT_w; j++)
				FD[i + FFT_h * j] = TD[j + FFT_w * i];
			
			// 沿垂直方向进行快速付立叶变换
			for(i = 0; i < FFT_w; i++)
				IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);
			
			//为反变换图像分配内存
			LONG size = 40 + 1024 + LineBytes * height;
			
			lpDIB_IFFT = (LPBITMAPINFO) malloc(size);
			if (NULL == lpDIB_IFFT)
				return;
			memcpy(lpDIB_IFFT, lpBitsInfo, size);
			
			//指向反变换图像数据指针
			BYTE* lpBits = (BYTE*)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
			BYTE* pixel;
			double temp;
			for(i = 0; i < FFT_h; i++) // 行
			{
				for(j = 0; j < FFT_w; j++) // 列
				{
					pixel = lpBits + LineBytes * (height - 1 - i) + j;
					temp= (TD[j*FFT_h + i].real() / pow(-1, i+j));
					if (temp < 0)
						temp = 0;
					else if (temp >255)
						temp = 255;
					*pixel = (BYTE)temp;
				}
			}
			
			// 删除临时变量
			delete FD;
			delete TD;
			//delete gFD;
}


void Template(int* Array, float coef)
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;
	// 复制BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];
	
	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	float result;
	
	// 行(除去边缘几行)
	for(i = 1; i < h - 1; i++)
	{
		// 列(除去边缘几列)
		for(j = 1; j < w - 1; j++)
		{
			// 指向新图第i行，第j个象素的指针
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			result = 0;
			// 计算3x3模板内像素灰度值的和
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// 指向原图在模板内每个像素点的灰度值，第i - 1 + k行，第j - 1 + l个象素的指针
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					// 灰度值乘上模板系数后累加
					result += (*pixel) * Array[k * 3 + l];
				}
			}
			// 乘上系数
			result *= coef;
			if (result < 0)
				*new_pixel = 0;
			else if(result > 255)
				*new_pixel = 255;
			else
				*new_pixel = (BYTE) (result + 0.5);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}


// 均值滤波
void AverageFilter() 
{
	int Array[9]; //3x3模板
	//标准均值滤波
	Array[0] = 1;	Array[1] = 1;	Array[2] = 1;
	Array[3] = 1;	Array[4] = 1;	Array[5] = 1;
	Array[6] = 1;	Array[7] = 1;	Array[8] = 1;
	Template(Array, (float)1/9);
	/*
	//高斯滤波
	Array[0] = 1;	Array[1] = 2;	Array[2] = 1;
	Array[3] = 2;	Array[4] = 4;	Array[5] = 2;
	Array[6] = 1;	Array[7] = 2;	Array[8] = 1;
	Template(Array, (float)1/16);
	*/
}

// 3.中值滤波
BYTE WINAPI GetMedianNum(BYTE* Array)
{
	int i,j;
	BYTE temp;
	// 用冒泡法对数组进行排序
	for (j = 0; j < 9 - 1; j ++)
	{
		for (i = 0; i < 9 - j - 1; i ++)
		{
			if (Array[i] > Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
			}
		}
	}
	// 返回中值
	return Array[4];
}

void MedianFilter() 
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;
	// 复制BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];
	
	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	BYTE Value[9]; //3x3模板
	// 行(除去边缘几行)
	for(i = 1; i < h - 1; i++)
	{
		// 列(除去边缘几列)
		for(j = 1; j < w - 1; j++)
		{
			// 指向新图第i行，第j个象素的指针
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			// 计算 3x3模板内像素的灰度值
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// 指向原图第i - 1 + k行，第j - 1 + l个象素的指针
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					// 保存象素值
					Value[k * 3 + l] = *pixel;
				}
			}
			// 获取中值
			*new_pixel = GetMedianNum(Value);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}

//梯度锐化
void GradSharp() 
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// 指向源图像的指针
	BYTE *lpSrc, *lpSrc1, *lpSrc2;
	int i, j;
	BYTE temp;
	// 每行
	for(i = 0; i < h-1; i++)
	{
		// 每列
		for(j = 0; j < w-1; j++)
		{
			// 指向图像第i行，第j个象素的指针
			lpSrc  = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j;
			// 指向图像第i+1行，第j个象素的指针
			lpSrc1 = (unsigned char*)lpBits + LineBytes * (h - 2 - i) + j;
			// 指向图像第i行，第j+1个象素的指针
			lpSrc2 = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j + 1;
			//梯度算子
			temp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			if (temp > 255)
				*lpSrc = 255;
			else
				*lpSrc = temp;
		}
	}
}


// 拉普拉斯锐化
void RaplasSharp() 
{
	int Array[9]; //3x3模板
				  /*
				  //拉普拉斯算子
				  Array[0] = 0;	Array[1] = 1;	Array[2] = 0;
				  Array[3] = 1;	Array[4] = -4;	Array[5] = 1;
				  Array[6] = 0;	Array[7] = 1;	Array[8] = 0;
	*/	
	//拉普拉斯锐化
	Array[0] = -1;	Array[1] = -1;	Array[2] = -1;
	Array[3] = -1;	Array[4] = 9;	Array[5] = -1;
	Array[6] = -1;	Array[7] = -1;	Array[8] = -1;
	Template(Array, (float)1);
}


//理想低-高通滤波(D>0:低通 D<=0:高通)
void Ideal_Filter_FFT(int D)
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int FFT_w = 1;
	while(FFT_w * 2 <= width)
		FFT_w *= 2;
	int FFT_h = 1;
	while(FFT_h * 2 <= height)
		FFT_h *= 2;
	
	//备份原始频域数据
	complex<double>* origin_FD = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		origin_FD[n] = gFD[n];
	
	//频率滤波（理想高/低通滤波）
	int i, j;
	double dis;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			if (D > 0) //低通
			{
				if (dis > D) 
					gFD[i * FFT_h + j] = 0; //理想低通，截断高频
			}
			else { //高通
				if (dis <= -D) 
					gFD[i * FFT_h + j] = 0; //理想高通，截断低频
			}
		}
	}
	
	//生成新的频谱图像
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	LONG size = 40 + 1024 + LineBytes * height;
	BITMAPINFO* new_lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	memcpy(new_lpDIB_FFT, lpDIB_FFT, size);
	BYTE* lpBits = (BYTE*)&new_lpDIB_FFT->bmiColors[new_lpDIB_FFT->bmiHeader.biClrUsed];
	double temp;
	BYTE* pixel;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			temp = sqrt(gFD[j * FFT_h + i].real() * gFD[j * FFT_h + i].real() + 
				gFD[j * FFT_h + i].imag() * gFD[j * FFT_h + i].imag())*2000 ;
			if (temp > 255)
				temp = 255;
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			*pixel = (BYTE)(temp);
		}
	}
	//释放原频谱图像
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	//更新新的频谱图像
	lpDIB_FFT = new_lpDIB_FFT;
	
	//傅里叶反变换
	IFourier();
	
	//恢复到原始频域数据
	delete gFD;
	gFD = origin_FD;
}

// 巴特沃斯低通/高通滤波
void BLPF_Filter_FFT(int D)
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int FFT_w = 1;
	while(FFT_w * 2 <= width)
		FFT_w *= 2;
	int FFT_h = 1;
	while(FFT_h * 2 <= height)
		FFT_h *= 2;
	
	//备份原始频域数据
	complex<double>* origin_FD = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		origin_FD[n] = gFD[n];
	
	//频率滤波（理想高/低通滤波）
	int i, j;
	double dis;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			
			if (D > 0) //低通
			{
				if (dis > D) 
					gFD[i * FFT_h + j] *= 1/(1+pow(dis/D,4));; //二阶巴特沃斯低通滤波器，截断高频
			}
			else { //高通
				if (dis <= -D) 
					gFD[i * FFT_h + j] *= 1/(1+pow(D/dis,4)); //二阶巴特沃斯高通滤波器，截断低频
			}
		}
	}
	
	//生成新的频谱图像
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	LONG size = 40 + 1024 + LineBytes * height;
	BITMAPINFO* new_lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	memcpy(new_lpDIB_FFT, lpDIB_FFT, size);
	BYTE* lpBits = (BYTE*)&new_lpDIB_FFT->bmiColors[new_lpDIB_FFT->bmiHeader.biClrUsed];
	double temp;
	BYTE* pixel;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			temp = sqrt(gFD[j * FFT_h + i].real() * gFD[j * FFT_h + i].real() + 
				gFD[j * FFT_h + i].imag() * gFD[j * FFT_h + i].imag())*2000 ;
			if (temp > 255)
				temp = 255;
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			*pixel = (BYTE)(temp);
		}
	}
	//释放原频谱图像
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	//更新新的频谱图像
	lpDIB_FFT = new_lpDIB_FFT;
	
	//傅里叶反变换
	IFourier();
	
	//恢复到原始频域数据
	delete gFD;
	gFD = origin_FD;
}