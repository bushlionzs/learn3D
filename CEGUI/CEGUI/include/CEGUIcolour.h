

#ifndef _CEGUIcolour_h_
#define _CEGUIcolour_h_

#include "CEGUIBase.h"


namespace CEGUI
{
typedef uint32 argb_t;    


class CEGUIEXPORT colour
{
public:
	
	colour(void);
	colour(const colour& val);
	colour(float red, float green, float blue, float alpha = 1.0f);
	colour(argb_t argb);

	
	argb_t	getARGB(void) const
	{
		if (!d_argbValid)
		{
			d_argb = calculateARGB();
			d_argbValid = true;
		}

		return d_argb;
	}
	
	float	getAlpha(void) const	{return d_alpha;}
	float	getRed(void) const		{return d_red;}
	float	getGreen(void) const	{return d_green;}
	float	getBlue(void) const		{return d_blue;}

	float	getHue(void) const;
	float	getSaturation(void) const;
	float	getLumination(void) const;


	
	void	setARGB(argb_t argb);
	inline void setAlpha(float alpha)
    {
        d_argbValid = false;
        d_alpha = alpha;
    }

	inline void setRed(float red)
    {   
        d_argbValid = false;
        d_red = red;
    }

	inline void setGreen(float green)
    {
        d_argbValid = false;
        d_green = green;
    }

	inline void setBlue(float blue)
    {
        d_argbValid = false;
        d_blue = blue;
    }

	inline void set(float red, float green, float blue, float alpha = 1.0f)
    {
        d_argbValid = false;
        d_alpha = alpha;
        d_red = red;
        d_green = green;
        d_blue = blue;
    }

	inline void setRGB(float red, float green, float blue)
    {
        d_argbValid = false;
        d_red = red;
        d_green = green;
        d_blue = blue;
    }

	inline void setRGB(const colour& val)
    {
        d_red = val.d_red;
        d_green = val.d_green;
        d_blue = val.d_blue;
        if (d_argbValid)
        {
            d_argbValid = val.d_argbValid;
            if (d_argbValid)
                d_argb = (d_argb & 0xFF000000) | (val.d_argb & 0x00FFFFFF);
        }
    }

	void	setHSL(float hue, float saturation, float luminance, float alpha = 1.0f);

	void	invertColour(void);
	void	invertColourWithAlpha(void);

	
	inline colour& operator=(argb_t val)
    {
        setARGB(val);
        return *this;
    }

	inline colour& operator=(const colour& val)
    {
        d_alpha = val.d_alpha;
        d_red   = val.d_red;
        d_green = val.d_green;
        d_blue  = val.d_blue;
        d_argb  = val.d_argb;
        d_argbValid = val.d_argbValid;

        return *this;
    }

	inline colour& operator&=(argb_t val)
    {
        setARGB(getARGB() & val);
        return *this;
    }

	inline colour& operator&=(const colour& val)
    {
        setARGB(getARGB() & val.getARGB());
        return *this;
    }

	inline colour& operator|=(argb_t val)
    {
        setARGB(getARGB() | val);
        return *this;
    }

	inline colour& operator|=(const colour& val)
    {
        setARGB(getARGB() | val.getARGB());
        return *this;
    }

	inline colour& operator<<=(int val)
    {
        setARGB(getARGB() << val);
        return *this;
    }

	inline colour& operator>>=(int val)
    {
        setARGB(getARGB() >> val);
        return *this;
    }

	inline colour operator+(const colour& val) const
    {
        return colour(
            d_red   + val.d_red, 
            d_green + val.d_green, 
            d_blue  + val.d_blue,
            d_alpha + val.d_alpha
        );
    }

	inline colour operator-(const colour& val) const
    {
        return colour(
            d_red   - val.d_red,
            d_green - val.d_green,
            d_blue  - val.d_blue,
            d_alpha - val.d_alpha
        );
    }

	inline colour operator*(const float val) const
    {       
        return colour(
            d_red   * val, 
            d_green * val, 
            d_blue  * val,
            d_alpha * val 
        );  
    }

    inline colour& operator*=(const colour& val)
    {
        d_red *= val.d_red;
        d_blue *= val.d_blue;
        d_green *= val.d_green;
        d_alpha *= val.d_alpha;

		d_argbValid = false;

        return *this;
    }

	
	inline bool operator==(const colour& rhs) const
    {
        return d_red   == rhs.d_red   &&
               d_green == rhs.d_green &&
               d_blue  == rhs.d_blue  &&
               d_alpha == rhs.d_alpha;
    }

	inline bool operator!=(const colour& rhs) const
    {
        return !(*this == rhs);
    }

	
	
	
	operator argb_t() const		{return getARGB();}

private:
	
	
	argb_t	calculateARGB(void) const;

	
	float d_alpha, d_red, d_green, d_blue;		
	mutable argb_t d_argb;						
	mutable bool d_argbValid;					
};

} 


#endif	
