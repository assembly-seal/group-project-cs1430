#ifndef force_h
#define force_h

#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.141592653

class force{
	private:
		double magnitude;
		double direction;  // radian
	
	public:
		force();
		force(double m, double d);
	
		void setMagnitude(double m);
		void setDirection(double d);
		double getMagnitude()const;
		double getDirection()const;
	
		force operator+(const force& other) const;
		force operator=(const force& other);
		force add(const force& other) const;
		void apply(const force& other);
	
		void display(ostream& os)const{
			os << getMagnitude() << " " << getDirection() << endl;
		}
};

#endif // force_h