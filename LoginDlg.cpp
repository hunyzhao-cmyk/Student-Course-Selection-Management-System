// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Demo.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

CDatabase my_db;
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USER, m_edtUser);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edtPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_EDIT_Register, &CLoginDlg::OnBnClickedEditRegister)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//数据库初始化 
	if (my_db.Open(_T("my_opengauss")))//打开ODBC数据源驱动配置的用户DNS名称，返回值TRUE则表示正确连接上

	{


		//AfxMessageBox(_T("OpenGauss数据库连接成功！"));

	}

	else

	{


		AfxMessageBox(_T("数据库连接失败，请检查虚拟机Opengauss是否运行或者ODBC驱动是否配置正确！"));

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLoginDlg::OnBnClickedCancel()
{
	if (my_db.IsOpen())//判断是否处于数据库连接状态 

	{


		my_db.Close();//如果当前处于连接状态，从数据源断开连接，释放系统资源 

	}
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
   /* Demo 登录函数 - 使用 gs_decrypt 解密后与用户输入匹配 */
    UpdateData(TRUE);

    CString strUser, strPwd;
    m_edtUser.GetWindowText(strUser);
    m_edtPassword.GetWindowText(strPwd);

    if (strUser.IsEmpty() || strPwd.IsEmpty())
    {
        AfxMessageBox(_T("学号和密码不能为空！"));
        return;
    }

    if (!my_db.IsOpen())
    {
        AfxMessageBox(_T("数据库未连接！"));
        return;
    }

    CString strKey = _T("yourKey@123");     // 必须与注册时使用的密钥相同

    // 使用 gs_decrypt 解密存储的密码，与用户输入的明文密码比对
    CString strSQL;
    strSQL.Format(_T("SELECT Uname FROM Userinformation WHERE Uname='%s' AND gs_decrypt(Upassword, '%s', 'aes128') = '%s'"),
        strUser, strKey, strPwd);
    // 若使用 AES128 简化版本：
    // strSQL.Format(_T("SELECT Uname FROM Userinformation WHERE Uname='%s' AND gs_decrypt_aes128(Upassword, '%s') = '%s'"),
    //               strUser, strKey, strPwd);

    CRecordset rs(&my_db);
    try
    {
        if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
        {
            if (!rs.IsEOF())
            {
                // 登录成功
                CDialogEx::OnOK();
            }
            else
            {
                AfxMessageBox(_T("学号或密码错误！"));
            }
            rs.Close();
        }
        else
        {
            AfxMessageBox(_T("查询失败！"));
        }
    }
    catch (CDBException* pe)
    {
        pe->ReportError();
        pe->Delete();
    }
}

void CLoginDlg::OnBnClickedEditRegister()
{
	// TODO: 在此添加控件通知处理程序代码
   /* Demo 注册函数 - 使用 gs_encrypt 加密存储密码 */
    UpdateData(TRUE);

    CString strUser, strPwd;
    m_edtUser.GetWindowText(strUser);
    m_edtPassword.GetWindowText(strPwd);

    // 学号不能为空
    if (strUser.IsEmpty())
    {
        AfxMessageBox(_T("学号不能为空！"));
        return;
    }
    // 密码长度验证（8~16位，包含至少3种字符，gs_encrypt的要求）
    if (strPwd.GetLength() < 8 || strPwd.GetLength() > 16)
    {
        AfxMessageBox(_T("密码长度必须为8~16位！"));
        return;
    }

    // 检查用户名是否已存在
    if (!my_db.IsOpen())
    {
        AfxMessageBox(_T("数据库未连接！"));
        return;
    }

    CString strCheckSQL;
    strCheckSQL.Format(_T("SELECT Uname FROM Userinformation WHERE Uname='%s'"), strUser);
    CRecordset rsCheck(&my_db);
    if (rsCheck.Open(AFX_DB_USE_DEFAULT_TYPE, strCheckSQL))
    {
        if (!rsCheck.IsEOF())
        {
            AfxMessageBox(_T("该学号已注册，请直接登录！"));
            rsCheck.Close();
            return;
        }
        rsCheck.Close();
    }

    // 加密密钥（使用固定的密钥，注意保密，实际应用中应从配置文件读取）
    CString strKey = _T("yourKey@123");     // 密钥长度8~16位

    // 构造 INSERT SQL，使用 gs_encrypt 加密密码（采用 aes128 算法）
    CString strSQL;
    strSQL.Format(_T("INSERT INTO Userinformation (Uname, Upassword) VALUES ('%s', gs_encrypt('%s', '%s', 'aes128'))"),
        strUser, strPwd, strKey);
    // 若使用 AES128 简化版本，可改为：
    // strSQL.Format(_T("INSERT INTO Userinformation (Uname, Upassword) VALUES ('%s', gs_encrypt_aes128('%s', '%s'))"),
    //               strUser, strPwd, strKey);

    try
    {
        my_db.ExecuteSQL(strSQL);
        AfxMessageBox(_T("注册成功！"));
    }
    catch (CDBException* pe)
    {
        pe->ReportError();
        pe->Delete();
    }
}
