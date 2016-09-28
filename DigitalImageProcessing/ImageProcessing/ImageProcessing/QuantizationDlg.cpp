// QuantizationDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "QuantizationDlg.h"
#include "afxdialogex.h"


// CQuantizationDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CQuantizationDlg, CDialogEx)

CQuantizationDlg::CQuantizationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuantizationDlg::IDD, pParent)
	, m_QuantBit(0)
{

}

CQuantizationDlg::~CQuantizationDlg()
{
}

void CQuantizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_QuantBit);
}


BEGIN_MESSAGE_MAP(CQuantizationDlg, CDialogEx)
END_MESSAGE_MAP()


// CQuantizationDlg 메시지 처리기입니다.
