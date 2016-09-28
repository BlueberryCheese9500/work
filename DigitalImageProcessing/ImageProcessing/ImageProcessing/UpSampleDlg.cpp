// UpSampleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "UpSampleDlg.h"
#include "afxdialogex.h"


// CUpSampleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUpSampleDlg, CDialogEx)

CUpSampleDlg::CUpSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpSampleDlg::IDD, pParent)
	, m_UpSampleRate(0)
{

}

CUpSampleDlg::~CUpSampleDlg()
{
}

void CUpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UpSampleRate);
}


BEGIN_MESSAGE_MAP(CUpSampleDlg, CDialogEx)
END_MESSAGE_MAP()


// CUpSampleDlg 메시지 처리기입니다.
