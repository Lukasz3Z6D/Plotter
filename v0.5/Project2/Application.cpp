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
#include "Label.h"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>


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
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Plotting FFT", monitors[1], NULL);
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


    static const float space = 0.1;
    static const float hight = 2;
    static const float width = 2;
    static const float interline = 0.02f;

    std::vector<float> pos
    ({
    -width/2+space, -hight/2+space, // 0
    -width/2+space, hight/2-space, // 1
    width/2-space,-hight/2+space,  // 2
    
    0.0f,-1.0f,//3
    0.0f,1.00f,//4
    -1.0f,0.0f,//5
    1.0f,0.0f,//6

    -1.0f,-1.0f,//7
    -1.0f,1.0f,//8
    1.0f,1.0f,//9
    1.0f,-1.00f//10
    });

    std::vector<unsigned long int> ind
    ({
        1,0,
        2,0,
        //3,4,
        //5,6,
        7,8,
        8,9,
        9,10,
        10,7
    });


    {
        

        Transform t(space, hight);

        std::vector<float> column;

        column = t.getColumn(1,space);


        std::vector<float> AmpAx = column;

        int end = AmpAx.size()-1;
        int i = 0;
        while (i < end) {
            ind.push_back((int)i + size(pos)/2 );
            ind.push_back((int)i + size(pos)/2+1 );
            ++i;
        }

        //step for x:
        float stepF = (width - 2 * space) / (size(column) - 1);
        end = ( AmpAx.size() );
        i = 0;
        while (i < end) {

            //X AXIS VALUES HERE
            pos.push_back(-width / 2 + space + (float)(i)*stepF);
            pos.push_back((float)AmpAx[i]);
            ++i;
        }





        float arr[2] = { 0.0f, 0.30f };
        float sizearr[2] = { 32.0f, 16.0f };
        string text1 = "[dBm]";
        string text2 = "[Hz]";
        float italic = 0.125f;
        float textSpaces= 0.25f;
        float arr2[2] = { 0.0f, 0.0f };
       
        Label myLabel(text1, sizearr,italic);

        //myLabel.Rotate();
        //myLabel.BottomLabel();
        myLabel.CenterLabel();
        myLabel.Rotate(3);
        //myLabel.CenterLabel();
        myLabel.Rotate(2);
        float arr3[2] = { -width/2 + space-interline,0.0f };
        myLabel.Position(arr3);

        //myLabel.CenterLabel();
        //std::cout<<std::endl<<std::endl << myLabel.scale[1] << std::endl;

        myLabel.Throw(pos, ind);

        std::cout << "\n\ntyle mamy znakow: " << myLabel.getSignsAmmount() << "\n";
        std::cout << "Przeciazenie: " << myLabel.isOverloaded() << "\n";
        std::cout << text1<<std::endl;


        Label myLabel2(text2, sizearr,italic);

        //myLabel.Rotate();
        //myLabel.BottomLabel();
        myLabel2.CenterLabel();
        float positionL2[2] = {0.0f,-myLabel2.getHight()-1.0f+space-interline};
        myLabel2.Position(positionL2);
        //std::cout<<std::endl<<std::endl << myLabel.scale[1] << std::endl;

        myLabel2.Throw(pos, ind);

        std::cout << "\n\ntyle mamy znakow: " << myLabel.getSignsAmmount() << "\n";
        std::cout << "Przeciazenie: " << myLabel.isOverloaded() << "\n";
        std::cout << text1 << std::endl;







        float* positions = new float[pos.size()];
        std::copy(pos.begin(), pos.end(), positions);
        //delete pos;

        unsigned long int* indices = new unsigned long int[ind.size()];
        std::copy(ind.begin(), ind.end(), indices);
        //delete ind;





        //std::cout <<"\n\n\npos size: "<<pos.size()<<"\n\n";

       //for (int i = 0; i < pos.size(); ++i)
            //std::cout << positions[i]<< "\t aaa" << std::endl;

       //std::cout << std::endl;

        //std::cout << "\n\n\nind size: " << ind.size() << "\n\n";

      // for (int i = 0; i < ind.size(); ++i)
           // std::cout << indices[i]<< "\t aaa" << std::endl;

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

