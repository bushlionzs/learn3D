#ifndef _GAME_DEFINE_H_
#define _GAME_DEFINE_H_

//#include <OgreVector2.h>
//#include <OgreVector3.h>
#include "ku.h"

/*  */ 
//typedef static			STATIC


///* 调用数学库 */
//typedef Ogre::Vector3	vector3;
//typedef Ogre::Vector2	vector2;

struct vector3
{
	float x, y, z;
	vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	inline float normalise()
	{
		//Real fLength = Math::Sqrt( x * x + y * y + z * z );

		float fLength = sqrtf(x * x + y * y + z * z);

		// Will also work for zero-sized vectors, but will change nothing
		if (fLength > 1e-08)
		{
			float fInvLength = 1.0f / fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
		}

		return fLength;
	}
};

struct vector2
{
	float x, y;
	vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	inline float normalise()
	{
		//Real fLength = Math::Sqrt( x * x + y * y + z * z );

		float fLength = sqrtf(x * x + y * y);

		// Will also work for zero-sized vectors, but will change nothing
		if (fLength > 1e-08)
		{
			float fInvLength = 1.0f / fLength;
			x *= fInvLength;
			y *= fInvLength;
		}

		return fLength;
	}

	inline vector2 operator + (const vector2& rkVector) const
	{
		return vector2(
			x + rkVector.x,
			y + rkVector.y);
	}

	inline vector2 operator - (const vector2& rkVector) const
	{
		return vector2(
			x - rkVector.x,
			y - rkVector.y);
	}

	inline bool operator == (const vector2& rkVector) const
	{
		return (x == rkVector.x && y == rkVector.y);
	}

	inline vector2 operator * (const float fScalar) const
	{
		return vector2(
			x * fScalar,
			y * fScalar);
	}

	inline vector2 operator * (const vector2& rhs) const
	{
		return vector2(
			x * rhs.x,
			y * rhs.y);
	}

	// overloaded operators to help Vector2
	inline friend vector2 operator * (const float fScalar, const vector2& rkVector)
	{
		return vector2(
			fScalar * rkVector.x,
			fScalar * rkVector.y);
	}

	inline float dotProduct(const vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}
};

struct fRay
{
public:
	vector3 mOrigin;
	vector3 mDirection;
};


#define KLU_PI			(3.1415926535)
#define KLU_PI_2		(2 * KLU_PI)
#define KLU_RADIAN		(KLU_PI / 180.0f)
#define KLU_MINFLOAT	(1.0E-9)



/* 语言设置 */
#ifdef LANG_CT
#define LANGUAGES_CODE	950		// 台湾
#else
#define LANGUAGES_CODE	936		// 
#endif



// 全视角
#define ENABLE_DEMO_MODE
#define ENABLE_DEBUG_STRING



/* 返回类型定义 */
enum KHAN_RETURN_RESULT
{
	KRR_INVALID			= -1,
	KRR_FAILED			= 0,						/* 失败 */
	KRR_SUCCEED			= 1,						/* 成功 */

	KRR_FILE_OPEN_FAILED,							/* 文件打开失败 */
};


/* 用户类型 */
enum USE_MODEL_TYPE
{
	UM_KYLIN = 0,
	UM_TEST,
	UM_BAIDU,
	UM_FENGXING,
	UM_XUNLEI,
	UM_ZHONGYOU,
	UM_SHENGDA,
};

extern USE_MODEL_TYPE			g_eUseModel;



//extern HWND						CGameState::m_hMainWnd;			/* 主窗口 */
//extern HWND						g_hLogoWnd;			/* 登陆 */
//extern HINSTANCE				g_hInstance;		/* 当前主程序模块句柄 */

/*
 * extern HANDLE g_hSemaphore;
 * //
 */
extern String					g_strCmdLine;

extern ku::CKU					gUtil;				/* 游戏辅助 */

#define CHECK_STR_LEN	8
extern const char				GAME_TAG[];			/* 启动标记 */
extern BOOL						g_bDebug;			/* 是否调试启动 */
extern BOOL						g_bDebugPackRes;	/* 是否包资源（仅调试版有效） */
extern BOOL						g_bGM;

/*
 * extern BOOL g_bLawless;
 * //
 */
extern FLOAT					g_fVideoMem;		/* 显存值 */
extern const FLOAT				g_fRequiredVideoMemory;		/* 最低要求 */

extern const char				RESOURCE_GROUP[];			/* 资源组名 */
extern const char				DEBUG_FILE_NAME[];			/* 调试版配置文件名 */
extern const char				LOGIN_FILE_NAME[];			/* 登陆配置文件名 */
extern char*					SERVER_LIST_FILE_NAME;		/* 服务器列表文件名 */
extern int						g_nProcess;					/* 流程判断 */

extern const char				ONLINE_SERVICE_PATH[];
extern const char				ONLINE_SERVICE_EXE[];
extern const char				ONLINE_SERVICE_INI[];

/* 记录游戏用到的信息 */
extern String g_strKhanInfo;

/* 异常捕获 */
#define ENABLE_EXCEPTION

#ifdef ENABLE_EXCEPTION
#define KYLIN_TRY	try{
#define KYLIN_CATCH(str)				\
}										\
catch (...)								\
{										\
	throw;								\
};
#else
#define KYLIN_TRY
#define KYLIN_CATCH(str)
#endif

/* GM指令修改权限 */
#define NAME_LENGTH		(16)
#define CONTENTS_LENGTH (256)

typedef struct
{
	unsigned char	cParameter;
	char			pName[NAME_LENGTH];
	char			pContents[CONTENTS_LENGTH];
} GMDATA, FAR * LPGMDATA;



#define GAME_FRONT_FPS		45
#define GAME_BACK_FPS		20

/* 快捷栏图标 */
#define MYWM_NOTIFYICON WM_USER + 1

const char	c_MAIN_WINDOW_CLASS[] = "CJSH2 WndClass";

//const int32	DEFWINDOW_WIDTH = 1024;
//const int32	DEFWINDOW_HEIGHT = 768;

const int32	c_MIN_WINDOW_WIDTH = 800;
const int32	c_MIN_WINDOW_HEIGHT = 600;

const int32	MAX_VERSION_LENGTH = 15;

const uint32	DEFWINDOW_STYLE = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_THICKFRAME;

// 游戏窗口比例 ( 例：3:4 = 0.75 )
//const FLOAT DEF_WINDOW_FOV = (FLOAT)DEFWINDOW_HEIGHT / (FLOAT)DEFWINDOW_WIDTH;



/* 游戏运行状态 */
enum GAME_STATE_TYPE
{
	GP_NONE				= -1,
	GP_LOGIN			= 0,
	GP_SELECT_CHAR,
	GP_CREATE_CHAR,
	GP_LOAD_SCENE,
	GP_CHANGER_SERVER,
	GP_MAIN,
};


/*
 * 物体基本状态 ( OSF = Object Status Flags ) ;
 */
#define OSF_NONE				(0x0)						/* 空状态 */
#define OSF_VISIABLE			(0x1)						/* 是否可见 */
#define OSF_OUT_VISUAL_FIELD	(0x2)						/* 已经不再玩家的视野范围,如果该值维持一定时间,则会被删除 */
#define OSF_RAY_QUERY			(0x4)						/* 鼠标能否选中 */


/* 坐标转换 */
enum GAME_ROT_TRAN_TYPE { GRT_ZX, GRT_FX, GRT_ZZ, GRT_FZ, };

/* 摄像机相关函数 */
enum GAME_CAMERA_TYPE { XCT_VIEW, XCT_SCENE, };

/* 指针类型 */
enum eCURSOR_TYPE
{
	CURSOR_WINBASE		= 0,
	CURSOR_NORMAL,			/* 普通 */
	CURSOR_ATTACK,			/* 攻击 */
	CURSOR_AUTORUN,			/* 自动行走中 */
	CURSOR_PICKUP,			/* 拾取物品 */
	CURSOR_UNREACHABLE,		/* 无法到达的区域 */
	CURSOR_MINE,			/* 采矿 */
	CURSOR_HERBS,			/* 采药 */
	CURSOR_SPEAK,			/* 谈话 */
	CURSOR_INTERACT,		/* 齿轮 */
	CURSOR_REPAIR,			/* 修理 */
	CURSOR_HOVER,			/* 鼠标激活(挂接物品...) */
	CURSOR_IDENTIFY,		/* 鼠标鉴定 */
	CURSOR_RING,			/* 技能环 */
	CURSOR_DIRECTION,		/* 方向技能 */
	CURSOR_OPERATION,		/* 可操作 */
	CURSOR_NOOPERATION,		/* 不可操作 */
	CURSOR_CATCH,			/* 捕捉 */
	CURSOR_NOCATCH,			/* 不可捕捉 */
	CURSOR_ROTATE,			/* 旋转 */
	CURSOR_CUSTOM,			/* 自定义鼠标（如拖拽物品等） */
	CURSOR_LINK,			/* 文字超链接 */
	CURSOR_SPLIT,			/* 拆分 */
	CURSOR_LOCK,			/* 加锁 */
	CURSOR_UNLOCK,			/* 解锁 */

	CURSOR_NUMBER,
};
struct SMapPosDefine
{
	vector3 pos;
	DWORD	dwSceneID;		/* 所在场景id */
	char	name[128];
	int32		nServerID;
	char	utf8name[128];	/* 优化名称 */
	bool	opti;
	int32		nObjType;
	int32		nObjState;

	SMapPosDefine()
	{
		opti = false;
		memset(utf8name, 0, 128);
	}
	void	Set_Name(const char *strName);
	void	Set_Pos_Name(const char *strName);
	void	Set_Pos_Utf8Name(const char *strName);
};


// 接受信息的服务器
const char SERVER_HOST[] = "http://59.151.11.160";

// 图形验证服务器
const char CAPTCHA_URL_WEB[]   = "http://gcode.70yx.com/VerifyCode.aspx";	// "http://180.96.7.3/VerifyCode.aspx";
const char CAPTCHA_URL_LOCAL[] = "http://180.96.7.3/VerifyCode.aspx";

// 控件窗口名称
const char WINDOW_SOFTKEY[]		= "LogOn_SoftKey";	// GameLogon.lua
const char WINDOW_PASSWORD[]	= "LogOn_PassWord";


#endif /* _GAME_DEFINE_H_ */
