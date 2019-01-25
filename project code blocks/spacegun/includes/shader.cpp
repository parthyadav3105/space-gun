
#include<shader.h>


#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

//GLEW
#define GLEW_STATIC
#include<glew.h>

string SHADER::readshadercode(const GLchar* path)
               {
                   string           code ;
                   ifstream         file ;
                   stringstream     stream ;

                   file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

                   try
                      {   //opening files
                          file.open(path);

                          //reading shader files into the string streams
                          stream << file.rdbuf();

                          //close file handlers
                          file.close();

                          //convert stream into char array
                          code  = stream.str();

                      }
                      catch(std::ifstream::failure e)
                      {
                          cout<<"SHADER FILE NOT SUCCESFULLY READ"<<endl;
                      }

                    return(code);

               }



void SHADER::checkcompileerror( GLuint shaderid)
             {
                 GLint success;
                 GLchar infoLog[512];

                           // Print compile errors if any
                 glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
                   if(!success)
                     {
                       glGetShaderInfoLog(shaderid, 512, NULL, infoLog);
                       cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog<< endl;
                     }

             }

void SHADER::checklinkingerror( )
             {
                 GLint success;
                 GLchar infoLog[512];

                  // Print linking errors if any
                 glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
                    if(!success)
                    {
                        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
                        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog <<endl;
                    }
             }




GLuint SHADER::makevertexshader(const GLchar* shadercode)
               {
                   GLuint shaderid =glCreateShader(GL_VERTEX_SHADER);
                   glShaderSource(shaderid , 1 , &shadercode,NULL);
                   glCompileShader(shaderid);
                   checkcompileerror(shaderid);
                   return(shaderid);
               }

GLuint SHADER::makefragmentshader(const GLchar* shadercode)
               {
                   GLuint shaderid =glCreateShader(GL_FRAGMENT_SHADER);
                   glShaderSource(shaderid , 1 , &shadercode,NULL);
                   glCompileShader(shaderid);
                   checkcompileerror(shaderid);
                   return(shaderid);
               }

SHADER::SHADER() { ; }


SHADER::SHADER(const GLchar* vertexsourcepath,const GLchar* fragmentsourcepath)
               {
                   string     vshadercode , fshadercode;

                   vshadercode = readshadercode(vertexsourcepath);
                   fshadercode = readshadercode(fragmentsourcepath);

                      const GLchar* vcode= vshadercode.c_str();
                      const GLchar* fcode= fshadercode.c_str();


                      // making and compiling shader
                    GLuint vertex=    makevertexshader(vcode);
                    GLuint fragment=  makefragmentshader(fcode);

                    //linking program

                    this->Program = glCreateProgram();
                    glAttachShader(this->Program, vertex);
                    glAttachShader(this->Program, fragment);
                    glLinkProgram(this->Program);


                    checklinkingerror( );


                    glDeleteShader(vertex);
                    glDeleteShader(fragment);


               }



void SHADER::use()
               {
                   glUseProgram(this->Program);
               }








                                    void SHADER::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform1f(glGetUniformLocation(this->Program, name), value);
                                    }

                                    void SHADER::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform1i(glGetUniformLocation(this->Program, name), value);
                                    }

                                    void SHADER::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform2f(glGetUniformLocation(this->Program, name), x, y);
                                    }

                                    void SHADER::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform2f(glGetUniformLocation(this->Program, name), value.x, value.y);
                                    }

                                    void SHADER::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform3f(glGetUniformLocation(this->Program, name), x, y, z);
                                    }

                                    void SHADER::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform3f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z);
                                    }

                                    void  SHADER::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform4f(glGetUniformLocation(this->Program, name), x, y, z, w);
                                    }

                                    void SHADER::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniform4f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z, value.w);
                                    }

                                    void SHADER::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
                                    {
                                        if (useShader)
                                            this->use();
                                        glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(matrix));
                                    }




