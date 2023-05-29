/********************************************************************
Copyright (c) 2010 Beijing Kylin Network Information 
Science and Technology Co, Ltd. All Rights Reserved.
author:		changhao

purpose:	
*********************************************************************/

#ifndef __Texture1ScaleInterpolatorAffector_H__
#define __Texture1ScaleInterpolatorAffector_H__

#include "OgreParticleAffector.h"
#include "OgreStringInterface.h"
#include "OgreColourValue.h"
#include "OgreVector3.h"

namespace Ogre 
{
    class  Texture1ScaleInterpolatorAffector : public ParticleAffector
    {
    public:

		enum { MAX_STAGES = 6 };

        class CmdTextureScaleAdjust : public ParamCommand
        {
		public:
			size_t		mIndex;

		public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
            void doCopy(void* target, const void* source);
#endif
        };

        /** Command object for red adjust (see ParamCommand).*/
		class CmdTimeAdjust : public ParamCommand
        {
        public:
			size_t		mIndex;

		public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
            void doCopy(void* target, const void* source);
#endif
		};

        /** Default constructor. */
        Texture1ScaleInterpolatorAffector(ParticleSystem* psys);

        /** See ParticleAffector. */
        void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		void setScaleAdjust(size_t index, const Ogre::Vector3& scale);
		Ogre::Vector3 getScaleAdjust(size_t index) const;
        
		void setTimeAdjust(size_t index, Real time);
        Real getTimeAdjust(size_t index) const;
      	virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
    	virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		static CmdTextureScaleAdjust	msTextureScaleCmd[MAX_STAGES];
        static CmdTimeAdjust	msTimeCmd[MAX_STAGES];

    protected:

		Ogre::Vector3					mTextureScale[MAX_STAGES];
		Real					mTimeAdj[MAX_STAGES];

    };


}


#endif

