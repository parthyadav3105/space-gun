#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

//GLEW
#define GLEW_STATIC
#include<glew.h>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


//General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.

class SHADER
{
    string readshadercode(const GLchar* path);
    GLuint makevertexshader(const GLchar* shadercode);
    GLuint makefragmentshader(const GLchar* shadercode);
    void checkcompileerror(const GLuint shaderid);
    void checklinkingerror( );
public:
       GLuint Program;

       SHADER();
       SHADER(const GLchar* vertexsourcepath,const GLchar* fragmentsourcepath);
       void use();

            // Utility functions
        void    SetFloat    (const GLchar *name, GLfloat value, GLboolean useShader = false);
        void    SetInteger  (const GLchar *name, GLint value, GLboolean useShader = false);
        void    SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
        void    SetVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
        void    SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
        void    SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
        void    SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
        void    SetVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
        void    SetMatrix4  (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);



};





#endif // SHADER_H_INCLUDED
