#ifndef __POINT_H__
#define __POINT_H__
#include <math.h>
#include <string>

using namespace std;

//used for min circle.
class Point
{
public:
	// The x corrdinate of a point
    double x;
    // The y corrdinate of a point
    double y;


	// Construct a point at the origin
	Point()
	{
		x = 0;
		y = 0;
	}
	// Construct a point at the specified location (xVal, yVal)
	Point(double xVal, double yVal)
	{
		x = xVal;
		y = yVal;
	}
	// Construct a point with the same location as the specified point
	/*Point(Point point)
	{
		x = point.x;
		y = point.y;
	}*/


	// Get the x corrdinate
	double getX()
	{
		return x;
	}
	// Get the y corrdinate
	double getY()
	{
		return y;
	}
	// Set the x corrdinate
	void setX(double xVal)
	{
		x = xVal;
	}
	// Set the y corrdinate
	void setY(double yVal)
	{
		y = yVal;
	}


    // Translate a point to the specified location
    void translate(Point point)
    {
		translate(point.x, point.y);
    }
    // Translate a point to the specified location (newX, newY)
    void translate(double newX, double newY)
    {
		x = newX;
		y = newY;
    }
    // Offset a point along the x and y axes by dx and dy, respectively
    void offset(double dx, double dy)
    {
		x += dx;
		y += dy;
    }
    // Calcualte the distance between two points
    double distance(Point point)
    {
		double dx = x - point.x;
		double dy = y - point.y;
		return sqrt(dx*dx + dy*dy);
    }
    // Calcualte the square of the distance between two points
    double distance2(Point point)
    {
		double dx = x - point.x;
		double dy = y - point.y;
		return (dx*dx + dy*dy);
    }
    // Calculate the middle point between two points
    Point midPoint(Point point)
    {
		return Point((x+point.x)/2, (y+point.y)/2);
    }


    // Determine whether two points are equal
    bool equals(Point point)
    {
		return (x == point.x) && (y == point.y);
    }
    // Return a representation of a point as a string
    string toString()
    {
		return "point = (";// + x + "," + y + ")";
    }
};
#endif
