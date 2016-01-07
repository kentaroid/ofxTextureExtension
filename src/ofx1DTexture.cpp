#include "ofx1DTexture.h"
#include "ofImage.h"

void ofx1DTexture::allocate(const ofTextureData & textureData, int glFormat, int pixelType){
	texData=textureData;
	texData.textureTarget = GL_TEXTURE_1D;
	texData.bFlipTexture=false;
	texData.tex_w = texData.width;
	texData.tex_h = texData.height;
	texData.tex_t = texData.width;
	texData.tex_u = texData.height;

	//for generate Texture ID and manage memories; 
	ofTexture::allocate(texData,glFormat,pixelType);

	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);
	glTexImage1D(texData.textureTarget, 0, texData.glInternalFormat, (GLint)texData.tex_w,  0, glFormat, pixelType, 0);  // init to black...

	glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, texData.magFilter);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, texData.minFilter);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	#ifndef TARGET_PROGRAMMABLE_GL
		if (!ofIsGLProgrammableRenderer()){
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
	#endif
	glBindTexture(texData.textureTarget,0);
}

/*
void ofx1DTexture::loadData(const ofPixels & pix){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getBytesStride());
	loadData(pix.getPixels(), pix.getWidth(), pix.getHeight(), ofGetGlFormat(pix), ofGetGlType(pix));
}
*/

void ofx1DTexture::loadData(const void * data, int w, int h, int glFormat, int glType){

	if(w > texData.tex_w || h > texData.tex_h) {
		ofTexture::allocate(w, h, glFormat, glFormat, glType);
	}
	
	// compute new tex co-ords based on the ratio of data's w, h to texture w,h;
#ifndef TARGET_OPENGLES
	if (texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB){
		texData.tex_t = w;
		texData.tex_u = h;
	} else 
#endif
	{
		texData.tex_t = (float)(w) / (float)texData.tex_w;
		texData.tex_u = (float)(h) / (float)texData.tex_h;
	}
	
	// bind texture
	glBindTexture(texData.textureTarget, (GLuint) texData.textureID);
	//update the texture image:
	glTexSubImage1D(texData.textureTarget, 0, 0, w,  glFormat, glType, data);
	// unbind texture target by binding 0
	glBindTexture(texData.textureTarget, 0);
	
	generateMipmap();
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const unsigned char * data, int w, int h, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,w,1,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data, w, h, glFormat, GL_UNSIGNED_BYTE);
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const unsigned short * data, int w, int h, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,w,2,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data, w, h, glFormat, GL_UNSIGNED_SHORT);
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const float * data, int w, int h, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,w,4,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data, w, h, glFormat, GL_FLOAT);
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofPixels & pix){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getBytesStride());
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), ofGetGlFormat(pix), ofGetGlType(pix));
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofShortPixels & pix){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getBytesStride());
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), ofGetGlFormat(pix), ofGetGlType(pix));
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofFloatPixels & pix){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getBytesStride());
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), ofGetGlFormat(pix), ofGetGlType(pix));
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofPixels & pix, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getWidth(),pix.getBytesPerChannel(),ofGetNumChannelsFromGLFormat(glFormat));
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), glFormat, ofGetGlType(pix));
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofShortPixels & pix, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getWidth(),pix.getBytesPerChannel(),ofGetNumChannelsFromGLFormat(glFormat));
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), glFormat, ofGetGlType(pix));
}

//----------------------------------------------------------
void ofx1DTexture::loadData(const ofFloatPixels & pix, int glFormat){
	ofSetPixelStoreiAlignment(GL_UNPACK_ALIGNMENT,pix.getWidth(),pix.getBytesPerChannel(),ofGetNumChannelsFromGLFormat(glFormat));
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), glFormat, ofGetGlType(pix));
}
