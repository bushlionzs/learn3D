#ifndef SplitStringBase_h__
#define SplitStringBase_h__

class	SplitStringBase
{
public:
	enum
	{
		MAX_FINAL_STRING_LENGTH = 11,
		MAX_SPLIT_STRING_LENGTH = 64,
		MAX_LEVEL_ONE_LENGTH	= 200,
		MAX_LEVEL_TWO_LENGTH	= MAX_LEVEL_ONE_LENGTH,
		MAX_INPUT_STRING_LENGTH = MAX_LEVEL_ONE_LENGTH *MAX_SPLIT_STRING_LENGTH
	};

	SplitStringBase(void);
	virtual~SplitStringBase(void);

	virtual const SplitStringBase *GetChild();

	virtual void Reset();

	virtual void Init(char cSplit, SplitStringBase *pChild);

	virtual bool DoSplit(const char *strSplit) = 0;

	virtual int32_t GetResultLineCount();

	virtual const char *GetResultLine(int32_t iLine);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	bool	DoSubSplit();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	SplitStringBase *m_pChild;
	char		m_SplitChar[2];
	char		m_strSplitLevelOne[MAX_LEVEL_ONE_LENGTH][MAX_SPLIT_STRING_LENGTH];
	int32_t		m_iLevelOneLineCount;
};
#endif
