#include "Shader.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>


namespace Visualisation
{
    namespace Engine
    {
        // Based on openGL tutorials

        Shader::Shader(const std::string& vsFileName, const std::string fsFileName)
        {
            loadShader(vsFileName, fsFileName);
        }

        Shader::~Shader()
        {
            glDeleteProgram(ProgramID);
        }

        GLuint Shader::getProgramID() const
        {
            return ProgramID;
        }

        void Shader::loadShader(const std::string& vsFileName, const std::string fsFileName){

            // Create the shaders
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            // Read the Vertex Shader code from the file
            std::string VertexShaderCode;
            std::ifstream VertexShaderStream(vsFileName, std::ios::in);
            if (VertexShaderStream.is_open()){
                std::string Line = "";
                while (getline(VertexShaderStream, Line))
                    VertexShaderCode += "\n" + Line;
                VertexShaderStream.close();
            }
            else{
                printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vsFileName.c_str());
                getchar();
                return;
            }

            // Read the Fragment Shader code from the file
            std::string FragmentShaderCode;
            std::ifstream FragmentShaderStream(fsFileName, std::ios::in);
            if (FragmentShaderStream.is_open()){
                std::string Line = "";
                while (getline(FragmentShaderStream, Line))
                    FragmentShaderCode += "\n" + Line;
                FragmentShaderStream.close();
            }



            GLint Result = GL_FALSE;
            int InfoLogLength;



            // Compile Vertex Shader
            //printf("Compiling shader : %s\n", vertex_file_path);
            char const * VertexSourcePointer = VertexShaderCode.c_str();
            glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
            glCompileShader(VertexShaderID);

            // Check Vertex Shader
            glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0){
                std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
                glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
                printf("%s\n", &VertexShaderErrorMessage[0]);
            }



            // Compile Fragment Shader
            //printf("Compiling shader : %s\n", fragment_file_path);
            char const * FragmentSourcePointer = FragmentShaderCode.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
            glCompileShader(FragmentShaderID);

            // Check Fragment Shader
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0){
                std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
                glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
                printf("%s\n", &FragmentShaderErrorMessage[0]);
            }



            // Link the program
            //printf("Linking program\n");
            ProgramID = glCreateProgram();
            glAttachShader(ProgramID, VertexShaderID);
            glAttachShader(ProgramID, FragmentShaderID);
            glLinkProgram(ProgramID);

            // Check the program
            glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
            glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0){
                std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
                glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
                printf("%s\n", &ProgramErrorMessage[0]);
            }

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);
        }
    }
}