/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "OgreHeader.h"
#include "OgrePointEmitter.h"
#include "OgreParticle.h"


namespace Ogre {

    //-----------------------------------------------------------------------
    PointEmitter::PointEmitter(ParticleSystem* psys)
        :ParticleEmitter(psys)
    {
        mType = "Point";
        // Set up parameters
        if (createParamDictionary("PointEmitter"))
        {
            addBaseParameters();
        }
        // No custom parameters
    }
    //-----------------------------------------------------------------------
    void PointEmitter::_initParticle(Particle* pParticle)
    {
        // Very simple emitter, uses default implementations with no modification

        // Call superclass
        ParticleEmitter::_initParticle(pParticle);

        // Point emitter emits from own position
        pParticle->mPosition = mPosition;

        // Generate complex data by reference
        genEmissionColour(pParticle->mColour);
        genEmissionDirection( pParticle->mPosition, pParticle->mDirection );
        genEmissionVelocity(pParticle->mDirection);

        // Generate simpler data
        pParticle->mTimeToLive = pParticle->mTotalTimeToLive = genEmissionTTL();
        
    }

    bool PointEmitter::loadFromStream(Serializer* pSerializer, DataStreamPtr& stream)
    {
		if (pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if (chunkId != Ogre::ParticleSystem::PSFF_POINT_EMITTER)
			{
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类ParticleEmitter的属性			
			pSerializer->readData(stream, &mEnabled, 1, sizeof(mEnabled));
			pSerializer->readData(stream, &mAngle, 1, sizeof(mAngle));
			pSerializer->readData(stream, &mColourRangeStart, 1, sizeof(mColourRangeStart));
			pSerializer->readData(stream, &mColourRangeEnd, 1, sizeof(mColourRangeEnd));
			Vector3 direction;
			pSerializer->readData(stream, &direction, 1, sizeof(direction));
			setDirection(direction);
			pSerializer->readData(stream, &mEmissionRate, 1, sizeof(mEmissionRate));
			pSerializer->readData(stream, &mPosition, 1, sizeof(mPosition));

			pSerializer->readData(stream, &mMinSpeed, 1, sizeof(mMinSpeed));
			pSerializer->readData(stream, &mMaxSpeed, 1, sizeof(mMaxSpeed));
			pSerializer->readData(stream, &mMinTTL, 1, sizeof(mMinTTL));
			pSerializer->readData(stream, &mMaxTTL, 1, sizeof(mMaxTTL));
			Real DurMin, DurMax;
			pSerializer->readData(stream, &DurMin, 1, sizeof(DurMin));
			pSerializer->readData(stream, &DurMax, 1, sizeof(DurMax));
			setDuration(DurMin, DurMax);
			Real RepMin, RepMax;
			pSerializer->readData(stream, &RepMin, 1, sizeof(RepMin));
			pSerializer->readData(stream, &RepMax, 1, sizeof(RepMax));
			setRepeatDelay(RepMin, RepMax);
			//属性			
			return true;
		}
		return false;
    }
}


