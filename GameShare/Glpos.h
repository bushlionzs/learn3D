#pragma once

struct GLPos
{
	float	m_fX;
	float	m_fZ;

	GLPos (void)
	:
	m_fX(0.0f),
	m_fZ(0.0f)
	{
	}
	GLPos (float fX, float fZ)
	:
	m_fX(fX),
	m_fZ(fZ)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_fX = 0.0f;
		m_fZ = 0.0f;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GLPos &operator=(GLPos const &rhs)
	{
		m_fX = rhs.m_fX;
		m_fZ = rhs.m_fZ;
		return *this;
	}

	GLPos &operator=(const GLPos* rhs)
	{
		if (rhs)
		{
			m_fX = rhs->m_fX;
			m_fZ = rhs->m_fZ;
		}		
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(GLPos &Ref)
	{
		return(fabs(m_fX - Ref.m_fX) + fabs(m_fZ - Ref.m_fZ)) < 0.0001f;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL operator!=(GLPos &Ref)
	{
		return(fabs(m_fX - Ref.m_fX) + fabs(m_fZ - Ref.m_fZ)) >= 0.0001f;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const GLPos &Ref)
	{
		return(fabs(m_fX - Ref.m_fX) + fabs(m_fZ - Ref.m_fZ)) < 0.0001f;
	}

	static uint32_t	GetSize()
	{
		return sizeof(float) + sizeof(float) ;
	}

	static uint32_t GetMsgMaxSize()
	{
		return sizeof(float)*2;
	}

	

};

