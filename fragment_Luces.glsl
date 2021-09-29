#version 430 core
out vec4 FragColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight 
{
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;


// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);


    // diffuse shading
    float diff = dot(normal, lightDir);


    vec3 lightDirn = normalize(light.direction);



    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), (material.shininess));

    // combine results
    vec3 ambient =   light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec ;// vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords))

    return (ambient + diffuse + specular);
}



void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    

    // directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
 
    
    FragColor = vec4(result, 1.0);
}