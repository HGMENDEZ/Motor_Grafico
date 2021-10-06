#version 330 core
out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 
 


float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;                                // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
     float depth = LinearizeDepth(gl_FragCoord.z) / far;        // divide by far for demonstration OPCION PARA HACER LINEAL EL VALOR DE LA PROFUNDIDAD

    // float depth = gl_FragCoord.z;                            // OPCION PARA PASAR LA PROFUNDIDAD POR DEFECTO

    FragColor = vec4(vec3(depth), 1.0);
}