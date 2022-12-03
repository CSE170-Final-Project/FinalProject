#include <intersection.h>
#include <glm/glm.hpp>
#include <stdio.h>

bool Plane_Plane(Face P1, Face P2)
{
	Ray r[4];

	r[0].pos = P1.A;
	r[0].dir = glm::normalize(P1.B - P1.A);

	r[1].pos = P1.B;
	r[1].dir = glm::normalize(P1.D - P1.B);

	r[2].pos = P1.D;
	r[2].dir = glm::normalize(P1.C - P1.D);

	r[3].pos = P1.C;
	r[3].dir = glm::normalize(P1.A - P1.C);

	for (Ray _r : r)
	{
		if(Ray_Face_intersect(_r, P2)) return true;
	}

	r[0].pos = P2.A;
	r[0].dir = glm::normalize(P2.B - P2.A);

	r[1].pos = P2.B;
	r[1].dir = glm::normalize(P2.D - P2.B);

	r[2].pos = P2.D;
	r[2].dir = glm::normalize(P2.C - P2.D);

	r[3].pos = P2.C;
	r[3].dir = glm::normalize(P2.A - P2.C);

	for (Ray _r : r)
	{
		if (Ray_Face_intersect(_r, P1)) return true;
	}

	return false;
}

bool Box_Plane(Hitbox box, Face plane)
{
	for (Face face : box.faces)
	{
		if (Plane_Plane(face, plane)) return true;
	}

	return false;
}


float Ray_Face_intersect(Ray ray, Face face)
{
    ray.pos;
    face.A;
    face.D;
    face.C;
  
	glm::vec3 norm = glm::cross ((face.C-face.A),(face.B-face.A));

	// ray.dir = ray.dir / sqrt(glm::dot(ray.dir, ray.dir));
	ray.dir = glm::normalize(ray.dir);
	// norm = norm / sqrt(glm::dot(norm, norm));
	norm = glm::normalize(norm);
	//glm::vec3 t = (ray.pos-norm)/(ray.dir);
	//glm::vec3 t = ((face.A-ray.pos)*norm)/((ray.dir)*norm);
	float t = glm::dot((face.A - ray.pos), norm) / glm::dot(ray.dir, norm);
	
	glm::mat3 planify_points(face.B - face.A, face.C-face.A, norm);
	planify_points = glm::inverse(planify_points);


	// return t;
	glm::vec3 b, c, d, p;
	b = planify_points * (face.B - face.A);
	c = planify_points * (face.C - face.A);
	d = planify_points * (face.D - face.A);
	p = planify_points * ((ray.pos + ray.dir * t) - face.A);
	
	if(p.x < 0 || p.y < 0) return -1;
	if(p.y > c.y + p.x * (c.y - d.y)/(c.x - d.x)) return -1;
	if(p.x > b.x + p.y * (b.x - d.x)/(b.y - d.y)) return -1;
	return t;


//t=((a-p0)*n)/(v*n)
//t=((initial point on the plane-initial point on the ray)/(direction vector of the ray)
// point of the plane =tv
}
