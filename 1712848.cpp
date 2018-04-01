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
void nhapsv(FILE *fi, int &n,sv a[10])
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
	printf("%d\n", n);
}
void main()
{
	FILE *fi = fopen("sinhvien1.txt", "r+");
	int n = 1;
	sinhvien a[10];
	if (fi != NULL)
	{
		nhapsv(fi,n,a);
	}
	else printf("Khong doc duoc file.");
	fclose(fi);
}