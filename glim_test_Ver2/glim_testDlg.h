
// glim_testDlg.h: 헤더 파일
//
#include "CShow_Image.h"
#include <iostream>
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

// 생성입니다.
public:
	CglimtestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	void Create_CShow_Image(CShow_Image* new_Image, UINT ID, CWnd* Window, int x, int y, int nWidth, int nHeight);
	void Draw_Background(int color);
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

};
