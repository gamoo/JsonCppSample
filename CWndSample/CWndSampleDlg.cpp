
// CWndSampleDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CCWndSampleDlg ��ȭ ����



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


// CCWndSampleDlg �޽��� ó����

BOOL CCWndSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCWndSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
