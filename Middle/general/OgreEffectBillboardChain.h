#ifndef _EffectBillboardChain_H__
#define _EffectBillboardChain_H__

#include "OgreSimpleRenderable.h"
#include "OgreColourValue.h"
namespace Ogre {


   /** Contains the data of an element of the EffectBillboardChain.
   */
   class EffectBillboardChainElement
   {

   public:

      EffectBillboardChainElement();

      EffectBillboardChainElement(Vector3 position,
                       Real width,
                       Real uTexCoord,
                       ColourValue colour);

      Vector3 position;
      Real width;
      Real uTexCoord;
      ColourValue colour;

   };

    /** Allows the rendering of a chain of connected billboards.
    */
   class EffectBillboardChain : public SimpleRenderable
   {

   public:
         
      typedef std::vector<EffectBillboardChainElement> EffectBillboardChainElementList;

      EffectBillboardChain(int maxNbChainElements = 10);
      virtual ~EffectBillboardChain();

      virtual void _notifyCurrentCamera(Camera* cam);
      virtual Real getSquaredViewDepth(const Camera* cam) const;
      virtual Real getBoundingRadius(void) const;

      void setNbChainElements(unsigned int nbChainElements);
      void setChainElement(unsigned int elementIndex, const EffectBillboardChainElement& billboardChainElement);
      void updateBoundingBox();

      void _updateRenderQueue(RenderQueue* queue);

      void isInitData(bool init)
      {
          mInitData = init;
      }

   protected:

	   void _createBuffer(void);

   protected:

      Real mRadius;

      int mCurrentNbChainElements;

      EffectBillboardChainElementList mChainElementList;

      // 这个chain的数据是否已经准备好送去渲染了
      bool mInitData;

      void updateHardwareBuffers();
   };

} // namespace

#endif

