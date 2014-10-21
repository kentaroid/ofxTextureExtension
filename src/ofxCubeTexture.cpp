#include "ofxCubeTexture.h"
#include "ofImage.h"		// for nextPow2()
#include <map>
#include "ofShader.h"
#include "of3dGraphics.h"


//-------------------------------------------------------------------------------
//using shader for drawing cube box


#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)

namespace ofxCubeTexShader{ 
	static ofShader _cubeShader;
	static bool bLoadedShader=false;
	static void loadCubeShader(){
		_cubeShader.setupShaderFromSource(GL_VERTEX_SHADER,STRINGIFY(
			varying vec3  texcoord;
		    uniform int uVFlip; 
			void main(void) 
			{
				texcoord = normalize(gl_Vertex.xyz);
				if(uVFlip>0)texcoord.y*=-1.0;
				gl_Position = ftransform();
			}
		));
		_cubeShader.setupShaderFromSource(GL_FRAGMENT_SHADER,STRINGIFY(
			uniform samplerCube tex;
			varying vec3  texcoord;
			void main (void){
				gl_FragColor = textureCube(tex, texcoord);
			}
		));
		_cubeShader.linkProgram();
		bLoadedShader=true;
	}
};

void ofxCubeTexture::drawCube(float x,float y,float z,float width,float height,float depth){
	begin(texData.bFlipTexture == ofIsVFlipped());

	//Drawing on triangle mesh is too bad!
	//ofBox(x,y,z,width,height,depth);

	x = x - width*.5;
	z = z - depth*.5;
	y = y - height*.5;

	glBegin(GL_QUADS);
	glVertex3f(x,y,z+depth);
	glVertex3f(x,y+height,z+depth);
	glVertex3f(x+width,y+height,z+depth);
	glVertex3f(x+width,y,z+depth);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x+width,y,z);
	glVertex3f(x+width,y+height,z);
	glVertex3f(x,y+height,z);
	glVertex3f(x,y,z);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x,y+height,z);
	glVertex3f(x,y+height,z+depth);
	glVertex3f(x,y,z+depth);
	glVertex3f(x,y,z);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x+width,y,z);
	glVertex3f(x+width,y,z+depth);
	glVertex3f(x+width,y+height,z+depth);
	glVertex3f(x+width,y+height,z);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x+width,y+height,z);
	glVertex3f(x+width,y+height,z+depth);
	glVertex3f(x,y+height,z+depth);
	glVertex3f(x,y+height,z);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x,y,z);
	glVertex3f(x,y,z+depth);
	glVertex3f(x+width,y,z+depth);
	glVertex3f(x+width,y,z);
	glEnd();

	end();
}
void ofxCubeTexture::drawSphere(float x,float y,float z,float radius){
	begin(texData.bFlipTexture == ofIsVFlipped());
	ofDrawSphere(x,y,z,radius);
	end();
}


void ofxCubeTexture::begin(bool vFlip){
	if(!ofxCubeTexShader::bLoadedShader)ofxCubeTexShader::loadCubeShader();
	ofxCubeTexShader::_cubeShader.begin();
	ofxCubeTexShader::_cubeShader.setUniformTexture("tex",*this,0);
	ofxCubeTexShader::_cubeShader.setUniform1i("uVFlip",vFlip?1:0);
}


void ofxCubeTexture::end(){
	ofxCubeTexShader::_cubeShader.end();
}

//------------------------------------------------------------------------------------

int CheckVerticalPosition(int width,int height){
	int num=0;
	for(int i=2;i<7;i++){
		if(width*i==height){
			num=i;
			break;
		}
	}
	return num;
}

void ofxCubeTexture::loadData(const unsigned char* const data, int w, int h, int glFormat){
	ofSetPixelStorei(w,1,ofGetNumChannelsFromGLFormat(glFormat));
	int num=CheckVerticalPosition(w, h);
	if(num==0){
		loadData(data,data,data,data,data,data, w, h, glFormat, GL_UNSIGNED_BYTE);
	}else{
		int step=ofGetNumChannelsFromGLFormat(glFormat)*w*w*1;
		loadData(data,data+(step*(1%num)),data+(step*(2%num)),data+(step*(3%num)),data+(step*(4%num)),data+(step*(5%num)), w, w, glFormat, GL_UNSIGNED_BYTE);
	}
}
void ofxCubeTexture::loadData(const unsigned short* data, int w, int h, int glFormat){
	ofSetPixelStorei(w,2,ofGetNumChannelsFromGLFormat(glFormat));
	int num=CheckVerticalPosition(w, h);
	if(num==0){
		loadData(data,data,data,data,data,data, w, h, glFormat, GL_UNSIGNED_SHORT);
	}else{
		int step=ofGetNumChannelsFromGLFormat(glFormat)*w*w;
		loadData(data,data+(step*(1%num)),data+(step*(2%num)),data+(step*(3%num)),data+(step*(4%num)),data+(step*(5%num)), w, w, glFormat, GL_UNSIGNED_SHORT);
	}
}
void ofxCubeTexture::loadData(const float* data, int w, int h, int glFormat){
	ofSetPixelStorei(w,4,ofGetNumChannelsFromGLFormat(glFormat));
	int num=CheckVerticalPosition(w, h);
	if(num==0){
		loadData(data,data,data,data,data,data, w, h, glFormat, GL_FLOAT);
	}else{
		int step=ofGetNumChannelsFromGLFormat(glFormat)*w*w;
		loadData(data,data+(step*(1%num)),data+(step*(2%num)),data+(step*(3%num)),data+(step*(4%num)),data+(step*(5%num)), w, w, glFormat, GL_FLOAT);
	}
}

//------------------------------------------------------------------------------------

void ofxCubeTexture::loadData(const ofPixels & pix){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(),ofGetGlFormat(pix));
}
void ofxCubeTexture::loadData(const ofShortPixels & pix){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(),ofGetGlFormat(pix));
}
void ofxCubeTexture::loadData(const ofFloatPixels & pix){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(),ofGetGlFormat(pix));
}
void ofxCubeTexture::loadData(const ofPixels & pix, int glFormat){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(), glFormat);
}
void ofxCubeTexture::loadData(const ofShortPixels & pix, int glFormat){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(), glFormat);
}
void ofxCubeTexture::loadData(const ofFloatPixels & pix, int glFormat){
	loadData(pix.getData(),pix.getWidth(),pix.getHeight(), glFormat);
}

//------------------------------------------------------------------------------------

void ofxCubeTexture::loadData(const unsigned char* const data_positive_x,const unsigned char* const data_negative_x,const unsigned char* const data_positive_y,const unsigned char* const data_negative_y,const unsigned char* const data_positive_z,const unsigned char* const data_negative_z, int w, int h, int glFormat){
	ofSetPixelStorei(w,1,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data_positive_x,data_negative_x,data_positive_y,data_negative_y,data_positive_z,data_negative_z, w, h, glFormat, GL_UNSIGNED_BYTE);
}
void ofxCubeTexture::loadData(const unsigned short* data_positive_x,const unsigned short* data_negative_x,const unsigned short* data_positive_y,const unsigned short* data_negative_y,const unsigned short* data_positive_z,const unsigned short* data_negative_z, int w, int h, int glFormat){
	ofSetPixelStorei(w,2,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data_positive_x,data_negative_x,data_positive_y,data_negative_y,data_positive_z,data_negative_z, w, h, glFormat, GL_UNSIGNED_SHORT);
}
void ofxCubeTexture::loadData(const float* data_positive_x,const float* data_negative_x,const float* data_positive_y,const float* data_negative_y,const float* data_positive_z,const float* data_negative_z, int w, int h, int glFormat){
	ofSetPixelStorei(w,4,ofGetNumChannelsFromGLFormat(glFormat));
	loadData(data_positive_x,data_negative_x,data_positive_y,data_negative_y,data_positive_z,data_negative_z, w, h, glFormat, GL_FLOAT);
}

//------------------------------------------------------------------------------------

void ofxCubeTexture::loadData(const ofPixels & pix_positive_x,const ofPixels & pix_negative_x,const ofPixels & pix_positive_y,const ofPixels & pix_negative_y,const ofPixels & pix_positive_z,const ofPixels & pix_negative_z){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(),ofGetGlFormat(pix_positive_x));
}
void ofxCubeTexture::loadData(const ofShortPixels & pix_positive_x,const ofShortPixels & pix_negative_x,const ofShortPixels & pix_positive_y,const ofShortPixels & pix_negative_y,const ofShortPixels & pix_positive_z,const ofShortPixels & pix_negative_z){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(),ofGetGlFormat(pix_positive_x));
}
void ofxCubeTexture::loadData(const ofFloatPixels & pix_positive_x,const ofFloatPixels & pix_negative_x,const ofFloatPixels & pix_positive_y,const ofFloatPixels & pix_negative_y,const ofFloatPixels & pix_positive_z,const ofFloatPixels & pix_negative_z){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(),ofGetGlFormat(pix_positive_x));
}
void ofxCubeTexture::loadData(const ofPixels & pix_positive_x,const ofPixels & pix_negative_x,const ofPixels & pix_positive_y,const ofPixels & pix_negative_y,const ofPixels & pix_positive_z,const ofPixels & pix_negative_z, int glFormat){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(), glFormat);
}
void ofxCubeTexture::loadData(const ofShortPixels & pix_positive_x,const ofShortPixels & pix_negative_x,const ofShortPixels & pix_positive_y,const ofShortPixels & pix_negative_y,const ofShortPixels & pix_positive_z,const ofShortPixels & pix_negative_z, int glFormat){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(), glFormat);
}
void ofxCubeTexture::loadData(const ofFloatPixels & pix_positive_x,const ofFloatPixels & pix_negative_x,const ofFloatPixels & pix_positive_y,const ofFloatPixels & pix_negative_y,const ofFloatPixels & pix_positive_z,const ofFloatPixels & pix_negative_z, int glFormat){
	loadData(pix_positive_x.getData(),pix_negative_x.getData(),pix_positive_y.getData(),pix_negative_y.getData(),pix_positive_z.getData(),pix_negative_z.getData(), pix_positive_x.getWidth(), pix_positive_x.getHeight(), glFormat);
}

//-------------------------------------------------------------------------

void ofxCubeTexture::allocate(const ofTextureData & textureData, int glFormat, int pixelType){
	texData=textureData;
	texData.textureTarget = GL_TEXTURE_CUBE_MAP;
	texData.magFilter=GL_LINEAR;
	texData.minFilter=GL_LINEAR_MIPMAP_LINEAR;
	texData.bFlipTexture=false;

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	ofTexture::allocate(texData,glFormat,pixelType);

	enableTextureTarget(0);
	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);

	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, glFormat, pixelType, 0);


	glTexParameterf( texData.textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf( texData.textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf( texData.textureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, texData.magFilter);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, texData.minFilter);


	#ifndef TARGET_PROGRAMMABLE_GL
		if (!ofIsGLProgrammableRenderer()){
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
	#endif
	disableTextureTarget(0);
}

//---------------------------------------------------------------------------------------

void ofxCubeTexture::loadData(const void * data_positive_x, const void * data_negative_x, const void * data_positive_y, const void * data_negative_y, const void * data_positive_z, const void * data_negative_z, int w, int h, int glFormat, int glType){
	if(w != texData.tex_w || h != texData.tex_h  ) {
		if(!isAllocated()){
			ofTexture::allocate(w, h, glFormat , glFormat, glType);
		}else{
			ofTexture::allocate(w,h,texData.glTypeInternal , glFormat, glType);
		}
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

	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, w, h, glFormat, glType, data_positive_x);
	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, w, h, glFormat, glType, data_negative_x);
	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, w, h, glFormat, glType, data_positive_y);
	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, w, h, glFormat, glType, data_negative_y);
	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, w, h, glFormat, glType, data_positive_z);
	glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, w, h, glFormat, glType, data_negative_z);
	
	// unbind texture target by binding 0
	glBindTexture(texData.textureTarget, 0);
	
	generateMipmap();
}