#pragma once
#include "KLSelfAdaptationWindow.h"
#include "IKLInjuryInfoBoard.h"


namespace CEGUI
{
	namespace KLInjuryInfoBoardProperties
	{
		
		class StartPos: public Property	
		{
			public:
			StartPos() : Property(
				"StartPos",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class Speed: public Property	
		{
			public:
			Speed() : Property(
				"Speed",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class Acceleration: public Property	
		{
			public:
			Acceleration() : Property(
				"Acceleration",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class Angle: public Property
		{
			public:
			Angle() : Property(
				"Angle",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class InjuryLife: public Property	
		{
			public:
			InjuryLife() : Property(
				"InjuryLife",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class AlphaMode: public Property	
		{
			public:
			AlphaMode() : Property(
				"AlphaMode",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class ColorType:public Property
		{
			public:
			ColorType() : Property(
				"ColorType",
				"",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class Justle: public Property
		{
		public:
			Justle() : Property(
				"Justle",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class TextFormat: public Property
		{
		public:
			TextFormat() : Property(
				"TextFormat",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class InjurySize: public Property
		{
		public:
			InjurySize() : Property(
				"InjurySize",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class PointMove: public Property
		{
		public:
			PointMove() : Property(
				"PointMove",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class InjuryPic: public Property
		{
		public:
			InjuryPic() : Property(
				"InjuryPic",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class InjuryFollow: public Property
		{
		public:
			InjuryFollow() : Property(
				"InjuryFollow",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class EmissiveMode: public Property
		{
		public:
			EmissiveMode() : Property(
				"EmissiveMode",
				"",
				"0")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	};
	

	class KLInjuryInfoBoard :	public KLSelfAdaptationWindow, public IKLInjuryInfoBoard
	{
	public:
		static const utf8   WidgetTypeName[];       
	public:
		KLInjuryInfoBoard(const String& type, const String& name);
		~KLInjuryInfoBoard(void);
		
	
	protected:
		
		typedef std::map<String, ImageSet> ImageTypeMap;
		ImageTypeMap	m_mapImageType;

		typedef std::map<String, String> ImageTextMap;
		ImageTextMap	m_mapImageText;		

		int				m_nColorType;

		typedef std::vector<int> TextFormatVecter;
		TextFormatVecter m_vTextFormat;

		typedef std::vector<const Image*> ImageVector;
		ImageVector		m_vImage;

		bool			m_bTextChanged;

	public:
		virtual void	setColorType( int nColorType );
		virtual void	setDisplayCenter( float fX, float fY );
		virtual void	setTextScale( float fScaleX, float fScaleY);
		virtual void	setCharImage(int nColor, int nType, const std::string& strText, const ImageSet& imagetSet);
		virtual void	setTextFormat(const String& strText);

	protected:
		virtual void	populateRenderCache();

		const Image*	getCharImageByType(const String& strType);
		const Image*	getCharImageByType(int nColor, int nType);
		const Image*	getCharImageByText(int nColor, const String& strText);
		bool			isValidateUtf32(utf32 value);

		const char*		getImagetTypeKey(int nColor, int nType);
		const char*		getImagetTextKey(int nColor, const String& strText);

		void			setTextChanged(bool bChanged)	{ m_bTextChanged = bChanged; }
		void			CollectImage();
		void			updateImageSize();

		virtual void	updateSelfSize(void);
		virtual void	updateSelfPosition(void);
		virtual void	setText(const String& text);

	
	protected:		
		struct InjuryBaseData
		{
			uint			uDataFlag;
			int				nLeft;

			int				nXSpeedA;
			int				nYSpeedA;
			int				nXSpeedB;
			int				nYSpeedB;

			int				nXAccA;
			int				nYAccA;
			int				nXAccB;
			int				nYAccB;

			int				nAngleA;
			int				nAngleB;

			float			fBeginSize;
			float			fEndSize;

			int				nPointMoveX;
			int				nPointMoveY;

			int				nAlphaMode;

			InjuryBaseData();
			void SetDataFlag(INJURY_DATA_FLAG eFlag);
			bool isDataValid(INJURY_DATA_FLAG eFlag) const;
		};

		typedef std::vector<InjuryBaseData> InjuryBaseDataVecter;
		typedef std::map<int, int> ConfigIndexMap;

		struct InjuryConfigData
		{
			int				nType;
			int				nColorType;
			int				nXStartPosA;
			int				nXStartPosB;
			int				nYStartPosA;
			int				nYStartPosB;
			bool			bJustle;
			int				nJustleAddX;
			int				nJustleAddY;
			float			fjustleCutLife;
			bool			bEmissive;
			int				nFollowMode;
			String			strTextFormat;

			ConfigIndexMap	mapIndexMap;
			InjuryBaseDataVecter vBasedata;

			InjuryConfigData();
		};

		typedef std::vector<InjuryConfigData> InjuryConfigVector;
		InjuryConfigVector  m_vInjuryConfig;

		ConfigIndexMap		m_mapConfigIndex;

		typedef std::vector<InjuryPicInfo> InjuryPicInfoVector;
		InjuryPicInfoVector m_vInjuryPicInfo;

		

	public:
		virtual int		getTypeMaxNum() const;
		virtual int 	getDataType(int nIndex) const;
		virtual bool	isDataValid(int nIndex, int nPhase, INJURY_DATA_FLAG eFlag) const;
	
		virtual int 	getColorType(int nIndex) const;
		virtual int		getFollowMode(int nIndex) const;
		virtual bool	isEmissive(int nIndex) const;		

		virtual bool 	isJustle(int nIndex) const;
		virtual int		getJustleAddX(int nIndex) const;
		virtual int		getJustleAddY(int nIndex) const;
		virtual float	getJustleCutLife(int nIndex) const;


		virtual int 	getXStartA(int nIndex) const;
		virtual int 	getXStartB(int nIndex) const;
		virtual int 	getYStartA(int nIndex) const;
		virtual int 	getYStartB(int nIndex) const;

		virtual const String getTextFormat(int nIndex) const;

		virtual int		getRankMaxNum(int nIndex) const;
		virtual int 	getLife(int nIndex, int nPhase) const;

		virtual int 	getXSpeedA(int nIndex, int nPhase) const;
		virtual int 	getXSpeedB(int nIndex, int nPhase) const;
		virtual int 	getYSpeedA(int nIndex, int nPhase) const;
		virtual int 	getYSpeedB(int nIndex, int nPhase) const;

		virtual int 	getXAccelerationA(int nIndex, int nPhase) const;
		virtual int 	getXAccelerationB(int nIndex, int nPhase) const;
		virtual int 	getYAccelerationA(int nIndex, int nPhase) const;
		virtual int 	getYAccelerationB(int nIndex, int nPhase) const;		

		virtual int		getAngleA(int nIndex, int nPhase) const;
		virtual int		getAngleB(int nIndex, int nPhase) const;

		virtual float	getBeginSize(int nIndex, int nPhase) const;
		virtual float	getEndSize(int nIndex, int nPhase) const;

		virtual int		getPointMoveX(int nIndex, int nPhase) const;
		virtual int		getPointMoveY(int nIndex, int nPhase) const;

		virtual int		getAlphaMode(int nIndex, int nPhase) const;

		virtual int		getInjuryPicMaxNum() const;
		virtual const InjuryPicInfo* getInjuryPicInfo(int nIndex) const;


		void			setInjuryPic(int nColor, int nType, const char* pText, const char* pImageSet, const char* pImageName);
		void			setStartPos(int nType, int nX1, int nX2, int nY1, int nY2);
		void			setColorType(int nType, int nVal);
		void			setJustle(int nType, int nEnable, int nX, int nY, float fCutLife);
		void			setTextFormat(int nType, const char* pText);
		void			setFollow(int nType, int nVal);
		void			setEmissiveMode(int nType, int nVal);

		void			setSpeed(int nType, int nRank, int nX1, int nX2, int nY1, int nY2);
		void			setAcceleration(int nType, int nRank, int nX1, int nX2, int nY1, int nY2);
		void			setAngle(int nType, int nRank, int nVal1, int nVal2);
		void			setLife(int nType, int nRank, int nVal);
		void			setAlphaMode(int nType, int nRank, int nVal);
		void			setInjurySize(int nType, int nRank, float fBeginSize, float fEndSize);
		void			setPointMove(int nType, int nRank, int nX, int nY);

		InjuryConfigData*	getInjuryConfigData(int nType);
		InjuryBaseData*		getInjuryBaseConfigData(int nType, int nRank);

	private:		
		static KLInjuryInfoBoardProperties::AlphaMode		d_AlphaModeProperty;
		static KLInjuryInfoBoardProperties::ColorType		d_ColorTypeProperty;
		static KLInjuryInfoBoardProperties::Angle			d_AngleProperty;
		static KLInjuryInfoBoardProperties::StartPos		d_StartPosProperty;
		static KLInjuryInfoBoardProperties::Speed			d_SpeedProperty;
		static KLInjuryInfoBoardProperties::Acceleration	d_AccelerationProperty;
		static KLInjuryInfoBoardProperties::InjuryLife	d_InjuryLifeProperty;
		static KLInjuryInfoBoardProperties::Justle		d_JustleProperty;
		static KLInjuryInfoBoardProperties::TextFormat	d_DocFormatProperty;
		static KLInjuryInfoBoardProperties::InjurySize	d_InjurySizeProperty;
		static KLInjuryInfoBoardProperties::PointMove		d_PointMoveProperty;
		static KLInjuryInfoBoardProperties::InjuryPic		d_InjuryPicProperty;
		static KLInjuryInfoBoardProperties::InjuryFollow	d_InjuryFollowProperty;
		static KLInjuryInfoBoardProperties::EmissiveMode	d_EmissiveModeProperty;

	};

	class FALAGARDBASE_API KLInjuryInfoBoardFactory : public WindowFactory
    {
    public:
        KLInjuryInfoBoardFactory(void) : WindowFactory(KLInjuryInfoBoard::WidgetTypeName) { }
        ~KLInjuryInfoBoardFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}