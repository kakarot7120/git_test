
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

// 생성입니다.
public:
	CglimtestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	void Create_CShow_Image(CShow_Image* new_Image, UINT ID, CWnd* Window, int x, int y, int nWidth, int nHeight);
	void Draw_Background(int r_color, int g_color, int b_color);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void Set_CString();
	void Create_Circle();
	BOOL ValidImage(int x, int y);

	int Select_Direction(int X_direction, int Y_direction);
	void Find_Circle_center(CImage& Image);

	int Common_Multiple(double nNUm1, double nNUm2);

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

	afx_msg void OnStnClickedX1();
	afx_msg void OnStnClickedY1();
	afx_msg void OnStnClickedX2();
	afx_msg void OnStnClickedY2();

	afx_msg void OnEnChangeX1Pos();
	afx_msg void OnEnChangeY1Pos();
	afx_msg void OnEnChangeX2Pos();
	afx_msg void OnEnChangeY2Pos();

	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnDraw();
	CString m_nExplanation;

	afx_msg void OnBnClickedBtnOpen();
	void OnOpenExplorer(); // 버튼 클릭 핸들러 선언
};
