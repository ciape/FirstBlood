#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h"
#include <time.h>



int main() {
    float x=785, y=105;
    float frame=1;
    float walkSpeed=0.1;
    int frameCount=3;
    int N=60,M=30;
    int size=16;
    int w = size*N;
    int h = size*M;
    
    /*Game game;
    while(game.GetWindow()->IsDone()){
        game.HandelInput();
        game.Update();
        game.Render();
    }
    Window window;
    sf::RectangleShape rectangle(sf::Vector2f(120.0f,120.0f));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(1,1);

    window.Update();
    window.BeginDraw();
    window.Draw(rectangle);
    window.EndDraw();*/

    sf::RenderWindow window(sf::VideoMode(w,h), "enemy move!");
    window.setVerticalSyncEnabled(true);
    sf::Texture t_enemy,t_ShortGrass,t_Alleyway,t_Mountain,t_MediumGrass,t_bonfire;

    //load images
    t_enemy.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/dragon.png");
    t_ShortGrass.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/ShortGrass");
    t_Alleyway.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/alleyway");
    t_Mountain.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/mountain1");
    t_MediumGrass.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/MediumGrass");
    t_bonfire.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/bonfire");

    sf::Sprite enemy(t_enemy),ShortGrass(t_ShortGrass),Alleyway(t_Alleyway),Mountain(t_Mountain),MediumGrass(t_MediumGrass),bonfire(t_bonfire);
    enemy.setTextureRect(sf::IntRect(190,250,190,150)); //intRect(left, top, width, length)
    enemy.setPosition(x,y);


    sf::Clock clock;
    float timer=0;


    while(window.isOpen()){
        sf::Event event;
        float time = clock.getElapsedTime().asSeconds(); //time flowing
        clock.restart();
        timer+=time;

        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }

        //enemy movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x+=2;
            frame+=walkSpeed;
            if(frame>=frameCount)
                frame=0;
            enemy.setTextureRect(sf::IntRect(int(frame)*190,445,190,150));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x-=2;
            frame+=walkSpeed;
            if(frame>=frameCount)
                frame=0;
            enemy.setTextureRect(sf::IntRect(5+int(frame)*190,250,190,150));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  {
            y+=0.75;
            frame+=walkSpeed;
            if(frame>=frameCount)
                frame=0;
            enemy.setTextureRect(sf::IntRect(int(frame)*190,0,190,200));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            y-=0.75;
            frame+=walkSpeed;
            if(frame>=frameCount)
                frame=0;
            enemy.setTextureRect(sf::IntRect(int(frame)*190,620,190,200));
        }
        enemy.setPosition(x,y);

        //bound enemy in the window
        if(x<=0) x=0;
        if(x>=770) x=770;
        if(y<=0) y=0;
        if(y>=295) y=295;
        window.clear();

        //background
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++) {
                ShortGrass.setPosition(i*t_ShortGrass.getSize().x,j*t_ShortGrass.getSize().y);
                window.draw(ShortGrass);
            }


        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++) {
                MediumGrass.setPosition(i*t_MediumGrass.getSize().x,j*t_MediumGrass.getSize().y);
                window.draw(MediumGrass);
            }



        for (int i=0,j=2; i<N; i++)
            Alleyway.setPosition(i*t_Alleyway.getSize().x,j*t_Alleyway.getSize().y);window.draw(Alleyway);


        Mountain.setPosition(static_cast<float>(4.2 * t_Mountain.getSize().x),
                             static_cast<float>(0.5 * t_Mountain.getSize().y));
        window.draw(Mountain);


        for (int i=0; i<18; i++) {
            bonfire.setPosition(i*t_ShortGrass.getSize().x, static_cast<float>(0.6 * t_Mountain.getSize().y));
            window.draw(bonfire);
        }
        for (int i=0; i<18; i++) {
            bonfire.setPosition(i*t_ShortGrass.getSize().x, static_cast<float>(1.1 * t_Mountain.getSize().y));
            window.draw(bonfire);
        }

        window.draw(enemy);
        window.display();
    }
    return 0;
}