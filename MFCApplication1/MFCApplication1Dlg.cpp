
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(BTN_CONVERT, &CMFCApplication1Dlg::OnBnClickedConvert)
	ON_BN_CLICKED(BTN_COPY, &CMFCApplication1Dlg::OnBnClickedCopy)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnBnClickedConvert()
{
	// 转换
	CString strEdit1;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strEdit1);

	if (strEdit1 == L"")
	{
		AfxMessageBox(L"请在左侧栏输入VS(.cpp)中Halcon程序_\n_Version>Halcon10");
		return;
	}

	CString strEditIn = strEdit1;

	//获取编辑框内容
	UpdateData(TRUE);
	CString strTemp;//用于分割的临时字符串
	//将编辑框的内容根据换行符分割开
	CStringArray editArr;
	int nPos = strEdit1.Find(_T('\n'));
	strTemp = _T("");
	while (0 <= nPos)
	{
		strTemp = strEdit1.Left(nPos);
		if (!strTemp.IsEmpty())
			editArr.Add(strTemp);
		strEdit1 = strEdit1.Right(strEdit1.GetLength() - nPos - 1);
		nPos = strEdit1.Find(_T('\n'));
	}
	if (!strEdit1.IsEmpty())
	{
		editArr.Add(strEdit1);
	}//多行字符串分割完毕

	//此时editArr里面保存的就是每一行的内容，可以用editArr.GetAt(i)进行访问
	for (int i = 0; i < editArr.GetCount(); i++)
	{
		CString aa = editArr.GetAt(i);
		//得到的一行行文本 /r记住，不带/n

		CString strScreen = _T("");
		int nFindn = 0;
		nFindn = aa.Find(L"(");
		strScreen = aa.Left(nFindn);

		CString replace = snakeString(strScreen);
		// 替换  把MeanImage替换为mean_image

		// 双引号变单引号
		int index = strEditIn.Find(strScreen);
		if (index == -1)
			continue;
		else
		{
			strEditIn.Replace(strScreen, replace);//前面的参数是要替换的字符串，后面的参数是你指定的新字符串
		}
	}

	strEditIn.Replace(L"&", L"");//前面的参数是要替换的字符串，后面的参数是你指定的新字符串
	strEditIn.Replace(L";", L"");//前面的参数是要替换的字符串，后面的参数是你指定的新字符串
	strEditIn.Replace(L"\"", L"\'");//前面的参数是要替换的字符串，后面的参数是你指定的新字符串
	strEditIn.Replace(L"\[0\]\.D\(\)", L"");//前面的参数是要替换的字符串，后面的参数是你指定的新字符串
	strEditIn.Replace(L"\/\/", L"*");

	strEditIn.Replace(L"\.D\(\)", L"");

	GetDlgItem(IDC_EDIT2)->SetWindowText(strEditIn);
}


// snake string, XxYy to xx_yy , XxYY to xx_yy
CString snakeString(CString string_In)
{
	CString data;
	bool j = false;
	int num = string_In.GetLength();
	for( int i = 0; i < num; i++ )
	{
		wchar_t d = string_In.GetAt(i);
		if( i > 0 && d >= 'A' && d <= 'Z' && j)
		{
			data.Append(L"_");
		}
		if( d != '_' && d!='\t')
		{
			j = true;
		}
		data.Append((CString)d);
	}
	return data.MakeLower();
}

void CMFCApplication1Dlg::OnBnClickedCopy()
{
	CString strEdit2;
	GetDlgItem(IDC_EDIT2)->GetWindowText(strEdit2);

	//put your text in source
	if (OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();

		DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strEdit2.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
		char *src;
		src = new char[dwNum];
		if (!src)
		delete[]src;
		WideCharToMultiByte(CP_OEMCP, NULL, strEdit2.GetBuffer(0), -1, src, dwNum, NULL, FALSE);

		int a = strlen(src) + 1;
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, a);
		buffer = (char*)GlobalLock(clipbuffer);

		strcpy_s(buffer, a, src);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();

		delete src;
		src = NULL;
	}
}
