#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

class  Camera 
{
public:
        Camera();
        float get_X(){return _x;}
        void set_X(float value){_x = value;}
        float get_Y(){return _y;}
        void set_Y(float value){_y = value;}
        float getMouseX(){return mouseX;}
        float getMouseY(){return mouseY;}
        void OnMouseDown(float x, float y);
        void OnMouseMove(float x, float y);
        void OnMouseUp(float x, float y);
        void OnMouseDown(MouseEvent* e){OnMouseDown(e->get_clientX(),e->get_clientY());}
        void OnMouseMove(MouseEvent* e){OnMouseMove(e->get_clientX(),e->get_clientY());}
        void OnMouseUp(MouseEvent* e){OnMouseUp(e->get_clientX(),e->get_clientY());}
        void Update();
protected:

private:
        float _x, _y;
        float mX, mY, dragX, dragY, lastX, lastY, mapX, mapY, tgtX, tgtY;
        float dx, dy, dist, dragDist, angle, step, mouseX, mouseY;
        bool mapDrag;
};
#endif // CAMERA_H
