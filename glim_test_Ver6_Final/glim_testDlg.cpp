
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
void CglimtestDlg::Draw_Background(int r_color, int g_color, int b_color) {
	std::cout << "Draw_Background 들어옴" << std::endl;

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

void CglimtestDlg::Create_Circle() {
	std::cout << "Create_Circle 들어옴" << std::endl;
	
	nCenterX = m_nX1_Pos;
	nCenterY = m_nY1_Pos ;

	_nWidth = m_pShow_Image->m_image.GetWidth();
	_nHeight = m_pShow_Image->m_image.GetHeight();
	_nPitch = m_pShow_Image->m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_pShow_Image->m_image.GetBits();

	memset(fm, 0x00, _nWidth * _nHeight);

	for (int j = m_nY1_Pos - nRadius; j < m_nY1_Pos + nRadius; j++) {
		for (int i = m_nX1_Pos - nRadius; i < m_nX1_Pos + nRadius; i++) {
			if (ValidImage(i, j))
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * _nPitch + i] = 0xFF;
		}
	}

	m_pShow_Image->Invalidate();
	AfxGetMainWnd()->UpdateWindow();
}

bool CglimtestDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius){
	//std::cout << "isInCircle 들어옴" << std::endl;

	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}
		return bRet;
}
BOOL CglimtestDlg::ValidImage(int x, int y) {
	//std::cout << "ValidImage 들어옴" << std::endl;

	int nWidth = m_pShow_Image->m_image.GetWidth();
	int nHeight = m_pShow_Image->m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

int CglimtestDlg::Select_Direction() {
	int direction = 0;

	nXTemp_Pos = m_nX2_Pos - m_nX1_Pos;
	nYTemp_Pos = m_nY2_Pos - m_nY1_Pos;

	if (0 < nXTemp_Pos && 0 < nYTemp_Pos)
		direction = 0;
	if (0 < nXTemp_Pos && 0 > nYTemp_Pos)
		direction = 1;
	if (0 > nXTemp_Pos && 0 < nYTemp_Pos)
		direction = 2;
	if (0 > nXTemp_Pos && 0 > nYTemp_Pos)
		direction = 3;

	return direction;
}

void CglimtestDlg::Set_CString() {
	std::cout << "Set_CString 들어옴" << std::endl;

	UpdateData(true);
	m_nExplanation = _T("설명서\n\n\n원을 이동 시키는 프로그램\n시작 좌표 (x1, y1) 입력, 범위 0 ~799 범위를 벗어나면 다시 입력\n Draw 버튼 입력 시 Action 버튼 입력 가능\n종료 좌표 (x2, y2) 입력, 범위 0 ~799 범위를 벗어나면 다시 입력\n Action 버튼 클릭 시 원 이동\nOpen 버튼 클릭시 탐색기 창 출력 후 원 이미지 선택\n이미지 선택 시 원의 중심 x로 표시(좌표도 출력)");
	
	UpdateData(false);
}

//구글에서 가져옴
void CglimtestDlg::OnOpenExplorer()
{
	// 파일 탐색기 열기
	CFileDialog dlg(TRUE, _T("*.jpg"), _T(""), OFN_FILEMUSTEXIST, _T("Image Files (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp|All Files (*.*)|*.*||"), this);
	dlg.m_ofn.lpstrInitialDir = _T("C:\\image\\"); // 초기 경로 설정

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName(); // 선택된 파일 경로

		// 이미지를 불러오고 대화 상자에 그리기
		CImage m_Image;
		if (m_Image.Load(filePath) == S_OK)
		{
			Find_Circle_center(m_Image);
			// 이미지가 성공적으로 로드되었을 때, 대화 상자의 화면에 그리기
			CClientDC dc(this);
			m_Image.Draw(dc.m_hDC, 10, 10);
		}
		else
		{
			AfxMessageBox(_T("Failed to load image."));
		}
	}
}

void CglimtestDlg::Find_Circle_center(CImage& Image) {

	unsigned char* fm = (unsigned char*)Image.GetBits();
	int nWidth = Image.GetWidth();
	int nHeight = Image.GetHeight();
	int nPitch = Image.GetPitch();

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	int nMax[2] = { 0 };
	int nMin[2] = { 900,900 };

	for (int j =0; j < nHeight; j++) {
		for (int i = 0; i < nHeight; i++) {
			if (fm[j * nPitch + i] == 0xFF) {
				nSumX += i;
				nSumY += j;
				nCount++;
				if (nMax[0] < i) nMax[0] = i;
				if (nMax[1] < j) nMax[1] = j;
				if (nMin[0] > i) nMin[0] = i;
				if (nMin[1] > j) nMin[1] = j;

			}
		}
	}
	if ((nMax[0] - nMin[0])==(nMax[1] - nMin[1]))
		nRadius = nMax[0] - nMin[0];

	nFindX = nSumX / nCount;
	nFindY = nSumY / nCount;

	for (int j = 0; j < nRadius /4; j++) {
		fm[(nFindY + j) * nPitch + (nFindX + j)] = 0x00;
	}
	for (int j = 0; j < nRadius / 4; j++) {
		fm[(nFindY + j) * nPitch + (nFindX - j)] = 0x00;
	}
	for (int j = 0; j < nRadius / 4; j++) {
		fm[(nFindY - j) * nPitch + (nFindX + j)] = 0x00;
	}
	for (int j = 0; j < nRadius / 4; j++) {
		fm[(nFindY - j) * nPitch + (nFindX - j)] = 0x00;
	}

	show_Center_Pos();

	AfxGetMainWnd()->UpdateWindow();
}

void CglimtestDlg::show_Center_Pos() {
	UpdateData(true);
	m_nShow_X = nFindX;
	m_nShow_Y = nFindY;
	UpdateData(false);
}



void CglimtestDlg::Move_Plus_Plus_Save(int& nNum, CString& strTime) {

	CString n_SNumber;
	CString nAddress;

	for (int x = 0; x < nXTemp_Pos; x++) {
		m_nX1_Pos++;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
	for (int y = 0; y < nYTemp_Pos; y++) {
		m_nY1_Pos++;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
	

}

void CglimtestDlg::Move_Plus_Minus_Save(int& nNum, CString& strTime) {

	CString n_SNumber;
	CString nAddress;

	for (int x = 0; x < nXTemp_Pos; x++) {
		m_nX1_Pos++;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
	for (int y = 0; y < std::abs(nYTemp_Pos); y++) {
		m_nY1_Pos--;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		Sleep(100);
	}
}


void CglimtestDlg::Move_Minus_Plus_Save(int& nNum, CString& strTime) {

	CString n_SNumber;
	CString nAddress;

	for (int x = 0; x < std::abs(nXTemp_Pos); x++) {
		m_nX1_Pos--;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
	for (int y = 0; y < nYTemp_Pos; y++) {
		m_nY1_Pos++;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
}

void CglimtestDlg::Move_Minus_Minus_Save(int& nNum, CString& strTime) {

	CString n_SNumber;
	CString nAddress;

	for (int x = 0; x < std::abs(nXTemp_Pos); x++) {
		m_nX1_Pos--;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
	for (int y = 0; y < std::abs(nYTemp_Pos); y++) {
		m_nY1_Pos--;
		Create_Circle();
		n_SNumber.Format(_T("%d"), nNum);
		nNum++;
		nAddress = nStart_address + strTime + n_SNumber + nEnd_address;
		m_pShow_Image->m_image.Save(nAddress);
		Sleep(100);
	}
}






////////////////////////////////////////////////////////////

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
	, m_nX1_Pos(0)
	, m_nY1_Pos(0)
	, m_nX2_Pos(0)
	, m_nY2_Pos(0)
	, nX1_count(-1)
	, nY1_count(-1)
	, nX2_count(-1)
	, nY2_count(-1)
	, m_nExplanation(_T(""))
	, nStart_address(_T("C:\\image\\"))
	, nEnd_address( _T(".bmp"))
	, m_nShow_X(0)
	, m_nShow_Y(0)
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
	DDX_Text(pDX, IDC_STATIC_TEST, m_nExplanation);

	DDX_Text(pDX, IDC_SHOW_X, m_nShow_X);
	DDX_Text(pDX, IDC_SHOW_Y, m_nShow_Y);

}

BEGIN_MESSAGE_MAP(CglimtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_X1_POS, &CglimtestDlg::OnEnChangeX1Pos)
	ON_EN_CHANGE(IDC_Y1_POS, &CglimtestDlg::OnEnChangeY1Pos)
	ON_EN_CHANGE(IDC_X2_POS, &CglimtestDlg::OnEnChangeX2Pos)
	ON_EN_CHANGE(IDC_Y2_POS, &CglimtestDlg::OnEnChangeY2Pos)

	ON_BN_CLICKED(IDC_BTN_ACTION, &CglimtestDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CglimtestDlg::OnBnClickedBtnDraw)

	ON_BN_CLICKED(IDC_BTN_OPEN, &CglimtestDlg::OnBnClickedBtnOpen)
	//ON_COMMAND(IDC_BTN_OPEN, &CglimtestDlg::OnOpenExplorer)

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

	Draw_Background(0xFF, 0xFF, 0xFF);

	m_pShow_Image->Create(IDD_CShow_Image, this);
	m_pShow_Image->ShowWindow(SW_SHOW);
	m_pShow_Image->MoveWindow(10, 10, 810, 810);
	Set_CString();

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
		case IDC_STATIC_TEST:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
		case IDC_CENTER_X:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
		case IDC_CENTER_Y:
			pDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
			pDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			break;
	

	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CglimtestDlg::OnEnChangeX1Pos()
{
	std::cout << "nX1_count 들어옴" << std::endl;
	++nX1_count;
	UpdateData(true);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nX_count : " << nX1_count << std::endl;
	std::cout << "m_nX1_Pos : " << m_nX1_Pos << std::endl;

	UpdateData(false);
}


void CglimtestDlg::OnEnChangeY1Pos()
{
	std::cout << "nY1_count 들어옴" << std::endl;
	++nY1_count;
	UpdateData(true);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nY_count : " << nY1_count << std::endl;
	std::cout << "m_nY1_Pos : " << m_nY1_Pos << std::endl;

	UpdateData(false);
}

void CglimtestDlg::OnEnChangeX2Pos()
{
	std::cout << "nX2_count 들어옴" << std::endl;
	++nX2_count;
	UpdateData(true);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nX2_count : " << nX2_count << std::endl;
	std::cout << "m_nX2_Pos : " << m_nX2_Pos << std::endl;

	UpdateData(false);
}


void CglimtestDlg::OnEnChangeY2Pos()
{
	std::cout << "nY2_count 들어옴" << std::endl;
	++nY2_count;
	UpdateData(true);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "nY2_count : " << nY2_count << std::endl;
	std::cout << "m_nY2_Pos : " << m_nY2_Pos << std::endl;

	UpdateData(false);
}


void CglimtestDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	nAction_check = 1;

	if (!nDraw_check) {
		AfxMessageBox(_T("Draw버튼 클릭 후 다시 눌러주세요"));
		nAction_check = 0;
	}
	else if (nX2_count < 0 || nY2_count < 0) {
		AfxMessageBox(_T("x, y 좌표 입력 해주세요."));
		nAction_check = 0;
	}

	else if (!(0 <= m_nX2_Pos && m_nX2_Pos < 800)) {
		AfxMessageBox(_T("x 좌표 범위 오류"));
		nAction_check = 0;
	}

	else if (!(0 <= m_nY2_Pos && m_nY2_Pos < 800)) {
		AfxMessageBox(_T("y 좌표 범위 오류"));
		nAction_check = 0;
	}

	if (nAction_check && nDraw_check) {
		nDraw_check = 0;

		nX2_count = 0;
		nY2_count = 0;

		int nNum = 0;
		CString n_SNumber;
		CString nAddress;
		CTime currentTime = CTime::GetCurrentTime();// 현재 시간 가져오기
		CString strTime = currentTime.Format(_T("%Y-%m-%d_%H-%M-%S_"));	// 시간 출력

		int nDirection_value = Select_Direction();
		switch (nDirection_value) {
		case 0:
			Move_Plus_Plus_Save(nNum, strTime);
			break;
		case 1:
			Move_Plus_Minus_Save(nNum, strTime);
			break;
		case 2:
			Move_Minus_Plus_Save(nNum, strTime);
			break;
		case 3:
			Move_Minus_Minus_Save(nNum, strTime);
			break;
		}
		
	}
	
}

void CglimtestDlg::OnBnClickedBtnDraw()
{
	nDraw_check = 1;

	if (nX1_count < 0 || nY1_count < 0) {
		AfxMessageBox(_T("x, y 좌표 입력 해주세요."));
		nDraw_check = 0;
	}

	else if (!(0 <= m_nX1_Pos && m_nX1_Pos < 800)) {
		AfxMessageBox(_T("x 좌표 범위 오류"));
		nDraw_check = 0;
	}

	else if (!(0 <= m_nY1_Pos && m_nY1_Pos < 800)) {
		AfxMessageBox(_T("y 좌표 범위 오류"));
		nDraw_check = 0;
	}

	if (nDraw_check) {
		nX1_count = 0;
		nY1_count = 0;

		nRadius = rand() % 50 + 1;
		Create_Circle();
	}
	
}

void CglimtestDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOpenExplorer();
}