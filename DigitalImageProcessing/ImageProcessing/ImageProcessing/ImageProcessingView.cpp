
// ImageProcessingView.cpp : CImageProcessingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

	BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
		// 표준 인쇄 명령입니다.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingView::OnDownSampling)
		ON_COMMAND(ID_QUANTIZATION, &CImageProcessingView::OnQuantization)
		ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingView::OnUpSampling)
	END_MESSAGE_MAP()

	// CImageProcessingView 생성/소멸

	CImageProcessingView::CImageProcessingView()
	{
		// TODO: 여기에 생성 코드를 추가합니다.

	}

	CImageProcessingView::~CImageProcessingView()
	{
	}

	BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CImageProcessingView 그리기

	void CImageProcessingView::OnDraw(CDC* pDC)
	{
		CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
		ASSERT_VALID(pDoc);
		// TODO: add draw code for native data here

		int i, j;
		unsigned char R, G, B;
		// 입력 영상 출력
		for(i = 0 ; i<pDoc->m_height ; i++){
			for(j = 0 ; j<pDoc->m_width ; j++){
				R = pDoc->m_InputImage[i*pDoc->m_width+j];
				G = B = R;
				pDC->SetPixel(j+5, i+5, RGB(R, G, B));
			}
		}

		// 축소된 영상 출력
		for(i = 0 ; i<pDoc->m_Re_height ; i++){
			for(j = 0 ; j<pDoc->m_Re_width ; j++){
				R = pDoc->m_OutputImage[i*pDoc->m_Re_width+j];
				G = B = R;
				pDC->SetPixel(j+pDoc->m_width+10, i+5, RGB(R, G, B));
			}
		}
	}


	// CImageProcessingView 인쇄

	BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// CImageProcessingView 진단

#ifdef _DEBUG
	void CImageProcessingView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CImageProcessingView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
		return (CImageProcessingDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CImageProcessingView 메시지 처리기


	void CImageProcessingView::OnDownSampling()
	{
		// TODO: Add your command handler code here
		CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
		ASSERT_VALID(pDoc);

		pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

		Invalidate(TRUE); // 화면 갱신

	}


	void CImageProcessingView::OnUpSampling()
	{
		CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
		ASSERT_VALID(pDoc);

		pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

		Invalidate(TRUE); // 화면 갱신

	}


	void CImageProcessingView::OnQuantization()
	{
		// TODO: Add your command handler code here
		CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
		ASSERT_VALID(pDoc);

		pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

		Invalidate(TRUE); // 화면 갱신

	}
