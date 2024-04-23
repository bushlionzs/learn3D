#include "OgreHeader.h"
#include "OgreEffectBillboardChain.h"
#include "OgreSimpleRenderable.h"
#include "OgreHardwareBufferManager.h"
#include "OgreNode.h"
#include "OgreCamera.h"
#include "OgreRoot.h"
#include "OgreVertexDeclaration.h"


namespace Ogre {

    EffectBillboardChainElement::EffectBillboardChainElement()
        : position(Ogre::Vector3::ZERO)
        , width(0.0f)
        , uTexCoord(0.0f)
        , colour(ColourValue::Black)
   {
   }

   EffectBillboardChainElement::EffectBillboardChainElement(Vector3 _position,
                                     Real _width,
                                     Real _uTexCoord,
                                     ColourValue _colour) :
      position(_position),
      width(_width),
      uTexCoord(_uTexCoord),
      colour(_colour)
   {
   }

   EffectBillboardChain::EffectBillboardChain(int maxNbChainElements)
   {
       mInitData= false;

       mRadius = 0.0f;
       mCurrentNbChainElements = maxNbChainElements;

       _createBuffer(); 

       // set basic white material
       this->setMaterial("BaseWhiteNoLighting");
   }
   
   EffectBillboardChain::~EffectBillboardChain()
   {
   }

    void EffectBillboardChain::_notifyCurrentCamera(Camera* cam)
    {
        SimpleRenderable::_notifyCurrentCamera(cam);

        updateHardwareBuffers();
    }

   Real EffectBillboardChain::getSquaredViewDepth(const Camera* cam) const
   {
       Vector3 min, max, mid, dist;
       min = mBox.getMinimum();
       max = mBox.getMaximum();
       mid = ((max - min) * 0.5) + min;
       dist = cam->getDerivedPosition() - mid;

       return dist.squaredLength();
   }

   Real EffectBillboardChain::getBoundingRadius(void) const
   {
       return mRadius;
   }

   void EffectBillboardChain::setNbChainElements(unsigned int nbChainElements)
   {
       mCurrentNbChainElements = nbChainElements;

	   _createBuffer();

	   mChainElementList.resize(mCurrentNbChainElements);
   }

   void EffectBillboardChain::setChainElement(unsigned int elementIndex, const EffectBillboardChainElement& billboardChainElement)
   {
       mChainElementList[elementIndex] = billboardChainElement;
   }

   void EffectBillboardChain::updateBoundingBox()
   {
       if (mChainElementList.size() < 2)
          return;

       Real width = mChainElementList[0].width;
       Vector3 widthVector = Vector3(width, width, width);
       const Vector3& position = mChainElementList[0].position;
       Vector3 minimum = position - widthVector;
       Vector3 maximum = position + widthVector;

       for (unsigned int i = 1; i < mChainElementList.size(); i++)
       {
         // Update the bounds of the bounding box
          Real width = mChainElementList[i].width;
          Vector3 widthVector = Vector3(width, width, width);
          const Vector3& position = mChainElementList[i].position;

          minimum.makeFloor(position - widthVector);
          maximum.makeCeil(position + widthVector);
       }

       // Set the current bounding box
       setBoundingBox(AxisAlignedBox(minimum, maximum));

       // Set the current radius
       mRadius = Math::Sqrt(std::max(minimum.squaredLength(), maximum.squaredLength()));
   }

   void EffectBillboardChain::updateHardwareBuffers()
    {
       if (mChainElementList.size() < 2)
          return;

       HardwareVertexBufferSharedPtr pVertexBuffer =
          mRenderOp.vertexData->getBuffer(0);

       void* pBufferStart = pVertexBuffer->lock(HardwareBuffer::HBL_DISCARD);

       // Here. we need to compute the position of the camera in the coordinate system of the billboard chain.

       
       Vector3 eyePos = mParent->_getDerivedOrientation().Inverse() *
                   (mCamera->getDerivedPosition() - mParent->_getDerivedPosition());

       // Compute the position of the vertices in the chain
	   unsigned int chainSize = mChainElementList.size();
       for (unsigned int i = 0; i < chainSize; i++)
       {
           // �����µ�ƫ��������Ϊÿ��ѭ���Ǽ����������㣬����Ҫ����2
           void* pBase = static_cast<void*>(
              static_cast<char*>(pBufferStart) +
              pVertexBuffer->getVertexSize() * i * 2);

           Vector3 chainTangent;
           if (i == 0) chainTangent = mChainElementList[1].position - mChainElementList[0].position;
           else if (i == chainSize - 1) chainTangent = mChainElementList[chainSize - 1].position - mChainElementList[chainSize - 2].position;
           else chainTangent = mChainElementList[i + 1].position - mChainElementList[i - 1].position;

           const Vector3& p1 = mChainElementList[i].position;

           Vector3 vP1ToEye = eyePos - p1;
           Vector3 vPerpendicular = chainTangent.crossProduct(vP1ToEye);
           vPerpendicular.normalise();
           vPerpendicular *= mChainElementList[i].width;

           Vector3 pos0 = p1 - vPerpendicular;
           Vector3 pos1 = p1 + vPerpendicular;

           // vertex 1
           // pos
           float* pFloat = static_cast<float*>(pBase);

           *pFloat++ = pos0.x;
           *pFloat++ = pos0.y;
           *pFloat++ = pos0.z;

           // colour
           ColourValue colour = mChainElementList[i].colour;
           RGBA* pColour = static_cast<RGBA*>( static_cast<void*>(pFloat) );

           *pColour = colour.getAsRGBA();
           pColour++;

           // tex coord
           pFloat = static_cast<float*>( static_cast<void*>(pColour) );
           *pFloat++ = mChainElementList[i].uTexCoord;
           *pFloat++ = 0.0f;

           // vertex 2
           // pos
           *pFloat++ = pos1.x;
           *pFloat++ = pos1.y;
           *pFloat++ = pos1.z;

           // colour
           pColour = static_cast<RGBA*>( static_cast<void*>(pFloat) );
           *pColour = colour.getAsRGBA();
           pColour++;

           // tex coord
           pFloat = static_cast<float*>( static_cast<void*>(pColour) );
           *pFloat++ = mChainElementList[i].uTexCoord;
           *pFloat++ = 1.0f;
       }

       pVertexBuffer->unlock();
   }

   void EffectBillboardChain::_createBuffer(void)
   {
	   if (mRenderOp.vertexData)
	   {
		   delete mRenderOp.vertexData;
		   mRenderOp.vertexData = NULL;
	   }

	   mRenderOp.vertexData = new VertexData();
	   mRenderOp.indexData = NULL;
	   mRenderOp.vertexData->vertexCount = mCurrentNbChainElements * 2;
	   mRenderOp.vertexData->vertexStart = 0;
	   mRenderOp.operationType = RenderOperation::OT_TRIANGLE_STRIP;
	   mRenderOp.useIndexes = false;

	   VertexDeclaration* decl = mRenderOp.vertexData->vertexDeclaration;

	   // Add a description for the buffer of the positions of the vertices
       size_t offset = 0;
	   decl->addElement(0, 0, offset, VET_FLOAT3, VES_POSITION);
       offset += VertexElement::getTypeSize(VET_FLOAT3);

       decl->addElement(0, 0, offset, VET_COLOUR, VES_DIFFUSE);
       offset += VertexElement::getTypeSize(VET_COLOUR);

       decl->addElement(0, 0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
       offset += VertexElement::getTypeSize(VET_FLOAT2);

	   // Create the buffer
	   HardwareVertexBufferSharedPtr pVertexBuffer =
		   HardwareBufferManager::getSingleton().createVertexBuffer(
		   decl->getVertexSize(0),
		   mCurrentNbChainElements * 2,
		   HardwareBuffer::HBU_STATIC_WRITE_ONLY);
   }

   void EffectBillboardChain::_updateRenderQueue(RenderQueue* queue)
   {
    
   }
}

