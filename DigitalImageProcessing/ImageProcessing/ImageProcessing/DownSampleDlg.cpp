// DownSampleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DownSampleDlg.h"
#include "afxdialogex.h"


// CDownSampleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDownSampleDlg, CDialog)

CDownSampleDlg::CDownSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownSampleDlg::IDD, pParent)
	, m_DownSampleRate(0)
{

}

CDownSampleDlg::~CDownSampleDlg()
{
}

void CDownSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DownSampleRate);
	DDV_MinMaxInt(pDX, m_DownSampleRate, 1, 32);
}


BEGIN_MESSAGE_MAP(CDownSampleDlg, CDialog)
END_MESSAGE_MAP()


// CDownSampleDlg 메시지 처리기입니다.
