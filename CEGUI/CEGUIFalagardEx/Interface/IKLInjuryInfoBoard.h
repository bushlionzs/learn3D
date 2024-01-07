#pragma once
#include "CEGUIVector.h"
#include "CEGUIString.h"

namespace CEGUI
{
	
	enum INJURY_DATA_FLAG
	{
		IDF_LIFE = 0,
		IDF_SPEED,
		IDF_ACC,
		IDF_ALPHAMODE,
		IDF_ANGLE,
		IDF_SIZE,
		IDF_POINTMOVE,

		IDF_MAXNUM,
	};
	struct ImageSet
	{
		std::string strSet;
		std::string strName;
	};
	struct InjuryPicInfo
	{
		int			nColor;
		int			nType;
		std::string	strText;
		ImageSet	imagetSet;
	};

	class IKLInjuryInfoBoard
	{
	public:

		virtual void	setColorType( int nType ) = 0;
		virtual void	setDisplayCenter( float fX, float fY ) = 0;
		virtual void	setTextScale( float fScaleX, float fScaleY) = 0;
		virtual void	setCharImage(int nColor, int nType, const std::string& strText, const ImageSet& imagetSet) = 0;
		virtual void	setTextFormat(const String& strText) = 0;
		
		virtual int		getTypeMaxNum() const = 0;
		virtual bool	isDataValid(int nIndex, int nPhase, INJURY_DATA_FLAG eFlag) const = 0;
		virtual int 	getDataType(int nIndex) const = 0;

		virtual int 	getColorType(int nIndex) const = 0;
		virtual int		getFollowMode(int nIndex) const = 0;
		virtual bool	isEmissive(int nIndex) const = 0;

		virtual bool 	isJustle(int nIndex) const = 0;
		virtual int		getJustleAddX(int nIndex) const = 0;
		virtual int		getJustleAddY(int nIndex) const = 0;
		virtual float	getJustleCutLife(int nIndex) const = 0;

		virtual int 	getXStartA(int nIndex) const = 0;
		virtual int 	getXStartB(int nIndex) const = 0;
		virtual int 	getYStartA(int nIndex) const = 0;
		virtual int 	getYStartB(int nIndex) const = 0;

		virtual const String getTextFormat(int nIndex) const = 0;

		virtual int		getRankMaxNum(int nIndex) const = 0;
		virtual int 	getLife(int nIndex, int nPhase) const = 0;

		virtual int 	getXSpeedA(int nIndex, int nPhase) const = 0;
		virtual int 	getXSpeedB(int nIndex, int nPhase) const = 0;
		virtual int 	getYSpeedA(int nIndex, int nPhase) const = 0;
		virtual int 	getYSpeedB(int nIndex, int nPhase) const = 0;

		virtual int 	getXAccelerationA(int nIndex, int nPhase) const = 0;
		virtual int 	getXAccelerationB(int nIndex, int nPhase) const = 0;
		virtual int 	getYAccelerationA(int nIndex, int nPhase) const = 0;
		virtual int 	getYAccelerationB(int nIndex, int nPhase) const = 0;

		virtual int		getAngleA(int nIndex, int nPhase) const = 0;
		virtual int		getAngleB(int nIndex, int nPhase) const = 0;

		virtual float	getBeginSize(int nIndex, int nPhase) const = 0;
		virtual float	getEndSize(int nIndex, int nPhase) const = 0;

		virtual int		getPointMoveX(int nIndex, int nPhase) const = 0;
		virtual int		getPointMoveY(int nIndex, int nPhase) const = 0;

		virtual int		getAlphaMode(int nIndex, int nPhase) const = 0;

		virtual int		getInjuryPicMaxNum() const = 0;
		virtual const InjuryPicInfo* getInjuryPicInfo(int nIndex) const = 0;
	};

}