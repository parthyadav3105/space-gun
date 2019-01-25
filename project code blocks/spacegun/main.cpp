
#include<iostream>
#include<conio.h>
#include<glm/glm.hpp>
#include<windows.h>
#include<windows.cpp>
#include<audio.h>
#include<audio.cpp>
#include<graphics.h>
#include<text.h>
#include<text.cpp>




using namespace std;

WINDOW* win;

struct BULLET
{
  glm::vec2 pos;
  BULLET* next;
  BULLET* previous;
};


class BULLETS
{   SPRITE img;
public:
    BULLET* front;
    BULLET* rear;
        BULLETS();
        ~BULLETS();
        void image_bullet(const char* file)                   {img.load(file);}
        void new_bullet(glm::vec2 position);
        void update_bullet(float distance);
        void draw_bullet();
        bool check_hit(int left,int right,int top,int bottom);
        void destroy_bullet(BULLET* n);
};

        BULLETS::BULLETS()
                        {
                            front=NULL;
                            rear=NULL;
                        }
        BULLETS::~BULLETS()
                        {
                            BULLET* n=front;
                                                  while(n!=NULL)
                                                  {  BULLET* s=n;
                                                      n=n->next;
                                                       delete s;
                                                  }

                        }

        void BULLETS::new_bullet(glm::vec2 position)
                                             {
                                                 BULLET* n=new BULLET;
                                                 if(n==NULL)
                                                               return;
                                                 n->pos=position;
                                                 n->next=NULL;
                                                 n->previous=NULL;
                                                 if(front==NULL)
                                                    front=rear=n;
                                                 else
                                                         {
                                                           n->next=NULL;
                                                           n->previous=rear;
                                                           n->previous->next=n;
                                                           rear=n;
                                                         }
                                             }

        void BULLETS::destroy_bullet(BULLET* n)
                                            {
                                                if(n==NULL)
                                                        front=rear=NULL;
                                                else
                                                    if(n==front)
                                                          {
                                                              front=n->next;
                                                              front->previous=NULL;
                                                          }
                                                else
                                                    if(n==rear)
                                                          {
                                                              rear=n->previous;
                                                              rear->next=NULL;
                                                          }
                                                else
                                                     if((n!=front)&&(n!=rear))
                                                            {n->next->previous=n->previous;
                                                              n->previous->next=n->next;
                                                            }
                                                    delete n;
                                            }

         void BULLETS::update_bullet(float distance)
                                            {
                                                BULLET* n=front;
                                                  while(n!=NULL)
                                                  {
                                                      n->pos.y+=distance;
                                                      n=n->next;
                                                  }


                                                  n=front;
                                                   while(n!=NULL)
                                                   {
                                                       if((n->pos.y>900)&&(n->pos.y<0))
                                                                       {  BULLET* s=n;
                                                                           n=n->next;
                                                                           destroy_bullet(s);
                                                                       }
                                                        else
                                                                                n=n->next;
                                                   }
                                            }

                bool BULLETS::check_hit(int left,int right,int bottom,int top)
                                           {
                                               BULLET* n=front;
                                               while(n!=NULL)
                                                           {
                                                               BULLET* s=n;
                                                               n=n->next;
                                                               if( ((s->pos.x+20)>left)&&((s->pos.x+20)<right)&&((s->pos.y+30)<top)&&((s->pos.y+30)>bottom)   )
                                                               {
                                                                   destroy_bullet(s);
                                                                   return true;
                                                               }
                                                          }
                                                return false;
                                           }

                void BULLETS::draw_bullet()
                                         {
                                             BULLET* n=front;
                                            while(n!=NULL)
                                                    {
                                                        img.draw(n->pos,glm::vec2(40,60));
                                                        n=n->next;
                                                    }
                                         }

class SHIP
{ glm::vec2 pos;
   SPRITE img;
   BULLETS bullet;
   AUDIO firesound;
   bool life;

   public:
          void draw();
          void move(BULLETS* bullets);
          glm::vec2 position()   {return pos;}
          BULLETS* bullets()      {return &bullet;}
          bool isalive()                     {return life;}
          SHIP();
          void Init()                         { life=true; pos=glm::vec2(775,10); }

};

  void SHIP::draw()
      {  img.draw(pos,glm::vec2(50,70));
          bullet.draw_bullet();
      }
   SHIP::SHIP()
      {   life=true;
          pos=glm::vec2(775,10);
          img.load("images/ship.png");
          bullet.image_bullet("images/bullet.png");
          firesound.load("audio/lasergun.wav");
      }
    void SHIP::move(BULLETS* bullets)
    {       static double last=glfwGetTime();
            static double dt,firedt,current;
            current=glfwGetTime();
            dt=current-last;
             last=current;
            static const float speed=900;

          if(win->iskeypressed(GLFW_KEY_LEFT))
              pos.x-=dt*speed;
         if(win->iskeypressed(GLFW_KEY_RIGHT))
              pos.x+=dt*speed;
        if(pos.x<0)
                  pos.x=0;
        if(pos.x>1550)
                 pos.x=1550;
        if(win->iskeypressed(GLFW_KEY_SPACE))
                        {
                            if(!firedt)
                            {bullet.new_bullet(pos+glm::vec2(-8,-5));
                            firesound.play();
                             bullet.new_bullet(pos+glm::vec2(19,-5));
                             firesound.play();
                             firedt=5;
                            }

                        }
        if(firedt!=0)
        firedt--;
        bullet.update_bullet(dt*(speed-150));

        if(bullets->check_hit(pos.x,pos.x+50,pos.y,pos.y+70))
                    {
                        life=false;
                    }

    }



    class DRONE
    {public:
        glm::vec2 pos;
        glm::vec2 destination;
        bool life;
      DRONE()   {life=false;}
      void update();
    };

    void DRONE::update()
    {static double last=glfwGetTime();
      static double dt,current;
      current=glfwGetTime();
      dt=current-last;
      float speed;
      glm::vec2 direction;
      float distance=(sqrt(((pos.x-destination.x)*(pos.x-destination.x))+((pos.y-destination.y)*(pos.y-destination.y))));


    if(distance>600)
          speed=4;
      if(distance<600)
          speed=3.7;
      if(distance<300)
          speed=3.4;
      if(distance<10)
          speed=0.1;

        if((((int)pos.x)!=((int)destination.x))&&(((int)pos.y)!=((int)destination.y)))
                {
                    if((destination.x-pos.x)<0)
                              direction.x=-1;
                    else
                                direction.x=1;
                    if((destination.y-pos.y)<0)
                              direction.y=-1;
                    else
                                direction.y=1;


                    float cosinecomponent=sqrt((destination.x-pos.x)*(destination.x-pos.x))/distance;
                     float sinecomponent=sqrt((destination.y-pos.y)*(destination.y-pos.y))/distance;
                  pos.x+=cosinecomponent*dt*speed*direction.x;
                  pos.y+=sinecomponent*dt*speed*direction.y;
                }
            else
                  destination=pos;

    }



class ENEMY
{   BULLETS bullet;
    DRONE drone[24];
    glm::vec2 target;
    SPRITE img;
    AUDIO firesound;

 public:
     ENEMY();
     void attack();
    void draw();
    void update(glm::vec2 t,BULLETS* bullets);
    bool isalive();
    BULLETS* bullets()      {return &bullet;}
};

   bool ENEMY::isalive()
      {
          for(int i=0;i<24;i++)
            if(drone[i].life)
                 return true;
          return false;
      }


     ENEMY::ENEMY()
     {  bullet.image_bullet("images/bullet2.png");
         img.load("images/drone1.png");
         firesound.load("audio/gunshot.wav");
     }


     void ENEMY::attack()
        {
            ifstream ifile;
            ifile.open("pattern1.eny");
            int i=0;
            while(!ifile.eof())
            {  ifile.read((char*)(&(drone[i])),sizeof(DRONE));
                i++;
            }
            ifile.close();
        }

    void ENEMY::update(glm::vec2 t,BULLETS* bullets)
       { target=t;
           static double last=glfwGetTime();
            static double dt,firedt,current;
            current=glfwGetTime();
            dt=current-last;
            last=current;
            static const float speed=450;

             bullet.update_bullet(-dt*speed);

           for(int i=0;i<24;i++)
                       if(drone[i].life)
                        drone[i].update();

           for(int i=0;i<24;i++)
                       if(drone[i].life)
                               {
                                  if(bullets->check_hit(drone[i].pos.x,drone[i].pos.x+50 ,drone[i].pos.y ,drone[i].pos.y+50 ))
                                   {
                                       drone[i].life=false;
                                    }
                               }

            for(int i=0;i<24;i++)
                        if((drone[i].life)&&(drone[i].pos==drone[i].destination))
                                {
                                      if(((drone[i].pos.x+25)>target.x)&&((drone[i].pos.x+25)<(target.x+ 50)))
                                              {
                                                  if(!firedt)
                                                                    {firesound.play();
                                                                        bullet.new_bullet(glm::vec2((drone[i].pos.x+5),drone[i].pos.y-30));
                                                                     firedt=20;
                                                                    }
                                              }

                                }
          if(firedt!=0)
          firedt--;




       }



     void ENEMY::draw()
     {  bullet.draw_bullet();
         for(int i=0;i<24;i++)
                       if(drone[i].life)
                        img.draw(drone[i].pos,glm::vec2(50,50)) ;
     }



     class GAME
     {  int lives;
         SHIP ship;
         ENEMY enemy;
         SPRITE background;


     public:
         void Init();
         void update();
         bool isalive();
     };

     bool GAME::isalive()
            {
                return(lives&&enemy.isalive());
            }

     void GAME::Init()
             {
                 lives=3;
                 ship.Init();
                  enemy.attack();
                  background.load("images/menu.png");

             }

     void GAME::update()
             {
                         ship.move(enemy.bullets());
                         enemy.update(ship.position(),ship.bullets());
                         if(!ship.isalive())
                         {
                             lives--;
                             ship.Init();
                         }

                         background.draw(glm::vec2(0,0),glm::vec2(1600,900));
                         enemy.draw();
                         ship.draw();

             }


             void screen()
                {
                    double last,current;
                    win->hidecursor();
                     FONT printer(1280,720);
                     printer.loadfont("font/font.ttf",76);
                    SPRITE background;
                    background.load("images/start.png");
                    background.draw(glm::vec2(0,0),glm::vec2(1600,900));
                    printer.print("Space Gun",450.0,300.0,1.2,glm::vec3(0.7,0.5,0.8));
                    win->update();
                     last=current=glfwGetTime();
                    while((current-last)<4)
                                {
                                    current=glfwGetTime();
                                }
                }



int main()
{
    WINDOW window("Space_gun");
     win=&window;
    AUDIO::Init();
    GRAPHICS_Init();




     screen();

    window.showcursor();
    SPRITE menu,ball,ball1,ball2;
    FONT printer(1280,720);
    printer.loadfont("font/font.ttf",76);
    menu.load("images/menu.png");
    ball.load("images/ball.png");
    ball1.load("images/ball1.png");
    ball2.load("images/ball2.png");



////


/*
   ofstream ofile;
   ofile.open("pattern1.eny");
   DRONE drone;

   drone.pos=glm::vec2(800,1000);
   drone.life=true;
   glm::vec2 des[24];

  int i;
   for( i=0;i<8;i++)
   {
       des[i]=glm::vec2(150+175*i,800);
   }
   for(int j=0;j<8;j++)
   {
       des[i]=glm::vec2(150+175*j,650);
       i++;
   }
      for(int j=0;j<8;j++)
   {
       des[i]=glm::vec2(150+175*j,500);
       i++;
   }
        for(i=0;i<24;i++)
        {   drone.destination=des[i];

             ofile.write((char*)(&drone),sizeof(drone) );
        }

          ofile.close();

*/






bool play=false;
bool game=true;
double x,y;
float r=0,p=0,e=0;
double last,current,dt;
float i=-90,j=-90;
last=glfwGetTime();

GAME war;


    while(game)
    {current=glfwGetTime();
      dt=current-last;
      last=current;



       //    war.update();
       menu.draw(glm::vec2(0,0),glm::vec2(1600,900));
       ball.draw(glm::vec2(200,600),glm::vec2(100,100),r*0.5);
       ball.draw(glm::vec2(500,850),glm::vec2(50,50),r*1.7);
       ball.draw(glm::vec2(1000,850),glm::vec2(60,50),r*3);
       ball.draw(glm::vec2(900,650),glm::vec2(50,50),r*1.7);
       ball.draw(glm::vec2(1400,750),glm::vec2(100,100),r*0.5);
       ball.draw(glm::vec2(i,j),glm::vec2(j/3+90,j/3+90),r);
       ball.draw(glm::vec2(-500,100),glm::vec2(600,600),r*0.5);
       ball.draw(glm::vec2(600,-500),glm::vec2(1000,1000),r*0.07);
       ball1.draw(glm::vec2(400,350),glm::vec2(200,200),r+p);
       ball2.draw(glm::vec2(950,350),glm::vec2(200,200),r+e);
       printer.print("Play",330.0,315.0,1,glm::vec3(1.0,1.0,1.0));
       printer.print("Exit",780.0,315.0,1,glm::vec3(1.0,1.0,1.0));

         window.getmouseposition(x,y);
      x=x*1600/1280;
      y=720-y;
      y=y*900/720;
      if((x>400)&&(x<600)&&(y>350)&&(y<550))  //Play
              {p+=dt*3;
                   if(window.isbuttonpressed(GLFW_MOUSE_BUTTON_LEFT))
                     {play=true;
                       war.Init();
                       window.hidecursor();

                     }
            }
         else
       if((x>950)&&(x<1150)&&(y>350)&&(y<550))  //Exit
              {e+=dt*3;
                if(window.isbuttonpressed(GLFW_MOUSE_BUTTON_LEFT))
                      {  game=false;
                      }
              }
         else
                 {
                     p=e=0;
                 }


        window.update();


        r+=dt*0.5;
        i+=dt*110;
        j+=dt*60;

        if(i>6400)
            i=j=-90;



        while(play)
        {
            if(!war.isalive())
            {play=false;
             game=false;
            window.showcursor();
            }

              if(window.iskeypressed(GLFW_KEY_ESCAPE))
                {play=false;
                 game=false;
                 window.showcursor();
                }

            war.update();
            window.update();
        }



    }



       AUDIO::terminate();
       GRAPHICS_terminate();
    return 0;
}
