#include "KLInjuryInfoBoard.h"
#include "CEGUIPropertyHelper.h"
namespace CEGUI
{
	const utf8 KLInjuryInfoBoard::WidgetTypeName[] = "Falagard/InjuryInfoBoard";
	
	KLInjuryInfoBoardProperties::AlphaMode			KLInjuryInfoBoard::d_AlphaModeProperty;
	KLInjuryInfoBoardProperties::ColorType			KLInjuryInfoBoard::d_ColorTypeProperty;	
	KLInjuryInfoBoardProperties::Angle				KLInjuryInfoBoard::d_AngleProperty;
	KLInjuryInfoBoardProperties::StartPos				KLInjuryInfoBoard::d_StartPosProperty;
	KLInjuryInfoBoardProperties::Speed				KLInjuryInfoBoard::d_SpeedProperty;
	KLInjuryInfoBoardProperties::Acceleration			KLInjuryInfoBoard::d_AccelerationProperty;
	KLInjuryInfoBoardProperties::InjuryLife			KLInjuryInfoBoard::d_InjuryLifeProperty;
	KLInjuryInfoBoardProperties::Justle				KLInjuryInfoBoard::d_JustleProperty;
	KLInjuryInfoBoardProperties::TextFormat			KLInjuryInfoBoard::d_DocFormatProperty;
	KLInjuryInfoBoardProperties::InjurySize			KLInjuryInfoBoard::d_InjurySizeProperty;
	KLInjuryInfoBoardProperties::PointMove			KLInjuryInfoBoard::d_PointMoveProperty;
	KLInjuryInfoBoardProperties::InjuryPic			KLInjuryInfoBoard::d_InjuryPicProperty;
	KLInjuryInfoBoardProperties::InjuryFollow			KLInjuryInfoBoard::d_InjuryFollowProperty;
	KLInjuryInfoBoardProperties::EmissiveMode			KLInjuryInfoBoard::d_EmissiveModeProperty;

	
	KLInjuryInfoBoard::KLInjuryInfoBoard(const String& type, const String& name) :
		KLSelfAdaptationWindow(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLInjuryInfoBoard )
			CEGUI_ADD_STATICPROPERTY( &d_AlphaModeProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_ColorTypeProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_AngleProperty );
			CEGUI_ADD_STATICPROPERTY( &d_StartPosProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_SpeedProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_AccelerationProperty );
			CEGUI_ADD_STATICPROPERTY( &d_InjuryLifeProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_JustleProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_DocFormatProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_InjurySizeProperty );
			CEGUI_ADD_STATICPROPERTY( &d_PointMoveProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_InjuryPicProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_InjuryFollowProperty  );
			CEGUI_ADD_STATICPROPERTY( &d_EmissiveModeProperty  );
		CEGUI_END_ADD_STATICPROPERTY

		m_nColorType = 0;
		m_bTextChanged = false;
	}
	
	KLInjuryInfoBoard::~KLInjuryInfoBoard(void)
	{
		m_vInjuryConfig.clear();
		m_vInjuryPicInfo.clear();
		m_mapImageType.clear();
		m_mapImageText.clear();
	}
	
	void KLInjuryInfoBoard::setTextScale( float fScaleX, float fScaleY)
	{
		setChangedSize(true);
		KLSimpleText::setTextScale( Size( fScaleX, fScaleY ) );
	}
	
	void KLInjuryInfoBoard::setDisplayCenter( float fX, float fY )
	{
		setCenter( Point( fX, fY ) );
	}
	
	void KLInjuryInfoBoard::setText( const String& text )
	{
		Window::setText(text);

		m_bSingleLine = true;
		m_ptCenter = Point(0, 0);
		m_fCurLife = 0;
		m_fMaxLife = m_fLife + m_fFadeInTime + m_fFadeOutTime;

		
		CollectImage();
		
		updateImageSize();
	}
	
	void KLInjuryInfoBoard::updateSelfPosition()
	{
		CEGUI::Point pos = m_ptCenter;
		switch( m_nFitType )
		{
		case SELF_FIT_LEFT:
			pos.d_y -= getAbsoluteHeight()/2.f;
			break;
		case SELF_FIT_RIGHT:
			pos.d_x -= getAbsoluteWidth();
			pos.d_y -= getAbsoluteHeight()/2;
			break;
		case SELF_FIT_TOP:
			pos.d_x -= getAbsoluteWidth() / 2;
			break;
		case SELF_FIT_BOTTOM:
			pos.d_x -= getAbsoluteWidth() / 2;
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_LEFTTOP:
			break;
		case SELF_FIT_LEFTBOTTOM:
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_RIGHTTOP:
			pos.d_x -= getAbsoluteWidth();
			break;
		case SELF_FIT_RIGHTBOTOM:
			pos.d_x -= getAbsoluteWidth();
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_CENTER:
			pos.d_x -= getAbsoluteWidth() / 2;
			pos.d_y -= getAbsoluteHeight() / 2;
			break;
		default:
			break;
		}

		static UVector2 position;
		position.d_x = cegui_absdim(PixelAligned(pos.d_x));
		position.d_y = cegui_absdim(PixelAligned(pos.d_y));
		d_area.setPosition(position);
	}
	
	bool KLInjuryInfoBoard::isValidateUtf32(utf32 value)
	{
		
		if( value >= 0x30 && value <= 0x39 )
			return true;
		return false;
	}
	
	void KLInjuryInfoBoard::updateSelfSize()
	{
	}
	
	void KLInjuryInfoBoard::updateImageSize()
	{
		if (m_vImage.empty())
		{
			setSize(Absolute, Size(0,0));
		}
		else
		{
			Size sizeScreen = System::getSingleton().getRenderer()->getSize();
			float vertScaling = sizeScreen.d_height / DefaultNativeVertRes;

			Size sz(0.f,0.f);
			for (int i=0; i<(int)m_vImage.size(); ++i)
			{
				const Image* pImage = m_vImage[i];
				if (NULL == pImage)
					continue;

				const Rect& imageArea = pImage->getSourceTextureArea();
				float fHeight = imageArea.getHeight() * vertScaling * d_fScaleY;
				float fWidth = imageArea.getWidth() * vertScaling * d_fScaleX;

				sz.d_width += fWidth;
				sz.d_height = fHeight;				
			}
			setSize(Absolute, sz);
		}
	}
	
	void KLInjuryInfoBoard::CollectImage()
	{
		m_vImage.clear();
		String strVal;

		
		for (int i=0; i<(int)m_vTextFormat.size(); ++i)
		{
			int nType = m_vTextFormat[i];
			
			if (0 <= nType)
			{				
				const Image* pImage = getCharImageByType(m_nColorType, nType);
				if (pImage)
				{
					m_vImage.push_back(pImage);
				}
			}
			
			else
			{
				for (size_t i=0; i<d_text.length(); ++i)
				{
					if (false == isValidateUtf32(d_text[i]))
						continue;

					strVal = d_text[i];
					const Image* pImage = getCharImageByText(m_nColorType, strVal);
					if (pImage)
					{
						m_vImage.push_back(pImage);
					}
				}
			}
		}
	}
	
	void KLInjuryInfoBoard::populateRenderCache()
	{
		
		if (m_changeSize)
		{
			setChangedSize(false);
			updateImageSize();
		}

		
		if (!m_vImage.empty())
		{
			float fTotalWidth = 0;
			for (size_t i=0; i<m_vImage.size(); ++i)
			{
				const Image* pImage = m_vImage[i];
				if (pImage)
				{
					fTotalWidth += pImage->getSourceTextureArea().getWidth();
				}
			}

			ColourRect final_cols(colour(1.0f,1.0f,1.0f, d_alpha));
			Rect wndArea(0, 0, getAbsoluteSize().d_width, getAbsoluteSize().d_height);
			float perWidth = wndArea.getWidth() / fTotalWidth;
			float curWidth = 0;			

			for (size_t i=0; i<m_vImage.size(); ++i)
			{
				const Image* pImage = m_vImage[i];
				if (pImage)
				{
					Rect rect = wndArea;
					rect.d_left = curWidth;
					curWidth += perWidth * pImage->getSourceTextureArea().getWidth();
					rect.d_right = curWidth;

					d_renderCache.cacheImage( *pImage, rect, 0, final_cols);
				}
			}
		}
	}
	
	const Image* KLInjuryInfoBoard::getCharImageByType(int nColor, int nType)
	{
		const char* szKey = getImagetTypeKey(nColor, nType);
		return getCharImageByType(szKey);
	}
	
	const Image* KLInjuryInfoBoard::getCharImageByType(const String& strType)
	{
		ImageTypeMap::iterator it = m_mapImageType.find(strType);
		if (it != m_mapImageType.end())
		{
			const ImageSet& info = it->second;
			return PropertyHelper::stringToImage(info.strSet, info.strName);
		}
		return NULL;
	}
	
	const Image* KLInjuryInfoBoard::getCharImageByText(int nColor, const String& strText)
	{
		const char* szTextKey = getImagetTextKey(nColor, strText);

		ImageTextMap::iterator it = m_mapImageText.find(szTextKey);
		if (it != m_mapImageText.end())
		{
			return getCharImageByType(it->second);
		}
		return NULL;
	}
	
	void KLInjuryInfoBoard::setCharImage(int nColor, int nType, const std::string& strText, const ImageSet& imagetSet)
	{
		const char* szKey = getImagetTypeKey(nColor, nType);
		m_mapImageType[szKey] = imagetSet;

		if (!strText.empty())
		{
			const char* szTextKey = getImagetTextKey(nColor, strText);
			m_mapImageText[szTextKey] = szKey;
		}
	}
	
	const char* KLInjuryInfoBoard::getImagetTypeKey(int nColor, int nType)
	{
		static char szTemp[64] = {0};
		sprintf(szTemp, "%d|%d", nColor, nType);
		return szTemp;
	}
	
	const char* KLInjuryInfoBoard::getImagetTextKey(int nColor, const String& strText)
	{
		static char szTemp[128] = {0};
		sprintf(szTemp, "%d|%s", nColor, strText.c_str());
		return szTemp;
	}
	
	void KLInjuryInfoBoard::setColorType( int nColorType )
	{
		m_nColorType = nColorType;
	}
	
	void KLInjuryInfoBoard::setTextFormat(const String& strText)
	{
		std::string strTextFormat = strText.c_str();
		m_vTextFormat.clear();

		const char splitKey = '|';
		std::string::size_type	sB = 0;
		std::string::size_type	sE = strTextFormat.find_first_of(splitKey);
		std::string::size_type	sLen = strTextFormat.size();
		std::string strValue;

		do
		{
			int nIndex = -1;
			bool bFind = false;

			if(sE != std::string::npos)
				bFind = true;

			strValue = strTextFormat.substr(sB, sE - sB);
			if ("d" == strValue)
				nIndex = -1;
			else
				nIndex = atoi(strValue.c_str());

			m_vTextFormat.push_back(nIndex);

			sE += 1;
			if(sE >= sLen)
				break;

			if (!bFind)
				break;

			sB = sE;
			sE = strTextFormat.find(splitKey, sB);
		} while(TRUE);
	}



	
	KLInjuryInfoBoard::InjuryConfigData* KLInjuryInfoBoard::getInjuryConfigData(int nType)
	{
		if (0 > nType)
			return NULL;

		ConfigIndexMap::iterator it = m_mapConfigIndex.find(nType);
		if (it != m_mapConfigIndex.end())
		{
			int nIndex = it->second;
			if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
			{
				return &m_vInjuryConfig[nIndex];
			}
		}
		else
		{
			InjuryConfigData data;
			data.nType = nType;
			m_vInjuryConfig.push_back(data);

			int nIndex = m_vInjuryConfig.size() - 1;
			m_mapConfigIndex[nType] = nIndex;

			return &m_vInjuryConfig[nIndex];
		}
		return NULL;
	}
	
	KLInjuryInfoBoard::InjuryBaseData* KLInjuryInfoBoard::getInjuryBaseConfigData(int nType, int nRank)
	{
		if (0 > nType || 0 > nRank)
			return NULL;

		InjuryConfigData* pConfigData = getInjuryConfigData(nType);
		if (NULL == pConfigData)
			return NULL;

		ConfigIndexMap::iterator it = pConfigData->mapIndexMap.find(nRank);
		if (it != pConfigData->mapIndexMap.end())
		{
			int nIndex = it->second;
			if (0 <= nIndex && nIndex < (int)pConfigData->vBasedata.size())
			{
				return &pConfigData->vBasedata[nIndex];
			}
		}
		else
		{
			pConfigData->vBasedata.push_back(InjuryBaseData());

			int nIndex = pConfigData->vBasedata.size();
			--nIndex;
			pConfigData->mapIndexMap[nRank] = nIndex;

			return &pConfigData->vBasedata[nIndex];			
		}
		return NULL;
	}

	
	void KLInjuryInfoBoard::setInjuryPic(int nColor, int nType, const char* pText, const char* pImageSet, const char* pImageName)
	{
		InjuryPicInfo info;
		info.nColor		= nColor;
		info.nType		= nType;
		info.strText	= pText;
		info.imagetSet.strSet	= pImageSet;
		info.imagetSet.strName	= pImageName;
		m_vInjuryPicInfo.push_back(info);
	}
	
	void KLInjuryInfoBoard::setStartPos(int nType, int nX1, int nX2, int nY1, int nY2)
	{
		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->nXStartPosA = nX1;
			pData->nXStartPosB = nX2;
			pData->nYStartPosA = nY1;
			pData->nYStartPosB = nY2;
		}
	}

	
	void KLInjuryInfoBoard::setColorType(int nType, int nVal)
	{
		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->nColorType = nVal;
		}
	}

	
	void KLInjuryInfoBoard::setJustle(int nType, int nEnable, int nX, int nY, float fCutLife)
	{
		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->bJustle			= 1 == nEnable;
			pData->nJustleAddX		= nX;
			pData->nJustleAddY		= nY;
			pData->fjustleCutLife	= fCutLife;
		}
	}

	
	void KLInjuryInfoBoard::setTextFormat(int nType, const char* pText)
	{
		if (NULL == pText)
			return;

		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->strTextFormat = pText;
		}
	}
	
	void KLInjuryInfoBoard::setFollow(int nType, int nVal)
	{
		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->nFollowMode = nVal;
		}
	}
	
	void KLInjuryInfoBoard::setEmissiveMode(int nType, int nVal)
	{
		InjuryConfigData* pData = getInjuryConfigData(nType);
		if (pData)
		{
			pData->bEmissive = 1 == nVal;
		}
	}

	
	void KLInjuryInfoBoard::setSpeed(int nType, int nRank, int nX1, int nX2, int nY1, int nY2)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nXSpeedA = nX1;
			pData->nXSpeedB = nX2;
			pData->nYSpeedA = nY1;
			pData->nYSpeedB = nY2;
			pData->SetDataFlag(IDF_SPEED);
		}
	}

	
	void KLInjuryInfoBoard::setAcceleration(int nType, int nRank, int nX1, int nX2, int nY1, int nY2)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nXAccA = nX1;
			pData->nXAccB = nX2;
			pData->nYAccA = nY1;
			pData->nYAccB = nY2;
			pData->SetDataFlag(IDF_ACC);
		}
	}

	
	void KLInjuryInfoBoard::setAngle(int nType, int nRank, int nVal1, int nVal2)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nAngleA = nVal1;
			pData->nAngleB = nVal2;
			pData->SetDataFlag(IDF_ANGLE);
		}
	}

	
	void KLInjuryInfoBoard::setLife(int nType, int nRank, int nVal)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nLeft = nVal;
			pData->SetDataFlag(IDF_LIFE);
		}
	}
	
	void KLInjuryInfoBoard::setAlphaMode(int nType, int nRank, int nVal)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nAlphaMode = nVal;
			pData->SetDataFlag(IDF_ALPHAMODE);
		}
	}

	
	void KLInjuryInfoBoard::setInjurySize(int nType, int nRank, float fBeginSize, float fEndSize)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->fBeginSize = fBeginSize;
			pData->fEndSize = fEndSize;
			pData->SetDataFlag(IDF_SIZE);
		}
	}

	
	void KLInjuryInfoBoard::setPointMove(int nType, int nRank, int nX, int nY)
	{
		if (0 > nRank)
			return;

		InjuryBaseData* pData = getInjuryBaseConfigData(nType, nRank);
		if (pData)
		{
			pData->nPointMoveX = nX;
			pData->nPointMoveY = nY;
			pData->SetDataFlag(IDF_POINTMOVE);
		}
	}


	
	int KLInjuryInfoBoard::getTypeMaxNum() const
	{
		return (int)m_vInjuryConfig.size();
	}
	
	int KLInjuryInfoBoard::getRankMaxNum(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return (int)m_vInjuryConfig[nIndex].vBasedata.size();
		}
		return 0;
	}
	
	int KLInjuryInfoBoard::getDataType(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nType;
		}
		return -1;
	}
	
	int KLInjuryInfoBoard::getColorType(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nColorType;
		}
		return -1;
	}
	
	bool KLInjuryInfoBoard::isJustle(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].bJustle;
		}
		return false;
	}
	
	int KLInjuryInfoBoard::getJustleAddX(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nJustleAddX;
		}
		return 0;
	}
	
	int KLInjuryInfoBoard::getJustleAddY(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nJustleAddY;
		}
		return 0;
	}
	
	float KLInjuryInfoBoard::getJustleCutLife(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].fjustleCutLife;
		}
		return 0.f;
	}
	
	bool KLInjuryInfoBoard::isEmissive(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].bEmissive;
		}
		return false;
	}
	
	int KLInjuryInfoBoard::getFollowMode(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nFollowMode;
		}
		return 0;	
	}
	
	int KLInjuryInfoBoard::getXStartA(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nXStartPosA;
		}
		return 0;
	}
	
	int KLInjuryInfoBoard::getXStartB(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nXStartPosB;
		}
		return 0;
	}
	
	int KLInjuryInfoBoard::getYStartA(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nYStartPosA;
		}
		return 0;
	}
	
	int KLInjuryInfoBoard::getYStartB(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].nYStartPosB;
		}
		return 0;
	}
	
	const String KLInjuryInfoBoard::getTextFormat(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryConfig.size())
		{
			return m_vInjuryConfig[nIndex].strTextFormat;
		}
		return "";
	}
	
	bool KLInjuryInfoBoard::isDataValid(int nIndex, int nPhase, INJURY_DATA_FLAG eFlag) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return false;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return false;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].isDataValid(eFlag);
	}
	
	int KLInjuryInfoBoard::getLife(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nLeft;
	}
	
	int KLInjuryInfoBoard::getXSpeedA(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nXSpeedA;
	}
	
	int KLInjuryInfoBoard::getXSpeedB(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nXSpeedB;
	}
	
	int KLInjuryInfoBoard::getYSpeedA(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nYSpeedA;
	}
	
	int KLInjuryInfoBoard::getYSpeedB(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nYSpeedB;
	}

	
	int KLInjuryInfoBoard::getXAccelerationA(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nXAccA;
	}
	
	int KLInjuryInfoBoard::getXAccelerationB(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nXAccB;
	}
	
	int KLInjuryInfoBoard::getYAccelerationA(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nYAccA;
	}
	
	int KLInjuryInfoBoard::getYAccelerationB(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nYAccB;
	}

	
	int KLInjuryInfoBoard::getAngleA(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nAngleA;
	}
	
	int KLInjuryInfoBoard::getAngleB(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nAngleB;
	}

	
	float KLInjuryInfoBoard::getBeginSize(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 1;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 1;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].fBeginSize;
	}
	
	float KLInjuryInfoBoard::getEndSize(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 1;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 1;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].fEndSize;
	}

	
	int KLInjuryInfoBoard::getPointMoveX(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nPointMoveX;
	}
	
	int KLInjuryInfoBoard::getPointMoveY(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nPointMoveY;
	}

	
	int KLInjuryInfoBoard::getAlphaMode(int nIndex, int nPhase) const
	{
		if (0 > nIndex || nIndex >= (int)m_vInjuryConfig.size())
			return 0;
		if (0 > nPhase || nPhase >= (int)m_vInjuryConfig[nIndex].vBasedata.size())
			return 0;

		return  m_vInjuryConfig[nIndex].vBasedata[nPhase].nAlphaMode;
	}
	
	int KLInjuryInfoBoard::getInjuryPicMaxNum() const
	{
		return (int)m_vInjuryPicInfo.size();
	}

	
	const InjuryPicInfo* KLInjuryInfoBoard::getInjuryPicInfo(int nIndex) const
	{
		if (0 <= nIndex && nIndex < (int)m_vInjuryPicInfo.size())
		{
			return &m_vInjuryPicInfo[nIndex];
		}
		return NULL;
	}




namespace KLInjuryInfoBoardProperties
{

	
	String StartPos::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void StartPos::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int	nXa = 0;
		int nXb = 0;
		int nYa = 0;
		int nYb = 0;
		sscanf(value.c_str(), "type:%d xA:%d xB:%d yA:%d yB:%d", &nType, &nXa, &nXb, &nYa, &nYb);
		static_cast<KLInjuryInfoBoard*>(receiver)->setStartPos( nType, nXa, nXb, nYa, nYb );
	}
	
	String Speed::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void Speed::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = -1;
		int nRank = 0;
		int	nXa = 0;
		int nXb = 0;
		int nYa = 0;
		int nYb = 0;
		sscanf( value.c_str(), "type:%d rank:%d xA:%d xB:%d yA:%d yB:%d", &nType, &nRank, &nXa, &nXb, &nYa, &nYb);
		static_cast<KLInjuryInfoBoard*>(receiver)->setSpeed( nType, nRank, nXa, nXb, nYa, nYb );
	}
	
	String Acceleration::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void Acceleration::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = -1;
		int nRank = 0;
		int	nXa = 0;
		int nXb = 0;
		int nYa = 0;
		int nYb = 0;
		sscanf( value.c_str(), "type:%d rank:%d xA:%d xB:%d yA:%d yB:%d", &nType, &nRank, &nXa, &nXb, &nYa, &nYb);
		static_cast<KLInjuryInfoBoard*>(receiver)->setAcceleration( nType, nRank, nXa, nXb, nYa, nYb );
	}
	
	String Angle::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void Angle::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int nRank = 0;
		int	nVal1 = 0;
		int nVal2 = 0;
		sscanf( value.c_str(), "type:%d rank:%d valueA:%d valueB:%d", &nType, &nRank, &nVal1, &nVal2);
		static_cast<KLInjuryInfoBoard*>(receiver)->setAngle( nType, nRank, nVal1, nVal2 );
	}
	
	String InjuryLife::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void InjuryLife::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int nRank = 0;
		int	nVal = 0;
		sscanf( value.c_str(), "type:%d rank:%d value:%d", &nType, &nRank, &nVal);
		static_cast<KLInjuryInfoBoard*>(receiver)->setLife( nType, nRank, nVal );
	}
	
	String AlphaMode::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void AlphaMode::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int nRank = 0;
		int	nMode = 0;
		int nTime = 0;
		sscanf( value.c_str(), "type:%d rank:%d value:%d ", &nType, &nRank, &nMode);
		static_cast<KLInjuryInfoBoard*>(receiver)->setAlphaMode( nType, nRank, nMode );
	}
	
	String ColorType::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void ColorType::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int	nVal = 0;
		sscanf( value.c_str(), "type:%d value:%d", &nType, &nVal);
		static_cast<KLInjuryInfoBoard*>(receiver)->setColorType( nType, nVal );
	}
	
	String Justle::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void Justle::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int nEnable = 0;
		int	nX = 0;
		int nY = 0;
		float fCutLift = 0.f;

		sscanf( value.c_str(), "type:%d enable:%d x:%d y:%d cutLife:%f", &nType, &nEnable, &nX, &nY, &fCutLift);
		static_cast<KLInjuryInfoBoard*>(receiver)->setJustle( nType, nEnable, nX, nY, fCutLift );
	}

	
	String InjuryPic::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void InjuryPic::set(PropertyReceiver* receiver, const String& value)
	{
		int  nColor	= 0;
		int  nType  = 0;
		char szText[256] = "\0";
		char szImageSet[256] = "\0";
		char szImageName[256] = "\0";
		sscanf(value.c_str(), "color:%d type:%d text:%s pic=set:%s image:%s", &nColor, &nType, szText, szImageSet, szImageName);
		static_cast<KLInjuryInfoBoard*>(receiver)->setInjuryPic( nColor, nType, szText, szImageSet, szImageName );
	}

	
	String TextFormat::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void TextFormat::set(PropertyReceiver* receiver, const String& value)
	{
		int  nType  = 0;
		char szText[256] = "\0";
		sscanf(value.c_str(), "type:%d format:%s", &nType, szText);
		static_cast<KLInjuryInfoBoard*>(receiver)->setTextFormat( nType, szText );
	}

	
	String InjurySize::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void InjurySize::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int	nRank = 0;
		float fVal1 = 1.f;
		float fVal2 = 1.f;
		sscanf(value.c_str(), "type:%d rank:%d beginSize:%f endSize:%f", &nType, &nRank, &fVal1, &fVal2);
		static_cast<KLInjuryInfoBoard*>(receiver)->setInjurySize( nType, nRank, fVal1, fVal2 );
	}

	
	String PointMove::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void PointMove::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int	nRank = 0;
		int nX = 0;
		int nY = 0;
		sscanf(value.c_str(), "type:%d rank:%d x:%d y:%d", &nType, &nRank, &nX, &nY);
		static_cast<KLInjuryInfoBoard*>(receiver)->setPointMove( nType, nRank, nX, nY );
	}
	
	String InjuryFollow::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void InjuryFollow::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int val = 0;
		sscanf(value.c_str(), "type:%d value:%d", &nType, &val);
		static_cast<KLInjuryInfoBoard*>(receiver)->setFollow( nType, val );
	}
	
	String EmissiveMode::get(const PropertyReceiver* receiver) const
	{
		return "";
	}

	void EmissiveMode::set(PropertyReceiver* receiver, const String& value)
	{
		int nType = 0;
		int val = 0;
		sscanf(value.c_str(), "type:%d value:%d", &nType, &val);
		static_cast<KLInjuryInfoBoard*>(receiver)->setEmissiveMode( nType, val );
	}
};


	KLInjuryInfoBoard::InjuryBaseData::InjuryBaseData()
	{
		uDataFlag	= 0;
		nLeft		= 0;
		nXSpeedA	= 0;
		nYSpeedA	= 0;
		nXSpeedB	= 0;
		nYSpeedB	= 0;
		nXAccA		= 0;
		nYAccA		= 0;
		nXAccB		= 0;
		nYAccB		= 0;
		nAngleA		= 0;
		nAngleB		= 0;
		fBeginSize	= 1;
		fEndSize	= 1;
		nPointMoveX	= 0;
		nPointMoveY	= 0;
		nAlphaMode	= 0;
	}

	void KLInjuryInfoBoard::InjuryBaseData::SetDataFlag(INJURY_DATA_FLAG eFlag)
	{
		uDataFlag |= (1 << eFlag);
	}

	bool KLInjuryInfoBoard::InjuryBaseData::isDataValid(INJURY_DATA_FLAG eFlag) const
	{
		if (uDataFlag & (1 << eFlag))
			return true;
		return false;
	}

	KLInjuryInfoBoard::InjuryConfigData::InjuryConfigData()
	{
		nType			= -1;
		nColorType		= 0;
		nXStartPosA		= 0;
		nXStartPosB		= 0;
		nYStartPosA		= 0;
		nYStartPosB		= 0;
		bJustle			= false;
		nJustleAddX 	= 0;
		nJustleAddY 	= 0;
		fjustleCutLife	= 0.f;
		bEmissive		= false;
		nFollowMode		= 0;
	}



    Window* KLInjuryInfoBoardFactory::createWindow(const String& name)
    {
        return new KLInjuryInfoBoard(d_type, name);
    }

    void KLInjuryInfoBoardFactory::destroyWindow(Window* window)
    {
		delete window;
    }
};