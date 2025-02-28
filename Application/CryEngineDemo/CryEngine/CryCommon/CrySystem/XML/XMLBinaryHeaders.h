// Copyright 2006-2021 Crytek GmbH / Crytek Group. All rights reserved.

// Created by: Michael Smith
//---------------------------------------------------------------------------
#ifndef __XMLBINARYHEADERS_H__
#define __XMLBINARYHEADERS_H__

namespace XMLBinary
{
class IFilter
{
public:
	enum EType
	{
		eType_ElementName,
		eType_AttributeName
	};
	virtual ~IFilter() {}
	virtual bool IsAccepted(EType type, const char* pName) const = 0;
};

//////////////////////////////////////////////////////////////////////////
typedef uint32_t NodeIndex;              //!< Only uint32 or uint16 are supported.

template<int size> struct Pad
{
	char pad[size];
};
template<> struct Pad<0> {};

struct Node
{
	uint32_t    nTagStringOffset;        //!< Offset in CBinaryXmlData::pStringData.
	uint32_t    nContentStringOffset;    //!< Offset in CBinaryXmlData::pStringData.
	uint16_t    nAttributeCount;
	uint16_t    nChildCount;
	NodeIndex nParentIndex;
	NodeIndex nFirstAttributeIndex;
	NodeIndex nFirstChildIndex;
	Pad<sizeof(uint32_t) - sizeof(NodeIndex)> reserved_for_alignment;
};

struct Attribute
{
	uint32_t nKeyStringOffset;           //!< Offset in CBinaryXmlData::pStringData.
	uint32_t nValueStringOffset;         //!< Offset in CBinaryXmlData::pStringData.
};

struct BinaryFileHeader
{
	char   szSignature[8];
	uint32_t nXMLSize;
	uint32_t nNodeTablePosition;
	uint32_t nNodeCount;
	uint32_t nAttributeTablePosition;
	uint32_t nAttributeCount;
	uint32_t nChildTablePosition;
	uint32_t nChildCount;
	uint32_t nStringDataPosition;
	uint32_t nStringDataSize;
};
}

#endif //__XMLBINARYHEADERS_H__
