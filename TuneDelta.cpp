// TuneDelta.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FragmentsRestorationAssitant.h"
#include "TuneDelta.h"
#include "afxdialogex.h"


// CTuneDelta �Ի���

IMPLEMENT_DYNAMIC(CTuneDelta, CDialogEx)

CTuneDelta::CTuneDelta(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTuneDelta::IDD, pParent)
	, m_editValueOfDelta(0)
{

}

CTuneDelta::~CTuneDelta()
{
}

void CTuneDelta::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELTA_CONF, m_editValueOfDelta);
}


BEGIN_MESSAGE_MAP(CTuneDelta, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONF_CONFIRM, &CTuneDelta::OnBnClickedButtonConfConfirm)
END_MESSAGE_MAP()


// CTuneDelta ��Ϣ�������


void CTuneDelta::OnBnClickedButtonConfConfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialog::EndDialog(0);
}


double CTuneDelta::GetDelta()
{
	return m_editValueOfDelta;
}

