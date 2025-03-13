#pragma once
#include <Cry3DEngine/I3DEngine.h>
class RenderShader : public IShader
{
public:
	friend class CRenderer;
	RenderShader(const char* name)
	{
		mName = name;
	}
	virtual int                        GetID() { return 0; }
	virtual int                        AddRef() { return 0; }
	virtual int                        Release() { return 0; }
	virtual int                        ReleaseForce() { return 0; }

	virtual const char* GetName()
	{
		return mName.c_str();
	}

	virtual const char* GetName() const
	{
		return mName.c_str();
	}

	virtual int                        GetFlags() const
	{
		return 0;
	}

	virtual int                        GetFlags2() const
	{
		return 0;
	}

	virtual void                       SetFlags2(int Flags)
	{
		
	}

	virtual void                       ClearFlags2(int Flags)
	{

	}
	virtual bool                       Reload(int nFlags, const char* szShaderName)
	{
		return true;
	}
	virtual TArray<CRenderElement*>* GetREs(int nTech)
	{
		return nullptr;
	}
	virtual DynArrayRef<SShaderParam>& GetPublicParams()
	{
		static DynArrayRef<SShaderParam> aa;
		return aa;
	}
	virtual void                       CopyPublicParamsTo(SInputShaderResources& copyToResource)
	{

	}

	virtual int                        GetTexId()
	{
		return 0;
	}
	virtual ITexture* GetBaseTexture(int* nPass, int* nTU)
	{
		return nullptr;
	}
	virtual unsigned int               GetUsedTextureTypes(void)
	{
		return 0;
	}
	virtual SShaderTexSlots* GetUsedTextureSlots(int nTechnique)
	{
		return nullptr;
	}
	virtual ECull                      GetCull(void)
	{
		return eCULL_None;
	}
	virtual int                        Size(int Flags)
	{
		return 0;
	}
	virtual uint64                     GetGenerationMask()
	{
		return 0;
	}

	virtual SShaderGen* GetGenerationParams()
	{
		return nullptr;
	}

	virtual int                        GetTechniqueID(int nTechnique, int nRegisteredTechnique)
	{
		return 0;
	}

	virtual InputLayoutHandle          GetVertexFormat(void)
	{
		InputLayoutHandle aa;
		return aa;
	}

	virtual EShaderType                GetShaderType()
	{
		return eST_General;
	}

	virtual EVertexModifier            GetVertexModificator()
	{
		EVertexModifier aa;
		return aa;
	}

	virtual void                       GetMemoryUsage(ICrySizer* pSizer) const
	{

	}
private:
	std::string mName;
};

class RenderShaderResources : public IRenderShaderResources
{
public:
	virtual void AddRef() const {}
	virtual void UpdateConstants(IShader* pSH) {}
	virtual void CloneConstants(const IRenderShaderResources* pSrc) {}

	// properties
	virtual void          ToInputLM(CInputLightMaterial& lm) {}
	virtual void          SetInputLM(const CInputLightMaterial& lm) {}

	virtual const ColorF& GetColorValue(EEfResTextures slot) const
	{
		static ColorF dummy;
		return dummy;
	}
	virtual void          SetColorValue(EEfResTextures slot, const ColorF& color) {}

	virtual float         GetStrengthValue(EEfResTextures slot) const { return 0.0f; }
	virtual void          SetStrengthValue(EEfResTextures slot, float value) {}

	// configs
	virtual const float& GetAlphaRef() const 
	{ 
		static float f;
		return f; 
	}
	virtual void                       SetAlphaRef(float v) {}

	virtual int                        GetResFlags() { return 0; }
	virtual void                       SetMtlLayerNoDrawFlags(uint8 nFlags) {}
	virtual uint8                      GetMtlLayerNoDrawFlags() const { return 0; }
	virtual CCamera* GetCamera() { return nullptr; }
	virtual void                       SetCamera(CCamera* pCam) {}
	virtual void                       SetMaterialName(const char* szName) {}
	virtual SEfResTexture* GetTexture(int nSlot) const
	{
		return nullptr;
	}
	virtual DynArrayRef<SShaderParam>& GetParameters()
	{
		static DynArrayRef<SShaderParam> dummy;
		return dummy;
	}

	virtual ColorF                     GetFinalEmittance()
	{
		return ColorF();
	}
	virtual float                      GetVoxelCoverage() { return 0.0f; }

	virtual void                    Release() const {}
	virtual void                    ConvertToInputResource(struct SInputShaderResources* pDst) {}
	virtual IRenderShaderResources* Clone() const
	{
		return nullptr;
	}

	virtual void SetShaderParams(struct SInputShaderResources* pDst, IShader* pSH);
	virtual size_t                  GetResourceMemoryUsage(ICrySizer* pSizer)
	{
		return 0;
	}

	virtual SDetailDecalInfo* GetDetailDecalInfo()
	{
		return nullptr;
	}

	// Set this shader resources as invalid
	virtual void SetInvalid() {}
	// Check if shader resource is valid
	virtual bool IsValid()
	{
		return true;
	}

	virtual void GetMemoryUsage(ICrySizer* pSizer) const {}

	std::vector<std::string>& getTextureNames()
	{
		return mTextureNames;
	}

	void setDiffuse(ColorF& diffuse)
	{
		mDiffuse = diffuse;
	}

	ColorF& getDiffuse()
	{
		return mDiffuse;
	}
private:
	std::vector<std::string> mTextureNames;

	ColorF mDiffuse;
};