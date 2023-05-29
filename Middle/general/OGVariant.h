#ifndef __OGVariant_H__
#define __OGVariant_H__

#include <any>

namespace Orphigine
{

    typedef std::any Variant;

    template<typename ValueType>
    ValueType * VariantCast(Variant * operand)
    {
		if (operand == NULL)
			return NULL;
		if (operand->has_value())
			return NULL;
        return std::any_cast<ValueType>(operand);
    }

    template<typename ValueType>
    const ValueType * VariantCast(const Variant * operand)
    {
		if (operand == NULL)
			return NULL;
		if (operand->has_value())
			return NULL;
        return std::any_cast<ValueType>(operand);
    }

    template<typename ValueType>
    ValueType VariantCast(const Variant & operand)
    {	
        return std::any_cast<ValueType>(operand);
    }

}

#endif __OGVariant_H__
