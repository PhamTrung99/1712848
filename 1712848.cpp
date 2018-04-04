#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<wchar.h>
#include<conio.h>

typedef struct sinhvien
{
	char MSSV[10];
	wchar_t ten[30];
	wchar_t khoa[30];
	int khoatuyen;
	char ngaysinh[8];
	char *link_anh;
	wchar_t mota[1000];
	wchar_t sothich;
}sv;
int demsv(FILE *fi, int &n)
{
	char ch;
	do
	{
		ch = fgetc(fi);
		if (ch == '\n')
		{
			n++;
		}
	} while (ch != EOF);
	return n;
}
void docsv(FILE *fi, FILE *fo, int n)
{
	sinhvien a[10];
	fseek(fi, 0, 0);
	for (int i = 0; i < n; i++)
	{
		fread(a[i].MSSV, sizeof(char), 10, fi);
		
	}
	fwrite(a[1].MSSV, sizeof(char), 10, fo);
}
void main()
{
	FILE *fi = fopen("sinhvien.csv", "r");
	FILE *fo = fopen("sinhvien.txt", "wt");
	int n = 0;
	if (fi != NULL)
	{
		int kq = demsv(fi,n);
		docsv(fi, fo, kq);
	}
	else printf("Khong doc duoc file.");
	fcloseall();
}