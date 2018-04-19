#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<wchar.h>
#include<conio.h>
#include <fcntl.h> 
#include <io.h>    
#include <codecvt> 
#include <fstream>
using namespace std;
typedef struct SINHVIEN
{
	wchar_t MSSV[20];
	wchar_t ten[50];
	wchar_t khoa[100];
	int khoatuyen;
	wchar_t ngaysinh[50];
	wchar_t anh[100];
	wchar_t mota[10000];
	wchar_t sothich[20][200];
	int demsothich;
}sv;
void tachkhoatuyen(FILE* fi, int &kt)
{
	fseek(fi,0, SEEK_CUR);
	fwscanf(fi, L"%d", &kt);
	fseek(fi,1L, SEEK_CUR);
}
void tachsv(FILE* fi, wchar_t nd[])
{
	int i = 0;
	wchar_t c;
	fseek(fi,0L, SEEK_CUR);
	while (1)
	{
		c = fgetwc(fi);
		if (c == L';' || c == L'\n' || c == EOF) break;
		else
		{
			nd[i] = c;
			i++;
		}
	}
	nd[i] = '\0';
}
int demsothich(FILE*fi)
{
	int dem = 0;
	wchar_t c;
	while (1)
	{
		c = fgetwc(fi);
		if (c == L';') dem++;
		if (c == '\n' || c == EOF) break;
	}
	return dem  - 6;
}
void sothichmoinguoi(FILE* fi, sv sv[10])
{
	for (int i = 0; i < 3; i++)
	{
		sv[i].demsothich = demsothich(fi);
	}
	rewind(fi);
}
void luusv(FILE* fi, sv &a){
	tachsv(fi, a.MSSV);
	tachsv(fi, a.ten);
	tachsv(fi, a.khoa);
	tachkhoatuyen(fi, a.khoatuyen);
	tachsv(fi, a.ngaysinh);
	tachsv(fi, a.anh);
	tachsv(fi, a.mota);
	/*for (int i = 0; i < a.demsothich; i++)
	{
		tachsv(fi, a.sothich[i]);
	}*/
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SINHVIEN a[10];
	FILE *fi = _wfopen(L"sinhvien.csv", L"r, ccs=UTF-8");
	int sosv = 2;
	if (fi != NULL)
	{
		//sothichmoinguoi(fi, a);
		fseek(fi,0L,SEEK_SET);
		for (int i = 0; i < sosv; i++)
		{
			luusv(fi, a[i]);
			wprintf(L"%s\n%s\n%s\n%d\n%s\n%s\n%s\n", a[i].MSSV, a[i].ten, a[i].khoa, a[i].khoatuyen, a[i].ngaysinh, a[i].anh, a[i].mota);
		}
	}
	else wprintf(L"Không đọc được file.");
	fclose(fi);
}