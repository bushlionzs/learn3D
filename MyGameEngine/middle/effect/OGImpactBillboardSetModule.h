#ifndef OGImpactBillboardSetModule_h__
#define OGImpactBillboardSetModule_h__


#include "OGImpactModule.h"

// ogre header
#include <OgreColourValue.h>

namespace Ogre	{
	class BillboardSet;
}

namespace Orphigine	
{	

	class _OrphigineExport ImpactBillboardSetModule : public ImpactModule
	{
	public:

		typedef Ogre::Vector3 ScaleValue;

		enum { MAX_STAGES = 3 };

		// ��������
		class CmdBillboardColour : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdBillboardAlpha : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdBillboardCount : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBillboardMaterial : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBillboardInterval : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBillboardWidth : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBillboardHeight : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBillboardScale : public Ogre::ParamCommand
		{
		public:
			size_t		mIndex;

		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdScaleIntervalTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdStacks : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdSlices : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdTexIntervalTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		/////////////////////////////////////////////////////////////
		ImpactBillboardSetModule(const String &type);
		~ImpactBillboardSetModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance( Real time, TransformInfo &info );
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		//////////////////////////////////////////////////////////////////////////
		void setBillboardColour(const Ogre::ColourValue &colour);
		const Ogre::ColourValue& getBillboardColour(void) const
		{
			return mBillboardColour;
		}

		void setBillboardScale(size_t index, const ScaleValue& scale);
		const ScaleValue& getBillboardScale(size_t index) const
		{
			return mBillboardScale[index];
		}

		void setScaleIntervalTime(Real time)
		{
			mScaleIntervalTime = time;
		}
		Real getScaleIntervalTime(void) const
		{
			return mScaleIntervalTime;
		}

		void setBillboardCount(int count);
		int getBillboardCount(void) const
		{
			return mBillboardCount;
		}

		void setBillboardMaterial(const String &material);
		String getBillboardMaterial(void) const
		{
			return mBillboardMaterial;
		}

		void setBillboardInterval(Real interval);
		Real getBillboardInterval(void) const
		{
			return mBillboardInterval;
		}

		void setBillboardWidth(Real width);
		Real getBillboardWidth(void) const
		{
			return mBillboardWidth;
		}

		void setBillboardHeight(Real height);
		Real getBillboardHeight(void) const
		{
			return mBillboardHeight;
		}

		void setBillboardAlpha(Real alpha)
		{
			mAlphaValue = alpha;
			mColourChanged = true;
		}
		Real getBillboardAlpha(void) const
		{
			return mAlphaValue;
		}

		/** sets of the stacks of texture coordinates */
		void setStacks(ulong stacks);
		ulong getStacks(void) const
		{
			return mStacks;
		}

		/** sets of the slices of texture coordinates */
		void setSlices(ulong slices);
		ulong getSlices(void) const
		{
			return mSlices;
		}

		void setTexIntervalTime(Real time)
		{
			mTexIntervalTime = time;
		}
		Real getTexIntervalTime(void) const
		{
			return mTexIntervalTime;
		}

		/// ����visible flag
		virtual void setVisibleFlag(uint32 flags);

	protected:

		bool _createBillboardSet(void);
		void _destroyBillboardSet(void);

		/** �����������е�billboard����ʼtexture index
		@remarks    ���stacks��slices�����˱仯����ô�͵������������ǵ���ʼtexture index
		*/
		void _resetBillboardStartTexIndex(void);

		void _resetBillboardStartScaleTime(void);

	protected:

		/// ����ЧԪ�����õ�billboard set
		Ogre::BillboardSet *mBillboardSet;
		/// ����billboard����ɫ
		Ogre::ColourValue	mBillboardColour;
		/// billboard�ĸ���
		int					mBillboardCount;
		/// billboard���õĲ�������
		String				mBillboardMaterial;
		/// ����billboard���ĵ�֮��ļ��
		Real				mBillboardInterval;
		/// billboard�Ŀ��
		Real				mBillboardWidth;
		/// billboard�ĸ߶�
		Real				mBillboardHeight;

		ScaleValue			mBillboardScale[MAX_STAGES];
		/// ��С�任�ļ��ʱ��
		Real				mScaleIntervalTime;
		/// ����billboard������ͬ�����ţ���������ṹ���ڱ���ÿ��billboard����Ϣ
		struct _CurrentScaleInfo
		{
			Real mCurrentScaleIntervalTime;
			int mCurrentIndex;
		};
		std::vector<_CurrentScaleInfo> mCurrentScaleInfos;

		/// ��ʾ��ɫ�Ƿ���Ҫ�������õı�־
		bool				mSizeChanged;

		/** billboard���õ�alphaֵ
		@remarks ����ʵ��������mBillboardColour�ϵ�һ���������������billboard�ϵ�
		��ɫֵ��mBillboardColour * mAlphaValue
		*/
		Real				mAlphaValue;

		/// ��ʾ��ɫ�Ƿ���Ҫ�������õı�־
		bool				mColourChanged;

		/// the stacks of texture coordinates
		ulong				mStacks;
		/// the slices of texture coordinates
		ulong				mSlices;

		/// ÿ��billboard���θı�texture index֮��ļ��ʱ��
		Real				mTexIntervalTime;

		Real				mCurrentTexIntervalTime;

		////////////////////////////////////////////////////////////////
		static CmdBillboardColour msBillboardColourCmd;
		static CmdBillboardAlpha msBillboardAlphaCmd;
		static CmdBillboardCount msBillboardCountCmd;
		static CmdBillboardMaterial msBillboardMaterialCmd;
		static CmdBillboardInterval msBillboardIntervalCmd;
		static CmdBillboardHeight msBillboardHeightCmd;
		static CmdBillboardWidth msBillboardWidthCmd;

		static CmdBillboardScale msBillboardScaleCmd[MAX_STAGES];
		static CmdScaleIntervalTime msScaleIntervalTimeCmd;

		static CmdStacks msStacksCmd;
		static CmdSlices msSlicesCmd;
		static CmdTexIntervalTime msTexIntervalTimeCmd;
	};
}

#endif // OGImpactBillboardSetModule_h__