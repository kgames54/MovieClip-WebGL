#include "Camera.h"

Camera::Camera()
{
_x = 0, _y = 0, mX = 0, mY = 0, dragX = 0, dragY = 0, mapX = 0, mapY = 0, tgtX = 0, tgtY = 0;
lastX = 0, lastY = 0, dx = 0, dy = 0, dist = 0, dragDist = 0, angle = 0, step = 0;
mapDrag = false;
}

void Camera::OnMouseDown(float x, float y)
{
mX = x;
mY = y;
mouseX = mX + _x;
mouseY = mY + _y;
lastX = -mX - dragX;
lastY = -mY - dragY;
mapDrag = true;
}

void Camera::OnMouseMove(float x, float y)
{
    mouseX = x + _x;
    mouseY = y + _y;
    if(mapDrag)
    {
    mX = x;
    mY = y;
    dragX = -mX - lastX;
    dragY = -mY - lastY;
    }
}

void Camera::OnMouseUp(float x, float y)
{
mouseX = x + _x;
mouseX = y + _y;
dragX = -mX - lastX;
dragY = -mY - lastY;
dx = dragX - mapX;
dy = dragY - mapY;
dist = Math.sqrt(dx*dx + dy*dy);
dragDist = dist;
mapDrag = false;
}

void Camera::Update()
{
dx = dragX - mapX;
dy = dragY - mapY;
dist = Math.sqrt(dx*dx + dy*dy);
angle = Math.atan2(dy, dx);
step-=dist / 10;
if(step < dist / 10)step = dist / 10;
    if((dist > step)) 
    {
    tgtX = mapX + step * Math.cos(angle);
    tgtY = mapY + step * Math.sin(angle);
    mapX = tgtX;
    mapY = tgtY;
    if(mapX < 0){mapX = 0; dragX = 0;}
    if(mapY < 0){mapY = 0; dragY = 0;}
    //if(mapX < (-(mapWidth*_zoom) + stage.stageWidth + 32)){mapX = -(mapWidth*_zoom) + stage.stageWidth + 32; dragX = mapX;}
    //if(mapY < (-(mapHeight*_zoom) + stage.stageHeight + 32)){mapY = -(mapHeight*_zoom) + stage.stageHeight + 32; dragY = mapY;}
    _x = mapX;
    _y = mapY;
    }
}
