#include <fstream>
#include <string.h>
#include <codecvt> 
#include <stdio.h>
#include <fcntl.h> 
#include <io.h>   
#include <stdlib.h>
#include<wchar.h>

using namespace std;
typedef struct SinhVien
{
	wchar_t MSSV[20];
	wchar_t ten[30];
	wchar_t khoa[30];
	int khoatuyen;
	wchar_t Ngaysinh[20];
	wchar_t Anh[100];
	wchar_t Mota[1000];
	wchar_t SoThich[20][200];
	int Dem_sothich;
}sv;
int demsv(FILE* fin)
{
	int dem = 0;
	wchar_t c[2000];
	do
	{
		fgetws(c, 2000, fin);
		dem++;
	} while (!feof(fin));
	rewind(fin);
	return dem;
}
void tachkhoatuyen(FILE* fin, int &s)
{
	fseek(fin, 2L, SEEK_CUR);
	fwscanf(fin, L"%d", &s);
	fseek(fin, 1L, SEEK_CUR);
}
void tach(FILE* fin, wchar_t noidung[])
{
	int i = 0;
	wchar_t c;
	fseek(fin, 2L, SEEK_CUR);
	while (1)
	{
		c = fgetwc(fin);
		if (c == L'"' || c == L'\n' || c == EOF) break;
		else
		{
			noidung[i] = c;
			i++;
		}
	}
	noidung[i] = '\0';
}
int demsothich(FILE*fin)
{
	int dem = 0;
	wchar_t c;
	while (1)
	{
		c = fgetwc(fin);
		if (c == L'"')
		{
			dem++;
		}
		else if (c == '\n' || c == EOF) break;
	}
	return (dem / 2) - 7;
}
void GanNoiDung(FILE* fin, sv &a)
{
	tach(fin, a.MSSV);
	tach(fin, a.ten);
	tach(fin, a.khoa);
	tachkhoatuyen(fin, a.khoatuyen);
	tach(fin, a.Ngaysinh);
	tach(fin, a.Anh);
	tach(fin, a.Mota);
	for (int i = 0; i < a.Dem_sothich; i++)
	{
		tach(fin, a.SoThich[i]);
	}
}
wchar_t* ten_html(sv a)
{
	wchar_t tenweb[50] = L"Websites\\";
	wchar_t duoifile[50] = L".html";
	wcscat(tenweb, a.MSSV);
	wcscat(tenweb, duoifile);
	return tenweb;
}
void chenvao(wchar_t cantim[], wchar_t chuoicha[], wchar_t chuoichen[])
{
	wchar_t gep1[200];
	wchar_t* gep2;
	chuoicha = wcsstr(chuoicha, cantim);
	int n = wcslen(chuoicha) - wcslen(chuoicha);
	wcsncpy(gep1, chuoicha, n);
	gep1[n] = L'\0';
	wcscat(chuoichen, chuoicha + wcslen(cantim));
	wcscat(gep1, chuoichen);
	wcscpy(chuoicha, gep1);
}
void gan_mail(wchar_t str_in[], wchar_t mail[])
{
	wcslwr(str_in);
	wchar_t b[20] = L"@gmail.com";
	mail[0] = str_in[0];
	int dem = 1;
	for (int i = 0; i < wcslen(str_in); i++)
	{
		if (str_in[i] == L' ')
		{
			mail[dem] = str_in[i + 1];
			dem++;
		}
	}
	mail[dem] = L'\0';
	wcscat(mail, b);
}
void gan_sothich(sv a, wchar_t str_out[])
{
	if (a.Dem_sothich != 0)   
	{
		for (int i = 0; i < a.Dem_sothich; i++)
		{
			wcscat(str_out, L"<li>");
			wcscat(str_out, a.SoThich[i]);
			wcscat(str_out, L"</li>");
		}
	}
	else str_out[0] = '\0';
}
void tim_thay_the(wchar_t str_gan[], sv a)
{
	wchar_t Tenhoa[40] = L"INHOA";
	wchar_t ten[40] = L"TÊN";
	wchar_t MSSV[10] = L"MSSV";
	wchar_t khoa[40] = L"MAJOR";
	wchar_t Nsinh[20] = L"NGÀY SINH";
	wchar_t Anh[100] = L"HINHANH";
	wchar_t Mota[1000] = L"MÔ TẢ";
	wchar_t Email[30] = L"EMAIL";
	wchar_t sothich[30] = L"SOTHICH";

	//Chèn tên hoa đầu trang.
	wchar_t *tro_tenhoa = wcsstr(str_gan, Tenhoa);
	if (tro_tenhoa != 0)
	{
		chenvao(Tenhoa, str_gan, wcsupr(a.ten));
	}

	// Chèn tên.
	wchar_t *tro_ten = wcsstr(str_gan, ten);
	if (tro_ten != 0)
	{
		chenvao(ten, str_gan, a.ten);
	}

	//Chèn MSSV.
	wchar_t *tro_mssv = wcsstr(str_gan, MSSV);
	if (tro_mssv != 0)
	{
		chenvao(MSSV, str_gan, a.MSSV);
	}

	//Chèn Khoa.
	wchar_t *tro_khoa = wcsstr(str_gan, khoa);
	if (tro_khoa != 0)
	{
		chenvao(khoa, str_gan, a.khoa);
	}

	//Chèn ngày sinh.
	wchar_t *tro_ngaysinh = wcsstr(str_gan, Nsinh);
	if (tro_ngaysinh != 0)
	{
		chenvao(Nsinh, str_gan, a.Ngaysinh);
	}

	//Chèn ảnh cá nhân.
	wchar_t *tro_anh = wcsstr(str_gan, Anh);
	if (tro_anh != 0)
	{
		chenvao(Anh, str_gan, a.Anh);
	}

	//Chèn mô tả sinh viên.
	wchar_t *tro_mota = wcsstr(str_gan, Mota);
	if (tro_mota != 0)
	{
		chenvao(Mota, str_gan, a.Mota);
	}

	//Chèn gmail sinh viên.
	wchar_t mail[30];
	gan_mail(a.ten, mail);
	wchar_t *tro_mail = wcsstr(str_gan, Email);
	if (tro_mail != 0)
	{
		chenvao(Email, str_gan, mail);
	}

	//Chèn các sở thích.
	wchar_t cacsothich[1000]{};
	gan_sothich(a, cacsothich);
	wchar_t *tro_st = wcsstr(str_gan, sothich);
	if (tro_st != 0)
	{
		chenvao(sothich, str_gan, cacsothich);
	}

}
void Xuat_HTML(FILE* HTMLgoc, FILE*csv, sv &a){
	rewind(HTMLgoc);
	wchar_t c[500];
	while (!feof(HTMLgoc))
	{
		fgetws(c, 500, HTMLgoc);
		tim_thay_the(c, a);
		fputws(c, csv);
	}
	fclose(csv);
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	sv a[20];
	int soSV, k;
	FILE *fin = _wfopen(L"ListSV.csv", L"r, ccs=UTF-8");
	if (fin != NULL)
	{
		fseek(fin, 0L, SEEK_SET);
		soSV = demsv(fin);
		for (int i = 0; i < soSV-1; i++)
		{
			a[i].Dem_sothich = demsothich(fin);
		}
		rewind(fin);
		fseek(fin, 1L, SEEK_CUR);
		for (k = 0; k < soSV; k++)
		{
			fseek(fin, 1L, SEEK_CUR);
			GanNoiDung(fin, a[k]);
			wprintf(L"%s\n", a[k].MSSV);
		}
	}else wprintf(L"Không thể đọc file \n");
	
	wchar_t *tenweb;
	FILE *HTMLgoc = _wfopen(L"HTMLgoc.html", L"r, ccs=UTF-8");
	if (HTMLgoc != NULL)
	{
		for (int i = 0; i < soSV; i++)
		{
			tenweb = ten_html(a[i]);
			FILE *fweb = _wfopen(tenweb, L"wt, ccs=UTF-8");
			if (fweb != NULL)
			{
				Xuat_HTML(HTMLgoc, fweb, a[i]);
			}else wprintf(L"Không thể mở file \n");
		}
	}else wprintf(L"Không thể mở file \n");
	fclose(fin);
	fclose(HTMLgoc);
}