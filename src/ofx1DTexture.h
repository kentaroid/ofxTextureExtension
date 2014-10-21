#pragma once
#include "oftexture.h"
class ofx1DTexture :public ofTexture{

public:

	using  ofTexture::allocate;
	void allocate(const ofTextureData & textureData, int glFormat, int pixelType);


	//override non virtual hack;
	void loadData(const unsigned char* const data, int w, int h, int glFormat);
	void loadData(const unsigned short* data, int w, int h, int glFormat);
	void loadData(const float* data, int w, int h, int glFormat);
	void loadData(const ofPixels & pix);
	void loadData(const ofShortPixels & pix);
	void loadData(const ofFloatPixels & pix);
	void loadData(const ofPixels & pix, int glFormat);
	void loadData(const ofShortPixels & pix, int glFormat);
	void loadData(const ofFloatPixels & pix, int glFormat);
	

protected:
    void loadData(const void * data, int w, int h, int glFormat, int glType);
};

