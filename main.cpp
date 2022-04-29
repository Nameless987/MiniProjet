#include <SFML/Graphics.hpp>    //Librairies       
#include <SFML/OpenGL.hpp>      //Librairies   
#include <iostream>             //Librairies
#include <vector>               //Librairies
#include <math.h>               //Librairies
#include <cstdlib>              //Librairies
#include<windows.h>             //Librairies

using namespace sf;
using namespace std;

#define PI 3.14159265

const char* nameProject = "MiniProjet";

const float pi = 3.14159265357989;

Font font;
Text text;
RenderWindow window(VideoMode(1920, 1080), nameProject, Style::Fullscreen);
Event event;
Mouse mouse;
Clock gameClock;

bool fullscreen = true;
bool pause;

/*
Dans le code je n'ai pas de coordonnées attachées à chacun des points du carré donc les formules sont moins belles et pour les collisions c'est moins précis

*/

struct point{
    float m;                 //Variables pour le carré
    float x;                 //Variables pour le carré
    float y;                 //Variables pour le carré
    float w;                 //Variables pour le carré
    float h;                 //Variables pour le carré
    float vx;                //Variables pour le carré
    float vy;                //Variables pour le carré
    float ax = 0;            //Variables pour le carré
    float ay = 5000;         //Variables pour le carré
    float mteta = 0;         //Variables pour le carré
    float teta = 0.01;       //Variables pour le carré
    float Vteta = 0.01;      //Variables pour le carré
    float mus = 0.4;         //Variables pour le carré
    float dx;                //Variables pour le carré
    float dy;                //Variables pour le carré
    float d = 0;             //Variables pour le carré
    float mu = 1;            //Variables pour le carré
    bool follow = false;     //Variables pour le carré
};

vector<point> player;
point newPlayer;

struct rect{                 //Inutile
    float x, y, w, h;        //Inutile
                             //Inutile
    vector<point> points;    //Inutile
                             //Inutile
    RectangleShape body;     //Inutile
};                           //Inutile

struct quadTree{             //Inutile
    quadTree *NE;            //Inutile
    quadTree *NW;            //Inutile
    quadTree *SE;            //Inutile
    quadTree *SW;            //Inutile
                             //Inutile
    rect box;                //Inutile
                             //Inutile
    //void insert(point p){  //Inutile
    //    if()               //Inutile
    //}                      //Inutile
};                           //Inutile

float dist(float a, float b, float c, float d){
    return sqrt(pow((c-a), 2) + pow((d-b), 2));
}

int main(){
    window.setFramerateLimit(200);
    int count = 0;
    float alpha;
    float phi;

    float p1x = 0;
    float p1y = window.getSize().y-100;
    float p2x = 500;
    float p2y = window.getSize().y;

    float prex = 0;
    float prey = 0;

    srand(time(NULL));

    Texture texture;
    if (!texture.loadFromFile("images/circle.png"))
        return 0;

    //texture.loadFromImage(image);
    //texture.loadFromFile("images/circle.png");

    VertexArray circles(PrimitiveType::Triangles);
    VertexArray line(PrimitiveType::Lines);

    for(int i=0; i<1; i++){                                                         //Partie graphique
        player.push_back(newPlayer);                                                //Partie graphique
        //player[i].w=rand()%1+1;                                                   //Partie graphique
        //player[i].h=rand()%1+1;                                                   //Partie graphique
        player[i].m = 1;                                                            //Partie graphique
        player[i].w=50;                                                             //Partie graphique
        player[i].h=50;                                                             //Partie graphique
        player[i].vx=0;                                                             //Partie graphique
        player[i].vy=0;                                                             //Partie graphique
        player[i].x=rand()%(window.getSize().x-int(2*player[i].w))+player[i].w;     //Partie graphique
        player[i].y=rand()%(window.getSize().y-int(2*player[i].h))+player[i].h;     //Partie graphique
        //player[i].body.setSize(Vector2f(player[i].w, player[i].h));               //Partie graphique
                                                                                    //Partie graphique
        circles.append(Vector2f(player[i].x-player[i].w, player[i].y-player[i].h)); //Partie graphique
        circles.append(Vector2f(player[i].x+player[i].w, player[i].y-player[i].h)); //Partie graphique
        circles.append(Vector2f(player[i].x+player[i].w, player[i].y+player[i].h)); //Partie graphique
        circles.append(Vector2f(player[i].x-player[i].w, player[i].y-player[i].h)); //Partie graphique
        circles.append(Vector2f(player[i].x-player[i].w, player[i].y+player[i].h)); //Partie graphique
        circles.append(Vector2f(player[i].x+player[i].w, player[i].y+player[i].h)); //Partie graphique
                                                                                    //Partie graphique
        //circles[i*6+0].texCoords = Vector2f(0, 0);                                //Partie graphique
        //circles[i*6+1].texCoords = Vector2f(1000, 0);                             //Partie graphique
        //circles[i*6+2].texCoords = Vector2f(1000, 1000);                          //Partie graphique
                                                                                    //Partie graphique
        //circles[i*6+3].texCoords = Vector2f(0, 0);                                //Partie graphique
        //circles[i*6+4].texCoords = Vector2f(0, 1000);                             //Partie graphique
        //circles[i*6+5].texCoords = Vector2f(1000, 1000);                          //Partie graphique
                                                                                    //Partie graphique
        circles[i*6+0].color = Color::Red;                                          //Partie graphique
        //circles[i*6+1].color = Color::Red;                                        //Partie graphique
        circles[i*6+2].color = Color::Green;                                        //Partie graphique
        circles[i*6+3].color = Color::Red;                                          //Partie graphique
        circles[i*6+4].color = Color::Blue;                                         //Partie graphique
        circles[i*6+5].color = Color::Green;                                        //Partie graphique
    }
    
    line.append(Vector2f(p1x, p1y));
    line.append(Vector2f(p2x, p2y));

    while(window.isOpen()){
        window.clear(Color(32, 32, 32, 255));
        
        //circles.clear();

        float r;
        
        float w = player[0].w;
        float h = player[0].h;
        float w1;
        float h1;
        float w2;
        float h2;
        float w3;
        float h3;

        float dt = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();

        while(window.pollEvent(event)){
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Enter) && (!fullscreen)) {                        //Clavier souris
				fullscreen = true;                                                                                                 //Clavier souris
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));  //Clavier souris
			}                                                                                                                      //Clavier souris
            else if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape) && (fullscreen)) {                   //Clavier souris
				fullscreen = false;                                                                                                //Clavier souris
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));  //Clavier souris
			}                                                                                                                      //Clavier souris
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space) && (fullscreen)) {                         //Clavier souris
                pause = !pause;                                                                                                    //Clavier souris
			}                                                                                                                      //Clavier souris
                                                                                                                                   //Clavier souris
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up) && (fullscreen)) {                            //Clavier souris
                p1y -= 2;                                                                                                          //Clavier souris
			}                                                                                                                      //Clavier souris
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down) && (fullscreen)) {                          //Clavier souris
                p1y += 2;                                                                                                          //Clavier souris
			}                                                                                                                      //Clavier souris
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left) && (fullscreen) && player[0].mus > 0) {     //Clavier souris
                player[0].mus -= 0.1;                                                                                              //Clavier souris
			}                                                                                                                      //Clavier souris
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right) && (fullscreen)) {                         //Clavier souris
                player[0].mus += 0.1;                                                                                              //Clavier souris
			}                                                                                                                      //Clavier souris
                                                                                                                                   //Clavier souris
            if(event.type == Event::MouseButtonPressed){                                                                           //Clavier souris
                r = dist(mouse.getPosition().x, mouse.getPosition().y, player[0].x, player[0].y);                                  //Clavier souris
                if(abs(r*cos(player[0].teta)) < w && abs(r*sin(player[0].teta)) < h){                                              //Clavier souris
                    alpha = -player[0].teta+acos((player[0].x-mouse.getPosition().x)/r);                                           //Clavier souris
                    if(player[0].y-mouse.getPosition().y < 0){                                                                     //Clavier souris
                        alpha = -player[0].teta-acos((player[0].x-mouse.getPosition().x)/r);                                       //Clavier souris
                    }                                                                                                              //Clavier souris
                    player[0].follow = true;                                                                                       //Clavier souris
                    float dx = player[0].x-mouse.getPosition().x;                                                                  //Clavier souris
                    float dy = player[0].y-mouse.getPosition().y;                                                                  //Clavier souris
                }                                                                                                                  //Clavier souris
                //alpha = acos(dx/Dtot);                                                                                           //Clavier souris
                //if(asin(dy/Dtot)<0){                                                                                             //Clavier souris
                //    alpha *= -1;                                                                                                 //Clavier souris
                //}                                                                                                                //Clavier souris
            }                                                                                                                      //Clavier souris

            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right){                               //Clavier souris
                p1x = mouse.getPosition().x;                                                                                       //Clavier souris
                p1y = mouse.getPosition().y;                                                                                       //Clavier souris
                                                                                                                                   //Clavier souris
            }                                                                                                                      //Clavier souris
            else if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right){                         //Clavier souris
                p2x = mouse.getPosition().x;                                                                                       //Clavier souris
                p2y = mouse.getPosition().y;                                                                                       //Clavier souris
                                                                                                                                   //Clavier souris
                phi = atan((p2y-p1y)/(p2x-p1x));                                                                                   //Clavier souris
            }                                                                                                                      //Clavier souris
                                                                                                                                   //Clavier souris
            if(event.type == Event::MouseButtonReleased){                                                                          //Clavier souris
                player[0].follow = false;                                                                                          //Clavier souris
            }                                                                                                                      //Clavier souris
            //if(event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased){                             //Clavier souris
            //    player[0].follow = !player[0].follow;                                                                            //Clavier souris
            //}                                                                                                                    //Clavier souris
            if(event.type == Event::Closed){                                                                                       //Clavier souris
                window.close();                                                                                                    //Clavier souris
            }                                                                                                                      //Clavier souris
        }                                                                                                                          //Clavier souris

        if(fullscreen && !pause){
            for(int i=0; i<player.size(); i++){

                if(player[i].follow){

                    player[i].Vteta += 0.2*dt*player[i].ay*cos(player[i].teta+alpha)/r;                                            //Oscillations pendule
                                                                                                                                   //Oscillations pendule
                    player[i].x = mouse.getPosition().x+(r*cos(player[i].teta+alpha));                                             //Oscillations pendule
                    player[i].y = mouse.getPosition().y+(r*sin(player[i].teta+alpha));                                             //Oscillations pendule
                                                                                                                                   //Oscillations pendule
                    player[i].vx = (player[i].x-prex)/dt;                                                                          //Oscillations pendule
                    player[i].vy = (player[i].y-prey)/dt;                                                                          //Oscillations pendule
                                                                                                                                   //Oscillations pendule
                    prex = player[i].x;                                                                                            //Oscillations pendule
                    prey = player[i].y;                                                                                            //Oscillations pendule
                                                                                                                                   //Oscillations pendule
                    phi = atan((p2y-p1y)/(p2x-p1x));                                                                               //Oscillations pendule


                    if((player[i].x-(player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta))))<0){                                                      //Collisions
                        player[i].Vteta *= -0.5;                                                                                                                          //Collisions
                    }                                                                                                                                                     //Collisions
                    else if((player[i].x+(player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta)))) > window.getSize().x){                              //Collisions
                        player[i].Vteta *= -0.5;                                                                                                                          //Collisions
                    }                                                                                                                                                     //Collisions
                    if((player[i].y-(player[i].w*abs(sin(player[i].teta))+player[i].h*abs(cos(player[i].teta))))<0){                                                      //Collisions
                        player[i].Vteta *= -0.5;                                                                                                                          //Collisions
                    }                                                                                                                                                     //Collisions
                    else if((player[i].y+(player[i].w*abs(sin(player[i].teta))+player[i].h*abs(cos(player[i].teta)))) > window.getSize().y){                              //Collisions
                        player[i].Vteta *= -0.5;                                                                                                                          //Collisions
                    }                                                                                                                                                     //Collisions
                                                                                                                                                                          //Collisions
                    if((player[i].y+(player[i].w*abs(sin(player[i].teta-phi))+player[i].h*abs(cos(player[i].teta-phi)))) > ((p2y-p1y)/(p2x-p1x))*(player[i].x-p1x)+p1y){  //Collisions
                        player[i].Vteta *= -0.5;                                                                                                                          //Collisions
                    }
                }
                else{
                    player[i].vx+=player[i].m*player[i].ax*dt;      //Mouvement
                    player[i].vy+=player[i].m*player[i].ay*dt;      //Mouvement
                    player[i].x+=player[i].vx*dt;                   //Mouvement
                    player[i].y+=player[i].vy*dt;                   //Mouvement
                    
                    phi = atan((p2y-p1y)/(p2x-p1x));

                    if((player[i].x-(player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta))))<0){                             //Collision mur gauche
                        player[i].x += 2*((player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta)))-player[i].x);
                        player[i].vx *= -0.5;
                        if(sin(player[i].mteta-pi)<0){
                            player[i].Vteta += -1*dt*(player[i].vx+player[i].Vteta)*cos(player[i].mteta);
                        }
                        else{
                            player[i].Vteta += dt*(player[i].vx-player[i].Vteta)*cos(player[i].mteta);
                        }
                    }
                    else if((player[i].x+(player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta)))) > window.getSize().x){     //Collision mur droit
                        player[i].x += 2*(window.getSize().x-(player[i].x+(player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta)))));
                        player[i].vx *= -0.5;
                        if(sin(player[i].mteta)<0){
                            player[i].Vteta += -1*dt*(player[i].vx+player[i].Vteta)*cos(player[i].mteta);
                        }
                        else{
                            player[i].Vteta += dt*(player[i].vx-player[i].Vteta)*cos(player[i].mteta);
                        }
                    }
                    if((player[i].y-(player[i].w*abs(sin(player[i].teta))+player[i].h*abs(cos(player[i].teta))))<0){                             //Collision plafond
                        player[i].y += 2*((player[i].w*abs(cos(player[i].teta))+player[i].h*abs(sin(player[i].teta)))-player[i].y);
                        player[i].vy *= -0.5;
                        if(cos(player[i].mteta+pi/2)<0){
                            player[i].Vteta += -1*dt*(player[i].vy+player[i].Vteta)*sin(player[i].mteta+pi/2);
                        }
                        else{
                            player[i].Vteta += dt*(player[i].vy-player[i].Vteta)*sin(player[i].mteta+pi/2);
                        }
                    }
                    else if((player[i].y+(player[i].w*abs(sin(player[i].teta))+player[i].h*abs(cos(player[i].teta)))) > window.getSize().y){     //Collision sol
                        player[i].y += 2*(window.getSize().y-(player[i].y+(player[i].w*abs(sin(player[i].teta))+player[i].h*abs(cos(player[i].teta)))));

                        if((player[i].teta<pi/2 && player[i].teta>0) || (player[i].teta<-pi/2 && player[i].teta>-pi)){  //Je crois qu'il y a quelques erreurs liées à ces conditions car j'utilise que le point du centre de masse et l'angle du carré
                            player[i].vy -= player[i].vy+0.5*player[i].vy*pow(sin(player[i].teta+pi/4), 2);
                            if(cos(player[i].mteta-pi/2)<0){
                                player[i].vx -= player[i].vy*pow(cos(player[i].teta+pi/4), 2);
                            }
                            else{
                                player[i].vx += player[i].vy*pow(cos(player[i].teta+pi/4), 2);
                            }
                        }
                        else{                                                                                           //Je crois qu'il y a quelques erreurs liées à ces conditions car j'utilise que le point du centre de masse et l'angle du carré
                            player[i].vy -= player[i].vy+0.5*player[i].vy*abs(pow(cos(player[i].teta+pi/4), 2));
                            if(cos(player[i].mteta-pi/2)<0){
                                player[i].vx -= player[i].vy*pow(sin(player[i].teta+pi/4), 2);
                            }
                            else{
                                player[i].vx += player[i].vy*pow(sin(player[i].teta+pi/4), 2);
                            }
                        }

                        if(player[i].vx>0){                                 //Frottements dynamiques très simplifiés (angle = pi/2 donc cos(angle) = 1)
                            player[i].vx -= 100*player[i].mus;
                        }
                        else if(player[i].vx<0){
                            player[i].vx += 100*player[i].mus;
                        }

                        if(cos(player[i].mteta-pi/2)<0){
                            player[i].Vteta += 1*dt*(player[i].vy+5*player[i].Vteta)*sin(player[i].mteta-pi/2);
                        }
                        else{
                            player[i].Vteta += -1*dt*(player[i].vy-5*player[i].Vteta)*sin(player[i].mteta-pi/2);
                        }
                    }
                    if((player[i].y+(player[i].w*abs(sin(player[i].teta-phi))+player[i].h*abs(cos(player[i].teta-phi)))) > ((p2y-p1y)/(p2x-p1x))*(player[i].x-p1x)+p1y){   //Collision ligne
                        player[i].y += 2*(((p2y-p1y)/(p2x-p1x))*(player[i].x-p1x)+p1y-(player[i].y+(player[i].w*abs(sin(player[i].teta-phi))+player[i].h*abs(cos(player[i].teta-phi)))));
                        
                        player[i].vy -= player[i].vy+0.5*player[i].vy*abs(pow(sin(player[i].teta+pi/4-phi), 2));

                        if(tan(phi) <= player[i].mus){
                            player[i].vx = 0;
                        }
                        else{
                            player[i].vx -= 0.5*player[i].vy*abs(pow(cos(player[i].teta+pi/4-phi), 2));
                        }
                        
                        if(player[i].vx<0){
                            player[i].vx += 10*cos(phi)*player[i].mus;
                        }

                        if(cos(player[i].mteta-pi/2-phi)<0){
                            player[i].Vteta += 0.5*dt*(player[i].vy+5*player[i].Vteta)*sin(player[i].mteta-pi/2);
                        }
                        else{
                            player[i].Vteta += -0.5*dt*(player[i].vy-5*player[i].Vteta)*sin(player[i].mteta-pi/2);
                        }
                    }
                }

                if(player[i].teta > 2*pi){
                    player[i].teta -= 2*pi;
                }
                else if(player[i].teta < -2*pi){
                    player[i].teta += 2*pi;
                }
                
                player[i].teta += player[i].Vteta*dt;
                player[i].mteta += player[i].Vteta*dt;
                if(player[i].mteta > pi/4){
                    player[i].mteta -= pi/2;
                }
                if(player[i].mteta < -pi/4){
                    player[i].mteta += pi/2;
                }

                //player[i].Vteta *= 0.99;

                w = player[i].w*sqrt(2)*cos(player[i].teta+pi/4);
                h = player[i].h*sqrt(2)*sin(player[i].teta+pi/4);

                w1 = player[i].w*sqrt(2)*cos(player[i].teta-pi/4);
                h1 = player[i].h*sqrt(2)*sin(player[i].teta-pi/4);

                w2 = -w;
                h2 = -h;

                w3 = -w1;
                h3 = -h1;
                
                circles[i*6+0].position = Vector2f(player[i].x+w2, player[i].y+h2);
                circles[i*6+1].position = Vector2f(player[i].x+w1, player[i].y+h1);
                circles[i*6+2].position = Vector2f(player[i].x+w, player[i].y+h);
                circles[i*6+3].position = circles[i*6+0].position;
                circles[i*6+4].position = Vector2f(player[i].x+w3, player[i].y+h3);
                circles[i*6+5].position = circles[i*6+2].position;

                line[0].position = Vector2f(p1x, p1y);
                line[1].position = Vector2f(p2x, p2y);

                // en fonction de cos(teta)

                //player[i].body.setPosition(player[i].x, player[i].y);
            }
        }
        
        window.draw(circles);
        window.draw(line);

        window.display();
    }

    return 0;
}