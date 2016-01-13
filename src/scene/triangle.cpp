#include "Triangle.h"

namespace staal {

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, Material* mat)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->material = mat;
}


Triangle::~Triangle()
{
}

bool Triangle::hit(const Ray &r, const float t0, const float t1, HitRecord& rec)
{
	float a = v1.v.x - v2.v.x;
	float b = v1.v.y - v2.v.y;
	float c = v1.v.z - v2.v.z;
	
	float d = v1.v.x - v3.v.x;
	float e = v1.v.y - v3.v.y;
	float f = v1.v.z - v3.v.z;

	float g = r.direction.x;
	float h = r.direction.y;
	float i = r.direction.z;

	float j = v1.v.x - r.origin.x;
	float k = v1.v.y - r.origin.y;
	float l = v1.v.z - r.origin.z;

	float eihf = e*i - h*f;
	float gfdi = g*f-d*i;
	float dheg = d* h - e *g;
	float akjb = a*k - j*b;
	float blkc = b * l - k*c;

	float M = a * eihf + b * gfdi + c * dheg;

	float t = -(f * akjb + e * (j*c - a*l) + d * blkc)/M;

	if( t < t0 || t > t1)
		return false;
	
	float gam = (i * akjb + h * (j*c - a*l) + g * blkc)/M;

	if (gam < 0 || gam > 1)
		return false;

	float bet = (j * eihf +k * gfdi + l * dheg)/M;

	if (bet < 0 || bet > (1 - gam))
		return false;
	
	rec.t = t;
	rec.normal = (1-bet-gam)*v1.normal + bet*v2.normal + gam*v3.normal;
	rec.point = (1-bet-gam)*v1.v + bet*v2.v + gam*v3.v;
	rec.surface = this;
	return true;
}

static float min(float a, float b, float c)
{
	float min = a;
	if (b < min ) 
		min = b;
	if (c < min )
		min = c;
	return min;
}

static float max(float a, float b, float c)
{
	float max = a;
	if (b > max ) 
		max = b;
	if (c > max )
		max = c;
	return max;
}

Box Triangle::boundingBox()
{
	float minx = min(v1.v.x, v2.v.x, v3.v.x);
	float maxx = max(v1.v.x, v2.v.x, v3.v.x);

	float miny = min(v1.v.y, v2.v.y, v3.v.y);
	float maxy = max(v1.v.y, v2.v.y, v3.v.y);

	float minz = min(v1.v.z, v2.v.z, v3.v.z);
	float maxz = max(v1.v.z, v2.v.z, v3.v.z);

	return Box(glm::vec3(minx,miny,minz), glm::vec3(maxx,maxy,maxz));
}


} // namespace staal