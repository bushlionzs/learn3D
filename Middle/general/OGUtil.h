#ifndef OGUTIL_H
#define	OGUTIL_H

#include <float.h>


namespace Orphigine
{

	typedef unsigned __int32	uint32;
	typedef   signed __int32	int32;

	inline static int Chop(int32 v)
	{
		int32 sign = v >> 31;
		int32 bits = v & ((1u<<31)-1);
		int32 exponent = (bits >> (FLT_MANT_DIG-1)) - ((1<<(32-FLT_MANT_DIG-1))-1);
		int32 exponent_sign = ~(exponent >> 31);
		uint32 mantissa_bits = (v << (32-FLT_MANT_DIG)) | (~0u<<31);
		int32 mantissa = mantissa_bits >> (31 - exponent);
		return ((mantissa ^ sign) - sign) & exponent_sign;
	}
	inline static int Floor(int32 v)
	{ 
		int32 sign = v >> 31;
		int32 bits = v & ((1u<<31)-1);
		int32 exponent = (bits >> (FLT_MANT_DIG-1)) - ((1<<(32-FLT_MANT_DIG-1))-1);
		int32 exponent_sign = ~(exponent >> 31);
		uint32 mantissa_bits = (bits << (32-FLT_MANT_DIG)) | (~0u<<31);
		int32 mantissa = mantissa_bits >> (31 - exponent);
		int32 zero = ((bits - 1) >> 31) ^ exponent_sign;
		int32 carry = ((1 << (31 - exponent)) - 1) & mantissa_bits ? 0 : 1;
		return (carry & zero & sign) + ((mantissa & exponent_sign) ^ sign);
	}

	inline int32 getInt(const float &v)		{	return *(int32*)&v;	}
	inline uint32 getUint(const float &v)	{	return *(uint32*)&v;}
	inline float getFloat(const uint32 &v)	{	return *(float*)&v;	}
	inline uint32 getAbs(const float &v)	{	return *(uint32*)&v & 0x7FFFFFFF; }	
	inline int getFastInt(const float &v)	{	return Chop(*(int32*)&v); }
	inline int getFastFloor(const float &v)	{	return Floor(*(int32*)&v); }
	inline int getFastCeil(const float &v)	{	return - Floor(*(int32*)&v ^ (1<<31)); }

} // Orphigine

#endif // OGUTIL_H


