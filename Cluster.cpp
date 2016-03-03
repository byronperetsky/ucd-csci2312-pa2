//
// Created by Byron on 2/11/2016.
//


#include <algorithm>
#include <sstream>
#include "Point.h"
#include "Cluster.h"

using namespace std;

namespace Clustering {


    LNode::LNode(const Point &aPoint, LNodePtr nextNode) : point(aPoint), next(nextNode) { }


    Cluster::Cluster() {

        __size = 0;
        __points = nullptr;
    }



//        // The big three: cpy ctor, overloaded operator=, dtor

    Cluster::Cluster(const Cluster &clusterF) {

        __size = 0;
        __points = nullptr;

        if (clusterF.__points == nullptr) {
            if (clusterF.__size == 0)
                __points = nullptr;
        }
        else {
            LNodePtr currentNode = clusterF.__points;

            while (currentNode != nullptr) {

                add(currentNode->point);

                currentNode = currentNode->next;
            }
        }
    }


    Cluster &Cluster::operator=(const Cluster &rhs) {


        if (this == &rhs)
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


        for (int index = 0; index < rhs.getSize(); ++index) {

            add(rhs_ptr->point);

            rhs_ptr = rhs_ptr->next;
        }


        return *this;
    }

    Cluster::~Cluster() {

        LNodePtr current;
        while (__points != nullptr) {

            current = __points;
            __points = current->next;

            delete current;
        }


    }


//        // Getters/setters
    int Cluster::getSize() const {

        return __size;
    }

//
//        // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &aAddedPoint) {

        LNodePtr prevN=__points;
        LNodePtr currentN=__points;
        LNodePtr put_ptr=new LNode(aAddedPoint, nullptr);



        if(__points==nullptr)
        {
            __points = put_ptr;
            __size++;

            return;
        }
        else if(__points->next==nullptr)
        {
            if(aAddedPoint<__points->point)
            {
                __points=put_ptr;
                put_ptr->next=prevN;
                __size++;

                return;
            }
            else
            {
                __points->next=put_ptr;
                __size++;

                return;
            }
        }
        else
        {
            currentN=currentN->next;

            if(aAddedPoint < prevN->point)
            {
                __points = put_ptr;
                put_ptr->next=prevN;
                __size++;

                return;
            }
            while(currentN!=nullptr)
            {
                if(aAddedPoint < currentN->point)
                {
                    prevN->next=put_ptr;
                    put_ptr->next=currentN;
                    __size++;

                    return;
                }

                currentN = currentN->next;
                prevN = prevN->next;
            }

            prevN->next=put_ptr;

            __size++;
        }
    }

    const Point &Cluster::remove(const Point &aRemovedPoint) {

        LNodePtr aNode;
        LNodePtr prevNode;


        if (!__points)
        {
            return aRemovedPoint;
        }


        if (__points->point == aRemovedPoint)
        {
            aNode = __points->next;
            delete __points;
            __points = aNode;
        }
        else
        {
            aNode = __points;
            while (aNode != nullptr && aNode->point != aRemovedPoint) {
                prevNode = aNode;
                aNode = aNode->next;
            }

            if (aNode)
            {

                prevNode->next = aNode->next;

                delete aNode;
            }
        }

        __size--;

        return aRemovedPoint;

    }

    bool Cluster::contains(const Point &aPoint) {

        LNodePtr currentN = __points;

        bool containts = false;

        for (; currentN != nullptr; currentN = currentN->next) {

            if (currentN->point == aPoint) {
                containts = true;
                break;
            }
        }

        return containts;

    }

//
//        // Overloaded operators
//
//        // Members: Subscript
    //  notice: const
    const Point &Cluster::operator[](unsigned int index) const {

        LNodePtr cursor=__points;
        for(int count =0; (count < index) && (cursor->next != nullptr); count++)
            cursor=cursor->next;
        return cursor->point;

    }

//        // Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &aPoint) {

        add(aPoint);

        return *this;


    }

    Cluster &Cluster::operator-=(const Point &aPoint) {

        remove(aPoint);

        return *this;

    }

//
//        // Members: Compound assignment (Cluster argument)
    // union
    Cluster &Cluster::operator+=(const Cluster &clusterF) {

        Cluster aCluster;
        LNodePtr currentN = clusterF.__points;

        while (__points != nullptr) {

            aCluster.add(__points->point);
            __points = __points->next;
        }

        for (; currentN != nullptr; currentN = currentN->next) {

            if (!aCluster.contains(currentN->point)) {
                aCluster.add(currentN->point);
            }

        }

        *this = aCluster;

        return *this;


    }

    // (asymmetric) difference
    Cluster &Cluster::operator-=(const Cluster &clusterF) {

        LNodePtr currentN = clusterF.__points;

        for (; currentN != nullptr; currentN = currentN->next) {

            if (contains(currentN->point)) {
                remove(currentN->point);
            }
        }

        return *this;
    }

//
//        // Friends: IO
    std::ostream &operator<<(std::ostream &outPoints, const Cluster &clusterF) {

        LNodePtr currentN = clusterF.__points;

        for (; currentN != nullptr; currentN = currentN->next) {

            outPoints << currentN->point;
            outPoints << '\n';

        }

        return outPoints;


    }

    std::istream &operator>>(std::istream &inPoint, Cluster &clusterF) {

        std::string holder;
        while (getline(inPoint,holder))
        {
            if (holder.empty())
            {
                return inPoint;
            }
            int count = std::count(holder.begin(), holder.end(), ',');
            Point ptr(count + 1);
            std::istringstream ss(holder);
            ss >> ptr;
            clusterF.add(ptr);
        }
        return inPoint;

    }

//
//        // Friends: Comparison
    bool operator==(const Cluster &lhClust, const Cluster &rhClust) {

        LNodePtr headLhs = lhClust.__points;
        LNodePtr headRhs = rhClust.__points;

        bool theEnd = true;


        if (lhClust.__size != rhClust.__size) {
            bool state = false;

            return state;
        }

        while (headLhs != nullptr) {

            if (headLhs->point != headRhs->point) {
                bool state = false;

                return state;
            }
            else {
                headRhs = headRhs->next;

                headLhs = headLhs->next;
            }

        }

        return theEnd;
    }

    bool operator!=(const Cluster &lhClust, const Cluster &rhClust) {


        bool state = false;

        if (lhClust == rhClust) {
            return state;
        }
        else {
            state = true;

            return state;
        }


    }

//
//        // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &lhClust, const Point &rhPoint) {

        Cluster clusterF(lhClust);
        clusterF += rhPoint;

        return clusterF;


    }

    const Cluster operator-(const Cluster &lhClust, const Point &rhPoint) {

        Cluster clusterF(lhClust);

        clusterF -= rhPoint;

        return clusterF;

    }

//
//        // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &lhClust, const Cluster &rhClust) {

        Cluster clusterF(lhClust);

        clusterF += rhClust;

        return clusterF;

    }

    const Cluster operator-(const Cluster &lhClust, const Cluster &rhClust) {

        Cluster clusterF(lhClust);

        clusterF += rhClust;

        return clusterF;

    }

}
