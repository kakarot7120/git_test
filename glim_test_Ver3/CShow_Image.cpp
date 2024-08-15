// CShow_Image.cpp: 구현 파일
//

#include "pch.h"
#include "glim_test.h"
#include "afxdialogex.h"
#include "CShow_Image.h"

#include "glim_testDlg.h"

//내가 만든 func
void CShow_Image::Select_Color(int r_color, int g_color, int b_color) {
	nWidth = 810;
	nHeight = 810;
	nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[PIXEL_SIZE];
		for (int i = 0; i < PIXEL_SIZE;i++) {
			rgb[i].rgbRed = r_color;
			rgb[i].rgbGreen = g_color;
			rgb[i].rgbBlue = b_color;
		}
		m_image.SetColorTable(0, PIXEL_SIZE, rgb);
	}
	/*unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, color, nWidth * nHeight);*/
}


// CShow_Image 대화 상자

IMPLEMENT_DYNAMIC(CShow_Image, CDialogEx)

CShow_Image::CShow_Image(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CShow_Image, pParent),
	nWidth(0), 
	nHeight(0), 
	nBpp(0)
{
	m_pGlim = pParent;
}

CShow_Image::~CShow_Image()
{

}

void CShow_Image::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShow_Image, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShow_Image 메시지 처리기



BOOL CShow_Image::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	/*nWidth = 810;
	nHeight = 810;
	nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256;i++) {
			rgb[i].rgbRed = i;
			rgb[i].rgbGreen = i;
			rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xFF, nWidth * nHeight);*/
	//Select_Color(0xFF);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CShow_Image::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
}




