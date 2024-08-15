
// glim_testDlg.h: 헤더 파일
//
#include "CShow_Image.h"
#include <iostream>
#include<cmath> 
#include <afx.h> 
#include<cstdlib>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma once

//내가 만든 define
#define PIXEL_SIZE 256

#define WIDTH 1080
#define HEIGHT 810
#define BPP 8


// CglimtestDlg 대화 상자
class CglimtestDlg : public CDialogEx
{

private:
	CShow_Image* m_pShow_Image;//선언만 한것(초기화 해야됨)

	CImage m_image;

	int nX1_count;
	int nY1_count;
	int nX2_count;
	int nY2_count;

	int nAction_check;
	int nDraw_check;

	int nXTemp_Pos;
	int nYTemp_Pos;

	int nRadius;
	int nCenterX;
	int nCenterY;
	int _nWidth;
	int _nHeight;
	int _nPitch;

	int nFindX;
	int nFindY;

	CString nStart_address;
	CString nEnd_address;

// 생성입니다.
public:
	CglimtestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	void Draw_Background(int r_color, int g_color, int b_color);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void Set_CString();
	void Create_Circle();
	BOOL ValidImage(int x, int y);

	int Select_Direction();
	void Find_Circle_center(CImage& Image);

	void Move_Plus_Plus_Save(int &nNum, CString& strTime);
	void Move_Plus_Minus_Save(int& nNum, CString& strTime);
	void Move_Minus_Plus_Save(int& nNum, CString& strTime);
	void Move_Minus_Minus_Save(int& nNum, CString& strTime);
	
	void show_Center_Pos();



// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_TEST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();

	int m_nX1_Pos;
	int m_nY1_Pos;
	int m_nX2_Pos;
	int m_nY2_Pos;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnEnChangeX1Pos();
	afx_msg void OnEnChangeY1Pos();
	afx_msg void OnEnChangeX2Pos();
	afx_msg void OnEnChangeY2Pos();

	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnDraw();
	CString m_nExplanation;

	afx_msg void OnBnClickedBtnOpen();
	void OnOpenExplorer(); // 버튼 클릭 핸들러 선언
	int m_nShow_X;
	int m_nShow_Y;
};
