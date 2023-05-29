#pragma once

#include "OgreHardwareVertexBuffer.h"

class VertexDeclaration
{
public:
    typedef std::list<VertexElement> VertexElementList;
public:
    VertexDeclaration();
    ~VertexDeclaration();

    const VertexElement& addElement(int16_t source, int16_t index, int32_t offset, VertexElementType theType,
        VertexElementSemantic semantic);

    const VertexElementList& getElementList();

    int32_t getVertexSize(int32_t source);

    void removeAllElements();
    const VertexElement* findElementBySemantic(
        VertexElementSemantic sem, unsigned short index = 0);

protected:
    VertexElementList mElementList;
};