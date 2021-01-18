#ifndef VECTOR_HPP
#define VECTOR_HPP
#include<assert.h>
#include<tuple>
namespace agl
{
    /*
     * 二维向量类
     * */
    template<typename T>
    class vector2
    {
    public:
        vector2(){}
        T x, y;
        T operator[](unsigned long i) const { return *((T*)(&x)+i); }
        T& operator[](unsigned long i) { return *((T*)(&x) + i); }
        vector2(T _x,T _y):x(_x), y(_y) {}
        vector2(T value) :x(value), y(value) {}
        ~vector2(){};
    };
    
    /*
     * 三维向量类
     * */
    template<typename T>
    class vector3
    {
    public:
        union
        {
            struct{T x,y,z;};
            struct{T r,g,b;};
        };
        T operator[](unsigned long i) const {return *((T*)(&x) + i);}
        T & operator[](unsigned long i) {return *((T*)(&x) + i);}
        vector3(){}
        vector3(T _x,T _y,T _z):x(_x),y(_y),z(_z){}
        vector3(T value):x(value),y(value),z(value){}
        ~vector3(){};
    };
    
    /*
     * 四维向量类
     * */
   /* template<typename T>
    class vector4:public point4<T>
    {
    public:
        vector4(){}
        vector4(T _x,T _y,T _z,T _w):point4<T>(_x,_y,_z,_w){}
        ~vector4(){};
    };*/
};
#endif // VECTOR_HPP
