#ifndef MOVIECLIP_H
#define MOVIECLIP_H

#include <cheerp/client.h>
#include <cheerp/clientlib.h>
#include <cheerp/webgl.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "Camera.h"

#define MAX_ANIM_OFFSET 8

using namespace client;

int vertexPositionAttribute;
int texcoordAttribute;
WebGLBuffer* positionBuf;
WebGLBuffer* texcoordBuf;
WebGLBuffer* colorBuf;
WebGLUniformLocation* pMatrixUniform;
WebGLUniformLocation* mvMatrixUniform;
WebGLUniformLocation* textureLocation;
WebGLUniformLocation* alphaUniform;
WebGLUniformLocation* qualityUniform;
WebGLUniformLocation* colorUniform;
WebGLUniformLocation* positionUniform;
WebGLUniformLocation* rotateUniform;
WebGLUniformLocation* texturedUniform;
WebGLProgram* program;
WebGLTexture *tex;
float pMatrix[16];

struct vec2
{
public:
       vec2(){x = 0, y = 0;}
       vec2(float value){x = value, y = value;}
       vec2(float _x,float _y){x = _x, y = _y;}
       void setX(float value){x = value;}
       void setY(float value){y = value;}
       float getX(){return x;}
       float getY(){return y;}
private:
       float x,y;
};

class MovieClip
{
public:
        MovieClip(WebGLRenderingContext* _gl, float width, float height);
        void checkReady();
        void setName(const char *value)
        {
        name = new char[strlen(value)];
        strcpy(name,value);
        }
        void setType(const char *value)
        {
        type = new char[strlen(value)];
        strcpy(type,value);
        }
        void setColor(float r, float g, float b)
        {
        color = new float[3];
        color[0] = r; color[1] = g; color[2] = b;
        }
        void setColor(float *value){color = value;}
        char* getName(){return name;}
        char* getType(){return type;}
        void set_timeupdate(bool value){ontimeupdate = value;}
        void set_playing(bool value){isPlaying = value;}
        bool get_playing(){return isPlaying;}
        void setQuality(float value){quality = value;}
        float getQuality(){return quality;}
        bool isCopyVideo(){return copyVideo;}
        void setCopyVideo(bool value){copyVideo = value;}
        int getClipType(){return clipType;}
        int getIndex(){return index-1;}
        int getMovieLength()
        {
        if(clipType == 0)return clipType;
        return Math.round(_playerVideo->get_duration()*(100 / 3.33));
        }
        int getCurrentTime()
        {
        if(clipType == 0)return clipType;
        return Math.round(_playerVideo->get_currentTime()*(100 / 3.33));
        }
        void setCurrentTime(int value)
        {
        double cTime = value / (100 / 3.3);
        if(clipType > 0)
            _playerVideo->set_currentTime(cTime);
        }
        float getInnerWidth(MovieClip* component){return (x+width)-component->getWidth();}
        float getWidth(){return width;}
        float getHeight(){return height;}
        float getX(){return x;}
        float getY(){return y;}
        float getAlpha(){return alpha;}
        void setRotate(float value)
        {
        rotate = value;
        rotation = new float[3];
        rotation[0] = 0;
        rotation[1] = 0;
        rotation[2] = rotate;
        }
        float getRotate(){return rotate;}
        void setRect(float w, float h)
        {
        width = w; height = h;
        updateBuffer(); 
        }
        void setPos(float _x, float _y)
        {
        x = _x; y = _y; 
        position = new float[3]; 
        position[0] = _x; 
        position[1] = _y; 
        position[2] = 0;
        }
        void setAlpha(float value){alpha = value;}
        void setStepAnimOffset(int offset);
        int **getAnimOffset(){return _anim_offset;}
        void printAnimOffset()
        {
        for(int i=0; i<MAX_ANIM_OFFSET; i++)
            console.log(_anim_offset[i][0]," ",_anim_offset[i][1]);
        }
        HTMLImageElement* getImageElement(){return _playerImage;}
        HTMLVideoElement* getVideoElement(){return _playerVideo;}
        void loadMovieClip(const char* url, int type);
        void loadSprite(const char* url, int type);
        void setIsTexture(bool value){isTexture = value;}
        bool getIsTexture(){return isTexture;}
        void setLockX(vec2 value){lockX = value;}
        void setLockY(vec2 value){lockY = value;}
        void setDragDrop(bool value){DragDrop = value;}
        bool getIsDrag(){return isDrag;}
        void setOffset(float _x, float _y){offsetX = _x, offsetY = _y;}
        float getOffsetX(){return offsetX;}
        float getOffsetY(){return offsetY;}
        bool hitSelect(Camera *cam)
        {
        return ((cam->getMouseX() > x+(width / 3)) && (cam->getMouseX() < (x+width)+(width / 2)) 
               && (cam->getMouseY() > y) && (cam->getMouseY() < (y+height)));
        }
        vec2* getLockX(){return &lockX;}
        vec2* getLockY(){return &lockY;}
        void setParent(MovieClip* value){Parent = value;}
        MovieClip* getParent(){return Parent;}
        float getLocalX(float value);
        void setLocalX(float max, float value){x = ((value / 240) * Parent->getWidth()) + 60;}
        void setTexturePointer(WebGLTexture* value){tex = value;}
        void OnMouseMove(float _x, float _y);
        void OnMouseDown(float _x, float _y);
        void OnMouseUp(float _x, float _y);
        void updateTexture();
        void Render(bool textured, Camera* cam);
    protected:

    private:
        void updateBuffer();
        void InitTexture();
        char *name, *type;
        float width, height, x, y, alpha, quality, rotate, offsetX, offsetY;
        bool ontimeupdate, isPlaying, copyVideo, isTexture;
        bool isDrag, DragDrop;
        vec2 lockX, lockY;
        float lastDragX,lastDragY;
        int clipType;
        float *color, *position, *rotation;
        float mvMatrix[16];
        int **_anim_offset;
        static int index;
        HTMLImageElement *_playerImage;
        HTMLVideoElement *_playerVideo;
        WebGLTexture *tex;
        WebGLBuffer* positionBuf;
        WebGLBuffer* texcoordBuf;
        WebGLRenderingContext* gl;
        MovieClip* Parent;
};

#endif // MOVIECLIP_H
