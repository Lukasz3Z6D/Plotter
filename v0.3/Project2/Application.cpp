// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Transform.h"
#include "Sign.h"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>

void mythread() {
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(.1ms);
}



GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    GLFWwindow* window = glfwCreateWindow( 1280, 720, "Plotting FFT", monitors[1], NULL);
    glfwSetWindowPos(window, 50, 50);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

void ClearAll()
{
    GLCall( glUseProgram(0) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
    GLCall( glBindVertexArray(0) );
}

int main(void)
{
    GLFWwindow* window =  InitWindow();

    if (!window)
        return -1;


    static const float space = 0.05;
    static const float hight = 2;
    static const float width = 2;


    std::vector<float> pos
    ({
    -width/2+space, -hight/2+space, // 0
    -width/2+space, hight/2-space, // 1
    width/2-space,-hight/2+space,  // 2
    });

    std::vector<unsigned long int> ind
    ({
        1,0,
        2,0,
    });


    {



        Transform t(space, hight);

        std::vector<float> column;

        column = t.getColumn(1);


        std::vector<float> AmpAx = column;

        //step for x:
        float stepF = (width - 2 * space) / (size(column) - 1);

        int end = (pos.size() + AmpAx.size() - 6);
        int i = 0;
        while (i < end) {

            //X AXIS VALUES HERE
            pos.push_back(-width / 2 + space + (float)(i)*stepF);
            pos.push_back((float)AmpAx[i]);
            ++i;
        }


        end = ((pos.size() / 2 - 2) * 2 - 3) / 2;
        i = 0;
        while (i < end) {
            ind.push_back((int)i + 3);
            ind.push_back((int)i + 4);
            ++i;
        }

        
        //letters%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%letters
        float textSpaces = 0.25;
        float arr[2] = { 0.0f, 0.0f };
        float sizearr[2] = { 8.0f, 4.0f };
        textSpaces = textSpaces / sizearr[0];
        float cursor=0.0f;

        Sign one(49, sizearr, arr, size(pos)/2);

        one.AppendVerticies(pos);
        one.AppendIndicies(ind);



        cursor=cursor+one.GetWidth() +textSpaces;
        arr[0] = cursor;

        Sign zero(48, sizearr, arr, size(pos) / 2 );

        zero.AppendVerticies(pos);
        zero.AppendIndicies(ind);




        cursor = cursor + zero.GetWidth() + textSpaces;
        arr[0] = cursor;

        Sign oneone(49, sizearr, arr, size(pos) / 2 );

        oneone.AppendVerticies(pos);
        oneone.AppendIndicies(ind);


        cursor = cursor + oneone.GetWidth() + textSpaces;
        arr[0] = cursor;

        Sign zerozero(48, sizearr, arr, size(pos) / 2 );

        zerozero.AppendVerticies(pos);
        zerozero.AppendIndicies(ind);





        float* positions = new float[pos.size()];
        std::copy(pos.begin(), pos.end(), positions);
        //delete pos;

        unsigned long int* indices = new unsigned long int[ind.size()];
        std::copy(ind.begin(), ind.end(), indices);
        //delete ind;





        std::cout <<"\n\n\npos size: "<<pos.size()<<"\n\n";

        for (int i = 0; i < pos.size(); ++i)
            std::cout << positions[i]<< "\t aaa" << std::endl;

       //std::cout << std::endl;

        std::cout << "\n\n\nind size: " << ind.size() << "\n\n";

        for (int i = 0; i < ind.size(); ++i)
            std::cout << indices[i]<< "\t aaa" << std::endl;

        //std::cout << "\n\n\n" << ind.size() << "\n\n";

        VertexArray va;

        VertexBuffer vb(positions, pos.size() * sizeof(float));
        IndexBuffer ib(indices, ind.size());


        int possize = pos.size();
        int indsize = ind.size();


        /*
        std::cout << std::endl;
        while (pos.empty() == 0) {
            std::cout << pos.back() << "\t";
            pos.pop_back();
            std::cout << pos.back() << "\t";
            pos.pop_back();
            std::cout << std::endl;
        }
        std::cout << std::endl;
        while (ind.empty() == 0) {
            std::cout << ind.back() << "\t";
            ind.pop_back();
            std::cout << ind.back() << "\t";
            ind.pop_back();
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */







        VertexBufferLayout layout;
        layout.AddFloat(2);

        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();


        ClearAll();

  
        //std::thread mythread( mythread );


        do {
            // Clear the screen
            GLCall( glClear( GL_COLOR_BUFFER_BIT );

            // set shader and set uniform color
            shader.Bind();
            shader.SetUniform4f("u_Color", 1.0, 1.0, 1.0, 1.0);

            // Bind index buffer
            va.Bind();
            ib.Bind();

            // Draw
            GLCall( glDrawElements(GL_LINES, indsize, GL_UNSIGNED_INT, nullptr)) );



            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();


        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0 );
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

