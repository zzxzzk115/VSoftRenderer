# VSoftRenderer

My toy soft renderer.

> VSoftRenderer is still under development...
> 
> Showcases:
> 
> - Gouraud Shading
>   ![Gouraud](./media/showcases/Gouraud.png)

## Features

- Programmable Shading Pipeline

    - Define a shader through C++:
        ```c++
        struct GouraudShader : public VGLShaderBase
        {
            Vector3Float LightDirection;
        
            Matrix4 MVP;
        
            Vector3Float VaryingIntensity; // written by vertex shader, read by fragment shader
        
            virtual Vector3Float vert(Vertex& vertex, int vertexIndexInFace) override
            {
                VaryingIntensity[vertexIndexInFace] = std::max(0.0f, LightDirection * vertex.Normal);
                Vector3Float glVertex = MVP * VGLShaderBase::vert(vertex, vertexIndexInFace);
                return glVertex;
            }
        
            virtual bool frag(Vector3Float bc, VSoftRenderer::Color& color) override
            {
                float intensity = VaryingIntensity * bc;
                color = VSoftRenderer::Color::COLOR_WHITE * intensity;
                return false;
            }
        };
        ```
      
    - Use OpenGL-like APIs:
      ```c++
      // ... load mesh from disk

      glViewPort(0, 0, 800, 800);
      
      glClearColor({50, 50, 50, 255});
      glClear();
      
      DirectionalLight light(Vector3Float(1, 1, 1).Normalized());

      // Camera parameters
      Vector3Float eye(1 , 1, 3);
      Vector3Float center(0 , 0, 0);
      Vector3Float up(0 , 1, 0);

      Matrix4 modelMatrix = Matrix4::Identity();
      Matrix4 viewMatrix = glLookAt(eye, center, up);
      Matrix4 projectionMatrix = glProjection(eye, center);

      Matrix4 mvp = projectionMatrix * viewMatrix * modelMatrix;

      GouraudShader shader = {};
      shader.MVP = mvp;
      shader.LightDirection = light.GetDirection();

      glBindShader(0, &shader);

      for (int meshIndex = 0; meshIndex < meshes.size(); ++meshIndex)
      {
          glBindMesh(meshIndex, meshes[meshIndex]);
          glUseShaderProgram(0);
          glDrawMeshIndexed(meshIndex);
      }
      ```