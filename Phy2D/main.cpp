#include"element.h"
#include <iostream>
using namespace std;
int main()
{
    auto window = openglInit();
    Screen screen;
    int sh = LoadShader(readFile("rect.vs"), readFile("rect.fs"));
    int vaoc = MakeShape::Circle();
    int vaor = MakeShape::Rectangle();
    phy2d::World world2d;
    static game_element_rect rect[8124];
    int index = 0;
    for (int i = 1; i <50; i++)
    {
        for (int j = 0; j <i; j++)
        {
            rect[index++].set(agl::vec2f(5, 5), agl::vec2f(j*15-i*15/2, 2000-i*15), 10, sh, vaor);
        }
    }
    for(int i = 0;i<index;i++)
        screen.push_shape(&rect[i]);
    for (int i = 0; i < index; i++)
        world2d.push(&rect[i]);
    rect[index].set(agl::vec2f(600, 20), agl::vec2f(0,-400), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[index]);
    world2d.push(&rect[index]);
    index++;
    rect[index].set(agl::vec2f(20, 400), agl::vec2f(-450, 25), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[index]);
    world2d.push(&rect[index]);
    index++;
    rect[index].set(agl::vec2f(20, 400), agl::vec2f(450, 90), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[index]);
    world2d.push(&rect[index]);

    index++;
    rect[index].set(agl::vec2f(200, 10), agl::vec2f(0, 000), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[index]);
    world2d.push(&rect[index]);


    /*static game_element_circle circle[9124];
    static game_element_rect rect[8];
    int indexr = 0, indexc = 0;
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < i; j++)
        {
            circle[indexc++].set(20, agl::vec2f(j * 7 - i * 7 / 2, 2000 - i * 7), 10, sh, vaoc);
        }
    }
    for (int i = 0; i < indexc; i++)
        screen.push_shape(&circle[i]);
    for (int i = 0; i < indexc; i++)
        world2d.push(&circle[i]);
    indexr = 0;
    rect[indexr].set(agl::vec2f(600, 20), agl::vec2f(0, -400), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[indexr]);
    world2d.push(&rect[indexr]);
    indexr++;
    rect[indexr].set(agl::vec2f(20, 400), agl::vec2f(-450, 15), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[indexr]);
    world2d.push(&rect[indexr]);
    indexr++;
    rect[indexr].set(agl::vec2f(20, 400), agl::vec2f(450, 15), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[indexr]);
    world2d.push(&rect[indexr]);

    indexr++;
    rect[indexr].set(agl::vec2f(200, 10), agl::vec2f(0, 000), FLT_MAX, sh, vaor);
    screen.push_shape(&rect[indexr]);
    world2d.push(&rect[indexr]);*/


    //game_element_rect rect;
    //rect.set(agl::vec2f(600, 20), agl::vec2f(0, -400), FLT_MAX, sh, vaor);
    ////rect.rotation = -30;
    //screen.push_shape(&rect);
    //world2d.push(&rect);
   

    //game_element_circle grect(30, agl::vec2f(0, -200), 10, sh, vaoc);
    //world2d.push(&grect);
    //screen.push_shape(&grect);

    //game_element_circle grect2(30, agl::vec2f(15, -100), 10, sh, vaoc);
    //world2d.push(&grect2);
    //screen.push_shape(&grect2);

   /* game_element_circle grect3(30, agl::vec2f(-100, -360), 1, sh, vaoc);
    world2d.push(&grect3);
    screen.push_shape(&grect3);*/

    

    //int cc;
    //cin >> cc;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //grect.update();
        //rect.update();
        //grect2.update();
        //grect3.update();
        /*for (int i = 0; i < indexr; i++)
            rect[i].update();
        for (int i = 0; i < indexc; i++)
            circle[i].update();*/
        for (int i = 0; i < index; i++)
            rect[i].update();
        screen.run();
        glfwSwapBuffers(window);
        glfwPollEvents();
        world2d.run(1/60.0);
    }
    return 0;
}