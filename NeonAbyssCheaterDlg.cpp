
// NeonAbyssCheaterDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NeonAbyssCheater.h"
#include "NeonAbyssCheaterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNeonAbyssCheaterDlg dialog

CNeonAbyssCheaterDlg::CNeonAbyssCheaterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEONABYSSCHEATER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNeonAbyssCheaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNeonAbyssCheaterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_HOTKEY()
	ON_STN_DBLCLK(IDC_STATIC_MONEY, &CNeonAbyssCheaterDlg::OnStnDblclickStaticMoney)
	ON_STN_DBLCLK(IDC_STATIC_HP, &CNeonAbyssCheaterDlg::OnStnDblclickStaticHp)
	ON_STN_CLICKED(IDC_STATIC_CRYSTAL, &CNeonAbyssCheaterDlg::OnStnClickedStaticCrystal)
	ON_STN_CLICKED(IDC_STATIC_SHIELD, &CNeonAbyssCheaterDlg::OnStnClickedStaticShield)
	ON_STN_CLICKED(IDC_STATIC_NBOMB, &CNeonAbyssCheaterDlg::OnStnClickedStaticNbomb)
	ON_STN_CLICKED(IDC_STATIC_FBOMB, &CNeonAbyssCheaterDlg::OnStnClickedStaticFbomb)
	ON_STN_CLICKED(IDC_STATIC_IBOMB, &CNeonAbyssCheaterDlg::OnStnClickedStaticIbomb)
	ON_STN_CLICKED(IDC_STATIC_ABOMB, &CNeonAbyssCheaterDlg::OnStnClickedStaticAbomb)
	ON_STN_CLICKED(IDC_STATIC_NKEY, &CNeonAbyssCheaterDlg::OnStnClickedStaticNkey)
	ON_STN_CLICKED(IDC_STATIC_RKEY, &CNeonAbyssCheaterDlg::OnStnClickedStaticRkey)
	ON_STN_CLICKED(IDC_STATIC_JUMP_LEVEL, &CNeonAbyssCheaterDlg::OnStnClickedStaticJumpLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_JUMP_LEVEL, &CNeonAbyssCheaterDlg::OnDeltaposSpinJumpLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_JUMP_HEIGHT, &CNeonAbyssCheaterDlg::OnDeltaposSpinJumpHeight)
	ON_STN_DBLCLK(IDC_STATIC_JUMP_HEIGHT, &CNeonAbyssCheaterDlg::OnStnDblclickStaticJumpHeight)
	ON_STN_CLICKED(IDC_STATIC_RUN_SPEED, &CNeonAbyssCheaterDlg::OnStnClickedStaticRunSpeed)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RUN_SPEED, &CNeonAbyssCheaterDlg::OnDeltaposSpinRunSpeed)
	ON_STN_CLICKED(IDC_STATIC_BULLET_RADIUS, &CNeonAbyssCheaterDlg::OnStnClickedStaticBulletRadius)
	ON_STN_CLICKED(IDC_STATIC_BULLET_SPEED, &CNeonAbyssCheaterDlg::OnStnClickedStaticBulletSpeed)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BULLET_RADIUS, &CNeonAbyssCheaterDlg::OnDeltaposSpinBulletRadius)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BULLET_SPEED, &CNeonAbyssCheaterDlg::OnDeltaposSpinBulletSpeed)
	ON_STN_CLICKED(IDC_STATIC_X_RAY_EYE, &CNeonAbyssCheaterDlg::OnStnClickedStaticXRayEye)
	ON_STN_CLICKED(IDC_STATIC_BULLET_FISSION, &CNeonAbyssCheaterDlg::OnStnClickedStaticBulletFission)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BULLET_FISSON, &CNeonAbyssCheaterDlg::OnDeltaposSpinBulletFisson)
	ON_STN_CLICKED(IDC_STATIC_FAITH_GEMS, &CNeonAbyssCheaterDlg::OnStnClickedStaticFaithGems)
END_MESSAGE_MAP()


// CNeonAbyssCheaterDlg message handlers

BOOL CNeonAbyssCheaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize Basic Timer
	SetTimer(BASIC_TIMER, 1000, NULL);

	// Register HotKey
	RegisterHotKey(m_hWnd, HK_SHOW_HIDE_KEY, 0, VK_F9);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNeonAbyssCheaterDlg::OnPaint()
{
	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNeonAbyssCheaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Timer Handler
void CNeonAbyssCheaterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == BASIC_TIMER) {
		CString showText;
		auto id = game_entry.getGameProcessID();
		if (game_entry.isGameRunning()) {
			showText.Format("PID:%lld", id);
			auto basic_info = game_entry.getHeroBasicInfo();
			for (auto item : basic_info) {
				CString s;
				// https://en.cppreference.com/w/cpp/utility/any
				auto typeName = item.second.type().name();
				if (typeName == T_DOUBLE) s.Format("%.4lg", std::any_cast<double>(item.second));
				else if (typeName == T_FLOAT) s.Format("%.4g", std::any_cast<float>(item.second));
				
				if (basic_label_map.find(item.first) != basic_label_map.end()) {
					int id = basic_label_map.at(item.first);
					SetDlgItemTextA(id, s);
				}
			}

			// Check fixed buttons
			for (auto item : basic_check_map) {
				game_entry.toggleFixedEntry(item.first, ((CButton*)GetDlgItem(item.second))->GetCheck());
			}
			game_entry.fixEntriesValue();
		}
		else showText = "Game not running...";
		SetDlgItemText(IDC_STATIC_GAME_STATUS, showText);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CNeonAbyssCheaterDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if (nHotKeyId == HK_SHOW_HIDE_KEY) {
		if (IsWindowVisible()) this->ShowWindow(SW_HIDE);
		else this->ShowWindow(SW_SHOW);
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CNeonAbyssCheaterDlg::OnBnClickedMfcbutton1()
{

}

// =============== DoubleClick Static events ============

void CNeonAbyssCheaterDlg::OnStnDblclickStaticMoney() { game_entry.writeBasicInfo<double>(GAME_BASIC_MONEY, 999); }

void CNeonAbyssCheaterDlg::OnStnDblclickStaticHp() { game_entry.writeBasicInfo<double>(GAME_BASIC_HP, 10); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticCrystal() { game_entry.writeBasicInfo<double>(GAME_BASIC_CRYSTAL, 10); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticShield() { game_entry.writeBasicInfo<double>(GAME_BASIC_SHIELD, 10); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticNbomb() { game_entry.writeBasicInfo<double>(GAME_BASIC_NORMAL_BOMB, 20); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticFbomb() { game_entry.writeBasicInfo<double>(GAME_BASIC_FIRE_BOMB, 20); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticIbomb() { game_entry.writeBasicInfo<double>(GAME_BASIC_ICE_BOMB, 20); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticAbomb() { game_entry.writeBasicInfo<double>(GAME_BASIC_ALCOHOL_BOMB, 20); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticNkey() { game_entry.writeBasicInfo<double>(GAME_BASIC_NORMAL_KEY, 66); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticRkey() { game_entry.writeBasicInfo<double>(GAME_BASIC_RAINBOW_KEY, 33); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticJumpLevel() { game_entry.writeBasicInfo<double>(GAME_BASIC_JUMP_LEVEL, 10); }

void CNeonAbyssCheaterDlg::OnStnDblclickStaticJumpHeight() { game_entry.writeBasicInfo<double>(GAME_BASIC_JUMP_BASE_HEIGHT, 1000); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticRunSpeed() { game_entry.writeBasicInfo<double>(GAME_BASIC_RUN_SPEED, 3); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticBulletRadius() { game_entry.writeBasicInfo<double>(GAME_BASIC_BULLET_RADIUS, 5); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticBulletSpeed() { game_entry.writeBasicInfo<float>(GAME_BASIC_BULLET_ATTACK_SPEED, 5); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticXRayEye() { game_entry.writeBasicInfo<double>(GAME_BASIC_XRAY_EYE, 1); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticBulletFission() { game_entry.writeBasicInfo<double>(GAME_BASIC_BULLET_FISSION_COUNT, 6); }

void CNeonAbyssCheaterDlg::OnStnClickedStaticFaithGems() { game_entry.writeBasicInfo<double>(GAME_BASIC_FAITH_GEMS, 300); }






void CNeonAbyssCheaterDlg::OnDeltaposSpinJumpLevel(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// pNMUpDown->iDelta 为1 说明点击了Spin的往下箭头
	game_entry.incrOrDecrBasicInfo<double>(std::string(GAME_BASIC_JUMP_LEVEL), pNMUpDown->iDelta == -1);
	*pResult = 0;
}


void CNeonAbyssCheaterDlg::OnDeltaposSpinJumpHeight(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// pNMUpDown->iDelta 为1 说明点击了Spin的往下箭头
	game_entry.incrOrDecrBasicInfo<double>(std::string(GAME_BASIC_JUMP_BASE_HEIGHT), pNMUpDown->iDelta == -1, 20);
	*pResult = 0;
}

void CNeonAbyssCheaterDlg::OnDeltaposSpinRunSpeed(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	game_entry.incrOrDecrBasicInfo<double>(std::string(GAME_BASIC_RUN_SPEED), pNMUpDown->iDelta == -1);
}




void CNeonAbyssCheaterDlg::OnDeltaposSpinBulletRadius(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	game_entry.incrOrDecrBasicInfo<double>(std::string(GAME_BASIC_BULLET_RADIUS), pNMUpDown->iDelta == -1);
}


void CNeonAbyssCheaterDlg::OnDeltaposSpinBulletSpeed(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	game_entry.incrOrDecrBasicInfo<float>(std::string(GAME_BASIC_BULLET_ATTACK_SPEED), pNMUpDown->iDelta == -1);
}


void CNeonAbyssCheaterDlg::OnDeltaposSpinBulletFisson(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	game_entry.incrOrDecrBasicInfo<double>(std::string(GAME_BASIC_BULLET_FISSION_COUNT), pNMUpDown->iDelta == -1);
}