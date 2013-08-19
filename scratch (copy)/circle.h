#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "point.h"
#include <exception>

using namespace std;

//used to calc min circle.
class Circle
{
public:
	// The center of a circle
    Point p;
    // The radius of a circle
    double r;


	// Construct a circle without any specification
	Circle()
    {
		p = Point(0,0);
		r = 0;
    }
	// Construct a circle with the specified circle
	/*Circle(Circle circle)
    {
		p = Point(circle.p);
		r = circle.r;
    }*/
	// Construct a circle with the specified center and radius
	Circle(Point center, double radius)
    {
		p = Point(center);
		r = radius;
    }
    // Construct a circle based on one point
	Circle(Point center)
    {
		p = Point(center);
		r = 0;
    }
    // Construct a circle based on two points
    Circle(Point p1, Point p2)
    {
		p = p1.midPoint(p2);
		r = p1.distance(p);
    }
    // Construct a circle based on three points
    Circle(Point p1, Point p2, Point p3)
    {
		try
		{

			if (!this->IsPerpendicular(p1, p2, p3) )		    this->CalcCircle(p1, p2, p3);
			else if (!this->IsPerpendicular(p1, p3, p2) )		this->CalcCircle(p1, p3, p2);
			else if (!this->IsPerpendicular(p2, p1, p3) )		this->CalcCircle(p2, p1, p3);
			else if (!this->IsPerpendicular(p2, p3, p1) )		this->CalcCircle(p2, p3, p1);
			else if (!this->IsPerpendicular(p3, p2, p1) )		this->CalcCircle(p3, p2, p1);
			else if (!this->IsPerpendicular(p3, p1, p2) )		this->CalcCircle(p3, p1, p2);
			else {

				throw "ERROR Creating MIN CIRCLE: FUNC(Circle p1, p2, p3) coincident lines";

				this->r=-1;
				return ;
			}

		}
		catch(exception& e)
		{
		}
    }

	void CalcCircle(Point p1, Point p2, Point p3){
			double x = (p3.getX()*p3.getX() * (p1.getY()-p2.getY()) + (p1.getX()*p1.getX() + (p1.getY()-p2.getY())*(p1.getY()-p3.getY()))
			          * (p2.getY()-p3.getY()) + p2.getX()*p2.getX() * (-p1.getY()+p3.getY()))
					  / (2 * (p3.getX() * (p1.getY()-p2.getY()) + p1.getX() * (p2.getY()-p3.getY()) + p2.getX() * (-p1.getY()+p3.getY())));

			double v1 = (p3.getY()-p2.getY()) * (x - (p2.getX() + p3.getX())/2);
			double v2 = (2 * (p3.getX() * (p1.getY()-p2.getY()) + p1.getX() * (p2.getY()-p3.getY()) + p2.getX() * (-p1.getY()+p3.getY())));
			double y = (p2.getY()+p3.getY())/2 - (p3.getX() - p2.getX())/(p3.getY()-p2.getY()) * (x - (p2.getX() + p3.getX())/2);

			if (v1 == 0 || v2 == 0){

				double p1x = p1.getX();
				double p1y = p1.getY();
				double p2x = p2.getX();
				double p2y = p2.getY();
				double p3x = p3.getX();
				double p3y = p3.getY();

				double a = p2x - p1x;
				double b = p2y - p1y;
				double c = p3x - p1x;
				double d = p3y - p1y;
				double e = a * (p2x + p1x) * 0.5 + b * (p2y + p1y) * 0.5;
				double f = c * (p3x + p1x) * 0.5 + d * (p3y + p1y) * 0.5;
				double det = a*d - b*c;

				double cx = (d*e - b*f)/det;
				double cy = (-c*e + a*f)/det;
				p =  Point(cx, cy);
				r =  sqrt( (p1x-cx)*(p1x-cx) + (p1y-cy)*(p1y-cy));
			}else{
				p =  Point(x, y);
				r = p.distance(p1);
			}
	}

	// Get the center
	Point getCenter()
	{
		return p;
	}
	// Get the radius
	double getRadius()
	{
		return r;
	}
	// Set the center
	void setCenter(Point center)
	{
		p.translate(center);
	}
	// Set the radius
	void setRadius(double radius)
	{
		r = radius;
	}

	// Translate the center of a circle to a specified point
    void translate(Point newCenter)
    {
		p.translate(newCenter);
    }
    // Offset a circle along its radius by dr
    void offset(double dr)
    {
		r += dr;
    }
    // Scale a circle along its radius by a factor
    void scale(double factor)
    {
		r *= factor;
    }
    // Calculate the diameter of a circle
    double getDiameter()
    {
		return (2*r);
    }
    // Calculate the circumference of a circle
    double getCircumference()
    {
		return (M_PI*2*r);
    }
    // Calcualte the area of a circle
    double getArea()
    {
		return (M_PI*r*r);
    }
	// Is a point in the circle
	int contain(Point point)
	{
		int answer = 0;
		double d = p.distance(point);
		if (d > r)
		{
			answer = 1;		// The point is outside the circle
		}
		else if (d == r)
		{
			answer = 0;		// The point is on the circumference of the circle
		}
		else
		{
			answer = -1;	// The point is inside the circle
		}
		return answer;
	}


	// Determine whether two points are equal
    bool equals(Circle circle)
    {
		return p.equals(circle.p) && (r == circle.r);
    }
    // Return a representation of a point as a string
    string toString()
    {
		return "Center = (";// + p.getX() + ", " + p.getY() + "); " + "Radius = " + r;
    }

	bool IsPerpendicular(Point pt1, Point pt2, Point pt3)
	// Check the given point are perpendicular to x or y axis
	{
		double yDelta_a= pt2.getY() - pt1.getY();
		double xDelta_a= pt2.getX() - pt1.getX();
		double yDelta_b= pt3.getY() - pt2.getY();
		double xDelta_b= pt3.getX() - pt2.getX();


	//	TRACE(" yDelta_a: %f xDelta_a: %f \n",yDelta_a,xDelta_a);
	//	TRACE(" yDelta_b: %f xDelta_b: %f \n",yDelta_b,xDelta_b);

		// checking whether the line of the two pts are vertical
		if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
			//TRACE("The points are pependicular and parallel to x-y axis\n");
			return false;
		}

		if (fabs(yDelta_a) <= 0.0000001){
	//		TRACE(" A line of two point are perpendicular to x-axis 1\n");
			return true;
		}
		else if (fabs(yDelta_b) <= 0.0000001){
	//		TRACE(" A line of two point are perpendicular to x-axis 2\n");
			return true;
		}
		else if (fabs(xDelta_a)<= 0.000000001){
	//		TRACE(" A line of two point are perpendicular to y-axis 1\n");
			return true;
		}
		else if (fabs(xDelta_b)<= 0.000000001){
	//		TRACE(" A line of two point are perpendicular to y-axis 2\n");
			return true;
		}
		else return false ;
	}
};
#endif
