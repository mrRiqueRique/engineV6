#include <Graphics/Shader.hpp>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc, std::string name) : name(name){
    std::string vertexCode = readShaderFile(vertexSrc);
    std::string fragmentCode = readShaderFile(fragmentSrc);

    const char* vsrc = vertexCode.c_str();
    const char* fsrc = fragmentCode.c_str();

    GLuint vs = compileShader(vsrc, GL_VERTEX_SHADER, name);
    GLuint fs = compileShader(fsrc, GL_FRAGMENT_SHADER, name);

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);

    glLinkProgram(ID);

    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    GLchar infoLog[512];
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Erro ao linkar o shader program:\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader(){
    glDeleteProgram(ID);
}

GLuint Shader::compileShader(const char* shader, GLenum type, const std::string& ID){
    GLuint s = glCreateShader(type);

    glShaderSource(s, 1, &shader, nullptr);
    glCompileShader(s);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(s, 512, NULL, infoLog);
        if(type == GL_VERTEX_SHADER)
            std::cerr << "Erro ao compilar " << ID << " vertex shader:\n" << infoLog << std::endl; 

        else if(type == GL_FRAGMENT_SHADER)
            std::cerr << "Erro ao compilar " << ID << " vertex shader:\n" << infoLog << std::endl; 
    }

    return s;
}

std::string Shader::readShaderFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de shader: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::activate() const {
    glUseProgram(ID);
}

void Shader::informMat3(const char* loc, glm::mat3 matrix) const {
    GLuint matLoc = glGetUniformLocation(ID, loc);
    glUniformMatrix3fv(matLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::informMat4(const char* loc, glm::mat4 matrix) const {
    GLuint matLoc = glGetUniformLocation(ID, loc);
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::informVec4(const char* loc, glm::vec4 vector) const {
    GLuint vecLoc = glGetUniformLocation(ID, loc);
    glUniform4f(vecLoc, vector.x, vector.y, vector.z, vector.w);
}

void Shader::informVec3(const char* loc, glm::vec3 vector) const {
    GLuint vecLoc = glGetUniformLocation(ID, loc);
    glUniform3f(vecLoc, vector.x, vector.y, vector.z);
}

void Shader::informVec2(const char* loc, glm::vec2 vector) const {
    GLuint vecLoc = glGetUniformLocation(ID, loc);
    glUniform2f(vecLoc, vector.x, vector.y);
}

void Shader::informDVec2(const char* loc, glm::dvec2 vector) const {
    GLuint dvecLoc = glGetUniformLocation(ID, loc);
    glUniform2d(dvecLoc, vector.x, vector.y);
}

void Shader::informBool(const char* loc, bool info) const {
    GLuint boolLoc = glGetUniformLocation(ID, loc);
    glUniform1i(boolLoc, info);
}

void Shader::informDouble(const char* loc, double value) const {
    GLuint doubleLoc = glGetUniformLocation(ID, loc);
    glUniform1d(doubleLoc, value);
}

void Shader::informFloat(const char* loc, float value) const {
    GLuint floatLoc = glGetUniformLocation(ID, loc);
    glUniform1f(floatLoc, value);
}

void Shader::informInt(const char* loc, int value) const {
    GLuint intLoc = glGetUniformLocation(ID, loc);
    glUniform1i(intLoc, value);
}

void Shader::activateWireframeMode(){
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
}

void Shader::deactivateWireframeMode(){
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
}
