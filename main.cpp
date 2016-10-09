#include <iostream>
#include <cmath>


using namespace std;


/**
 This computes the number of array elements necessary to store the coordinates for the sphere
 @param rows - the number of rows for the sphere
 @param segments - the number of segments for the sphere
 @return the number of array elements.
 **/
int NumVec3ArrayElements(const int rows, const int segments)
{
    return  ((segments * 2) + 1) * 6* rows;
}


/**
 The function creates the vertices for a sphere. Note, the sphere must be rendered as a GL_TRIANGLE_STRIP to obtain
 a complete surface model. The outcome are two arrays with points.
 
 The number of elements you need for your array is
 
	N = (segments * 2 + 1) * 6 * rows
	e.g. with 10 rows and 10 segments
	N = (10*2 + 1) * 6* 10 = 1260 elememts -> float vertices[1260]l float normals[1260];
	which results in 1260/3 = 420 vertices
 
 @oaram rows - the number of vertex rows.
 @param segments - the number of segments per row.
 @param center - a pointer to a array with 3 elements of the origin [x, y, z]
 @param r - the radius of the sphere
 @param spherePoints - pointer to a vector that can contain the vertices. The vector must already been initialized
 @param normals - pointer to a vector that can contain the normals. The vector must already been initialized
 **/
int Make_Sphere(const int rows, const int segments, const float *center, const float r, float* spherePoints, float* normals)
{
    
    
    const float PI = 3.141592653589793238462643383279502884197;
    
    int current_size = 0;
    for (float theta = 0.; theta < PI; theta += PI/float(rows)) // Elevation [0, PI]
    {
        //double theta = 1.57;
        float theta2 = theta + PI/float(rows);
        int count = 0;
        int count_row = 0;
        
        // Iterate through phi, theta then convert r,theta,phi to  XYZ
        for (float phi = 0.; phi < 2*PI + PI/float(segments) ; phi += PI/float(segments)) // Azimuth [0, 2PI]
        {
            int index = current_size + count;
            
            spherePoints[index] 	 = r * cos(phi) * sin(theta) + center[0];
            spherePoints[index + 1] = r * sin(phi) * sin(theta) + center[1];
            spherePoints[index + 2] = r            * cos(theta) + center[2];
            count+=3;
            
            spherePoints[index + 3] = r * cos(phi) * sin(theta2) + center[0];
            spherePoints[index + 4] = r * sin(phi) * sin(theta2) + center[1];
            spherePoints[index + 5] = r            * cos(theta2) + center[2];
            count+=3;
            
            normals[index]     =  cos(phi) * sin(theta);
            normals[index + 1] =  sin(phi) * sin(theta);
            normals[index + 2] =  cos(theta);
            
            normals[index + 3]  =  cos(phi) * sin(theta2);
            normals[index + 4]  =  sin(phi) * sin(theta2);
            normals[index + 5]  =  cos(theta2);
            
        }
        if(count_row == 0) count_row = count;
        
        current_size += count;
    }
    return current_size/3;
}




int main(int argc, char *argv[]) {
    
    // Set the center and the radius
    float center[3] = {0.0, 0.0, 0.0};
    float radius = 10.0;
    
    
    // Set the number of segment elements and rows of the sphere.
    // This will affect the number of triangles in the model
    int segments = 10;
    int rows = 10;
    
    
    // Compute the number of array elements necessary to store all coordinates.
    int  N = NumVec3ArrayElements(rows, segments);
    
    
    // create memory for the vertices and the normals.
    float points[N];
    float normals[N];
    
    
    // Create the points and the normal vectors
    int number_vertices = Make_Sphere(rows, segments, center, radius, points, normals);
    
    
    std::cout << number_vertices;
}



class GLMaterial
{
public:
glm::vec3 _specular_material;
glm::vec3 _diffuse_material;
glm::vec3 _ambient_material;
    float _shininess;
    
    int     _ambientColorPos;
    int     _diffuseColorPos;
    int     _specularColorPos;
    int     _shininessIdx;
    
    GLMaterial()
    {
        _specular_material = glm: :vec3(1.0, 0.0, 0.0);
        _diffuse_material = glm: :vec3(1.0, 0.0, 0.0);
        _ambient_material = glm: :vec3(1.0, 0.0, 0.0);
    }
};

class GLLightSource
    {
    public:
        float   _specular_intensity;
        float   _diffuse_intensity;
        float   _ambient_intensity;
        
        int     _specularIdx;
        int     _diffuseIdx;
        int     _ambientIdx;
        
    glm: :vec3      _lightPos;
        
        GLLightSource():
        _specular_intensity(1.0), _diffuse_intensity (1.0), _ambient_intensity(1.0)
        {
            _lightPos = glm::vec3(0.0, 0.0, 0.0);
            _specularIdx = diffuseIdx = _ambientIdx = -1;
        }
    };

    _sphereMaterial._diffuse_material = glm::vec3(1.0, 0.5, 0.0);
    _sphereMaterial._ambient_material = glm::vec3(1.0, 0.5, 0.0);
    _sphereMaterial._specular_material = glm::vec3(1.0, 0.5, 0.0);
    _sphereMaterial._shininess = 1.0;

    _sphereMaterial._ambientColorPos = glGetUniformLocation(_program, "ambient_color");
    _sphereMaterial._diffusionColorPos = glGetUniformLocation(_program, "diffuse_color");
    _sphereMaterial._specularColorPos = glGetUniformLocation(_program, "specular_color");
    _sphereMaterial._shininessIdx = glGetUniformLocation(_program, "shininess");

    glUniform3fv (_sephereMaterial._ambientColorPos, 1, &_sphereMaterial._ambient_material[0] );
    glUniform3fv(_sphereMaterial._diffuseColorPos, 1, &_sphereMaterial._diffuse_material[0]);
    glUniform3fv(_sphereMaterial._specularColorPos, 1, &_sphereMaterial._specular_material[0]);
    glUniform3fv(_sphereMaterial.shininessIdx,_sphereMaterial._shininess);
    
    _Light_source0._lightPos = glm::vec3(50.0, 50.0, 0.0);
    _Light_source0._ambient_intensity = 0.5;
    _Light_source0._specular_intensity = 1.0;
    _Light_source0._diffuse_intensity = 1.0;
    
    _Light_source0._ambientIdx = glGetUniformLocation(_program, "ambient_intensity");
    _Light_source0._diffuseIdk = glGetUniformLocation(_program, "diffuse_intensity");
    _Light_cource0._specularIdk = glGetUniformLocation(_program, "specular_intensity");
    
    glUniform1f(_light_source0._ambientIdx,_light_source0._ambient_intensity);
    glUniform1f(_light_source0._diffuseIdx,_light_source0._diffuse_intensity);
    glUniform1f(_light_source0._specularIdx,_light_source0._specular_intensity);
    glUniform3fv(_lightPosition,1,&_light_source0._lightPos[0]);

static const string vs_string_GLSphere_410 =
#version 410 core
{
    uniform (projectionMatrixBox);
    uniform mat4 viewMatrixBox;
    uniform mat4 modelMatrixBox;
    uniform vec3 diffuse_color;
    uniform vec3 ambient_color;
    uniform vec3 specular_color;
    uniform float diffuse_intensity;
    uniform float ambient_intensity;
    uniform float specular_intensity;
    uniform uniform float shininess;
    in vec3 in_Position;
    in vec3 in_Normal;
    in vec3 in_in Color;
    out vec3 pass_Color;
    
    
    void main (void)
    {
        
        vec3 normal = normalize(in_normal);
        vec4 transformedNormal = noramlize (transpose(inverse(modelMatricBox)) * vec4( normal, 1.0));
        vec4 surfacePosition = viewMatrixBox * modelMatrixBox * vec4 (in_Position, 1.0);
        
        vec4 surface_to_light = normalize( vec4(light_position, 1.0) - surfacePosition);
        
        float diffuse_coeffecient = max( dot(transformedNormal, surface_to_light), 0.0);
        vec3 out_diffuse_color = diffuse_color * diffuse_coeffecient * diffuse_intensity;
        
        vec3 incidenceVector = -surface_to_light.xyz;
        vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);
        vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
        vec3 surfaceToCamera = normalize(cameraPosition - surfacePosition.xyz);
        float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
        float specular_coeffiecent = pow(cosAngle, shininess);
        vec3 out_specular_color = specular_color * specular_coeffiecent * specular_intensity;
        
        gl_Position = projectionMatrixBox * viewedMatrixBox = modelMatrixBox * vec4(in_Position, 1.0);
        pass_Color = vec3(out_diffuse_color + out_ambient_color + out_specular_color);
        
        vec3 incidenceVector = -surface_to_light.xyz;
        vec3 reflectionVector = reflect(incidenceVector, transormedNormal.xyz:);
        vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
        vec3 surfaceToCamera = normalize(cameraPosition - surfacePosition.xyz);
        float cosAngle = max( dot(surfaceToCamera, reflectionVector),0.0);
        float specular_coeffiecent = pow(cosAngle, shininess);
        vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;
        
        
    
    
    
    
    

