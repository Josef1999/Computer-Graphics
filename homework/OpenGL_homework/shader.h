#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>// ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// ��ɫ������ID
	unsigned int ID;

	//���캯�� ��ȡ����ɫ����Ƭ����ɫ��
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// 1. ���ļ�·�����ļ�
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ȷ��ifstream���ܹ��׳��쳣
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// ���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// ���ļ����ж��뵽buffer��
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// �ر��ļ���
			vShaderFile.close();
			fShaderFile.close();
			// ����ת��string����
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			//�Լ��ӵģ����ڲ��ԣ���ӡ������̨
			//std::cout << vertexCode << std::endl;
			//std::cout << fragmentCode << std::endl;
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "����Shader��ȡ�ļ�ʧ��" << std::endl;
		}
		//ת���ɲ���Ҫ��char *���ͣ�
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. ������ɫ��
		unsigned int vertex, fragment;
		// ����ɫ��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// ��ɫ������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// ɾ����ɫ������Ϊ�����Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// ������ɫ����
	// ------------------------------------------------------------------------
	//ʹ����ɫ����
	void use()
	{
		glUseProgram(ID);
	}
	// �Ƚ�ʵ�õ�ͳһ����
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setBool(const std::string& name, bool value1,bool value2) const
	{
		glUniform2i(glGetUniformLocation(ID, name.c_str()), (int)value1,(int)value2);
	}
	void setBool(const std::string& name, bool value1, bool value2, bool value3) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3);
	}
	void setBool(const std::string& name, bool value1, bool value2, bool value3, bool value4) const
	{
		glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3, (int)value4);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setInt(const std::string& name, int value1, int value2) const
	{
		glUniform2i(glGetUniformLocation(ID, name.c_str()), value1, value2);
	}
	void setInt(const std::string& name, int value1, int value2, int value3) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
	}
	void setInt(const std::string& name, int value1, int value2, int value3, int value4) const
	{
		glUniform4i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value1, float value2) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
	}
	void setFloat(const std::string& name, float value1, float value2, float value3) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
	}
	void setFloat(const std::string& name, float value1, float value2, float value3, float value4) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
	}
	// ------------------------------------------------------------------------
	void setMat(const std::string& name, glm::mat4 m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE, glm::value_ptr(m));
	}
private:
	// ���ڼ����ɫ������ / ���Ӵ����ʵ�ó�������
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024]; //�洢��Ϣ��־
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "����Shader�������: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "����Shader���Ӵ���: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif