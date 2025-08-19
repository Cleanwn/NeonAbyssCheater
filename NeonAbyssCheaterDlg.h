
// NeonAbyssCheaterDlg.h : header file
//

#pragma once

#include "GameEntry.h"


// CNeonAbyssCheaterDlg dialog
class CNeonAbyssCheaterDlg : public CDialogEx
{
	// Construction
public:
	CNeonAbyssCheaterDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEONABYSSCHEATER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;
	GameEntry game_entry;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Key to StaticLabelID
	const std::map<std::string, int> basic_label_map = {
		{GAME_BASIC_MONEY, IDC_STATIC_MONEY}, {GAME_BASIC_HP, IDC_STATIC_HP}, {GAME_BASIC_CRYSTAL, IDC_STATIC_CRYSTAL}, {GAME_BASIC_SHIELD, IDC_STATIC_SHIELD},
		{GAME_BASIC_NORMAL_BOMB, IDC_STATIC_NBOMB}, {GAME_BASIC_ICE_BOMB, IDC_STATIC_IBOMB}, {GAME_BASIC_JUMP_LEVEL, IDC_STATIC_JUMP_LEVEL},
		{GAME_BASIC_RAINBOW_KEY, IDC_STATIC_RKEY}, {GAME_BASIC_NORMAL_KEY, IDC_STATIC_NKEY}, {GAME_BASIC_ALCOHOL_BOMB, IDC_STATIC_ABOMB},
		{GAME_BASIC_FIRE_BOMB, IDC_STATIC_FBOMB}, {GAME_BASIC_JUMP_BASE_HEIGHT, IDC_STATIC_JUMP_HEIGHT}, {GAME_BASIC_RUN_SPEED, IDC_STATIC_RUN_SPEED},
		{GAME_BASIC_BULLET_RADIUS, IDC_STATIC_BULLET_RADIUS}, {GAME_BASIC_BULLET_ATTACK_SPEED, IDC_STATIC_BULLET_SPEED}, {GAME_BASIC_XRAY_EYE, IDC_STATIC_X_RAY_EYE},
		{GAME_BASIC_BULLET_FISSION_COUNT, IDC_STATIC_BULLET_FISSION}, {GAME_BASIC_FAITH_GEMS, IDC_STATIC_FAITH_GEMS}
	};

	// Key to CheckBoxID
	const std::map<std::string, int> basic_check_map = {
		{GAME_BASIC_MONEY, IDC_CHECK_MONEY}, {GAME_BASIC_HP, IDC_CHECK_HP}, {GAME_BASIC_CRYSTAL, IDC_CHECK_CRYSTAL}, {GAME_BASIC_SHIELD, IDC_CHECK_SHIELD},
		{GAME_BASIC_NORMAL_BOMB, IDC_CHECK_NBOMB}, {GAME_BASIC_ICE_BOMB, IDC_CHECK_IBOMB}, {GAME_BASIC_JUMP_LEVEL, IDC_CHECK_JUMP_LEVEL},
		{GAME_BASIC_RAINBOW_KEY, IDC_CHECK_RKEY}, {GAME_BASIC_NORMAL_KEY, IDC_CHECK_NKEY}, {GAME_BASIC_ALCOHOL_BOMB, IDC_CHECK_ABOMB},
		{GAME_BASIC_FIRE_BOMB, IDC_CHECK_FBOMB}, {GAME_BASIC_JUMP_BASE_HEIGHT, IDC_CHECK_JUMP_HEIGHT}, {GAME_BASIC_RUN_SPEED, IDC_CHECK_RUN_SPEED},
		{GAME_BASIC_BULLET_RADIUS, IDC_CHECK_BULLET_RADIUS}, {GAME_BASIC_BULLET_ATTACK_SPEED, IDC_CHECK_BULLET_SPEED}, {GAME_BASIC_XRAY_EYE, IDC_CHECK_X_RAY_EYE},
		{GAME_BASIC_BULLET_FISSION_COUNT, IDC_CHECK_BULLET_FISSON}, {GAME_BASIC_JUMP_COUNT, IDC_CHECK_JUMP_COUNT}, {GAME_BASIC_FAITH_GEMS, IDC_CHECK_FAITH_GEMS}
	};


public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnStnDblclickStaticMoney();
	afx_msg void OnStnDblclickStaticHp();
	afx_msg void OnStnClickedStaticCrystal();
	afx_msg void OnStnClickedStaticShield();
	afx_msg void OnStnClickedStaticNbomb();
	afx_msg void OnStnClickedStaticFbomb();
	afx_msg void OnStnClickedStaticIbomb();
	afx_msg void OnStnClickedStaticAbomb();
	afx_msg void OnStnClickedStaticNkey();
	afx_msg void OnStnClickedStaticRkey();
	afx_msg void OnStnClickedStaticJumpLevel();
	afx_msg void OnDeltaposSpinJumpLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinJumpHeight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnDblclickStaticJumpHeight();
	afx_msg void OnStnClickedStaticRunSpeed();
	afx_msg void OnDeltaposSpinRunSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticBulletRadius();
	afx_msg void OnStnClickedStaticBulletSpeed();
	afx_msg void OnDeltaposSpinBulletRadius(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBulletSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticXRayEye();
	afx_msg void OnStnClickedStaticBulletFission();
	afx_msg void OnDeltaposSpinBulletFisson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticFaithGems();
};


// ==== Timer ID ====
#define BASIC_TIMER 1000


// ==== HotKey ID ====
#define HK_SHOW_HIDE_KEY 2000
