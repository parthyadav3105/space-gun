#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <iostream>
#include <map>

// GLEW
#define GLEW_STATIC
#include <glew.h>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"


/// Holds all state information relevant to a character as loaded using FreeType

struct Character {
                                        GLuint            TextureID;      // ID handle of the glyph texture
                                        glm::ivec2    Size;                  // Size of glyph
                                        glm::ivec2    Bearing;         // Offset from baseline to left/top of glyph
                                        GLuint            Advance;       // Horizontal offset to advance to next glyph
                                     };


                              // A renderer class for rendering text displayed by a font loaded using the FreeType library. A single font is loaded, processed into a list of Character items for later rendering.
                            class FONT
                            {
                                  GLuint VAO, VBO;
                                  SHADER *m_textshader;      // Shader used for text rendering
                              public:
                                                // Holds a list of pre-compiled Characters
                                                map<GLchar, Character>  Characters;



                                                // Constructor
                                                FONT(GLuint width, GLuint height);

                                                ~FONT( );

                                                // Pre-compiles a list of characters from the given font
                                                void loadfont( string font ,  GLuint  fontSize);

                                                // Renders a string of text using the precompiled list of characters
                                                void print( string text ,  GLfloat x , GLfloat y , GLfloat scale =1.0f , glm::vec3 color = glm::vec3(1.0f)  ) ;

                            };


#endif // TEXT_H_INCLUDED
