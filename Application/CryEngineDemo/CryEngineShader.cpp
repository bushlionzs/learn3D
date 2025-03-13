#include "stdafx.h"
#include "CryEngineShader.h"

void RenderShaderResources::SetShaderParams(struct SInputShaderResources* pDst, IShader* pSH)
{
    mTextureNames.resize(EFTT_MAX);
    for (uint32_t i = 0; i < EFTT_MAX; i++)
    {
        mTextureNames[i] = pDst->m_Textures[i].m_Name;
    }
}