#ifndef PLANE_HPP
#define PLANE_HPP
#include"vector.hpp"
#include"vmath.hpp"
namespace agl
{
    template<typename T>
    class Plane3
    {
    public:
        agl::point3<T> p;
        agl::vector3<T> n;
        Plane3(){}
        Plane3(const agl::point3<T> & _p,const agl::vector3<T> & _n):p(_p),n(_n){}
        ~Plane3(){}
    };
    
    template<typename T>
    class Triangle3
    {
    public:
        agl::point3<T> a,b,c;
        Triangle3(){}
        Triangle3(const agl::point3<T> &_a,const agl::point3<T> &_b,const agl::point3<T> &_c):a(_a),b(_b),c(_c){}
        operator Plane3<T>()
        {
            vector3<T> x(a.x,a.y,a.z);
            vector3<T> y(b.x,b.y,b.z);
            vector3<T> z(c.x,c.y,c.z);
            return agl::Plane3<T>(a,cross(x-y,y-z));
        }
    };
};


#endif // PLANE_HPP
