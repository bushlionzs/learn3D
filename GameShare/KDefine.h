#ifndef _GAME_DEFINE_H_
#define _GAME_DEFINE_H_

//#include <OgreVector2.h>
//#include <OgreVector3.h>
#include "ku.h"

/*  */ 
//typedef static			STATIC


///* ������ѧ�� */
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



/* �������� */
#ifdef LANG_CT
#define LANGUAGES_CODE	950		// ̨��
#else
#define LANGUAGES_CODE	936		// 
#endif



// ȫ�ӽ�
#define ENABLE_DEMO_MODE
#define ENABLE_DEBUG_STRING



/* �������Ͷ��� */
enum KHAN_RETURN_RESULT
{
	KRR_INVALID			= -1,
	KRR_FAILED			= 0,						/* ʧ�� */
	KRR_SUCCEED			= 1,						/* �ɹ� */

	KRR_FILE_OPEN_FAILED,							/* �ļ���ʧ�� */
};


/* �û����� */
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



//extern HWND						CGameState::m_hMainWnd;			/* ������ */
//extern HWND						g_hLogoWnd;			/* ��½ */
//extern HINSTANCE				g_hInstance;		/* ��ǰ������ģ���� */

/*
 * extern HANDLE g_hSemaphore;
 * //
 */
extern String					g_strCmdLine;

extern ku::CKU					gUtil;				/* ��Ϸ���� */

#define CHECK_STR_LEN	8
extern const char				GAME_TAG[];			/* ������� */
extern BOOL						g_bDebug;			/* �Ƿ�������� */
extern BOOL						g_bDebugPackRes;	/* �Ƿ����Դ�������԰���Ч�� */
extern BOOL						g_bGM;

/*
 * extern BOOL g_bLawless;
 * //
 */
extern FLOAT					g_fVideoMem;		/* �Դ�ֵ */
extern const FLOAT				g_fRequiredVideoMemory;		/* ���Ҫ�� */

extern const char				RESOURCE_GROUP[];			/* ��Դ���� */
extern const char				DEBUG_FILE_NAME[];			/* ���԰������ļ��� */
extern const char				LOGIN_FILE_NAME[];			/* ��½�����ļ��� */
extern char*					SERVER_LIST_FILE_NAME;		/* �������б��ļ��� */
extern int						g_nProcess;					/* �����ж� */

extern const char				ONLINE_SERVICE_PATH[];
extern const char				ONLINE_SERVICE_EXE[];
extern const char				ONLINE_SERVICE_INI[];

/* ��¼��Ϸ�õ�����Ϣ */
extern String g_strKhanInfo;

/* �쳣���� */
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

/* GMָ���޸�Ȩ�� */
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

/* �����ͼ�� */
#define MYWM_NOTIFYICON WM_USER + 1

const char	c_MAIN_WINDOW_CLASS[] = "CJSH2 WndClass";

//const int32	DEFWINDOW_WIDTH = 1024;
//const int32	DEFWINDOW_HEIGHT = 768;

const int32	c_MIN_WINDOW_WIDTH = 800;
const int32	c_MIN_WINDOW_HEIGHT = 600;

const int32	MAX_VERSION_LENGTH = 15;

const uint32	DEFWINDOW_STYLE = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_THICKFRAME;

// ��Ϸ���ڱ��� ( ����3:4 = 0.75 )
//const FLOAT DEF_WINDOW_FOV = (FLOAT)DEFWINDOW_HEIGHT / (FLOAT)DEFWINDOW_WIDTH;



/* ��Ϸ����״̬ */
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
 * �������״̬ ( OSF = Object Status Flags ) ;
 */
#define OSF_NONE				(0x0)						/* ��״̬ */
#define OSF_VISIABLE			(0x1)						/* �Ƿ�ɼ� */
#define OSF_OUT_VISUAL_FIELD	(0x2)						/* �Ѿ�������ҵ���Ұ��Χ,�����ֵά��һ��ʱ��,��ᱻɾ�� */
#define OSF_RAY_QUERY			(0x4)						/* ����ܷ�ѡ�� */


/* ����ת�� */
enum GAME_ROT_TRAN_TYPE { GRT_ZX, GRT_FX, GRT_ZZ, GRT_FZ, };

/* �������غ��� */
enum GAME_CAMERA_TYPE { XCT_VIEW, XCT_SCENE, };

/* ָ������ */
enum eCURSOR_TYPE
{
	CURSOR_WINBASE		= 0,
	CURSOR_NORMAL,			/* ��ͨ */
	CURSOR_ATTACK,			/* ���� */
	CURSOR_AUTORUN,			/* �Զ������� */
	CURSOR_PICKUP,			/* ʰȡ��Ʒ */
	CURSOR_UNREACHABLE,		/* �޷���������� */
	CURSOR_MINE,			/* �ɿ� */
	CURSOR_HERBS,			/* ��ҩ */
	CURSOR_SPEAK,			/* ̸�� */
	CURSOR_INTERACT,		/* ���� */
	CURSOR_REPAIR,			/* ���� */
	CURSOR_HOVER,			/* ��꼤��(�ҽ���Ʒ...) */
	CURSOR_IDENTIFY,		/* ������ */
	CURSOR_RING,			/* ���ܻ� */
	CURSOR_DIRECTION,		/* ������ */
	CURSOR_OPERATION,		/* �ɲ��� */
	CURSOR_NOOPERATION,		/* ���ɲ��� */
	CURSOR_CATCH,			/* ��׽ */
	CURSOR_NOCATCH,			/* ���ɲ�׽ */
	CURSOR_ROTATE,			/* ��ת */
	CURSOR_CUSTOM,			/* �Զ�����꣨����ק��Ʒ�ȣ� */
	CURSOR_LINK,			/* ���ֳ����� */
	CURSOR_SPLIT,			/* ��� */
	CURSOR_LOCK,			/* ���� */
	CURSOR_UNLOCK,			/* ���� */

	CURSOR_NUMBER,
};
struct SMapPosDefine
{
	vector3 pos;
	DWORD	dwSceneID;		/* ���ڳ���id */
	char	name[128];
	int32		nServerID;
	char	utf8name[128];	/* �Ż����� */
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


// ������Ϣ�ķ�����
const char SERVER_HOST[] = "http://59.151.11.160";

// ͼ����֤������
const char CAPTCHA_URL_WEB[]   = "http://gcode.70yx.com/VerifyCode.aspx";	// "http://180.96.7.3/VerifyCode.aspx";
const char CAPTCHA_URL_LOCAL[] = "http://180.96.7.3/VerifyCode.aspx";

// �ؼ���������
const char WINDOW_SOFTKEY[]		= "LogOn_SoftKey";	// GameLogon.lua
const char WINDOW_PASSWORD[]	= "LogOn_PassWord";


#endif /* _GAME_DEFINE_H_ */
