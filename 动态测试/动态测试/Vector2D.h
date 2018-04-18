#include <math.h>

class Vector2D
{
public:

	float	x;
	float	y;

	Vector2D() {}

	Vector2D(float r, float s)
	{
		x = r;
		y = s;
	}

	Vector2D& Set(float r, float s)
	{
		x = r;
		y = s;
		return (*this);
	}

	float& operator [](long k)
	{
		return ((&x)[k]);
	}

	const float& operator [](long k) const
	{
		return ((&x)[k]);
	}

	Vector2D& operator +=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}

	Vector2D& operator -=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	Vector2D& operator *=(float t)
	{
		x *= t;
		y *= t;
		return (*this);
	}

	Vector2D& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		return (*this);
	}

	Vector2D& operator &=(const Vector2D& v)
	{
		x *= v.x;
		y *= v.y;
		return (*this);
	}

	Vector2D& Normalize(void)
	{
		
		return (*this *= (float)(1.0 / sqrt(x * x + y * y)));
	}
};


inline Vector2D operator -(const Vector2D& v)
{
	return (Vector2D(-v.x, -v.y));
}

inline Vector2D operator +(const Vector2D& v1, const Vector2D& v2)
{
	return (Vector2D(v1.x + v2.x, v1.y + v2.y));
}

inline Vector2D operator -(const Vector2D& v1, const Vector2D& v2)
{
	return (Vector2D(v1.x - v2.x, v1.y - v2.y));
}

inline Vector2D operator *(const Vector2D& v, float t)
{
	return (Vector2D(v.x * t, v.y * t));
}

inline Vector2D operator *(float t, const Vector2D& v)
{
	return (Vector2D(t * v.x, t * v.y));
}

inline Vector2D operator /(const Vector2D& v, float t)
{
	float f = 1.0F / t;
	return (Vector2D(v.x * f, v.y * f));
}

inline float operator *(const Vector2D& v1, const Vector2D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

inline Vector2D operator &(const Vector2D& v1, const Vector2D& v2)
{
	return (Vector2D(v1.x * v2.x, v1.y * v2.y));
}

inline bool operator ==(const Vector2D& v1, const Vector2D& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y));
}

inline bool operator !=(const Vector2D& v1, const Vector2D& v2)
{
	return ((v1.x != v2.x) || (v1.y != v2.y));
}


class Point2D : public Vector2D
{
public:

	Point2D() {}

	Point2D(float r, float s) : Vector2D(r, s) {}

	Vector2D& GetVector2D(void)
	{
		return (*this);
	}

	const Vector2D& GetVector2D(void) const
	{
		return (*this);
	}

	Point2D& operator =(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		return (*this);
	}

	Point2D& operator *=(float t)
	{
		x *= t;
		y *= t;
		return (*this);
	}

	Point2D& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		return (*this);
	}
};


inline Point2D operator -(const Point2D& p)
{
	return (Point2D(-p.x, -p.y));
}

inline Point2D operator +(const Point2D& p1, const Point2D& p2)
{
	return (Point2D(p1.x + p2.x, p1.y + p2.y));
}

inline Point2D operator +(const Point2D& p, const Vector2D& v)
{
	return (Point2D(p.x + v.x, p.y + v.y));
}

inline Point2D operator -(const Point2D& p, const Vector2D& v)
{
	return (Point2D(p.x - v.x, p.y - v.y));
}

inline Vector2D operator -(const Point2D& p1, const Point2D& p2)
{
	return (Vector2D(p1.x - p2.x, p1.y - p2.y));
}

inline Point2D operator *(const Point2D& p, float t)
{
	return (Point2D(p.x * t, p.y * t));
}

inline Point2D operator *(float t, const Point2D& p)
{
	return (Point2D(t * p.x, t * p.y));
}

inline Point2D operator /(const Point2D& p, float t)
{
	float f = 1.0F / t;
	return (Point2D(p.x * f, p.y * f));
}


inline float Dot(const Vector2D& v1, const Vector2D& v2)
{
	return (v1 * v2);
}

inline Vector2D ProjectOnto(const Vector2D& v1, const Vector2D& v2)
{
	return (v2 * (v1 * v2));
}

inline float Magnitude(const Vector2D& v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

inline float InverseMag(const Vector2D& v)
{
	return ((float)(1.0 / sqrt(v.x * v.x + v.y * v.y)));
}

inline float SquaredMag(const Vector2D& v)
{
	return (v.x * v.x + v.y * v.y);
}


class Vector3D
{
public:

	float	x;
	float	y;
	float	z;

	Vector3D() {}

	Vector3D(float r, float s, float t)
	{
		x = r;
		y = s;
		z = t;
	}

	Vector3D(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0.0F;
	}

	Vector3D(const Vector2D& v, float u)
	{
		x = v.x;
		y = v.y;
		z = u;
	}

	Vector3D& Set(float r, float s, float t)
	{
		x = r;
		y = s;
		z = t;
		return (*this);
	}

	Vector3D& Set(const Vector2D& v, float u)
	{
		x = v.x;
		y = v.y;
		z = u;
		return (*this);
	}

	float& operator [](long k)
	{
		return ((&x)[k]);
	}

	const float& operator [](long k) const
	{
		return ((&x)[k]);
	}

	Vector2D& GetVector2D(void)
	{
		return (*reinterpret_cast<Vector2D *>(this));
	}

	const Vector2D& GetVector2D(void) const
	{
		return (*reinterpret_cast<const Vector2D *>(this));
	}

	Point2D& GetPoint2D(void)
	{
		return (*reinterpret_cast<Point2D *>(this));
	}

	const Point2D& GetPoint2D(void) const
	{
		return (*reinterpret_cast<const Point2D *>(this));
	}

	Vector3D& operator =(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0.0F;
		return (*this);
	}

	Vector3D& operator +=(const Vector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vector3D& operator +=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}

	Vector3D& operator -=(const Vector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	Vector3D& operator -=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	Vector3D& operator *=(float t)
	{
		x *= t;
		y *= t;
		z *= t;
		return (*this);
	}

	Vector3D& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		z *= f;
		return (*this);
	}

	Vector3D& operator %=(const Vector3D& v)
	{
		float		r, s;

		r = y * v.z - z * v.y;
		s = z * v.x - x * v.z;
		z = x * v.y - y * v.x;
		x = r;
		y = s;

		return (*this);
	}

	Vector3D& operator &=(const Vector3D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return (*this);
	}

	Vector3D& Normalize(void)
	{
		return (*this *= (float)(1.0 / sqrt(x * x + y * y + z * z)));
	}
};


inline Vector3D operator -(const Vector3D& v)
{
	return (Vector3D(-v.x, -v.y, -v.z));
}

inline Vector3D operator +(const Vector3D& v1, const Vector3D& v2)
{
	return (Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

inline Vector3D operator +(const Vector3D& v1, const Vector2D& v2)
{
	return (Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z));
}

inline Vector3D operator -(const Vector3D& v1, const Vector3D& v2)
{
	return (Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

inline Vector3D operator -(const Vector3D& v1, const Vector2D& v2)
{
	return (Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z));
}

inline Vector3D operator *(const Vector3D& v, float t)
{
	return (Vector3D(v.x * t, v.y * t, v.z * t));
}

inline Vector3D operator *(float t, const Vector3D& v)
{
	return (Vector3D(t * v.x, t * v.y, t * v.z));
}

inline Vector3D operator /(const Vector3D& v, float t)
{
	float f = 1.0F / t;
	return (Vector3D(v.x * f, v.y * f, v.z * f));
}

inline float operator *(const Vector3D& v1, const Vector3D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float operator *(const Vector3D& v1, const Vector2D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

inline Vector3D operator %(const Vector3D& v1, const Vector3D& v2)
{
	return (Vector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
}

inline Vector3D operator &(const Vector3D& v1, const Vector3D& v2)
{
	return (Vector3D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

inline bool operator ==(const Vector3D& v1, const Vector3D& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z));
}

inline bool operator !=(const Vector3D& v1, const Vector3D& v2)
{
	return ((v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z));
}


class Point3D : public Vector3D
{
public:

	Point3D() {}

	Point3D(float r, float s, float t) : Vector3D(r, s, t) {}
	Point3D(const Vector2D& v) : Vector3D(v) {}
	Point3D(const Vector2D& v, float u) : Vector3D(v, u) {}

	Vector3D& GetVector3D(void)
	{
		return (*this);
	}

	const Vector3D& GetVector3D(void) const
	{
		return (*this);
	}

	Point2D& GetPoint2D(void)
	{
		return (*reinterpret_cast<Point2D *>(this));
	}

	const Point2D& GetPoint2D(void) const
	{
		return (*reinterpret_cast<const Point2D *>(this));
	}

	Point3D& operator =(const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);
	}

	Point3D& operator =(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0.0F;
		return (*this);
	}

	Point3D& operator *=(float t)
	{
		x *= t;
		y *= t;
		z *= t;
		return (*this);
	}

	Point3D& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		z *= f;
		return (*this);
	}

	Point3D& operator &=(const Vector3D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return (*this);
	}
};


inline Point3D operator -(const Point3D& p)
{
	return (Point3D(-p.x, -p.y, -p.z));
}

inline Point3D operator +(const Point3D& p1, const Point3D& p2)
{
	return (Point3D(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z));
}

inline Point3D operator +(const Point3D& p, const Vector3D& v)
{
	return (Point3D(p.x + v.x, p.y + v.y, p.z + v.z));
}

inline Point3D operator +(const Vector3D& v, const Point3D& p)
{
	return (Point3D(v.x + p.x, v.y + p.y, v.z + p.z));
}

inline Vector3D operator -(const Point3D& p1, const Point3D& p2)
{
	return (Vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
}

inline Point3D operator -(const Point3D& p, const Vector3D& v)
{
	return (Point3D(p.x - v.x, p.y - v.y, p.z - v.z));
}

inline Point3D operator -(const Vector3D& v, const Point3D& p)
{
	return (Point3D(v.x - p.x, v.y - p.y, v.z - p.z));
}

inline Point3D operator *(const Point3D& p, float t)
{
	return (Point3D(p.x * t, p.y * t, p.z * t));
}

inline Point3D operator *(float t, const Point3D& p)
{
	return (Point3D(t * p.x, t * p.y, t * p.z));
}

inline Point3D operator /(const Point3D& p, float t)
{
	float f = 1.0F / t;
	return (Point3D(p.x * f, p.y * f, p.z * f));
}

inline float operator *(const Point3D& p1, const Point3D& p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

inline float operator *(const Point3D& p, const Vector3D& v)
{
	return (p.x * v.x + p.y * v.y + p.z * v.z);
}

inline float operator *(const Vector3D& v, const Point3D& p)
{
	return (v.x * p.x + v.y * p.y + v.z * p.z);
}

inline float operator *(const Point3D& p, const Vector2D& v)
{
	return (p.x * v.x + p.y * v.y);
}

inline float operator *(const Vector2D& v, const Point3D& p)
{
	return (v.x * p.x + v.y * p.y);
}

inline Vector3D operator %(const Point3D& p1, const Point3D& p2)
{
	return (Vector3D(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x));
}

inline Vector3D operator %(const Point3D& p, const Vector3D& v)
{
	return (Vector3D(p.y * v.z - p.z * v.y, p.z * v.x - p.x * v.z, p.x * v.y - p.y * v.x));
}

inline Vector3D operator %(const Vector3D& v, const Point3D& p)
{
	return (Vector3D(v.y * p.z - v.z * p.y, v.z * p.x - v.x * p.z, v.x * p.y - v.y * p.x));
}

inline Point3D operator &(const Point3D& p1, const Point3D& p2)
{
	return (Point3D(p1.x * p2.x, p1.y * p2.y, p1.z * p2.z));
}

inline Point3D operator &(const Point3D& p, const Vector3D& v)
{
	return (Point3D(p.x * v.x, p.y * v.y, p.z * v.z));
}

inline Point3D operator &(const Vector3D& v, const Point3D& p)
{
	return (Point3D(v.x * p.x, v.y * p.y, v.z * p.z));
}


inline float Dot(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 * v2);
}

inline float Dot(const Point3D& p, const Vector3D& v)
{
	return (p * v);
}

inline Vector3D Cross(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 % v2);
}

inline Vector3D Cross(const Point3D& p, const Vector3D& v)
{
	return (p % v);
}

inline Vector3D ProjectOnto(const Vector3D& v1, const Vector3D& v2)
{
	return (v2 * (v1 * v2));
}

inline float Magnitude(const Vector3D& v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float InverseMag(const Vector3D& v)
{
	return ((float)(1.0 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z)));
}

inline float SquaredMag(const Vector3D& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}


class Vector4D
{
public:

	float	x;
	float	y;
	float	z;
	float	w;

	Vector4D() {}

	Vector4D(float r, float s, float t, float u)
	{
		x = r;
		y = s;
		z = t;
		w = u;
	}

	Vector4D(const Vector3D& v, float u)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = u;
	}

	Vector4D(const Vector3D& v, const Point3D& q)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = -(v * q);
	}

	Vector4D(const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.0F;
	}

	Vector4D(const Point3D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		w = 1.0F;
	}

	Vector4D(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0.0F;
		w = 0.0F;
	}

	Vector4D(const Point2D& p)
	{
		x = p.x;
		y = p.y;
		z = 0.0F;
		w = 1.0F;
	}

	Vector4D& Set(float r, float s, float t, float u)
	{
		x = r;
		y = s;
		z = t;
		w = u;
		return (*this);
	}

	Vector4D& Set(const Vector3D &v, float u)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = u;
		return (*this);
	}

	Vector4D& Set(const Vector3D &v, const Point3D& q)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = -(v * q);
		return (*this);
	}

	float& operator [](long k)
	{
		return ((&x)[k]);
	}

	const float& operator [](long k) const
	{
		return ((&x)[k]);
	}

	Vector3D& GetVector3D(void)
	{
		return (*reinterpret_cast<Vector3D *>(this));
	}

	const Vector3D& GetVector3D(void) const
	{
		return (*reinterpret_cast<const Vector3D *>(this));
	}

	Point3D& GetPoint3D(void)
	{
		return (*reinterpret_cast<Point3D *>(this));
	}

	const Point3D& GetPoint3D(void) const
	{
		return (*reinterpret_cast<const Point3D *>(this));
	}

	Vector4D& operator =(const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.0F;
		return (*this);
	}

	Vector4D& operator =(const Point3D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		w = 1.0F;
		return (*this);
	}

	Vector4D& operator =(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0.0F;
		w = 0.0F;
		return (*this);
	}

	Vector4D& operator =(const Point2D& p)
	{
		x = p.x;
		y = p.y;
		z = 0.0F;
		w = 1.0F;
		return (*this);
	}

	Vector4D& operator +=(const Vector4D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return (*this);
	}

	Vector4D& operator +=(const Vector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vector4D& operator +=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}

	Vector4D& operator -=(const Vector4D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return (*this);
	}

	Vector4D& operator -=(const Vector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	Vector4D& operator -=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	Vector4D& operator *=(float t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;
		return (*this);
	}

	Vector4D& operator /=(float t)
	{
		float f = 1.0F / t;
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return (*this);
	}

	Vector4D& operator &=(const Vector4D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return (*this);
	}

	Vector4D& Normalize(void)
	{
		return (*this *= (float)(1.0 / sqrt(x * x + y * y + z * z + w * w)));
	}
};


inline Vector4D operator -(const Vector4D& v)
{
	return (Vector4D(-v.x, -v.y, -v.z, -v.w));
}

inline Vector4D operator +(const Vector4D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w));
}

inline Vector4D operator +(const Vector4D& v1, const Vector3D& v2)
{
	return (Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w));
}

inline Vector4D operator +(const Vector3D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v2.w));
}

inline Vector4D operator +(const Vector4D& v1, const Vector2D& v2)
{
	return (Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w));
}

inline Vector4D operator +(const Vector2D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x + v2.x, v1.y + v2.y, v2.z, v2.w));
}

inline Vector4D operator -(const Vector4D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
}

inline Vector4D operator -(const Vector4D& v1, const Vector3D& v2)
{
	return (Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w));
}

inline Vector4D operator -(const Vector3D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, -v2.w));
}

inline Vector4D operator -(const Vector4D& v1, const Vector2D& v2)
{
	return (Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w));
}

inline Vector4D operator -(const Vector2D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x - v2.x, v1.y - v2.y, -v2.z, -v2.w));
}

inline Vector4D operator *(const Vector4D& v, float t)
{
	return (Vector4D(v.x * t, v.y * t, v.z * t, v.w * t));
}

inline Vector4D operator *(float t, const Vector4D& v)
{
	return (Vector4D(t * v.x, t * v.y, t * v.z, t * v.w));
}

inline Vector4D operator /(const Vector4D& v, float t)
{
	float f = 1.0F / t;
	return (Vector4D(v.x * f, v.y * f, v.z * f, v.w * f));
}

inline float operator *(const Vector4D& v1, const Vector4D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

inline float operator *(const Vector4D& v1, const Vector3D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float operator *(const Vector3D& v1, const Vector4D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float operator *(const Vector4D& v, const Point3D& p)
{
	return (v.x * p.x + v.y * p.y + v.z * p.z + v.w);
}

inline float operator *(const Point3D& v1, const Vector4D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v2.w);
}

inline float operator *(const Vector4D& v1, const Vector2D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

inline float operator *(const Vector2D& v1, const Vector4D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

inline float operator *(const Vector4D& v, const Point2D& p)
{
	return (v.x * p.x + v.y * p.y + v.w);
}

inline float operator *(const Point2D& v1, const Vector4D& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v2.w);
}

inline Vector3D operator %(const Vector4D& v1, const Vector3D& v2)
{
	return (Vector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
}

inline Vector4D operator &(const Vector4D& v1, const Vector4D& v2)
{
	return (Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w));
}

inline bool operator ==(const Vector4D& v1, const Vector4D& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w));
}

inline bool operator !=(const Vector4D& v1, const Vector4D& v2)
{
	return ((v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w));
}


inline float Dot(const Vector4D& v1, const Vector4D& v2)
{
	return (v1 * v2);
}

inline Vector4D ProjectOnto(const Vector4D& v1, const Vector4D& v2)
{
	return (v2 * (v1 * v2));
}

inline float Magnitude(const Vector4D& v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

inline float InverseMag(const Vector4D& v)
{
	return ((float)(1.0 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w)));
}

inline float SquaredMag(const Vector4D& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}