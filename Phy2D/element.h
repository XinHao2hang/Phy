#pragma once
#include"Screen.h"
#include"World.h"

class game_element_rect : public DisplayRect,public phy2d::PhyRect
{
public:
    game_element_rect() {}
    game_element_rect(agl::vec2f size,agl::vec2f pos,float m,int sh,int vao) :phy2d::PhyRect(size,pos,m),DisplayRect(sh,vao)
    {
        //设置大小
        setSize(r.x, r.y);
    }
    void set(agl::vec2f size, agl::vec2f pos, float m, int sh, int vao)
    {
        *this= game_element_rect(size, pos, m, sh, vao);
    }
    void update()
    {

        //设置位置
        DisplayRect::position = glm::vec3(phy2d::PhyRect::position.x / (SCR_WIDTH/2.0), phy2d::PhyRect::position.y / (SCR_HEIGHT/2.0), 0);
        DisplayRect::rotate = phy2d::PhyRect::rotation;
    }
    ~game_element_rect() {}
};

class game_element_circle : public DisplayCircle, public phy2d::PhyCircle
{
public:
    game_element_circle() {}
    game_element_circle(float size, agl::vec2f pos, float m, int sh, int vao) :phy2d::PhyCircle(size, pos, m), DisplayCircle(sh, vao)
    {
        //设置大小
        setSize(r);
    }
    void set(float size, agl::vec2f pos, float m, int sh, int vao)
    {
        *this = game_element_circle(size, pos, m, sh, vao);
    }
    void update()
    {

        //设置位置
        DisplayCircle::position = glm::vec3(phy2d::PhyCircle::position.x / (SCR_WIDTH / 2.0), phy2d::PhyCircle::position.y / (SCR_HEIGHT / 2.0), 0);
        DisplayCircle::rotate = phy2d::PhyCircle::rotation;
    }
    ~game_element_circle() {}
};

