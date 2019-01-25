

#include<windows.h>

#include<soil2/soil2.h>
#include<iostream>




           void resize_callback( GLFWwindow* window, int w, int h )                                                                 {         glViewport(0,0,w,h) ;       }
           void key_callback( GLFWwindow* window, int key,int scancode, int action,int mode);
           void mouse_callback( GLFWwindow* window, int key,int action,int mode);
           void cursor_callback( GLFWwindow* window, double xpos,double ypos);
           void error_callback(int id, const char* description)                                                                                     {std::cout << description << std::endl;}
           void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);


                        //creates a fullscreen window
      WINDOW::WINDOW(char* title)
                                    {
                                        m_title = title;

                                         if (  !glfwInit()  )
                                                { glfwTerminate();
                                                    std::cout<<"failed to initialize glfw"<<std::endl ;
                                                }


                                           glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
                                           glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
                            //               glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                                            glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
                                            const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                                            glfwWindowHint(GLFW_RED_BITS,mode->redBits);
                                            glfwWindowHint(GLFW_GREEN_BITS,mode->greenBits);
                                            glfwWindowHint(GLFW_BLUE_BITS,mode->blueBits);
                                            glfwWindowHint(GLFW_REFRESH_RATE,mode->refreshRate);

                                             m_windows=glfwCreateWindow( 1280 ,720, m_title ,glfwGetPrimaryMonitor() ,NULL );
                                             if( m_windows== NULL )
                                                            std::cout<<"failed to create window"<<std::endl;

                                            glfwMakeContextCurrent(m_windows);

                                            glfwSwapInterval(1);
                                            glfwSetWindowUserPointer(m_windows,this),
                                            glfwSetWindowSizeCallback(m_windows, resize_callback );
                                            glfwSetKeyCallback(m_windows, key_callback );
                                            glfwSetMouseButtonCallback(m_windows, mouse_callback );
                                            glfwSetCursorPosCallback(m_windows,cursor_callback);
                                            glfwSetScrollCallback(m_windows,scroll_callback);
                                            glfwSetErrorCallback(&error_callback);

                                            //CURSOR ICON
                                           GLFWimage cursorImage; cursorImage.pixels =
                                           SOIL_load_image("images/cursor.PNG", &cursorImage.width, &cursorImage.height, 0, SOIL_LOAD_RGBA);
                                            GLFWcursor *cursor = glfwCreateCursor(&cursorImage, 0, 0); SOIL_free_image_data(cursorImage.pixels);
                                            glfwSetCursor(m_windows, cursor);



                                            glewExperimental = GL_TRUE;
                                            if( glewInit()  != GLEW_OK)
                                                     std::cout<<"failed to initilize glew "<<std::endl;

                                             std::cout<<"opengl version  "<<glGetString(GL_VERSION)<<std::endl;






                                            ms_scroll_y=0;
                                            glfwGetWindowSize(m_windows,&m_width,&m_height);
                                        for ( int  i = 0  ; i < MAX_KEYS ; i++)
                                                      m_keys[i]=false;

                                        for ( int j= 0  ; j < MAX_BUTTONS ; j++)
                                                      m_buttons[j]=false;

                                    }



     WINDOW::~WINDOW()
                                    {glfwTerminate();       // Terminate GLFW, clearing any resources allocated by GLFW.
                                    }



    void WINDOW::hidecursor()
                                    {glfwSetInputMode(m_windows,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
                                    }
    void WINDOW::showcursor()
                                    {glfwSetInputMode(m_windows,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
                                    }

    void WINDOW::clear()
                                   {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
                                    }

     void WINDOW::update()
                                  { glfwSwapBuffers(m_windows);
                                      glfwPollEvents();
                                  }

    bool WINDOW::closed()  const
                              {
                                  return(glfwWindowShouldClose( m_windows ));
                              }

     void WINDOW::closed(bool setit)  const
                              {
                                  glfwSetWindowShouldClose( m_windows ,setit);
                              }



                           void key_callback( GLFWwindow* window, int key,int scancode, int action,int mode)
                                    {
                                           WINDOW* win=   (WINDOW*)( glfwGetWindowUserPointer(window));
                                           win->m_keys[ key ]= ( action != GLFW_RELEASE  );
                                     }

                              void mouse_callback( GLFWwindow* window, int button,int action,int mode)
                              {
                                   WINDOW* win=   (WINDOW*)( glfwGetWindowUserPointer(window));
                                         win->m_buttons[ button ]= ( action != GLFW_RELEASE  );
                              }

                            void cursor_callback( GLFWwindow* window, double xpos,double ypos)
                              {
                                    WINDOW* win=   (WINDOW*)( glfwGetWindowUserPointer(window));
                                    win->ms_x=(int)(xpos);
                                    win->ms_y=(int)(ypos);
                              }

                            void scroll_callback(GLFWwindow* window,double xoffset,double yoffset)
                            {
                                WINDOW* win=(WINDOW*)( glfwGetWindowUserPointer(window));
                                win->ms_scroll_y=yoffset;
                            }

                         bool WINDOW::iskeypressed(unsigned int keycode)  const
                                   {
                                       if( keycode >= MAX_KEYS )
                                             return( false );
                                       return(m_keys[keycode]);
                                   }

                        bool WINDOW::isbuttonpressed(unsigned int button)  const
                                {
                                       if( button >= MAX_BUTTONS )
                                             return( false );
                                       return( m_buttons[button] );
                                   }

                   void WINDOW::getmouseposition(double& x,double& y)  const
                              {
                                  x=ms_x;
                                  y=ms_y;
                               }


