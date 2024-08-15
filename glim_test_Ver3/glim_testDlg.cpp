
// glim_testDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "glim_test.h"
#include "glim_testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//내가 만든 func
void CglimtestDlg::Create_CShow_Image(CShow_Image* new_Image, UINT ID, CWnd* Window, int x, int y, int nWidth, int nHeight) {
	//new_Image = new CShow_Image;
	new_Image->Create(ID, Window);
	new_Image->ShowWindow(SW_SHOW);
	new_Image->MoveWindow(x, y, nWidth, nHeight);
}

void CglimtestDlg::Draw_Background(int r_color, int g_color, int b_color) {
	int nWidth = 1200;
	int nHeight = 840;
	int nBpp = 8;

	m_image.Create(nWidth, nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[PIXEL_SIZE];
		for (int i = 0; i < PIXEL_SIZE;i++) {
			rgb[i].rgbRed = r_color;
			rgb[i].rgbGreen = g_color;
			rgb[i].rgbBlue = b_color;
		}
		m_image.SetColorTable(0, PIXEL_SIZE, rgb);
	}
	
}

void CglimtestDlg::test_num() {
	UpdateData(true);
	m_nX1_Pos = 100;
	UpdateData(false);
}
////////////////////////////////////////////////////////////
// 
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CglimtestDlg 대화 상자



CglimtestDlg::CglimtestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_TEST_DIALOG, pParent)
	, m_nX1_Pos(NULL)
	, m_nY1_Pos(NULL)
	, m_nX2_Pos(0)
	, m_nY2_Pos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CglimtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_X1_POS, m_nX1_Pos);
	DDX_Text(pDX, IDC_Y1_POS, m_nY1_Pos);
	DDX_Text(pDX, IDC_X2_POS, m_nX2_Pos);
	DDX_Text(pDX, IDC_Y2_POS, m_nY2_Pos);
}

BEGIN_MESSAGE_MAP(CglimtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()

	ON_STN_CLICKED(IDC_Y1, &CglimtestDlg::OnStnClickedY1)
	ON_STN_CLICKED(IDC_X1, &CglimtestDlg::OnStnClickedX1)
	ON_STN_CLICKED(IDC_X2, &CglimtestDlg::OnStnClickedX2)
	ON_STN_CLICKED(IDC_Y2, &CglimtestDlg::OnStnClickedY2)
	ON_EN_CHANGE(IDC_X1_POS, &CglimtestDlg::OnEnChangeX1Pos)
	ON_EN_CHANGE(IDC_Y1_POS, &CglimtestDlg::OnEnChangeY1Pos)
	ON_EN_CHANGE(IDC_X2_POS, &CglimtestDlg::OnEnChangeX2Pos)
	ON_EN_CHANGE(IDC_Y2_POS, &CglimtestDlg::OnEnChangeY2Pos)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CglimtestDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CglimtestDlg::OnBnClickedBtnDraw)
END_MESSAGE_MAP()


// CglimtestDlg 메시지 처리기

BOOL CglimtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	m_pShow_Image = new CShow_Image;
	// 
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*m_pShow_Image = new CShow_Image;
	m_pShow_Image->Create(IDD_CShow_Image,this);
	m_pShow_Image->ShowWindow(SW_SHOW);
	m_pShow_Image->MoveWindow(10, 10, 810, 810);*/

	Draw_Background(0xFF, 0xFF, 0xFF);

	if (m_pShow_Image)
		Create_CShow_Image(m_pShow_Image, IDD_CShow_Image, this, 10, 10, 810, 810);
	else
		std::cout << "m_pShow_Image create 실패" << std::endl;


	if (m_pShow_Image)
		m_pShow_Image->Select_Color(0x00, 0x00, 0xFF);
	else
		std::cout << "Select_Color 실패" << std::endl;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CglimtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CglimtestDlg::OnPaint()
{
	std::cout << "OnPaint 들어옴" << std::endl;
	static int num = 0;
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		m_image.Draw(dc, 0, 0);
		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//Draw_Background 함수 사용시 필요함
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		CDialogEx::OnPaint();
		if (m_image) m_image.Draw(dc, 0, 0); 
	}

	
	/*CClientDC dc(this);
	if (m_image) m_image.Draw(dc, 0, 0);*/
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CglimtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CglimtestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//항상 delete 해야됨
	if (m_pShow_Image) {
		std::cout << "delete 들어옴" << std::endl;
		delete m_pShow_Image;
	}
		
	
}

HBRUSH CglimtestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (pWnd->GetDlgCtrlID()){
		case IDC_X1:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
		case IDC_Y1:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
		case IDC_X2:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
		case IDC_Y2:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CglimtestDlg::OnStnClickedX1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CglimtestDlg::OnStnClickedY1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CglimtestDlg::OnStnClickedX2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CglimtestDlg::OnStnClickedY2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CglimtestDlg::OnEnChangeX1Pos()
{
	UpdateData(true);

	std::cout << "nX_count 들어옴" << std::endl;

	static int nX_count = 0;
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nX_count : " << nX_count << std::endl;
	std::cout << "m_nX1_Pos : " << m_nX1_Pos << std::endl;

	++nX_count;
	UpdateData(false);

	//if (0 <= m_nX1_Pos && m_nX1_Pos < 800)


}


void CglimtestDlg::OnEnChangeY1Pos()
{
	UpdateData(true);
	std::cout << "nY_count 들어옴" << std::endl;

	static int nY_count = 0;
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nY_count : " << nY_count << std::endl;
	std::cout << "m_nY1_Pos : " << m_nY1_Pos << std::endl;

	++nY_count;
	UpdateData(false);

}

void CglimtestDlg::OnEnChangeX2Pos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CglimtestDlg::OnEnChangeY2Pos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CglimtestDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CglimtestDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
