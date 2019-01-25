#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<soil2/soil2.h>
#include<shader.h>
#include<shader.cpp>


  SHADER shader;
  unsigned int VAO;
  unsigned int VBO;


void GRAPHICS_Init()
{    glClearColor(0.05f,0.05f,0.05f,1.0f);
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     shader=SHADER("shaders/ship.vsh","shaders/ship.fsh");
     shader.use();
     glm::mat4 projection=glm::ortho(0.0 , 1600.0 , 0.0 , 900.0 , -1.0 , 1.0 );
     shader.SetMatrix4("projection",projection);


     float vertices[]={0.0,1.0,  0.0,1.0,
                                    1.0,0.0,  1.0,0.0,
                                    0.0,0.0,  0.0,0.0,

                                    0.0,1.0,  0.0,1.0,
                                     1.0,1.0,   1.0,1.0,
                                      1.0,0.0,  1.0,0.0
                                  };

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
                           glEnableVertexAttribArray(0);
                           glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(GLvoid*)0 );
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

}



void GRAPHICS_terminate()
{
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}



void drawsprite(unsigned int texture,glm::vec2 position,glm::vec2 size,float angle)
{
    shader.use();
    glm::mat4 model;
    model=glm::translate(model,glm::vec3(position,0.0));
    model=glm::translate(model,glm::vec3(0.5*size.x,0.5*size.y,0.0));
    model=glm::rotate(model,angle,glm::vec3(0.0,0.0,1.0));
    model=glm::translate(model,glm::vec3(-0.5*size.x,-0.5*size.y,0.0));
    model=glm::scale(model,glm::vec3(size,1.0));
    shader.SetMatrix4("model",model);

    glBindTexture(GL_TEXTURE_2D,texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);

}




class SPRITE
                    {
                        unsigned int texture;

                    public:
                        SPRITE();
                        ~SPRITE();
                        void load(const char* filename);
                        void draw(glm::vec2 position,glm::vec2 size=glm::vec2(100,100),double angle=0.0);

                    };



SPRITE::SPRITE()
         {
             glGenTextures(1,&texture);
         }


SPRITE::~SPRITE()
         {
             glDeleteTextures(1,&texture);
         }



void SPRITE::load(const char* filename)
         {
               glBindTexture(GL_TEXTURE_2D,texture);

                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

               int w,h;
               unsigned char* image=SOIL_load_image(filename,&w,&h,0,SOIL_LOAD_RGBA);

               glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
               SOIL_free_image_data(image);
               glBindTexture(GL_TEXTURE_2D,0);

         }



void SPRITE::draw(glm::vec2 position,glm::vec2 size,double angle)
         {
             drawsprite(texture,position,size,angle);
         }



#endif // GRAPHICS_H_INCLUDED
