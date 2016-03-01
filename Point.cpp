//
// Created by Byron on 2/11/2016.
//


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "Point.h"



namespace Clustering {

    unsigned int Point::__idGen = 0; // id generator

    Point::Point(int dimensions){

        //Generates a unique id for each point as they are made and increments idGen for the next point.
        __id = __idGen;
        ++__idGen;

        __dim = dimensions; //Assigns the number of dimensions of the point.
        __values = new double[__dim]; //Creates a dynamically allocated array of doubles that holds each dimension

        //Initializes array to 0.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = 0;

        }
    }

    //FOR PERSONAL TESTING AND DEBUGGING!!!!
    Point::Point(int dimensions, double * values){

        //Generates a unique id for each point as they are made and increments idGen for the next point.
        __id = __idGen;
        ++__idGen;

        __dim = dimensions; //Assings the number of dimensions of the point.

        __values = new double[__dim]; //Creates a dynamically allocated array of doubles that holds each dimension

        //Initializes the array __values to the values of the array values.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = values[index];

        }
    }

//// Big three: cpy ctor, overloaded operator=, dtor

    //Copy Constructor
    Point::Point(const Point & toBeCopied){

        //Assigning all values too be copied.
        __id = toBeCopied.__id;
        __dim = toBeCopied.__dim;
        __values = new double[__dim];

        //Loop to toBeCopied to a new dynamically allocated array.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = toBeCopied.__values[index];

        }

    }

    //Overloaded = operator
    Point &Point::operator=(const Point & rhs){

        //Checks for self-assignment
        if(this == &rhs)
            return *this;
        else
        {
            //Assigning all values too be copied.
            __id = rhs.__id;
            __dim = rhs.__dim;
            __values = new double[__dim];

            //Loop to copy rhs to a new dynamically allocated array.
            for(int index = 0 ; index < __dim ; index++ ){

                __values[index] = rhs.__values[index];

            }

        }

        return *this;
    }

    //Destructor
    Point::~Point(){

        delete[] __values;
    }

// Accessors & mutators

    //Returns the values of __id
    int Point::getId() const{

        return __id;
    }

    //Returns the value of __dim
    int Point::getDims() const{

        return __dim;

    }

    //Sets the value of dimension in __value <-- D.A.A.
    void Point::setValue(int dimension, double value){

        __values[dimension] = value;

    }

    double Point::getValue(int dimension) const{

        return __values[dimension];

    }

//// Functions
    double Point::distanceTo(const Point & pointDistance) const{

        double aDistanceTo = 0;
        double sumOfDistance = 0;
        double finalDistance = 0;

        for (int index = 0; index < __dim ; ++index) {

            aDistanceTo = (__values[index] - pointDistance.__values[index]) * (__values[index] - pointDistance.__values[index]);

            sumOfDistance += aDistanceTo;

        }


        finalDistance = sqrt(sumOfDistance);

        return finalDistance;






    }
//
//// Overloaded operators
//
//// Members
// p *= 6; p.operator*=(6);
    Point &Point::operator*=(double aValue ){

        for (int index = 0; index < __dim; ++index) {

            __values[index] *= aValue;

        }

        return *this;

    }


    Point &Point::operator/=(double aValue){

        for (int index = 0; index < __dim ; ++index) {

            __values[index] /= aValue;

        }

        return *this;

    }

    // prevent (p1 * 2) = p2;
    const Point Point::operator*(double aValue) const{

        Point aPoint(*this); //Makes a new point with the dim of the current point

        aPoint *= aValue; // * the current point by the value

        return aPoint; // returns the point

    }

    // p3 = p2 / 2;
    const Point Point::operator/(double aValue) const{

        Point aPoint(*this);

        aPoint /= aValue;

        return aPoint;
    }

    double &Point::operator[](int index){

        while(index < 0 || index >= __dim)// <---Bounds checking
            index = 0;

        return __values[index];

    }

//// Friends
//friend Point &operator+=(Point &, const Point &);
//friend Point &operator-=(Point &, const Point &);
//friend const Point operator+(const Point &, const Point &);
//friend const Point operator-(const Point &, const Point &);
//
//friend bool operator==(const Point &, const Point &);
//friend bool operator!=(const Point &, const Point &);
//
//friend bool operator<(const Point &, const Point &);
//friend bool operator>(const Point &, const Point &);
//friend bool operator<=(const Point &, const Point &);
//friend bool operator>=(const Point &, const Point &);
//
//friend std::ostream &operator<<(std::ostream &, const Point &);
//friend std::istream &operator>>(std::istream &, Point &);


}