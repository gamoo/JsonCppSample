
// CWndSampleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CWndSample.h"
#include "CWndSampleDlg.h"
#include "afxdialogex.h"

#include "json/json.h"

#pragma comment(lib, "lib_json")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCWndSampleDlg 대화 상자



CCWndSampleDlg::CCWndSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCWndSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCWndSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCWndSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCWndSampleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCWndSampleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCWndSampleDlg 메시지 처리기

BOOL CCWndSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCWndSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCWndSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCWndSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// write
bool WriteToFile(const char* filename, const char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "wb");

	if (fp == nullptr)
	{
		return false;
	}

	size_t fileSize = fwrite(buffer, 1, len, fp);

	fclose(fp);

	return true;
}

// read
bool ReadFromFile(const char* filename, char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "rb");

	if (fp == nullptr)
	{
		return false;
	}

	size_t fileSize = fread(buffer, 1, len, fp);

	fclose(fp);

	return true;
}


#include <memory> // unique_ptr
#include <iostream>

void CCWndSampleDlg::OnBnClickedButton1()
{
	// TODO: Task List

	::AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);

	FILE* pCout;
	freopen_s(&pCout, "CONOUT$", "w", stdout);

	Json::Value root;
	Json::Value encoding;
	root["encoding"] = "UTF-8";

	Json::Value plugins;
	plugins.append("python");
	plugins.append("C++");
	plugins.append("ruby");
	root["plugins"] = plugins;
	Json::Value indent;
	indent["length"] = 3;
	indent["use_space"] = true;
	root["indent"] = indent;

	Json::StreamWriterBuilder builder;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(root, &std::cout);

	std::cout << std::endl;

	

	std::string outputString = Json::writeString(builder, root);

	WriteToFile("test.json", outputString.c_str(), outputString.length());

	
	// READ

	std::cout << std::endl << "READ" << std::endl;

	const int len = 1024;
	char readBuffer[len] = { 0, };

	ReadFromFile("test.json", readBuffer, len);

	std::string input = readBuffer;
	Json::Value rootRead;

	Json::CharReaderBuilder readerBuilder;
	builder["collectComments"] = false;

	std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());

	JSONCPP_STRING errs;
	bool parsingSuccessful = reader->parse(input.data(), input.data() + input.length(), &rootRead, &errs);

	if (parsingSuccessful == false) {

		return;
	}

	std::string encodingRead = rootRead.get("encoding", "").asString();
	std::cout << encodingRead << std::endl;

	const Json::Value pluginsRead = rootRead["plugins"];

	for (int n = 0; n < pluginsRead.size(); ++n) {

		std::cout << pluginsRead[n].asString() << std::endl;
	}

	std::cout << rootRead["indent"].get("length", 0).asInt() << std::endl;
	std::cout << rootRead["indent"]["use_space"].asBool() << std::endl;

	fclose(pCout);
	::FreeConsole();

}


void CCWndSampleDlg::OnBnClickedButton2()
{
	Json::Value root;
	Json::Value action;

	action["state"] = "SP_2WAY_TRANSFER_COMPLETE";

	Json::Value params;
	Json::Value items;
	Json::Value items1;
	Json::Value items2;

	items1["item_name"] = "contacts";
	items1["item_state"] = "success";
	items1["read_count"] = 10;
	items1["write_count"] = 10;
	
	items2["item_name"] = "sms";
	items2["item_state"] = "success";
	items2["read_count"] = 10;
	items2["write_count"] = 10;

	items.append(items1);
	items.append(items2);

	params["items"] = items;
	
	action["params"] = params;
	root["uiAction"] = action;

	Json::StreamWriterBuilder builder;

	std::string outputString = Json::writeString(builder, root);

	::OutputDebugStringA(outputString.c_str());

	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(root, &std::cout);

	std::cout << std::endl;
}
