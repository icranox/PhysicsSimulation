#include<math.h>

class myMath {
public:
	//fast inverse square root
	static float RSqrt(const float x);

};

float myMath::RSqrt(const float x) {
	long i;
	float y, r;
	y = x * 0.5f;
	i = *(long*) &x;
	i = 0x5f3759df - ( i >> 1 );
	r = *(float*) &i;
	return (r * (1.5f - r * r * y));
}


//========================================================================
//
//	myVec2
//
//========================================================================
class myVec2 {
public:
	float x;
	float y;

	myVec2();
	myVec2(const float x, const float y);
	void Set(const float x, const float y);
	void Zero();

	float & operator[](const int index);
	myVec2 & operator=(const myVec2 &other);
	myVec2 & operator=(const float a);
	myVec2 operator*(const float a) const;
	myVec2 operator/(const float a) const;
	myVec2 operator+(const float a) const;
	myVec2 operator-(const float a) const;
	myVec2 operator*(const myVec2 &other) const;
	myVec2 operator/(const myVec2 &other) const;
	myVec2 operator+(const myVec2 &other) const;
	myVec2 operator-(const myVec2 &other) const;
	myVec2 & operator*=(const float a);
	myVec2 & operator/=(const float a);
	myVec2 & operator+=(const float a);
	myVec2 & operator-=(const float a);
	myVec2 & operator*=(const myVec2 &other);
	myVec2 & operator/=(const myVec2 &other);
	myVec2 & operator+=(const myVec2 &other);
	myVec2 & operator-=(const myVec2 &other);
	bool operator==(const myVec2 &other) const;
	bool operator!=(const myVec2 &other) const;

	float Length() const;
	float LengthSqr() const;
	float LengthFast() const;

	void Normalize();
	void NormalizeFast();

	const float * ToFloatPtr() const;

};

myVec2::myVec2() {
	x = y = 0;
}

myVec2::myVec2(const float x, const float y) {
	this->x = x;
	this->y = y;
}

void myVec2::Set(const float x, const float y) {
	this->x = x;
	this->y = y;
}

void myVec2::Zero() {
	x = y = 0;
}


float &myVec2::operator[](const int index) {
	return (&x)[index];
}

myVec2 &myVec2::operator=(const myVec2 &other) {
	x = other.x;
	y = other.y;
	return *this;
}

myVec2 &myVec2::operator=(const float a) {
	x = a;
	y = a;
	return *this;
}

myVec2 myVec2::operator*(const float a) const {
	return myVec2(x * a, y * a);
}

myVec2 myVec2::operator/(const float a) const {
	return myVec2(x / a, y / a);
}

myVec2 myVec2::operator+(const float a) const {
	return myVec2(x + a, y + a);
}

myVec2 myVec2::operator-(const float a) const {
	return myVec2(x - a, y - a);
}

myVec2 myVec2::operator*(const myVec2 &other) const {
	return myVec2(x * other.x, y * other.y); 
}

myVec2 myVec2::operator/(const myVec2 &other) const {
	return myVec2(x / other.x, y / other.y);
}

myVec2 myVec2::operator+(const myVec2 &other) const {
	return myVec2(x + other.x, y + other.y);
}

myVec2 myVec2::operator-(const myVec2 &other) const {
	return myVec2(x - other.x, y - other.y);
}

myVec2 &myVec2::operator*=(const float a) {
	x *= a;
	y *= a;
	return *this;
}

myVec2 &myVec2::operator/=(const float a) {
	x /= a;
	y /= a;
	return *this;
}

myVec2 &myVec2::operator+=(const float a) {
	x += a;
	y += a;
	return *this;
}

myVec2 &myVec2::operator-=(const float a) {
	x -= a;
	y -= a;
	return *this;
}

myVec2 &myVec2::operator*=(const myVec2 &other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

myVec2 &myVec2::operator/=(const myVec2 &other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

myVec2 &myVec2::operator+=(const myVec2 &other) {
	x += other.x;
	y += other.y;
	return *this;
}

myVec2 &myVec2::operator-=(const myVec2 &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bool myVec2::operator==(const myVec2 &other) const {
	return ((x == other.x) && (y == other.y));
}

bool myVec2::operator!=(const myVec2 &other) const {
	return !((x == other.x) && (y == other.y));
}

float myVec2::Length() const {
	return sqrtf(x * x + y * y);
}

float myVec2::LengthFast() const {
	float lengthSqr = x * x + y * y;
	return lengthSqr * myMath::RSqrt(lengthSqr);
}

float myVec2::LengthSqr() const {
	return x * x + y * y;
}

void myVec2::Normalize() {
	float length=1/sqrtf(x*x+y*y);
	x *= length;
	y *= length;
}

void myVec2::NormalizeFast() {
	float length=myMath::RSqrt(x*x+y*y);
	x *= length;
	y *= length;
}

const float *myVec2::ToFloatPtr() const {
	return &x;
}





//========================================================================
//
//	myVec3
//
//========================================================================
class myVec3 {
public:
	float x;
	float y;
	float z;

	myVec3();
	myVec3(const float x, const float y, const float z);
	void Set(const float x, const float y, const float z);
	void Zero();

	float & operator[](const int index);
	myVec3 & operator=(const myVec3 &other);
	myVec3 & operator=(const float a);
	myVec3 operator*(const float a) const;
	myVec3 operator/(const float a) const;
	myVec3 operator+(const float a) const;
	myVec3 operator-(const float a) const;
	myVec3 operator*(const myVec3 &other) const;
	myVec3 operator/(const myVec3 &other) const;
	myVec3 operator+(const myVec3 &other) const;
	myVec3 operator-(const myVec3 &other) const;
	myVec3 & operator*=(const float a);
	myVec3 & operator/=(const float a);
	myVec3 & operator+=(const float a);
	myVec3 & operator-=(const float a);
	myVec3 & operator*=(const myVec3 &other);
	myVec3 & operator/=(const myVec3 &other);
	myVec3 & operator+=(const myVec3 &other);
	myVec3 & operator-=(const myVec3 &other);
	bool operator==(const myVec3 &other) const;
	bool operator!=(const myVec3 &other) const;

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	void NormalizeFast();

	myVec3 Cross(const myVec3 &other) const;
	myVec3 & Cross(const myVec3 &a, const myVec3 &b);
	float Dot(const myVec3 &other) const;

	myVec2 ToMyVec2() const;

	const float * ToFloatPtr() const;

};

myVec3::myVec3() {
	x = y = z = 0;
}

myVec3::myVec3(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void myVec3::Set(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void myVec3::Zero() {
	x = y = z = 0;
}

float &myVec3::operator[](const int index) {
	return (&x)[index];
}

myVec3 &myVec3::operator=(const myVec3 &other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

myVec3 &myVec3::operator=(const float a) {
	x = a;
	y = a;
	z = a;
	return *this;
}

myVec3 myVec3::operator*(const float a) const {
	return myVec3(x * a, y * a, z * a);
}

myVec3 myVec3::operator/(const float a) const {
	return myVec3(x / a, y / a, z / a);
}

myVec3 myVec3::operator+(const float a) const {
	return myVec3(x + a, y + a, z + a);
}

myVec3 myVec3::operator-(const float a) const {
	return myVec3(x - a, y - a, z - a);
}

myVec3 myVec3::operator*(const myVec3 &other) const {
	return myVec3(x * other.x, y * other.y, z * other.z); 
}

myVec3 myVec3::operator/(const myVec3 &other) const {
	return myVec3(x / other.x, y / other.y, z / other.z);
}

myVec3 myVec3::operator+(const myVec3 &other) const {
	return myVec3(x + other.x, y + other.y, z + other.z);
}

myVec3 myVec3::operator-(const myVec3 &other) const {
	return myVec3(x - other.x, y - other.y, z - other.z);
}

myVec3 &myVec3::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

myVec3 &myVec3::operator/=(const float a) {
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

myVec3 &myVec3::operator+=(const float a) {
	x += a;
	y += a;
	z += a;
	return *this;
}

myVec3 &myVec3::operator-=(const float a) {
	x -= a;
	y -= a;
	z -= a;
	return *this;
}

myVec3 &myVec3::operator*=(const myVec3 &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

myVec3 &myVec3::operator/=(const myVec3 &other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

myVec3 &myVec3::operator+=(const myVec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

myVec3 &myVec3::operator-=(const myVec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool myVec3::operator==(const myVec3 &other) const {
	return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool myVec3::operator!=(const myVec3 &other) const {
	return !((x == other.x) && (y == other.y) && (z == other.z));
}

float myVec3::Length() const {
	return sqrt(x * x + y * y + z * z);
}

float myVec3::LengthSqr() const {
	return (x * x + y * y + z * z);
}

void myVec3::Normalize() {
	float length = 1 / Length();
	x *= length;
	y *= length;
	z *= length;
}

void myVec3::NormalizeFast() {
	float length = myMath::RSqrt(LengthSqr());
	x *= length;
	y *= length;
	z *= length;
}

myVec3 myVec3::Cross(const myVec3 &other) const {
	return myVec3(	y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
}

myVec3 &myVec3::Cross(const myVec3 &a, const myVec3 &b) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return *this;
}


float myVec3::Dot(const myVec3 &other) const {
	return (x * other.x + y * other.y + z * other.z);
}

const float *myVec3::ToFloatPtr() const {
	return &x;
}

myVec2 myVec3::ToMyVec2() const {
	return myVec2(x, y);
}




//========================================================================
//
//	myVec4
//
//========================================================================
class myVec4 {
public:
	float x;
	float y;
	float z;
	float w;

	myVec4();
	myVec4(const float x, const float y, const float z, const float w);
	void Set(const float x, const float y, const float z, const float w);
	void Zero();

	float & operator[](const int index);
	myVec4 & operator=(const myVec4 &other);
	myVec4 & operator=(const float a);
	myVec4 operator*(const float a) const;
	myVec4 operator/(const float a) const;
	myVec4 operator+(const float a) const;
	myVec4 operator-(const float a) const;
	myVec4 operator*(const myVec4 &other) const;
	myVec4 operator/(const myVec4 &other) const;
	myVec4 operator+(const myVec4 &other) const;
	myVec4 operator-(const myVec4 &other) const;
	myVec4 & operator*=(const float a);
	myVec4 & operator/=(const float a);
	myVec4 & operator+=(const float a);
	myVec4 & operator-=(const float a);
	myVec4 & operator*=(const myVec4 &other);
	myVec4 & operator/=(const myVec4 &other);
	myVec4 & operator+=(const myVec4 &other);
	myVec4 & operator-=(const myVec4 &other);
	bool operator==(const myVec4 &other) const;
	bool operator!=(const myVec4 &other) const;

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	void NormalizeFast();

	myVec3 ToMyVec3() const;
	myVec2 ToMyVec2() const;
	const float * ToFloatPtr() const;


};

myVec4::myVec4() {
	x = y = z = w = 0;
}

myVec4::myVec4(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void myVec4::Set(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void myVec4::Zero() {
	x = y = z = w = 0;
}

float &myVec4::operator[](const int index) {
	return (&x)[index];
}

myVec4 &myVec4::operator=(const myVec4 &other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

myVec4 &myVec4::operator=(const float a) {
	x = a;
	y = a;
	z = a;
	w = a;
	return *this;
}

myVec4 myVec4::operator*(const float a) const {
	return myVec4(x * a, y * a, z * a, w * a);
}

myVec4 myVec4::operator/(const float a) const {
	return myVec4(x / a, y / a, z / a, w / a);
}

myVec4 myVec4::operator+(const float a) const {
	return myVec4(x + a, y + a, z + a, w + a);
}

myVec4 myVec4::operator-(const float a) const {
	return myVec4(x - a, y - a, z - a, w - a);
}

myVec4 myVec4::operator*(const myVec4 &other) const {
	return myVec4(x * other.x, y * other.y, z * other.z, w * other.w); 
}

myVec4 myVec4::operator/(const myVec4 &other) const {
	return myVec4(x / other.x, y / other.y, z / other.z, w / other.w);
}

myVec4 myVec4::operator+(const myVec4 &other) const {
	return myVec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

myVec4 myVec4::operator-(const myVec4 &other) const {
	return myVec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

myVec4 &myVec4::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}

myVec4 &myVec4::operator/=(const float a) {
	x /= a;
	y /= a;
	z /= a;
	w /= a;
	return *this;
}

myVec4 &myVec4::operator+=(const float a) {
	x += a;
	y += a;
	z += a;
	w += a;
	return *this;
}

myVec4 &myVec4::operator-=(const float a) {
	x -= a;
	y -= a;
	z -= a;
	w -= a;
	return *this;
}

myVec4 &myVec4::operator*=(const myVec4 &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

myVec4 &myVec4::operator/=(const myVec4 &other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

myVec4 &myVec4::operator+=(const myVec4 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

myVec4 &myVec4::operator-=(const myVec4 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}


bool myVec4::operator==(const myVec4 &other) const {
	return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
}

bool myVec4::operator!=(const myVec4 &other) const {
	return !((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
}

float myVec4::Length() const {
	return sqrt(x * x + y * y + z * z);
}

float myVec4::LengthSqr() const {
	return (x * x + y * y + z * z);
}

void myVec4::Normalize() {
	float length = 1 / Length();
	x *= length;
	y *= length;
	z *= length;
	w *= length;
}

void myVec4::NormalizeFast() {
	float length = myMath::RSqrt(LengthSqr());
	x *= length;
	y *= length;
	z *= length;
	w *= length;
}

myVec3 myVec4::ToMyVec3() const {
	return myVec3(x, y, z);
}

myVec2 myVec4::ToMyVec2() const {
	return myVec2(x, y);
}

const float *myVec4::ToFloatPtr() const {
	return &x;
}




//========================================================================
//
//	myMat2
//
//	column major 
//
//	| mat[0][0]	mat[1][0] |
//	| mat[0][1]	mat[1][1] |
//	
//
//========================================================================
class myMat2 {
public:
	myVec2 mat[2];

	myMat2(){};
	myMat2(const myVec2 &x, const myVec2 &y);
	myMat2(	const float xx, const float xy,
			const float yx, const float yy);

	float Determinant();

};

myMat2::myMat2(const myVec2 &x, const myVec2 &y) {

}

myMat2::myMat2(	const float xx, const float xy,
				const float yx, const float yy) {

}


float myMat2::Determinant() {
	return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
}


//========================================================================
//
//	myMat3
//
//	column major
//
//	| mat[0][0]	mat[1][0] mat[2][0] |
//	| mat[0][1]	mat[1][1] mat[2][1] |
//	| mat[0][2] mat[1][2] mat[2][2] |
//
//========================================================================
class myMat3 {
public:
	myVec3 mat[3];

	myMat3(){};
	myMat3(const myVec3 &x, const  myVec3 &y, const  myVec3 &z);
	myMat3(	const float xx, const float xy, const float xz,
			const float yx, const float yy, const float yz, 
			const float zx, const float zy, const float zz);
	myMat3(const myMat3 &other);

	myMat3 Identity(); 

	myVec3 operator*(const myVec3 &v) const;
	myMat3 operator*(const myMat3 &other) const;

	myMat3 operator-(const myMat3 &other) const;
	myMat3 operator+(const myMat3 &other) const;

	myMat3 & operator*=(const myVec3 &v);
	myMat3 & operator*=(const myMat3 &other);

	myMat3 & operator-=(const myMat3 &other);
	myMat3 & operator+=(const myMat3 &other);


	float Determinant();

	myMat3 Transpose();
	myMat3 Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool InverseSelf();			// returns false if determinant is zero
	myMat3 InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool InverseFastSelf();		// returns false if determinant is zero



};

myMat3::myMat3(const myVec3 &x, const  myVec3 &y, const  myVec3 &z) {

}

myMat3::myMat3(	const float xx, const float xy, const float xz,
				const float yx, const float yy, const float yz, 
				const float zx, const float zy, const float zz) {

}

myMat3::myMat3(const myMat3 &other) {

}

myVec3 myMat3::operator*(const myVec3 &v) const {
	return myVec3();
}

myMat3 myMat3::operator*(const myMat3 &other) const {
	return myMat3();
}

	
myMat3 myMat3::operator-(const myMat3 &other) const {
	return myMat3();
}

myMat3 myMat3::operator+(const myMat3 &other) const {
	return myMat3();
}


myMat3 & myMat3::operator*=(const myVec3 &v) {

	return *this;
}

myMat3 & myMat3::operator*=(const myMat3 &other) {

	return *this;
}


myMat3 & myMat3::operator-=(const myMat3 &other) {

	return *this;
}

myMat3 & myMat3::operator+=(const myMat3 &other) {

	return *this;
}


float myMat3::Determinant() {
	//detX_XY_XY subdeterminant X=order e.g. 2x2 XY=rowX and rowY, XY=columnX and columnY
	//2x2 sub-determinants
	float det2_12_12 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
	float det2_12_02 = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
	float det2_12_01 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

	//return ((mat[0][0] * det2_12_12) - (mat[0][1] * det2_12_02) + (mat[0][2] * det2_12_01));
	return mat[0][0] * det2_12_12 - mat[0][1] * det2_12_02 + mat[0][2] * det2_12_01;
}

myMat3 myMat3::Transpose() {
	return myMat3();
}

myMat3 myMat3::Inverse() const {
	return myMat3();
}

bool myMat3::InverseSelf() {
	return false;
}

myMat3 myMat3::InverseFast() const {
	return myMat3();
}

bool myMat3::InverseFastSelf() {
	return false;
}




//========================================================================
//
//	myMat4
//
//	column major
//
//	| mat[0][0]	mat[1][0] mat[2][0] mat[3][0] |
//	| mat[0][1]	mat[1][1] mat[2][1] mat[3][1] |
//	| mat[0][2] mat[1][2] mat[2][2] mat[3][2] |
//	| mat[0][3] mat[1][3] mat[2][3] mat[3][3] |
//
//========================================================================
class myMat4 {
public:
	myVec4 mat[4];

	myMat4(){};
	myMat4(const myVec4 &x, const  myVec4 &y, const  myVec4 &z, const myVec4 &w);
	myMat4(	const float xx, const float yx, const float zx, const float wx, 
			const float xy, const float yy, const float zy, const float wy, 
			const float xz, const float yz, const float zz, const float wz, 
			const float xw, const float yw, const float zw, const float ww);

	const myVec4 & operator[](int index) const;
	myVec4 & operator[](int index);
	myVec4 operator*(const myVec4 &v) const;
	myMat4 operator*(const myMat4 &other) const;

	myMat4 & operator*=(const myVec4 &v);
	myMat4 & operator*=(const myMat4 &other);

	myMat4 operator-(const myMat4 &other) const;
	myMat4 operator+(const myMat4 &other) const;

	myMat4 & operator-=(const myMat4 &other);
	myMat4 & operator+=(const myMat4 &other);

	float Determinant();

	const float * ToFloatPtr() const;
	//float * ToFloatPtr();


};

myMat4::myMat4(const myVec4 &x, const  myVec4 &y, const  myVec4 &z, const myVec4 &w) {
	mat[0] = x;
	mat[1] = y;
	mat[2] = z;
	mat[3] = w;
}

myMat4::myMat4(	const float xx, const float yx, const float zx, const float wx, 
				const float xy, const float yy, const float zy, const float wy, 
				const float xz, const float yz, const float zz, const float wz, 
				const float xw, const float yw, const float zw, const float ww) {
					
	mat[0].x = xx;
	mat[0].y = xy;
	mat[0].z = xz;
	mat[0].w = xw;

	mat[1].x = yx;
	mat[1].y = yy;
	mat[1].z = yz;
	mat[1].w = yw;

	mat[2].x = zx;
	mat[2].y = zy;
	mat[2].z = zz;
	mat[2].w = zw;

	mat[3].x = wx;
	mat[3].y = wy;
	mat[3].z = wz;
	mat[3].w = ww;
}

const myVec4 &myMat4::operator[](int index) const {
	return mat[index];
}

myVec4 &myMat4::operator[](int index) {
	return mat[index];
}

myVec4 myMat4::operator*(const myVec4 &v) const {
	return myVec4(	mat[0].x * v.x + mat[1].x * v.y + mat[2].x * v.z + mat[3].x * v.w,
					mat[0].y * v.x + mat[1].y * v.y + mat[2].y * v.z + mat[3].y * v.w,
					mat[0].z * v.x + mat[1].z * v.y + mat[2].z * v.z + mat[3].z * v.w,
					mat[0].w * v.x + mat[1].w * v.y + mat[2].w * v.z + mat[3].w * v.w);
}

myMat4 myMat4::operator*(const myMat4 &other) const {
	myVec4 x = myVec4(	mat[0].x * other.mat[0].x + mat[1].x * other.mat[0].y + mat[2].x * other.mat[0].z + mat[3].x * other.mat[0].w,
						mat[0].y * other.mat[0].x + mat[1].y * other.mat[0].y + mat[2].y * other.mat[0].z + mat[3].y * other.mat[0].w,
						mat[0].z * other.mat[0].x + mat[1].z * other.mat[0].y + mat[2].z * other.mat[0].z + mat[3].z * other.mat[0].w,
						mat[0].w * other.mat[0].x + mat[1].w * other.mat[0].y + mat[2].w * other.mat[0].z + mat[3].w * other.mat[0].w);

	myVec4 y = myVec4(	mat[0].x * other.mat[1].x + mat[1].x * other.mat[1].y + mat[2].x * other.mat[1].z + mat[3].x * other.mat[1].w,
						mat[0].y * other.mat[1].x + mat[1].y * other.mat[1].y + mat[2].y * other.mat[1].z + mat[3].y * other.mat[1].w,
						mat[0].z * other.mat[1].x + mat[1].z * other.mat[1].y + mat[2].z * other.mat[1].z + mat[3].z * other.mat[1].w,
						mat[0].w * other.mat[1].x + mat[1].w * other.mat[1].y + mat[2].w * other.mat[1].z + mat[3].w * other.mat[1].w);

	myVec4 z = myVec4(	mat[0].x * other.mat[2].x + mat[1].x * other.mat[2].y + mat[2].x * other.mat[2].z + mat[3].x * other.mat[2].w,
						mat[0].y * other.mat[2].x + mat[1].y * other.mat[2].y + mat[2].y * other.mat[2].z + mat[3].y * other.mat[2].w,
						mat[0].z * other.mat[2].x + mat[1].z * other.mat[2].y + mat[2].z * other.mat[2].z + mat[3].z * other.mat[2].w,
						mat[0].w * other.mat[2].x + mat[1].w * other.mat[2].y + mat[2].w * other.mat[2].z + mat[3].w * other.mat[2].w);

	myVec4 w = myVec4(	mat[0].x * other.mat[3].x + mat[1].x * other.mat[3].y + mat[2].x * other.mat[3].z + mat[3].x * other.mat[3].w,
						mat[0].y * other.mat[3].x + mat[1].y * other.mat[3].y + mat[2].y * other.mat[3].z + mat[3].y * other.mat[3].w,
						mat[0].z * other.mat[3].x + mat[1].z * other.mat[3].y + mat[2].z * other.mat[3].z + mat[3].z * other.mat[3].w,
						mat[0].w * other.mat[3].x + mat[1].w * other.mat[3].y + mat[2].w * other.mat[3].z + mat[3].w * other.mat[3].w);

	
					
	
	return myMat4(x, y, z, w);
}

myMat4 &myMat4::operator*=(const myVec4 &v) {
	return *this;
}

myMat4 &myMat4::operator*=(const myMat4 &other) {
	return *this;
}


myMat4 myMat4::operator-(const myMat4 &other) const {
	return myMat4( mat[0] - other.mat[0],  mat[1] - other.mat[1],  mat[2] - other.mat[2],  mat[3] - other.mat[3]);
}

myMat4 myMat4::operator+(const myMat4 &other) const {
	return myMat4( mat[0] + other.mat[0],  mat[1] + other.mat[1],  mat[2] + other.mat[2],  mat[3] + other.mat[3]);
}

myMat4 &myMat4::operator-=(const myMat4 &other) {
	mat[0] -= other.mat[0];
	mat[1] -= other.mat[1];
	mat[2] -= other.mat[2];
	mat[3] -= other.mat[3];
	return *this;
}

myMat4 &myMat4::operator+=(const myMat4 &other) {
	mat[0] += other.mat[0];
	mat[1] += other.mat[1];
	mat[2] += other.mat[2];
	mat[3] += other.mat[3];
	return *this;
}



float myMat4::Determinant() {
	
	//2x2 sub-determinants
	float det2_01_01 = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	float det2_01_02 = mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0];
	float det2_01_03 = mat[0][0] * mat[1][3] - mat[0][3] * mat[1][0];
	float det2_01_12 = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
	float det2_01_13 = mat[0][1] * mat[1][3] - mat[0][3] * mat[1][1];
	float det2_01_23 = mat[0][2] * mat[1][3] - mat[0][3] * mat[1][2];

	//3x3 sub-determinants
	float det3_201_123 = mat[2][1] * det2_01_23 - mat[2][2] * det2_01_13 + mat[2][3] * det2_01_12;
	float det3_201_023 = mat[2][0] * det2_01_23 - mat[2][2] * det2_01_03 + mat[2][3] * det2_01_02;
	float det3_201_013 = mat[2][0] * det2_01_13 - mat[2][1] * det2_01_03 + mat[2][3] * det2_01_01;
	float det3_201_012 = mat[2][0] * det2_01_12 - mat[2][1] * det2_01_02 + mat[2][2] * det2_01_01;

	return -mat[3][0] * det3_201_123 + mat[3][1] * det3_201_023 - mat[3][2] * det3_201_013 + mat[3][3] * det3_201_012;

}


const float *myMat4::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

