#pragma once
#include "ofTexture.h"

class ofxCubeTexture : public ofTexture{
public:

	//void loadData(ofFloatImage &data_px,ofFloatImage &data_nx,ofFloatImage &data_py,ofFloatImage &data_ny,ofFloatImage &data_pz,ofFloatImage &data_nz);
	//void loadData(string file_px,string file_nx,string file_py,string file_ny,string file_pz,string file_nz);
	//void loadData(string filename);
	//void loadData(ofFloatImage &image);

	void drawCube(float x,float y,float z,float width,float height,float depth);
	void drawSphere(float x,float y,float z,float radius);

	void begin(bool vFlip=false);
	void end();

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


	void loadData(const unsigned char* const data_positive_x,const unsigned char* const data_negative_x,const unsigned char* const data_positive_y,const unsigned char* const data_negative_y,const unsigned char* const data_positive_z,const unsigned char* const data_negative_z, int w, int h, int glFormat);
	void loadData(const unsigned short* data_positive_x,const unsigned short* data_negative_x,const unsigned short* data_positive_y,const unsigned short* data_negative_y,const unsigned short* data_positive_z,const unsigned short* data_negative_z, int w, int h, int glFormat);
	void loadData(const float* data_positive_x,const float* data_negative_x,const float* data_positive_y,const float* data_negative_y,const float* data_positive_z,const float* data_negative_z, int w, int h, int glFormat);
	void loadData(const ofPixels & pix_positive_x,const ofPixels & pix_negative_x,const ofPixels & pix_positive_y,const ofPixels & pix_negative_y,const ofPixels & pix_positive_z,const ofPixels & pix_negative_z);
	void loadData(const ofShortPixels & pix_positive_x,const ofShortPixels & pix_negative_x,const ofShortPixels & pix_positive_y,const ofShortPixels & pix_negative_y,const ofShortPixels & pix_positive_z,const ofShortPixels & pix_negative_z);
	void loadData(const ofFloatPixels & pix_positive_x,const ofFloatPixels & pix_negative_x,const ofFloatPixels & pix_positive_y,const ofFloatPixels & pix_negative_y,const ofFloatPixels & pix_positive_z,const ofFloatPixels & pix_negative_z);
	void loadData(const ofPixels & pix_positive_x,const ofPixels & pix_negative_x,const ofPixels & pix_positive_y,const ofPixels & pix_negative_y,const ofPixels & pix_positive_z,const ofPixels & pix_negative_z, int glFormat);
	void loadData(const ofShortPixels & pix_positive_x,const ofShortPixels & pix_negative_x,const ofShortPixels & pix_positive_y,const ofShortPixels & pix_negative_y,const ofShortPixels & pix_positive_z,const ofShortPixels & pix_negative_z, int glFormat);
	void loadData(const ofFloatPixels & pix_positive_x,const ofFloatPixels & pix_negative_x,const ofFloatPixels & pix_positive_y,const ofFloatPixels & pix_negative_y,const ofFloatPixels & pix_positive_z,const ofFloatPixels & pix_negative_z, int glFormat);

protected:
    void loadData(const void * data_positive_x, const void * data_negative_x, const void * data_positive_y, const void * data_negative_y, const void * data_positive_z, const void * data_negative_z, int w, int h, int glFormat, int glType);
};

