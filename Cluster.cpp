//
// Created by Byron on 2/11/2016.
//

#include <cassert>

#include "Point.h"
#include "Cluster.h"

namespace Clustering {



        LNode::LNode(const Point &aPoint, LNodePtr nextNode) : point(aPoint), next(nextNode) { }


        Cluster::Cluster(){

            __size = 0;
            __points = nullptr;
        }



//        // The big three: cpy ctor, overloaded operator=, dtor

        Cluster::Cluster(const Cluster & clusterF){

            __size = 0;
            __points = nullptr;

            if(clusterF.__points == nullptr)
            {
                if(clusterF.__size == 0)
                    __points = nullptr;
            }
            else
            {
                LNodePtr currentNode = clusterF.__points;

                while (currentNode != nullptr){

                    add(currentNode->point);

                    currentNode = currentNode->next;
                }
            }
        }


        Cluster & Cluster::operator=(const Cluster &rhs){


            if(this == &rhs)
                return *this;

            LNodePtr current = __points;
            LNodePtr next;


            while (current != nullptr) {

                next = current->next;
                delete current;
                current = next;
                __size--;

            }

            __size = 0;
            __points = nullptr;

           LNodePtr rhs_ptr = rhs.__points;


           for (int index = 0; index < rhs.getSize() ; ++index) {

                add(rhs_ptr->point);

                rhs_ptr = rhs_ptr->next;
           }


            return *this;
        }

        Cluster::~Cluster(){

            LNodePtr current;
            while (__points != nullptr) {

                current = __points;
                __points = current->next;

                delete current;
            }




        }
//
//        // Getters/setters
        int Cluster::getSize() const{

            return __size;
    }
//
//        // Set functions: They allow calling c1.add(c2.remove(p));
        void Cluster::add(const Point & aPoint){

            LNodePtr aNode = new LNode(aPoint, nullptr);

            if(__points == nullptr)
            {
                __points = aNode;
            }
            else if(aPoint < __points->point)
            {
                aNode->next = __points;
                __points = aNode;
            }
            else
            {
                LNodePtr  currentN = __points->next;
                LNodePtr  prevN = __points;

                bool check = true;

                while (check){

                    if (currentN == nullptr || currentN->point > aPoint )
                    {
                        aNode->next = currentN;
                        prevN->next = aNode;

                        break;
                    }
                    else
                    {
                        prevN = currentN;
                        currentN = currentN->next;
                    }

                }
                __size++;
        }







    }
        const Point &remove(const Point & aPoint){

            return true;

        }
//        bool contains(const Point &);
//
//        // Overloaded operators
//
//        // Members: Subscript
//        const Point &operator[](unsigned int index) const; // notice: const
//
//        // Members: Compound assignment (Point argument)
//        Cluster &operator+=(const Point &);
//        Cluster &operator-=(const Point &);
//
//        // Members: Compound assignment (Cluster argument)
//        Cluster &operator+=(const Cluster &); // union
//        Cluster &operator-=(const Cluster &); // (asymmetric) difference
//
//        // Friends: IO
//        friend std::ostream &operator<<(std::ostream &, const Cluster &);
//        friend std::istream &operator>>(std::istream &, Cluster &);
//
//        // Friends: Comparison
        bool operator==(const Cluster & lhClust, const Cluster & rhClust){

            LNodePtr headLhs = lhClust.__points;
            LNodePtr headRhs = rhClust.__points;

            bool theEnd = true;


            if (lhClust.__size != rhClust.__size)
            {
                bool state = false;

                return state;
            }

            while(headLhs != nullptr){

                if ( headLhs->point != headRhs->point)
                {
                    bool state = false;

                    return state;
                }
                else
                {
                    headRhs = headRhs->next;

                    headLhs = headLhs->next;
                }

            }

            return theEnd;
        }

//        friend bool operator!=(const Cluster &, const Cluster &);
//
//        // Friends: Arithmetic (Cluster and Point)
//        friend const Cluster operator+(const Cluster &, const Point &);
//        friend const Cluster operator-(const Cluster &, const Point &);
//
//        // Friends: Arithmetic (two Clusters)
//        friend const Cluster operator+(const Cluster &, const Cluster &); // union
//        friend const Cluster operator-(const Cluster &, const Cluster &); // (asymmetric) difference

}
