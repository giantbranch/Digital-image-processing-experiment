#include "stdafx.h"

LPBITMAPINFO  lpBitsInfo = NULL;

BOOL LoadBmpFile (char* BmpFileName)
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
	if (NULL == (lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;
	
	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	
	//���ļ����ݶ���lpBitsInfo
	fread((char*)lpBitsInfo, size, 1, fp);
	lpBitsInfo->bmiHeader.biClrUsed = NumColors;


	return FALSE;
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
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;	//ÿ���ֽ�
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];	//ʵ��λͼ����
	
	int statistics[255];	//����ͳ������
	BYTE* Pixel;	//�洢����ֵ
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

