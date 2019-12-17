#ifndef MATRIX_H
#define MATRIX_H

using namespace client;

const float M[4][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
inline const int getItemMatrix(int x, int y) {return M[x][y];}

void MakePerspective(float* matrix, double FOV, double AspectRatio, double Closest, double Farest)
{
	double YLimit = Closest * client::Math.tan(FOV * client::Math.get_PI() / 360);
	double A = -( Farest + Closest ) / ( Farest - Closest );
	double B = -2 * Farest * Closest / ( Farest - Closest );
	double C = (2 * Closest) / ( (YLimit * AspectRatio) * 2 );
	double D = (2 * Closest) / ( YLimit * 2 );
	double f = client::Math.tan(FOV * client::Math.get_PI() / 360);

	matrix[0] = C;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 0;

	matrix[4] = 0;
	matrix[5] = D;
	matrix[6] = 0;
	matrix[7] = 0;

	matrix[8] = 0;
	matrix[9] = 0;
	matrix[10] = A;
	matrix[11] = -1;

	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = B;
	matrix[15] = 0;
}

void orthographic(float* matrix, float left, float right, float bottom, float top, float near, float far)
{
    matrix[0] = 2 / (right - left);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    
    matrix[4] = 0;
    matrix[5] = 2 / (top - bottom);
    matrix[6] = 0;
    matrix[7] = 0;
    
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 2 / (near - far);
    matrix[11] = 0;
    
    matrix[12] = (left + right) / (left - right);
    matrix[13] = (bottom + top) / (bottom - top);
    matrix[14] = (near + far) / (near - far);
    matrix[15] = 1;
}

void MakeIdentity(float* matrix)
{
        matrix[0]=1;
	matrix[1]=0;
	matrix[2]=0;
	matrix[3]=0;

	matrix[4]=0;
	matrix[5]=1;
	matrix[6]=0;
	matrix[7]=0;

	matrix[8]=0;
	matrix[9]=0;
	matrix[10]=1;
	matrix[11]=0;

	matrix[12]=0;
	matrix[13]=0;
	matrix[14]=0;
	matrix[15]=1;
}

void Translate(float* matrix, float x, float y, float z)
{
	float nx=matrix[0]*x + matrix[4]*y + matrix[8]*z + matrix[12];
	float ny=matrix[1]*x + matrix[5]*y + matrix[9]*z + matrix[13];
	float nz=matrix[2]*x + matrix[6]*y + matrix[10]*z + matrix[14];
	float nw=matrix[3]*x + matrix[7]*y + matrix[11]*z + matrix[15];

	matrix[12]=x;
	matrix[13]=y;
	matrix[14]=z;
	matrix[15]=nw;
}

float* multiply(float *a, float *b, float *dst) {
if((!a) || (!b))return NULL;
    float b00 = b[0 * 4 + 0];
    float b01 = b[0 * 4 + 1];
    float b02 = b[0 * 4 + 2];
    float b03 = b[0 * 4 + 3];
    float b10 = b[1 * 4 + 0];
    float b11 = b[1 * 4 + 1];
    float b12 = b[1 * 4 + 2];
    float b13 = b[1 * 4 + 3];
    float b20 = b[2 * 4 + 0];
    float b21 = b[2 * 4 + 1];
    float b22 = b[2 * 4 + 2];
    float b23 = b[2 * 4 + 3];
    float b30 = b[3 * 4 + 0];
    float b31 = b[3 * 4 + 1];
    float b32 = b[3 * 4 + 2];
    float b33 = b[3 * 4 + 3];
    float a00 = a[0 * 4 + 0];
    float a01 = a[0 * 4 + 1];
    float a02 = a[0 * 4 + 2];
    float a03 = a[0 * 4 + 3];
    float a10 = a[1 * 4 + 0];
    float a11 = a[1 * 4 + 1];
    float a12 = a[1 * 4 + 2];
    float a13 = a[1 * 4 + 3];
    float a20 = a[2 * 4 + 0];
    float a21 = a[2 * 4 + 1];
    float a22 = a[2 * 4 + 2];
    float a23 = a[2 * 4 + 3];
    float a30 = a[3 * 4 + 0];
    float a31 = a[3 * 4 + 1];
    float a32 = a[3 * 4 + 2];
    float a33 = a[3 * 4 + 3];
    dst[ 0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
    dst[ 1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
    dst[ 2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
    dst[ 3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
    dst[ 4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
    dst[ 5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
    dst[ 6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
    dst[ 7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
    dst[ 8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
    dst[ 9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
    dst[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
    dst[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
    dst[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
    dst[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
    dst[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
    dst[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
    return dst;
  }

float* axisRotation(float *axis, float angleInRadians, float *dst) 
{
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];
    float n = Math.sqrt(x * x + y * y + z * z);
    x /= n;
    y /= n;
    z /= n;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float c = Math.cos(angleInRadians);
    float s = Math.sin(angleInRadians);
    float oneMinusCosine = 1 - c;

    dst[ 0] = xx + (1 - xx) * c;
    dst[ 1] = x * y * oneMinusCosine + z * s;
    dst[ 2] = x * z * oneMinusCosine - y * s;
    dst[ 3] = 0;
    dst[ 4] = x * y * oneMinusCosine - z * s;
    dst[ 5] = yy + (1 - yy) * c;
    dst[ 6] = y * z * oneMinusCosine + x * s;
    dst[ 7] = 0;
    dst[ 8] = x * z * oneMinusCosine + y * s;
    dst[ 9] = y * z * oneMinusCosine - x * s;
    dst[10] = zz + (1 - zz) * c;
    dst[11] = 0;
    dst[12] = 0;
    dst[13] = 0;
    dst[14] = 0;
    dst[15] = 1;
    return dst;
}

void axisRotate(float *m, float *axis, float angleInRadians, float *dst) 
{
float angleInRadian = angleInRadians * Math.get_PI() / 360;
multiply(m, axisRotation(axis, angleInRadian, dst),dst);
}

#endif // MATRIX_H
