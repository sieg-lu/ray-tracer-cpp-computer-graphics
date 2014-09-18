#ifndef __V_MATH_H__
#define __V_MATH_H__

#define _USE_MATH_DEFINES

#include <math.h>

static const double PI = acos(-1.0);

inline bool DoubleEquals(double a, double b, double eps = 1e-5)
{
    if (fabs(a - b) < eps) {
        return true;
    }
    return false;
}
inline int DoubleCompare(double a, double b, double eps = 1e-5)
{
    if (DoubleEquals(a, b, eps)) {
        return 0;
    }
    if (a < b) {
        return -1;
    }
    return 1;
}

class Vector2D
{
public:
    union {
        struct { double x, y; };
        struct { double s, t; };
        struct { double r, g; };
        double num[2];
    };
    Vector2D() : x(0.0f), y(0.0f) { }
    ~Vector2D() { }
    Vector2D(double num) : x(num), y(num) { }
    Vector2D(double x, double y) : x(x), y(y) { }
    Vector2D(const Vector2D &u) : x(u.x), y(u.y) { }
    inline Vector2D& operator = (const Vector2D &u) { x = u.x; y = u.y; return *this; }
    inline Vector2D operator - () { return Vector2D(-x, -y); }
    inline Vector2D& operator += (double num) { x += num; y += num; return *this; }
    inline Vector2D& operator += (const Vector2D &u) { x += u.x; y += u.y; return *this; }
    inline Vector2D& operator -= (double num) { x -= num; y -= num; return *this; }
    inline Vector2D& operator -= (const Vector2D &u) { x -= u.x; y -= u.y; return *this; }
    inline Vector2D& operator *= (double num) { x *= num; y *= num; return *this; }
    inline Vector2D& operator *= (const Vector2D &u) { x *= u.x; y *= u.y; return *this; }
    inline Vector2D& operator /= (double num) { x /= num; y /= num; return *this; }
    inline Vector2D& operator /= (const Vector2D &u) { x /= u.x; y /= u.y; return *this; }
    inline bool operator == (const Vector2D &u) { return DoubleEquals(x, u.x) && DoubleEquals(y, u.y); }
    inline bool operator != (const Vector2D &u) { return !(DoubleEquals(x, u.x) && DoubleEquals(y, u.y)); }
    friend inline Vector2D operator + (const Vector2D &u, double num) { return Vector2D(u.x + num, u.y + num); }
    friend inline Vector2D operator + (double num, const Vector2D &u) { return Vector2D(num + u.x, num + u.y); }
    friend inline Vector2D operator + (const Vector2D &u, const Vector2D &v) { return Vector2D(u.x + v.x, u.y + v.y); }
    friend inline Vector2D operator - (const Vector2D &u, double num) { return Vector2D(u.x - num, u.y - num); }
    friend inline Vector2D operator - (double num, const Vector2D &u) { return Vector2D(num - u.x, num - u.y); }
    friend inline Vector2D operator - (const Vector2D &u, const Vector2D &v) { return Vector2D(u.x - v.x, u.y - v.y); }
    friend inline Vector2D operator * (const Vector2D &u, double num) { return Vector2D(u.x * num, u.y * num); }
    friend inline Vector2D operator * (double num, const Vector2D &u) { return Vector2D(num * u.x, num * u.y); }
    friend inline Vector2D operator * (const Vector2D &u, const Vector2D &v) { return Vector2D(u.x * v.x, u.y * v.y); }
    friend inline Vector2D operator / (const Vector2D &u, double num) { return Vector2D(u.x / num, u.y / num); }
    friend inline Vector2D operator / (double num, const Vector2D &u) { return Vector2D(num / u.x, num / u.y); }
    friend inline Vector2D operator / (const Vector2D &u, const Vector2D &v) { return Vector2D(u.x / v.x, u.y / v.y); }
};

// ----------------------------------------------------------------------------------------------------------------------------

class Vector3D
{
public:
    union {
        struct { double x, y, z; };
        struct { double s, t, p; };
        struct { double r, g, b; };
        double num[3];
    };
    Vector3D() : x(0.0f), y(0.0f), z(0.0f) { }
    ~Vector3D() { }
    Vector3D(double num) : x(num), y(num), z(num) { }
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) { }
    Vector3D(const Vector2D &u, double z) : x(u.x), y(u.y), z(z) { }
    Vector3D(const Vector3D &u) : x(u.x), y(u.y), z(u.z) { }
    inline Vector3D& operator = (const Vector3D &u) { x = u.x; y = u.y; z = u.z; return *this; }
    inline Vector3D operator - () { return Vector3D(-x, -y, -z); }
    inline double* operator & () { return (double*)this; }
    inline operator Vector2D () { return *(Vector2D*)this; }
    inline Vector3D& operator += (double num) { x += num; y += num; z += num; return *this; }
    inline Vector3D& operator += (const Vector3D &u) { x += u.x; y += u.y; z += u.z; return *this; }
    inline Vector3D& operator -= (double num) { x -= num; y -= num; z -= num; return *this; }
    inline Vector3D& operator -= (const Vector3D &u) { x -= u.x; y -= u.y; z -= u.z; return *this; }
    inline Vector3D& operator *= (double num) { x *= num; y *= num; z *= num; return *this; }
    inline Vector3D& operator *= (const Vector3D &u) { x *= u.x; y *= u.y; z *= u.z; return *this; }
    inline Vector3D& operator /= (double num) { x /= num; y /= num; z /= num; return *this; }
    inline Vector3D& operator /= (const Vector3D &u) { x /= u.x; y /= u.y; z /= u.z; return *this; }
    inline bool operator == (const Vector3D &u) { return DoubleEquals(x, u.x) && DoubleEquals(y, u.y) && DoubleEquals(z, u.z); }
    inline bool operator != (const Vector3D &u) { return !(DoubleEquals(x, u.x) && DoubleEquals(y, u.y) && DoubleEquals(z, u.z)); }
    friend inline Vector3D operator + (const Vector3D &u, double num) { return Vector3D(u.x + num, u.y + num, u.z + num); }
    friend inline Vector3D operator + (double num, const Vector3D &u) { return Vector3D(num + u.x, num + u.y, num + u.z); }
    friend inline Vector3D operator + (const Vector3D &u, const Vector3D &v) { return Vector3D(u.x + v.x, u.y + v.y, u.z + v.z); }
    friend inline Vector3D operator - (const Vector3D &u, double num) { return Vector3D(u.x - num, u.y - num, u.z - num); }
    friend inline Vector3D operator - (double num, const Vector3D &u) { return Vector3D(num - u.x, num - u.y, num - u.z); }
    friend inline Vector3D operator - (const Vector3D &u, const Vector3D &v) { return Vector3D(u.x - v.x, u.y - v.y, u.z - v.z); }
    friend inline Vector3D operator * (const Vector3D &u, double num) { return Vector3D(u.x * num, u.y * num, u.z * num); }
    friend inline Vector3D operator * (double num, const Vector3D &u) { return Vector3D(num * u.x, num * u.y, num * u.z); }
    friend inline Vector3D operator * (const Vector3D &u, const Vector3D &v) { return Vector3D(u.x * v.x, u.y * v.y, u.z * v.z); }
    friend inline Vector3D operator / (const Vector3D &u, double num) { return Vector3D(u.x / num, u.y / num, u.z / num); }
    friend inline Vector3D operator / (double num, const Vector3D &u) { return Vector3D(num / u.x, num / u.y, num / u.z); }
    friend inline Vector3D operator / (const Vector3D &u, const Vector3D &v) { return Vector3D(u.x / v.x, u.y / v.y, u.z / v.z); }
};

// ----------------------------------------------------------------------------------------------------------------------------

class Vector4D
{
public:
    union {
        struct { double x, y, z, w; };
        struct { double s, t, p, q; };
        struct { double r, g, b, a; };
        double num[4];
    };
    Vector4D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    ~Vector4D() { }
    Vector4D(double num) : x(num), y(num), z(num), w(num) { }
    Vector4D(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) { }
    Vector4D(const Vector2D &u, double z, double w) : x(u.x), y(u.y), z(z), w(w) { }
    Vector4D(const Vector3D &u, double w) : x(u.x), y(u.y), z(u.z), w(w) { }
    Vector4D(const Vector4D &u) : x(u.x), y(u.y), z(u.z), w(u.w) { }
    inline Vector4D& operator = (const Vector4D &u) { x = u.x; y = u.y; z = u.z; w = u.w; return *this; }
    inline Vector4D operator - () { return Vector4D(-x, -y, -z, -w); }
    inline double* operator & () { return (double*)this; }
    inline operator Vector2D () { return *(Vector2D*)this; }
    inline operator Vector3D () { return *(Vector3D*)this; }
    inline Vector4D& operator += (double num) { x += num; y += num; z += num; w += num; return *this; }
    inline Vector4D& operator += (const Vector4D &u) { x += u.x; y += u.y; z += u.z; w += u.w; return *this; }
    inline Vector4D& operator -= (double num) { x -= num; y -= num; z -= num; w -= num; return *this; }
    inline Vector4D& operator -= (const Vector4D &u) { x -= u.x; y -= u.y; z -= u.z; w -= u.w; return *this; }
    inline Vector4D& operator *= (double num) { x *= num; y *= num; z *= num; w *= num; return *this; }
    inline Vector4D& operator *= (const Vector4D &u) { x *= u.x; y *= u.y; z *= u.z; w *= u.w; return *this; }
    inline Vector4D& operator /= (double num) { x /= num; y /= num; z /= num; w /= num; return *this; }
    inline Vector4D& operator /= (const Vector4D &u) { x /= u.x; y /= u.y; z /= u.z; w /= u.w; return *this; }
    inline bool operator == (const Vector4D &u) { return DoubleEquals(x, u.x) && DoubleEquals(y, u.y) && DoubleEquals(z, u.z) && DoubleEquals(w, u.w); }
    inline bool operator != (const Vector4D &u) { return !(DoubleEquals(x, u.x) && DoubleEquals(y, u.y) && DoubleEquals(z, u.z) && DoubleEquals(w, u.w)); }
    friend inline Vector4D operator + (const Vector4D &u, double num) { return Vector4D(u.x + num, u.y + num, u.z + num, u.w + num); }
    friend inline Vector4D operator + (double num, const Vector4D &u) { return Vector4D(num + u.x, num + u.y, num + u.z, num + u.w); }
    friend inline Vector4D operator + (const Vector4D &u, const Vector4D &v) { return Vector4D(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w); }
    friend inline Vector4D operator - (const Vector4D &u, double num) { return Vector4D(u.x - num, u.y - num, u.z - num, u.w - num); }
    friend inline Vector4D operator - (double num, const Vector4D &u) { return Vector4D(num - u.x, num - u.y, num - u.z, num - u.w); }
    friend inline Vector4D operator - (const Vector4D &u, const Vector4D &v) { return Vector4D(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w); }
    friend inline Vector4D operator * (const Vector4D &u, double num) { return Vector4D(u.x * num, u.y * num, u.z * num, u.w * num); }
    friend inline Vector4D operator * (double num, const Vector4D &u) { return Vector4D(num * u.x, num * u.y, num * u.z, num * u.w); }
    friend inline Vector4D operator * (const Vector4D &u, const Vector4D &v) { return Vector4D(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w); }
    friend inline Vector4D operator / (const Vector4D &u, double num) { return Vector4D(u.x / num, u.y / num, u.z / num, u.w / num); }
    friend inline Vector4D operator / (double num, const Vector4D &u) { return Vector4D(num / u.x, num / u.y, num / u.z, num / u.w); }
    friend inline Vector4D operator / (const Vector4D &u, const Vector4D &v) { return Vector4D(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w); }
};

// ----------------------------------------------------------------------------------------------------------------------------

class Matrix
{
public:
    double M[16];
    Matrix()
    {
        M[0] = 1.0f; M[4] = 0.0f; M[8] = 0.0f; M[12] = 0.0f;
        M[1] = 0.0f; M[5] = 1.0f; M[9] = 0.0f; M[13] = 0.0f;
        M[2] = 0.0f; M[6] = 0.0f; M[10] = 1.0f; M[14] = 0.0f;
        M[3] = 0.0f; M[7] = 0.0f; M[11] = 0.0f; M[15] = 1.0f;
    }
    ~Matrix() { }
    Matrix(const Matrix &Matrix)
    {
        for (int i = 0; i < 16; i++) {
            M[i] = Matrix.M[i];
        }
    }
    Matrix& operator = (const Matrix &Matrix)
    {
        for (int i = 0; i < 16; i++) {
            M[i] = Matrix.M[i];
        }
        return *this;
    }
    inline double& operator [] (int Index)
    {
        return M[Index];
    }
    inline double* operator & ()
    {
        return (double*)this;
    }
    friend inline Matrix operator * (const Matrix &Matrix1, const Matrix &Matrix2)
    {
        Matrix Matrix3;

        Matrix3.M[0] = Matrix1.M[0] * Matrix2.M[0] + Matrix1.M[4] * Matrix2.M[1] + Matrix1.M[8] * Matrix2.M[2] + Matrix1.M[12] * Matrix2.M[3];
        Matrix3.M[1] = Matrix1.M[1] * Matrix2.M[0] + Matrix1.M[5] * Matrix2.M[1] + Matrix1.M[9] * Matrix2.M[2] + Matrix1.M[13] * Matrix2.M[3];
        Matrix3.M[2] = Matrix1.M[2] * Matrix2.M[0] + Matrix1.M[6] * Matrix2.M[1] + Matrix1.M[10] * Matrix2.M[2] + Matrix1.M[14] * Matrix2.M[3];
        Matrix3.M[3] = Matrix1.M[3] * Matrix2.M[0] + Matrix1.M[7] * Matrix2.M[1] + Matrix1.M[11] * Matrix2.M[2] + Matrix1.M[15] * Matrix2.M[3];

        Matrix3.M[4] = Matrix1.M[0] * Matrix2.M[4] + Matrix1.M[4] * Matrix2.M[5] + Matrix1.M[8] * Matrix2.M[6] + Matrix1.M[12] * Matrix2.M[7];
        Matrix3.M[5] = Matrix1.M[1] * Matrix2.M[4] + Matrix1.M[5] * Matrix2.M[5] + Matrix1.M[9] * Matrix2.M[6] + Matrix1.M[13] * Matrix2.M[7];
        Matrix3.M[6] = Matrix1.M[2] * Matrix2.M[4] + Matrix1.M[6] * Matrix2.M[5] + Matrix1.M[10] * Matrix2.M[6] + Matrix1.M[14] * Matrix2.M[7];
        Matrix3.M[7] = Matrix1.M[3] * Matrix2.M[4] + Matrix1.M[7] * Matrix2.M[5] + Matrix1.M[11] * Matrix2.M[6] + Matrix1.M[15] * Matrix2.M[7];

        Matrix3.M[8] = Matrix1.M[0] * Matrix2.M[8] + Matrix1.M[4] * Matrix2.M[9] + Matrix1.M[8] * Matrix2.M[10] + Matrix1.M[12] * Matrix2.M[11];
        Matrix3.M[9] = Matrix1.M[1] * Matrix2.M[8] + Matrix1.M[5] * Matrix2.M[9] + Matrix1.M[9] * Matrix2.M[10] + Matrix1.M[13] * Matrix2.M[11];
        Matrix3.M[10] = Matrix1.M[2] * Matrix2.M[8] + Matrix1.M[6] * Matrix2.M[9] + Matrix1.M[10] * Matrix2.M[10] + Matrix1.M[14] * Matrix2.M[11];
        Matrix3.M[11] = Matrix1.M[3] * Matrix2.M[8] + Matrix1.M[7] * Matrix2.M[9] + Matrix1.M[11] * Matrix2.M[10] + Matrix1.M[15] * Matrix2.M[11];

        Matrix3.M[12] = Matrix1.M[0] * Matrix2.M[12] + Matrix1.M[4] * Matrix2.M[13] + Matrix1.M[8] * Matrix2.M[14] + Matrix1.M[12] * Matrix2.M[15];
        Matrix3.M[13] = Matrix1.M[1] * Matrix2.M[12] + Matrix1.M[5] * Matrix2.M[13] + Matrix1.M[9] * Matrix2.M[14] + Matrix1.M[13] * Matrix2.M[15];
        Matrix3.M[14] = Matrix1.M[2] * Matrix2.M[12] + Matrix1.M[6] * Matrix2.M[13] + Matrix1.M[10] * Matrix2.M[14] + Matrix1.M[14] * Matrix2.M[15];
        Matrix3.M[15] = Matrix1.M[3] * Matrix2.M[12] + Matrix1.M[7] * Matrix2.M[13] + Matrix1.M[11] * Matrix2.M[14] + Matrix1.M[15] * Matrix2.M[15];

        return Matrix3;
    }
    friend inline Vector2D operator * (const Matrix &Matrix, const Vector2D &Vector)
    {
        return Matrix * Vector4D(Vector, 0.0f, 1.0f);
    }
    friend inline Vector3D operator * (const Matrix &Matrix, const Vector3D &Vector)
    {
        return Matrix * Vector4D(Vector, 1.0f);
    }
    friend inline Vector4D operator * (const Matrix &Matrix, const Vector4D &Vector)
    {
        Vector4D v;
        v.x = Matrix.M[0] * Vector.x + Matrix.M[4] * Vector.y + Matrix.M[8] * Vector.z + Matrix.M[12] * Vector.w;
        v.y = Matrix.M[1] * Vector.x + Matrix.M[5] * Vector.y + Matrix.M[9] * Vector.z + Matrix.M[13] * Vector.w;
        v.z = Matrix.M[2] * Vector.x + Matrix.M[6] * Vector.y + Matrix.M[10] * Vector.z + Matrix.M[14] * Vector.w;
        v.w = Matrix.M[3] * Vector.x + Matrix.M[7] * Vector.y + Matrix.M[11] * Vector.z + Matrix.M[15] * Vector.w;
        return v;
    }
};

inline Vector2D Normalize(const Vector2D &u)
{
    return u * (1.0f / sqrt(u.x * u.x + u.y * u.y));
}
inline Vector3D Normalize(const Vector3D &u)
{
    return u * (1.0f / sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}
inline Matrix RotationMatrix(double angle, const Vector3D &u)
{
    Matrix R;
    angle = angle / 180.0f * (double)M_PI;
    Vector3D v = Normalize(u);
    double c = 1.0f - cos(angle), s = sin(angle);

    R[0] = 1.0f + c * (v.x * v.x - 1.0f);
    R[1] = c * v.x * v.y + v.z * s;
    R[2] = c * v.x * v.z - v.y * s;
    R[3] = 0.0f;

    R[4] = c * v.x * v.y - v.z * s;
    R[5] = 1.0f + c * (v.y * v.y - 1.0f);
    R[6] = c * v.y * v.z + v.x * s;
    R[7] = 0.0f;

    R[8] = c * v.x * v.z + v.y * s;
    R[9] = c * v.y * v.z - v.x * s;
    R[10] = 1.0f + c * (v.z * v.z - 1.0f);
    R[11] = 0.0f;

    R[12] = 0.0f;
    R[13] = 0.0f;
    R[14] = 0.0f;
    R[15] = 1.0f;

    return R;
}
// ----------------------------------------------------------------------------------------------------------------------------

inline double Dot(const Vector2D &u, const Vector2D &v)
{
    return u.x * v.x + u.y * v.y;
}
inline double Length(const Vector2D &u)
{
    return sqrt(u.x * u.x + u.y * u.y);
}
inline double Length2(const Vector2D &u)
{
    return u.x * u.x + u.y * u.y;
}
inline Vector2D Reflect(const Vector2D &i, const Vector2D &n)
{
    return i - 2.0f * Dot(n, i) * n;
}
inline Vector2D Refract(const Vector2D &i, const Vector2D &n, double eta)
{
    Vector2D r;
    double ndoti = Dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);
    if (k >= 0.0f) {
        r = eta * i - n * (eta * ndoti + sqrt(k));
    }
    return r;
}
inline Vector2D Rotate(const Vector2D &u, double angle)
{
    return RotationMatrix(angle, Vector3D(0.0f, 0.0f, 1.0f)) * Vector4D(u, 0.0f, 1.0f);
}

// ----------------------------------------------------------------------------------------------------------------------------

inline Vector3D Cross(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}
inline double Dot(const Vector3D &u, const Vector3D &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
inline double Length(const Vector3D &u)
{
    return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}
inline double Length2(const Vector3D &u)
{
    return u.x * u.x + u.y * u.y + u.z * u.z;
}
inline Vector3D Mix(const Vector3D &u, const Vector3D &v, double a)
{
    return u * (1.0f - a) + v * a;
}
inline Vector3D Reflect(const Vector3D &i, const Vector3D &n)
{
    return i - 2.0f * Dot(n, i) * n;
}
inline Vector3D Refract(const Vector3D &i, const Vector3D &n, double eta)
{
    Vector3D r;
    double ndoti = Dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);
    if (k >= 0.0f) {
        r = eta * i - n * (eta * ndoti + sqrt(k));
    }
    return r;
}
inline Vector3D Rotate(const Vector3D &u, double angle, const Vector3D &v)
{
    return RotationMatrix(angle, v) * Vector4D(u, 1.0f);
}
inline Vector3D Limit(const Vector3D& src, double bottom, double top)
{
    Vector3D result;
    if (src.r < bottom) {
        result.r = bottom;
    } else if (src.r > top) {
        result.r = top;
    } else {
        result.r = src.r;
    }
    if (src.g < bottom) {
        result.g = bottom;
    } else if (src.g > top) {
        result.g = top;
    } else {
        result.g = src.g;
    }
    if (src.b < bottom) {
        result.b = bottom;
    } else if (src.b > top) {
        result.b = top;
    } else {
        result.b = src.b;
    }
    return result;
}

// ----------------------------------------------------------------------------------------------------------------------------

inline Matrix BiasMatrix()
{
    Matrix B;
    B[0] = 0.5f; B[4] = 0.0f; B[8] = 0.0f; B[12] = 0.5f;
    B[1] = 0.0f; B[5] = 0.5f; B[9] = 0.0f; B[13] = 0.5f;
    B[2] = 0.0f; B[6] = 0.0f; B[10] = 0.5f; B[14] = 0.5f;
    B[3] = 0.0f; B[7] = 0.0f; B[11] = 0.0f; B[15] = 1.0f;
    return B;
}
inline Matrix BiasMatrixInverse()
{
    Matrix BI;
    BI[0] = 2.0f; BI[4] = 0.0f; BI[8] = 0.0f; BI[12] = -1.0f;
    BI[1] = 0.0f; BI[5] = 2.0f; BI[9] = 0.0f; BI[13] = -1.0f;
    BI[2] = 0.0f; BI[6] = 0.0f; BI[10] = 2.0f; BI[14] = -1.0f;
    BI[3] = 0.0f; BI[7] = 0.0f; BI[11] = 0.0f; BI[15] = 1.0f;
    return BI;
}
inline Matrix ViewMatrix(const Vector3D &x, const Vector3D &y, const Vector3D &z, const Vector3D &position)
{
    Matrix V;
    V[0] = x.x; V[1] = y.x; V[2] = z.x; V[3] = 0.0f;
    V[4] = x.y; V[5] = y.y; V[6] = z.y; V[7] = 0.0f;
    V[8] = x.z; V[9] = y.z; V[10] = z.z; V[11] = 0.0f;
    V[12] = -Dot(x, position); V[13] = -Dot(y, position); V[14] = -Dot(z, position); V[15] = 1.0f;
    return V;
}
inline Matrix ViewMatrixInverse(Matrix &V)
{
    Matrix VI;
    VI[0] = V[0]; VI[1] = V[4]; VI[2] = V[8]; VI[3] = 0.0f;
    VI[4] = V[1]; VI[5] = V[5]; VI[6] = V[9]; VI[7] = 0.0f;
    VI[8] = V[2]; VI[9] = V[6]; VI[10] = V[10]; VI[11] = 0.0f;

    VI[12] = -(VI[0] * V[12] + VI[4] * V[13] + VI[8] * V[14]);
    VI[13] = -(VI[1] * V[12] + VI[5] * V[13] + VI[9] * V[14]);
    VI[14] = -(VI[2] * V[12] + VI[6] * V[13] + VI[10] * V[14]);
    VI[15] = 1.0f;
    return VI;
}
inline Matrix OrthoProjectionMatrix(double left, double right, double bottom, double top, double n, double f)
{
    Matrix OP;
    OP[0] = 2.0f / (right - left);OP[1] = 0.0f;OP[2] = 0.0f;OP[3] = 0.0f;
    OP[4] = 0.0f;OP[5] = 2.0f / (top - bottom);OP[6] = 0.0f;OP[7] = 0.0f;
    OP[8] = 0.0f;OP[9] = 0.0f;OP[10] = -2.0f / (f - n);OP[11] = 0.0f;

    OP[12] = -(right + left) / (right - left);
    OP[13] = -(top + bottom) / (top - bottom);
    OP[14] = -(f + n) / (f - n);
    OP[15] = 1.0f;
    return OP;
}
inline Matrix PerspectiveProjectionMatrix(double fovy, double x, double y, double n, double f)
{
    Matrix PP;
    double coty = 1.0f / tan(fovy * (double)M_PI / 360.0f);
    double aspect = x / (y > 0.0f ? y : 1.0f);
    PP[0] = coty / aspect; PP[1] = 0.0f; PP[2] = 0.0f; PP[3] = 0.0f;
    PP[4] = 0.0f; PP[5] = coty; PP[6] = 0.0f; PP[7] = 0.0f;
    PP[8] = 0.0f; PP[9] = 0.0f; PP[10] = (n + f) / (n - f); PP[11] = -1.0f;
    PP[12] = 0.0f; PP[13] = 0.0f; PP[14] = 2.0f * n * f / (n - f); PP[15] = 0.0f;
    return PP;
}
inline Matrix PerspectiveProjectionMatrixInverse(Matrix &PP)
{
    Matrix PPI;
    PPI[0] = 1.0f / PP[0]; PPI[1] = 0.0f; PPI[2] = 0.0f; PPI[3] = 0.0f;
    PPI[4] = 0.0f; PPI[5] = 1.0f / PP[5]; PPI[6] = 0.0f; PPI[7] = 0.0f;
    PPI[8] = 0.0f; PPI[9] = 0.0f; PPI[10] = 0.0f; PPI[11] = 1.0f / PP[14];
    PPI[12] = 0.0f; PPI[13] = 0.0f; PPI[14] = 1.0f / PP[11]; PPI[15] = -PP[10] / (PP[11] * PP[14]);
    return PPI;
}
inline Matrix ScaleMatrix(double x, double y, double z)
{
    Matrix S;
    S[0] = x; S[1] = 0.0f; S[2] = 0.0f; S[3] = 0.0f;
    S[4] = 0.0f; S[5] = y; S[6] = 0.0f; S[7] = 0.0f;
    S[8] = 0.0f; S[9] = 0.0f; S[10] = z; S[11] = 0.0f;
    S[12] = 0.0f; S[13] = 0.0f; S[14] = 0.0f; S[15] = 1.0f;
    return S;
}
inline Matrix TranslationMatrix(double x, double y, double z)
{
    Matrix T;
    T[0] = 1.0f; T[1] = 0.0f; T[2] = 0.0f; T[3] = 0.0f;
    T[4] = 0.0f; T[5] = 1.0f; T[6] = 0.0f; T[7] = 0.0f;
    T[8] = 0.0f; T[9] = 0.0f; T[10] = 1.0f; T[11] = 0.0f;
    T[12] = x; T[13] = y; T[14] = z; T[15] = 1.0f;
    return T;
}

// ----------------------------------------------------------------------------------------------------------------------------

#endif