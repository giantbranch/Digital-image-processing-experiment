#include "stdafx.h"
#include <complex>

#define PI 3.1415926535

using namespace std;

LPBITMAPINFO  lpBitsInfo = NULL;
LPBITMAPINFO  TmplpBitsInfo = NULL;
LPBITMAPINFO  lpBitsInfo1 = NULL;
BITMAPINFO* lpDIB_FFT = NULL;  //���ٸ���Ҷ�任
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
	
	BITMAPFILEHEADER   bf;       //�ļ�ͷ�ṹ
	BITMAPINFOHEADER   bi;       //��Ϣͷ�ṹ
	
	//���ļ�ͷBITMAPFILEHEADER�ṹ���ļ��ж�������д��bf��
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	
	//����ϢͷBITMAPINFOHEADER�ṹ���ļ��ж�������д��bi��
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
	
	//����ͼ����ÿһ�����ع�ռ�����ֽ�LineBytes
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;
	
	//����ʵ��ͼ������ռ�õ��ֽ���ImgSize
	DWORD ImgSize=LineBytes * bi.biHeight;
	
	DWORD NumColors;  //ʵ���õ�����ɫ��������ɫ�������е���ɫ����
	if (bi.biClrUsed != 0)
		NumColors = bi.biClrUsed; //���bi.biClrUsed��Ϊ�㣬���Ǳ�ͼ��ʵ���õ�����ɫ��
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
			NumColors=0; //�������ɫͼ��û�õ���ɫ��
			break;
		}
	}
	//�����ڴ棬��СΪBITMAPINFOHEADER�ṹ����+��ɫ��+ʵ��λͼ����
	LONG size= sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (TmplpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;
	
	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	
	//���ļ����ݶ���lpBitsInfo
	fread((char*)TmplpBitsInfo, size, 1, fp);
	TmplpBitsInfo->bmiHeader.biClrUsed = NumColors;
	
	
	return TmplpBitsInfo;
}

void Gray()
{
	int w = lpBitsInfo->bmiHeader.biWidth;	//���
	int h = lpBitsInfo->bmiHeader.biHeight;	//�߶�
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿһ����ռ���ֽ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//��ɫ��ָ��
	//��ͼ���ڴ��С
	int new_LineBytes =(w * 8 + 31)/32 * 4;
	LONG size = 40 + 1024 + new_LineBytes * h;
	LPBITMAPINFO new_lpBitsInfo = (LPBITMAPINFO) malloc(size);
	//��д�ļ���Ϣͷ
	memcpy(new_lpBitsInfo, lpBitsInfo, 40);
	new_lpBitsInfo->bmiHeader.biBitCount = 8;
	new_lpBitsInfo->bmiHeader.biClrUsed = 256;
	//��ɫ��
	int i,j;
	for (i = 0; i < 256; i ++)
	{
		new_lpBitsInfo->bmiColors[i].rgbBlue = i;
		new_lpBitsInfo->bmiColors[i].rgbGreen = i;
		new_lpBitsInfo->bmiColors[i].rgbRed = i;
		new_lpBitsInfo->bmiColors[i].rgbReserved = 0; 
	}
	//λͼ����
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
		//����һ
		//fourBit = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)&(15<<(1-point.x%2)*4);
		//������
		if (!point.x%2)//�жϵ������8���ֽ��е���߻����ұߣ������0��ʼ
		{
			//�������ߣ�ȡ����λ��������λ����
			fourBit = *(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)>>4;
		}else{
			//������ұߣ�ȡ����λ����15����00001111������
			fourBit = (BYTE)*(lpBits + LineBytes * (h - 1 - point.y) + point.x/2)&15;
		}
		//ͨ����ɫ���ȡrgb��ֵ
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
	AfxMessageBox("��û��");
}
int statistics[256];	//����ͳ������
void GrayStatistics () {
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿ���ֽ�
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//ʵ��λͼ����
	
	//��ʼ��ͳ������
	for (int k = 0; k<256 ;k++)
	{
		statistics[k] = 0;
	}
	
	
	BYTE* Pixel;	//����ָ��
	int R;
	for (int i = 0; i <=h ; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Pixel = lpBits + LineBytes*i +j;
			R = lpBitsInfo->bmiColors[*Pixel].rgbRed;	//��ΪΪ256��ɫ����ȡ����һ��ֵ����
			statistics[R]++;
		}
	}
	
	//���Թ��̣��ҳ����ֵ���Ա㻭ͼʱȷ���߶ȵı���
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

//���Ե�����
void linearity(){
	int w = lpBitsInfo->bmiHeader.biWidth;	//���
	int h = lpBitsInfo->bmiHeader.biHeight;	//�߶�
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿһ����ռ���ֽ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//��ɫ��ָ��
	BYTE *pixel;
	int newVal;
	int a=2,b=10;
	
	for (int i = 0; i < h; i ++)
	{
		for (int j = 0; j < w; j++)
		{
			// pixel = lpBits + LineBytes*(h-1-i)+ j; 
			pixel = lpBits + LineBytes*i+ j; 
			newVal = a*(*pixel)+b;	//�������Ե������Ľ��
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
	int w = lpBitsInfo->bmiHeader.biWidth;	//���
	int h = lpBitsInfo->bmiHeader.biHeight;	//�߶�
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿһ����ռ���ֽ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//��ɫ��ָ��
	
	int i,j;
	BYTE * pixel;
	float t[256]={0},temp=0;
	int size = w*h;
	int newStatistics[256],mapping[256];//��ͳ�������ӳ������
	//�Ҷ�ͳ��
	GrayStatistics();
	
	
	int k =0;
	//�����һ��ֱ��ͼ��   statistics/ͼ���С��w*h��
	for (i = 0; i < 256; i++){
		temp += statistics[i];
		t[i] += temp;	
		t[i]/=size;			//�����ۻ�ֱ��ͼt
		mapping[i] = int(255*t[i]+0.5); //��ȡ��Ӧ�Ҷ�ֵ����Ӧ���µĻҶ�ֵ���ֶ�:����Ҷ�DB =int(255*t +0.5)��
	}
	
	for(i=0;i<h;i++){
		for(j=0;j<w;j++)
		{
			pixel=lpBits+LineBytes*i+j;
			*pixel=mapping[*pixel];	//��ȡ��Ӧ��ĻҶ�ֵ������ӳ���ֵ���ǵ�
		}
	}
		
}

void FT(complex<double>* TD,complex<double>* FD,int m)
{
	int u,x;
	double angle;
	for(u=0;u<m;u++)
	{
		FD[u]=0;//��ʼ�������ֵ
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
	
	//ת��
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
	
	//��ͼ���ڴ��С
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
	// ���㸶��Ҷ�任����
	LONG count = 1 << r;
	// �����Ȩϵ��
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	
	// ��ʱ���д��X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	
	// ���õ����㷨���п��ٸ���Ҷ�任�����ΪƵ��ֵX2
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
	
	// ����������λ�������У�
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
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}


void Fourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//ָ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}
	
	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}
	
	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // ��
	{
		for(j = 0; j < FFT_w; j++)  // ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			
			// ��ʱ��ֵ
			//TD[j + FFT_w * i] = complex<double>(*pixel, 0);
			TD[j + FFT_w * i] = complex<double>(*pixel * pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}
	
	// ɾ����ʱ����
	delete TD;
	
	//����Ƶ��ͼ��
	//ΪƵ��ͼ������ڴ�
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return;
	memcpy(lpDIB_FFT, lpBitsInfo, size);
	
	//ָ��Ƶ��ͼ������ָ��
	lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
	
	double temp;
	for(i = 0; i < FFT_h; i++) // ��
	{
		for(j = 0; j < FFT_w; j++) // ��
		{
			// ����Ƶ�׷���
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// �ж��Ƿ񳬹�255
			if (temp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			
			// ����Դͼ��
			*pixel = (BYTE)(temp);
		}
	}
	
	// ɾ����ʱ����
	// delete FD;
	gFD=FD;
	
}


void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	// ���㸶��Ҷ�任����
	count = 1 << r;
	
	// ������������洢��
	complex<double> * X = new complex<double>[count];
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// ����
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// �ͷ��ڴ�
	delete X;
}

void IFourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	
	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}
	
	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}
	
	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // ��
		for(j = 0; j < FFT_w; j++)  // ��
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
		
		// ��ˮƽ������п��ٸ���Ҷ�任
		for(i = 0; i < FFT_h; i++)
			IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
		
		// �����м�任���
		for(i = 0; i < FFT_h; i++)
			for(j = 0; j < FFT_w; j++)
				FD[i + FFT_h * j] = TD[j + FFT_w * i];
			
			// �ش�ֱ������п��ٸ���Ҷ�任
			for(i = 0; i < FFT_w; i++)
				IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);
			
			//Ϊ���任ͼ������ڴ�
			LONG size = 40 + 1024 + LineBytes * height;
			
			lpDIB_IFFT = (LPBITMAPINFO) malloc(size);
			if (NULL == lpDIB_IFFT)
				return;
			memcpy(lpDIB_IFFT, lpBitsInfo, size);
			
			//ָ�򷴱任ͼ������ָ��
			BYTE* lpBits = (BYTE*)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
			BYTE* pixel;
			double temp;
			for(i = 0; i < FFT_h; i++) // ��
			{
				for(j = 0; j < FFT_w; j++) // ��
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
			
			// ɾ����ʱ����
			delete FD;
			delete TD;
			//delete gFD;
}


void Template(int* Array, float coef)
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;
	// ����BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];
	
	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	float result;
	
	// ��(��ȥ��Ե����)
	for(i = 1; i < h - 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = 1; j < w - 1; j++)
		{
			// ָ����ͼ��i�У���j�����ص�ָ��
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			result = 0;
			// ����3x3ģ�������ػҶ�ֵ�ĺ�
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// ָ��ԭͼ��ģ����ÿ�����ص�ĻҶ�ֵ����i - 1 + k�У���j - 1 + l�����ص�ָ��
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					// �Ҷ�ֵ����ģ��ϵ�����ۼ�
					result += (*pixel) * Array[k * 3 + l];
				}
			}
			// ����ϵ��
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


// ��ֵ�˲�
void AverageFilter() 
{
	int Array[9]; //3x3ģ��
	//��׼��ֵ�˲�
	Array[0] = 1;	Array[1] = 1;	Array[2] = 1;
	Array[3] = 1;	Array[4] = 1;	Array[5] = 1;
	Array[6] = 1;	Array[7] = 1;	Array[8] = 1;
	Template(Array, (float)1/9);
	/*
	//��˹�˲�
	Array[0] = 1;	Array[1] = 2;	Array[2] = 1;
	Array[3] = 2;	Array[4] = 4;	Array[5] = 2;
	Array[6] = 1;	Array[7] = 2;	Array[8] = 1;
	Template(Array, (float)1/16);
	*/
}

// 3.��ֵ�˲�
BYTE WINAPI GetMedianNum(BYTE* Array)
{
	int i,j;
	BYTE temp;
	// ��ð�ݷ��������������
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
	// ������ֵ
	return Array[4];
}

void MedianFilter() 
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;
	// ����BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];
	
	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	BYTE Value[9]; //3x3ģ��
	// ��(��ȥ��Ե����)
	for(i = 1; i < h - 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = 1; j < w - 1; j++)
		{
			// ָ����ͼ��i�У���j�����ص�ָ��
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			// ���� 3x3ģ�������صĻҶ�ֵ
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// ָ��ԭͼ��i - 1 + k�У���j - 1 + l�����ص�ָ��
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					// ��������ֵ
					Value[k * 3 + l] = *pixel;
				}
			}
			// ��ȡ��ֵ
			*new_pixel = GetMedianNum(Value);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}

//�ݶ���
void GradSharp() 
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	// ָ��Դͼ���ָ��
	BYTE *lpSrc, *lpSrc1, *lpSrc2;
	int i, j;
	BYTE temp;
	// ÿ��
	for(i = 0; i < h-1; i++)
	{
		// ÿ��
		for(j = 0; j < w-1; j++)
		{
			// ָ��ͼ���i�У���j�����ص�ָ��
			lpSrc  = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j;
			// ָ��ͼ���i+1�У���j�����ص�ָ��
			lpSrc1 = (unsigned char*)lpBits + LineBytes * (h - 2 - i) + j;
			// ָ��ͼ���i�У���j+1�����ص�ָ��
			lpSrc2 = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j + 1;
			//�ݶ�����
			temp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			if (temp > 255)
				*lpSrc = 255;
			else
				*lpSrc = temp;
		}
	}
}


// ������˹��
void RaplasSharp() 
{
	int Array[9]; //3x3ģ��
				  /*
				  //������˹����
				  Array[0] = 0;	Array[1] = 1;	Array[2] = 0;
				  Array[3] = 1;	Array[4] = -4;	Array[5] = 1;
				  Array[6] = 0;	Array[7] = 1;	Array[8] = 0;
	*/	
	//������˹��
	Array[0] = -1;	Array[1] = -1;	Array[2] = -1;
	Array[3] = -1;	Array[4] = 9;	Array[5] = -1;
	Array[6] = -1;	Array[7] = -1;	Array[8] = -1;
	Template(Array, (float)1);
}


//�����-��ͨ�˲�(D>0:��ͨ D<=0:��ͨ)
void Ideal_Filter_FFT(int D)
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int FFT_w = 1;
	while(FFT_w * 2 <= width)
		FFT_w *= 2;
	int FFT_h = 1;
	while(FFT_h * 2 <= height)
		FFT_h *= 2;
	
	//����ԭʼƵ������
	complex<double>* origin_FD = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		origin_FD[n] = gFD[n];
	
	//Ƶ���˲��������/��ͨ�˲���
	int i, j;
	double dis;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			if (D > 0) //��ͨ
			{
				if (dis > D) 
					gFD[i * FFT_h + j] = 0; //�����ͨ���ضϸ�Ƶ
			}
			else { //��ͨ
				if (dis <= -D) 
					gFD[i * FFT_h + j] = 0; //�����ͨ���ضϵ�Ƶ
			}
		}
	}
	
	//�����µ�Ƶ��ͼ��
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
	//�ͷ�ԭƵ��ͼ��
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	//�����µ�Ƶ��ͼ��
	lpDIB_FFT = new_lpDIB_FFT;
	
	//����Ҷ���任
	IFourier();
	
	//�ָ���ԭʼƵ������
	delete gFD;
	gFD = origin_FD;
}

// ������˹��ͨ/��ͨ�˲�
void BLPF_Filter_FFT(int D)
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int FFT_w = 1;
	while(FFT_w * 2 <= width)
		FFT_w *= 2;
	int FFT_h = 1;
	while(FFT_h * 2 <= height)
		FFT_h *= 2;
	
	//����ԭʼƵ������
	complex<double>* origin_FD = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		origin_FD[n] = gFD[n];
	
	//Ƶ���˲��������/��ͨ�˲���
	int i, j;
	double dis;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			
			if (D > 0) //��ͨ
			{
				if (dis > D) 
					gFD[i * FFT_h + j] *= 1/(1+pow(dis/D,4));; //���װ�����˹��ͨ�˲������ضϸ�Ƶ
			}
			else { //��ͨ
				if (dis <= -D) 
					gFD[i * FFT_h + j] *= 1/(1+pow(D/dis,4)); //���װ�����˹��ͨ�˲������ضϵ�Ƶ
			}
		}
	}
	
	//�����µ�Ƶ��ͼ��
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
	//�ͷ�ԭƵ��ͼ��
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	//�����µ�Ƶ��ͼ��
	lpDIB_FFT = new_lpDIB_FFT;
	
	//����Ҷ���任
	IFourier();
	
	//�ָ���ԭʼƵ������
	delete gFD;
	gFD = origin_FD;
}