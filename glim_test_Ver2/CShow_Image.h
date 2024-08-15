#pragma once
#include "afxdialogex.h"
#include <iostream>

//내가 만든 define
#define PIXEL_SIZE 256


// CShow_Image 대화 상자

class CShow_Image : public CDialogEx
{
	DECLARE_DYNAMIC(CShow_Image)

private:
	CWnd* m_pGlim;

	int nWidth;
	int nHeight;
	int nBpp;

public:
	CShow_Image(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CShow_Image();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CShow_Image };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void Select_Color(int color);

	CImage m_image;
};
