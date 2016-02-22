#version 330

in vec4 color;
in vec4 fragVert;
in vec3 fragNormal;


    
uniform struct Mat {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float S;
} material;
    
uniform vec3 lightPos;
uniform vec3 cameraPosition;

layout(location = 0) out vec4 fragColor;

void main(void)
{
    //fragColor = color;
    
    //calculate normal in world coordinates
    vec3 normal = normalize(fragNormal);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = fragVert.xyz;
    vec3 surfaceToCamera = normalize(cameraPosition - fragPosition);
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = lightPos - fragPosition;

    //calculate the cosine of the angle of incidence
    //float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    //brightness = clamp(brightness, 0, 1);
    
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * material.Kd;    

    float specularCoefficient = 0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), material.S);
    vec3 specular = specularCoefficient * material.Ks;
        

    vec3 surfaceColor = material.Ka + diffuse + specular;
    surfaceColor = clamp(surfaceColor, 0, 1);
    
    vec3 gamma = vec3(1.0/2.2);
    vec3 finalColor = pow(surfaceColor, gamma);
    fragColor = vec4(finalColor.rgb, 1.0f);    
};