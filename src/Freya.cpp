#include "Freya.h"

namespace FREYA {

	/************************************************************************/
	/*                              FreyaPoint                              */
	/************************************************************************/
	bool FreyaPoint::empty() const
	{
		return x == 0 && y == 0;
	}

	FreyaPoint FreyaPoint::copy() const
	{
		return make(x,y);
	}

	FreyaPoint FreyaPoint::make(float ix, float iy)
	{
		return FreyaPoint{ ix,iy };
	}

	/************************************************************************/
	/*                          FreyaSize                                   */
	/************************************************************************/
	bool FreyaSize::empty() const
	{
		return height == 0 && width == 0;
	}

	FreyaSize FreyaSize::copy() const
	{
		return make(width,height);
	}

	float FreyaSize::ratioWH() const
	{
		if (height == 0)
		{
			return 0;
		}
		return width/height;
	}

	void FreyaSize::reset()
	{
		width = 0;
		height = 0;
	}

	bool FreyaSize::equals(const FreyaSize& other) const
	{
		return other.width == width && other.height == height;
	}

	FreyaSize FreyaSize::scale(float scale) const
	{
		return make(width * scale ,height * scale);
	}

	FreyaSize FreyaSize::scaleInt(float scale) const
	{
		if (scale == 1)
		{
			return *this;
		}

		int w = (int)(width * scale);
		int h = (int)(height * scale);

		if ((w & 1) == 1)
			w++;

		if ((h & 1) == 1)
			h++;

		return make((float)w, (float)h);
	}

	float FreyaSize::diagonal() const
	{
		return std::sqrt(width * width + height * height);
	}

	float FreyaSize::ratio() const
	{
		if (height == 0) return 0.0f;
		return width/height;
	}

	FreyaSize FreyaSize::make(float iwidth, float iheight)
	{
		return FreyaSize{ iwidth,iheight };
	}

}