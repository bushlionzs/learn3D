#pragma once

Ogre::Matrix3 EulerAnglesToRotationMatrix(const Ogre::Vector3& eulerAngles);
uint32_t DivRoundUp(uint32_t x, uint32_t y);

uint32_t  CalcConstantBufferByteSize(uint32_t byteSize);

uint32_t  CalcStoreBufferByteSize(uint32_t byteSize);
