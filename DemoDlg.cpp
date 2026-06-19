
// DemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"

extern CDatabase my_db;

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
public:
	
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


// CMyDemoDlg 对话框



CMyDemoDlg::CMyDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2_SHOW, my_list);
	DDX_Control(pDX, IDC_EDIT_SNO, m_edtsno);
	DDX_Control(pDX, IDC_EDIT_SNAME, m_edtsname);
	DDX_Control(pDX, IDC_EDIT_SSEX, m_edtssex);
	DDX_Control(pDX, IDC_EDIT_SAGE, m_edtsage);
	DDX_Control(pDX, IDC_EDIT_SDEPT, m_edtsdept);
	DDX_Control(pDX, IDC_CHECK_MATH, m_chkMath);
	DDX_Control(pDX, IDC_CHECK_ENGLISH, m_chkEnglish);
	DDX_Control(pDX, IDC_CHECK_PHYSICS, m_chkPhysics);
	DDX_Control(pDX, IDC_CHECK_CHEMISTRY, m_chkChemistry);
	DDX_Control(pDX, IDC_CHECK_BIOLOGY, m_chkBiology);
}

// 在 BEGIN_MESSAGE_MAP 和 END_MESSAGE_MAP 之间添加消息映射项，不能留空
BEGIN_MESSAGE_MAP(CMyDemoDlg, CDialogEx)
	// 例如：
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_NOTIFY(NM_CLICK, IDC_LIST2_SHOW, &CMyDemoDlg::OnNMClickList2Show)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMyDemoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CMyDemoDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CMyDemoDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMyDemoDlg::OnBnClickedButtonDelete)


	ON_BN_CLICKED(IDC_BUTTON_SELECT_COURSE, &CMyDemoDlg::OnBnClickedButtonSelectCourse)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMyDemoDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CMyDemoDlg 消息处理程序

BOOL CMyDemoDlg::OnInitDialog()
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
	
	//list控件初始化 
	my_list.InsertColumn(0, _T("学号"), LVCFMT_LEFT, 70);

	my_list.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 70);

	my_list.InsertColumn(2, _T("性别"), LVCFMT_LEFT, 70);

	my_list.InsertColumn(3, _T("年龄"), LVCFMT_LEFT, 70);

	my_list.InsertColumn(4, _T("所在系"), LVCFMT_LEFT, 70);

	my_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//选择节点的时候选中整行
	ShowData();//显示表格数据 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDemoDlg::OnPaint()
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
HCURSOR CMyDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyDemoDlg::ShowData()
{
	my_list.DeleteAllItems();//清空原有数据  


	CRecordset my_set(&my_db);//申明CRecordset类的对象，用于调取表格数据   


	if (my_set.Open(AFX_DB_USE_DEFAULT_TYPE, _T("select * from student")))//获取数据

	{


		//AfxMessageBox(_T("读取数据集成功"));  

	}

	else

	{


		AfxMessageBox(_T("读取数据集失败！请检查连接是否异常！"));


		return;

	}


	if (my_set.IsBOF())//判断数据集是否为空 

	{


		AfxMessageBox(_T("该表格数据集为空"));


		return;

	}



	int i = 0;//表示记录的行号，注意从第0行开始往list控件插入数据 


	//5个字符串变量，用于保存一条记录的各个属性 

	CString str_sno = _T("");

	CString str_sname = _T("");

	CString str_ssex = _T("");

	CString str_sage = _T("");

	CString str_sdept = _T("");


	while (!my_set.IsEOF()) {//判断当前是否有数据可供读取  





		my_set.GetFieldValue((short)0, str_sno);//取第1个属性 


		my_list.InsertItem(i, str_sno);



		my_set.GetFieldValue((short)1, str_sname);//取第2个属性 


		my_list.SetItemText(i, 1, str_sname);



		my_set.GetFieldValue((short)2, str_ssex);//取第3个属性 


		my_list.SetItemText(i, 2, str_ssex);





		my_set.GetFieldValue((short)3, str_sage);//取第4个属性 


		my_list.SetItemText(i, 3, str_sage);



		my_set.GetFieldValue((short)4, str_sdept);//取第5个属性 


		my_list.SetItemText(i, 4, str_sdept);



		my_set.MoveNext();//数据指针下移一行 


		i++;


	}


	//释放当前资源 

	my_set.Close(); // TODO: 在此处添加实现代码.
}



void CMyDemoDlg::OnNMClickList2Show(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString strsno, strsname, strssex, strsage, strsdept;//用于保存从list控件上获取的值 

	if (pNMItemActivate->iItem != -1)//pNMItemActivate->iItem为鼠标焦点处对应的行号 

	{


		strsno = my_list.GetItemText(pNMItemActivate->iItem, 0);


		m_edtsno.SetWindowText(strsno);



		strsname = my_list.GetItemText(pNMItemActivate->iItem, 1);


		m_edtsname.SetWindowText(strsname);



		strssex = my_list.GetItemText(pNMItemActivate->iItem, 2);


		m_edtssex.SetWindowText(strssex);



		strsage = my_list.GetItemText(pNMItemActivate->iItem, 3);


		m_edtsage.SetWindowText(strsage);



		strsdept = my_list.GetItemText(pNMItemActivate->iItem, 4);


		m_edtsdept.SetWindowText(strsdept);

		m_strOriginalSno = strsno;   // 保存原始学号，供修改时使用

		UpdateData(FALSE);//刷新界面将底层代码的数据传递给上层的界面 

	} // TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CMyDemoDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//刷新界面，把数据传递给底层代码 


	CString strsno, strsname, strssex, strsage, strsdept;//用于保存从edit控件上获取的值 


	//从界面上的edit控件获取用户输入的值 
	m_edtsno.GetWindowText(strsno);

	m_edtsname.GetWindowText(strsname);

	m_edtssex.GetWindowText(strssex);

	m_edtsage.GetWindowText(strsage);

	m_edtsdept.GetWindowText(strsdept);


	if (strsno == _T(""))

	{


		AfxMessageBox(_T("学号为主码，取值不能为空！"));


		return;//等待用户重新输入 

	}

	else

	{


		if (strsname == _T(""))



			strsname = _T("NULL");


		else



			strsname = _T("'") + strsname + _T("'");



		if (!strssex.CompareNoCase(_T("男")) || !strssex.CompareNoCase(_T("女")))


		{



			strssex = _T("'") + strssex + _T("'");


		}


		else {



			AfxMessageBox(_T("性别只能输入“男”或“女”！"));



			return; return;//等待用户重新输入  





		}






		if (strsage == _T(""))



			strsage = _T("NULL");



		if (strsdept == _T(""))



			strsdept = _T("NULL");


		else



			strsdept = _T("'") + strsdept + _T("'");



		CString mstrsql;


		mstrsql.Format(_T("insert into student values('%s',%s,%s,%s,%s)"), strsno, strsname, strssex,
			strsage, strsdept);


		//AfxMessageBox(mstrsql);//测试生成的sql语言，如果添加数据失败，可打开这个语句查看SQL代码是否符合语法





			try


		{



			my_db.ExecuteSQL(mstrsql);


		}


		catch (CDBException* pe)


		{



			//如果有异常发生，弹出错误消息框，帮助纠正bug 



			pe->ReportError();



			pe->Delete();


		}



		ShowData();//加载数据 
	}
}


void CMyDemoDlg::OnBnClickedButtonClose()
{
	if (my_db.IsOpen())//判断是否处于数据库连接状态 

	{


		my_db.Close();//如果当前处于连接状态，从数据源断开连接，释放系统资源 

	}
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}

void CMyDemoDlg::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	// Demo 修改按钮功能实现

	// 1. 从编辑框中获取用户修改后的数据
	CString strSno, strSname, strSsex, strSage, strSdept;
m_edtsno.GetWindowText(strSno);

	m_edtsname.GetWindowText(strSname);

	m_edtssex.GetWindowText(strSsex);

	m_edtsage.GetWindowText(strSage);

	m_edtsdept.GetWindowText(strSdept);

	// 2. 数据校验：学号不能为空
	if (strSno.IsEmpty())
	{
		AfxMessageBox(_T("学号不能为空！"));
		return;
	}

	// 3. 检查是否有选中的行（原始学号需要提前保存，见下文说明）
	//    这里假设你有一个成员变量 CString m_strOriginalSno，用于保存点击List Control时选中的原始学号
	if (m_strOriginalSno.IsEmpty())
	{
		AfxMessageBox(_T("请先在列表中选择要修改的行！"));
		return;
	}

	// 4. 构造 UPDATE SQL 语句
	//    注意：年龄字段 sage 是数值类型，不需要加单引号；其他字符串字段需要加单引号。
	//    如果字段内容可能包含单引号，需要做转义处理（将单引号替换为两个单引号），这里为了简洁暂不考虑。
	CString strSQL;
	strSQL.Format(_T("UPDATE student SET sno='%s', sname='%s', ssex='%s', sage=%s, sdept='%s' WHERE sno='%s'"),
		strSno, strSname, strSsex, strSage, strSdept, m_strOriginalSno);


	// 5. 执行 SQL 更新
	try
	{
		my_db.ExecuteSQL(strSQL);   // 注意：my_db 是全局 CDatabase 对象
		AfxMessageBox(_T("修改成功！"));

		// 6. 刷新 List Control 显示最新数据
		ShowData();   // 这个函数是你之前写的，用于从数据库加载数据并显示到 m_list 中

		// 7. 清空原始学号记录，避免重复修改时误用
		m_strOriginalSno.Empty();

		// 8. 可选：清空编辑框内容
		m_edtsno.SetWindowText(_T(""));
		m_edtsname.SetWindowText(_T(""));
		m_edtssex.SetWindowText(_T(""));
		m_edtsage.SetWindowText(_T(""));
		m_edtsdept.SetWindowText(_T(""));
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}
}

void CMyDemoDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	// Demo 删除按钮功能实现

	// 1. 获取当前选中的行号（需要保存选中的学号，类似于修改功能）
	//    我们已有一个成员变量 m_strOriginalSno，在点击列表行时保存了原始学号
	if (m_strOriginalSno.IsEmpty())
	{
		AfxMessageBox(_T("请先在列表中选择要删除的行！"));
		return;
	}

	// 2. 弹出确认对话框，防止误删
	CString strMsg;
	strMsg.Format(_T("确定要删除学号为 %s 的学生记录吗？\n删除后将无法恢复！"), m_strOriginalSno);
	if (AfxMessageBox(strMsg, MB_YESNO | MB_ICONWARNING) != IDYES)
	{
		return;  // 用户选择“否”，取消删除
	}

	// 3. 构造 DELETE SQL 语句
	CString strSQL;
	strSQL.Format(_T("DELETE FROM student WHERE sno='%s'"), m_strOriginalSno);

	// 可选：输出 SQL 用于调试
	// AfxMessageBox(strSQL);

	// 4. 执行删除
	try
	{
		my_db.ExecuteSQL(strSQL);
		AfxMessageBox(_T("删除成功！"));

		// 5. 刷新列表显示
		ShowData();

		// 6. 清空编辑框和保存的原始学号
		m_edtsno.SetWindowText(_T(""));
		m_edtsname.SetWindowText(_T(""));
		m_edtssex.SetWindowText(_T(""));
		m_edtsage.SetWindowText(_T(""));
		m_edtsdept.SetWindowText(_T(""));
		m_strOriginalSno.Empty();
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}
}




void CMyDemoDlg::OnBnClickedButtonSelectCourse()
{
	// TODO: 在此添加控件通知处理程序代码
	 // Demo 选课按钮功能实现

	// 1. 获取当前选中的学生学号
	// 方法一：使用之前保存的 m_strOriginalSno（前提是用户最近点击过List Control）
	// 方法二：直接从List Control获取当前选中行的学号（更稳妥）
	CString strSno;

	// 获取List Control中当前选中的行（可能有多个选中，我们取第一个）
	POSITION pos = my_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("请先选中一个学生！"));
		return;
	}
	int nItem = my_list.GetNextSelectedItem(pos);
	strSno = my_list.GetItemText(nItem, 0); // 假设学号在第0列

	if (strSno.IsEmpty())
	{
		AfxMessageBox(_T("获取学号失败！"));
		return;
	}

	// 2. 定义课程ID与CheckBox的映射关系
	//    假设课程ID分别为 1,2,3,4,5 对应 MATH,ENGLISH,PHYSICS,CHEMISTRY,BIOLOGY
	struct CourseInfo {
		int courseId;
		CButton* pCheckBox;
		CString courseName;
	};

	CourseInfo courses[] = {
		{1, &m_chkMath, _T("MATH")},
		{2, &m_chkEnglish, _T("ENGLISH")},
		{3, &m_chkPhysics, _T("PHYSICS")},
		{4, &m_chkChemistry, _T("CHEMISTRY")},
		{5, &m_chkBiology, _T("BIOLOGY")}
	};

	// 3. 遍历所有课程，如果勾选则插入SC表
	int nInsertCount = 0;
	CString strErrors;

	for (int i = 0; i < 5; i++)
	{
		if (courses[i].pCheckBox->GetCheck() == BST_CHECKED)
		{
			// 检查该学生是否已经选了这门课（避免重复插入主键冲突）
			CString strCheckSQL;
			strCheckSQL.Format(_T("SELECT * FROM sc WHERE sno='%s' AND cno=%d"), strSno, courses[i].courseId);
			CRecordset rsCheck(&my_db);
			bool bAlreadyExists = false;
			if (rsCheck.Open(AFX_DB_USE_DEFAULT_TYPE, strCheckSQL))
			{
				if (!rsCheck.IsEOF())
					bAlreadyExists = true;
				rsCheck.Close();
			}
			if (bAlreadyExists)
			{
				CString msg;
				msg.Format(_T("学生 %s 已经选过课程 %s，跳过。"), strSno, courses[i].courseName);
				strErrors += msg + _T("\n");
				continue;
			}

			// 执行插入
			CString strSQL;
			strSQL.Format(_T("INSERT INTO sc (sno, cno) VALUES ('%s', %d)"), strSno, courses[i].courseId);
			try
			{
				my_db.ExecuteSQL(strSQL);
				nInsertCount++;
			}
			catch (CDBException* pe)
			{
				CString errMsg;
				errMsg.Format(_T("选课失败：学生 %s 课程 %s，错误：%s"), strSno, courses[i].courseName, pe->m_strError);
				strErrors += errMsg + _T("\n");
				pe->Delete();
			}
		}
	}

	// 4. 反馈结果
	if (nInsertCount > 0)
	{
		CString msg;
		msg.Format(_T("成功选课 %d 门。"), nInsertCount);
		AfxMessageBox(msg);
	}
	if (!strErrors.IsEmpty())
	{
		AfxMessageBox(strErrors);
	}
}

void CMyDemoDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	 // Demo 重置按钮功能：删除当前选中学生在SC表中的所有选课记录

	// 1. 检查是否有选中的学生（原始学号需要提前保存）
	//    这里使用之前为“修改”功能添加的成员变量 m_strOriginalSno
	if (m_strOriginalSno.IsEmpty())
	{
		AfxMessageBox(_T("请先在列表中选择要重置的学生！"));
		return;
	}

	// 2. 二次确认（防止误操作）
	CString msg;
	msg.Format(_T("确定要清空学号为 %s 的学生所有选课记录吗？"), m_strOriginalSno);
	if (AfxMessageBox(msg, MB_YESNO | MB_ICONQUESTION) != IDYES)
		return;

	// 3. 构造 DELETE SQL 语句
	//    删除 SC 表中该学号的所有记录
	CString strSQL;
	strSQL.Format(_T("DELETE FROM sc WHERE sno = '%s'"), m_strOriginalSno);

	// 4. 执行 SQL 删除
	try
	{
		my_db.ExecuteSQL(strSQL);
		AfxMessageBox(_T("重置成功！已清空该学生的选课记录。"));

		// 5. 可选：刷新界面中可能显示的选课列表（如果你有一个单独的选课列表控件）
		//    如果没有单独的选课列表，可以只提示成功。
		//    根据实验要求，只需要底层数据库更新即可，无需刷新学生表（学生表不变）。
		//    但如果你希望更新某个选课显示区域，可以在这里调用刷新函数。
		//    例如： UpdateCourseList();   // 需要你自己实现

		// 6. 注意：不需要清空 m_strOriginalSno，因为重置后可能继续操作该学生
		//    也不清空编辑框内容，以便继续选课或重置。
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}
}
