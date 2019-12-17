#include "MovieClip.h"

// ---------------------------------------------------------------------------------------------------------------------
MovieClip::MovieClip(WebGLRenderingContext* _gl, float w, float h)
{
this->gl = _gl;
this->ontimeupdate = false;
this->isPlaying = false;
this->copyVideo = false;
this->isTexture = false;
this->isDrag = false;
this->DragDrop = false;
this->width = w; 
this->height = h;
this->clipType = 0;
this->x = 0;
this->y = 0;
this->lastDragX = 0;
this->lastDragY = 0;
this->offsetX = 0;
this->offsetY = 0;
this->alpha = 1;
this->quality = 0.9;
this->rotate = 0.0f;
this->lockX = vec2();
this->lockY = vec2();
this->index++;
_anim_offset = (int**)malloc(sizeof(int*)*MAX_ANIM_OFFSET);
for(int i=0; i<MAX_ANIM_OFFSET; i++)
    _anim_offset[i] = new int[2];    
updateBuffer();
setColor(1.0f,1.0f,1.0f);
setPos(0.0f,0.0f);
setRotate(0.0f);
InitTexture();
 }
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::updateBuffer()
{
positionBuf=gl->createBuffer();
gl->bindBuffer(gl->get_ARRAY_BUFFER(), positionBuf);
        float _width = width;
        float _height = height;
        float vertices[] = {        
        0, 0,
        0, _height,
        _width, 0,
        
        _width, 0,
        0, _height,
        _width, _height,
        };
gl->bufferData(gl->get_ARRAY_BUFFER(), cheerp::MakeTypedArray(vertices), gl->get_STATIC_DRAW());
        
texcoordBuf=gl->createBuffer();
gl->bindBuffer(gl->get_ARRAY_BUFFER(), texcoordBuf);
        float texcoords[] = {
        0, 0,
        0, 1,
        1, 0,
        1, 0,
        0, 1,
        1, 1,
        };
gl->bufferData(gl->get_ARRAY_BUFFER(), cheerp::MakeTypedArray(texcoords), gl->get_STATIC_DRAW());
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::checkReady() {
    if ((isPlaying) && (ontimeupdate)) {
      copyVideo = true;
    }
  }
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::updateTexture()
{
gl->activeTexture(gl->get_TEXTURE0());
gl->bindTexture(gl->get_TEXTURE_2D(), tex);
gl->pixelStorei(gl->get_UNPACK_PREMULTIPLY_ALPHA_WEBGL(), true);
switch(clipType)
{
case 0:     
     if(_playerImage)gl->texImage2D(gl->get_TEXTURE_2D(), 0, gl->get_RGBA(), gl->get_RGBA(), gl->get_UNSIGNED_BYTE(), _playerImage);
     break;
case 1:
     if(_playerVideo)gl->texImage2D(gl->get_TEXTURE_2D(), 0, gl->get_RGBA(), gl->get_RGBA(), gl->get_UNSIGNED_BYTE(), _playerVideo);
     break;
}
     gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_MIN_FILTER(), gl->get_LINEAR());
     gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_MAG_FILTER(), gl->get_NEAREST());
     gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_WRAP_S(), gl->get_CLAMP_TO_EDGE());
     gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_WRAP_T(), gl->get_CLAMP_TO_EDGE());
     gl->getExtension("OES_texture_float");
     gl->getExtension("OES_texture_float_linear");
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::InitTexture()
{
tex = gl->createTexture();
gl->activeTexture(gl->get_TEXTURE0());
gl->bindTexture(gl->get_TEXTURE_2D(), tex);
// let's assume all images are not a power of 2
gl->pixelStorei(gl->get_UNPACK_PREMULTIPLY_ALPHA_WEBGL(), true);
Uint8Array *pixels = new Uint8Array(new int[0,255,0,255]);
gl->texImage2D(gl->get_TEXTURE_2D(), 0, gl->get_RGBA(), 1, 1, 0, gl->get_RGBA(), gl->get_UNSIGNED_BYTE(), pixels);
gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_MIN_FILTER(), gl->get_NEAREST());
gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_MAG_FILTER(), gl->get_NEAREST());
gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_WRAP_S(), gl->get_CLAMP_TO_EDGE());
gl->texParameteri(gl->get_TEXTURE_2D(), gl->get_TEXTURE_WRAP_T(), gl->get_CLAMP_TO_EDGE());
gl->getExtension("OES_texture_float");
gl->getExtension("OES_texture_float_linear");
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::loadMovieClip(const char* url, int type)
{
clipType = type;
InitTexture();        
_playerVideo = static_cast<HTMLVideoElement*>(document.createElement("video"));
_playerVideo->setAttribute("id","_playerVideo");
_playerVideo->setAttribute("clipID",index);
_playerVideo->setAttribute("clipType",type);
_playerVideo->set_autoplay(true);
_playerVideo->set_muted(true);
_playerVideo->set_loop(true);
_playerVideo->set_src(url);
//_playerVideo->addEventListener("playing",cheerp::Callback(isVideoPlaying));
//_playerVideo->addEventListener("timeupdate",cheerp::Callback(isTimeUpdate));
//_playerVideo->addEventListener("loadeddata",cheerp::Callback(isVideoLoaded));
_playerVideo->play();
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::loadSprite(const char* url, int type)
{
clipType = type;
InitTexture();
_playerImage = static_cast<HTMLImageElement*>(document.createElement("img"));
_playerImage->setAttribute("id","_playerImage");
_playerImage->setAttribute("src",url);
_playerImage->setAttribute("clipID",index);
_playerImage->setAttribute("clipType",type);

_playerImage->set_crossOrigin("");
//_playerImage->addEventListener("load", cheerp::Callback(isImageLoaded));
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::Render(bool textured, Camera* cam)
{        
        if(copyVideo)
        {
        gl->activeTexture(gl->get_TEXTURE0());
        gl->bindTexture(gl->get_TEXTURE_2D(), tex);
        gl->useProgram(program);
        
	gl->bindBuffer(gl->get_ARRAY_BUFFER(), positionBuf);
        gl->enableVertexAttribArray(vertexPositionAttribute);
	gl->vertexAttribPointer(vertexPositionAttribute, 2, gl->get_FLOAT(), false, 0, 0);
        
        gl->bindBuffer(gl->get_ARRAY_BUFFER(), texcoordBuf);
        gl->enableVertexAttribArray(texcoordAttribute);
	gl->vertexAttribPointer(texcoordAttribute, 2, gl->get_FLOAT(), false, 0, 0);
 
        MakeIdentity(mvMatrix);
        float moveOriginMatrix[16];
        float axis[3] = {0, 0, 1};
        MakeIdentity(moveOriginMatrix);
        Translate(moveOriginMatrix, offsetX, offsetY, 0.0f);
        
        if(!cam)
        {
        axisRotate(mvMatrix,axis,rotate,mvMatrix);
        Translate(mvMatrix, x, y, 0.0f);
        multiply(mvMatrix, moveOriginMatrix, mvMatrix);
        }
        if(cam)
        {
        axisRotate(mvMatrix,axis,rotate,mvMatrix);
        Translate(mvMatrix, x-cam->get_X(), y-cam->get_Y(), 0.0f);
        multiply(mvMatrix, moveOriginMatrix, mvMatrix);
        }
	gl->uniformMatrix4fv(mvMatrixUniform, false, cheerp::MakeTypedArray(mvMatrix));
        gl->uniform1i(textureLocation, 0);
        gl->uniform1f(alphaUniform,alpha);
        gl->uniform1f(qualityUniform,quality);
        gl->uniform3fv(colorUniform,cheerp::MakeTypedArray(color));
        gl->uniform1i(texturedUniform, textured); 
	gl->drawArrays(gl->get_TRIANGLES(), 0, 6);
        gl->useProgram(0);
        }
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::setStepAnimOffset(int offset)
{
int j = 0;
for(int i=0; i < MAX_ANIM_OFFSET; i++)
{
j++;
_anim_offset[i][0] = j;
j+=offset;
_anim_offset[i][1] = j;
 }
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::OnMouseMove(float _x, float _y)
{
if(isDrag)
{
if(((lockX.getX() == 0) && (lockX.getY() == 0)) || 
                  ((x >= lockX.getX()) && (x <= lockX.getY())))x = _x - lastDragX;
if(((lockY.getX() == 0) && (lockY.getY() == 0)) || 
                  ((y >= lockY.getX()) && (y <= lockY.getY())))y = _y - lastDragY;
if(x < lockX.getX())x = lockX.getX();
if(x > lockX.getY())x = lockX.getY();
//if(y < lockY.getX())y = lockY.getX();
//if(y > lockY.getY())y = lockY.getY();
 }
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::OnMouseDown(float _x, float _y)
{
    if(DragDrop)
    {
    lastDragX = _x - x;
    lastDragY = _y - y;
    isDrag = true;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void MovieClip::OnMouseUp(float _x, float _y)
{
if(DragDrop)
{
if(x < lockX.getX())x = lockX.getX()+1;
if(x > lockX.getY())x = lockX.getY()-1;
isDrag = false;
 }
}
// ---------------------------------------------------------------------------------------------------------------------
float MovieClip::getLocalX(float value)
{
if(!Parent)return 0;
float px = (x - Parent->getX()) - width;
float pw = Parent->getWidth();
float lX = (px  / pw) * value;
if(lX < 0)lX = 0;
if(lX > (0.955f*(value-1)))lX = 1*value;
return lX;
}
// ---------------------------------------------------------------------------------------------------------------------
