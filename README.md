# VSoftRenderer

<h4 align="center">
  <strong>VSoftRenderer</strong> is my cross-platform 3D toy soft renderer.
</h4>


<p align="center">
    <a href="https://github.com/zzxzzk115/VSoftRenderer/actions" alt="CI-Windows">
        <img src="https://img.shields.io/github/actions/workflow/status/zzxzzk115/VSoftRenderer/BuildWindows.yml?branch=master&label=CI-Windows&logo=github" /></a>
    <a href="https://github.com/zzxzzk115/VSoftRenderer/actions" alt="CI-Linux">
        <img src="https://img.shields.io/github/actions/workflow/status/zzxzzk115/VSoftRenderer/BuildLinux.yml?branch=master&label=CI-Linux&logo=github" /></a>
    <a href="https://github.com/zzxzzk115/VSoftRenderer/actions" alt="CI-MacOS">
        <img src="https://img.shields.io/github/actions/workflow/status/zzxzzk115/VSoftRenderer/BuildMacOS.yml?branch=master&label=CI-MacOS&logo=github" /></a>
    <a href="https://github.com/zzxzzk115/VSoftRenderer/issues" alt="GitHub Issues">
        <img src="https://img.shields.io/github/issues/zzxzzk115/VSoftRenderer">
    </a>
    <a href="https://github.com/zzxzzk115/VSoftRenderer/blob/master/LICENSE" alt="GitHub">
        <img src="https://img.shields.io/github/license/zzxzzk115/VSoftRenderer">
    </a>
</p>

> VSoftRenderer is still under development...
> 
> Showcases:
> 
> - Gouraud Shading
>   ![Gouraud](Media/Showcases/Gouraud.png)
> - Phong Shading with Diffuse + Normal + Specular Textures
>   ![Phong With Textures](Media/Showcases/Phong_With_Textures.png)

## Features

- Cross Platform (Windows, Linux, macOS)
- Light-weight Implementation
- Programmable Shading Pipeline
  - Define a shader through C++:
      ```c++
      struct PhongShader : public VGLShaderBase
      {
          int BindDiffuseTextureSlot;
          int BindNormalTextureSlot;
          int BindSpecularTextureSlot;

          Vector3Float UniformLightDirection;
          Matrix4      UniformMVP;
          Matrix4      UniformMVPIT;
    
          std::vector<Vector2Float> VaryingUVs {3};
    
          virtual void vert(int faceIndex, int vertexIndexInFace, Vector3Float& gl_Position) override
          {
              VaryingUVs[vertexIndexInFace] = TargetMesh->GetUV(faceIndex, vertexIndexInFace);
              gl_Position = UniformMVP * gl_Position;
          }
    
          virtual bool frag(Vector3Float bc, VGL::Color& gl_FragColor) override
          {
              Vector2Float uv = VaryingUVs[0] * bc.X + VaryingUVs[1] * bc.Y + VaryingUVs[2] * bc.Z;
              Vector3Float n = (UniformMVPIT * sample2D(BindNormalTextureSlot, uv.X, uv.Y).XYZ()).Normalized();
              Vector3Float l = (UniformMVP * UniformLightDirection).Normalized();
              Vector3Float r = (n*(n*l*2.f) - l).Normalized();
              float diffuseIntensity = std::max(0.0f, n * l);
              Color diffuseColor = sample2D(BindDiffuseTextureSlot, uv.X, uv.Y);
              float specularIntensity = std::pow(std::max(0.0f, r.Z), sample2D(BindSpecularTextureSlot, uv.X, uv.Y).R / 1.0f);
              gl_FragColor = (diffuseColor * (diffuseIntensity + 0.4f * specularIntensity)).Clamped().IgnoreAlpha();
              return false;
          }
      };
      ```
    
  - Use OpenGL-like APIs:
    ```c++
    // ... load meshes & textures from disk

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

    glBindTexture(0, diffuseTexture);
    glBindTexture(1, normalTexture);
    glBindTexture(2, specularTexture);
    
    PhongShader shader = {};
    shader.UniformMVP = mvp;
    shader.UniformMVPIT = mvp.InverseTranspose();
    shader.UniformLightDirection = light.GetDirection();
    shader.BindDiffuseTextureSlot = 0;
    shader.BindNormalTextureSlot = 1;
    shader.BindSpecularTextureSlot = 2;
    
    glBindShader(0, &shader);
    
    for (int meshIndex = 0; meshIndex < meshes.size(); ++meshIndex)
    {
        glBindMesh(meshIndex, meshes[meshIndex]);
        glUseShaderProgram(0);
        glDrawMeshIndexed(meshIndex);
    }
    ```

## Prerequisites

To build **VSoftRenderer**, you must first install the following tools.

### Windows 10/11

- Visual Studio 2019 (or above) with C++ Desktop Development Environment
- CMake 3.20 (or above)
- Git 2.1 (or above)

### Ubuntu 22.04 or above (Linux or WSL2)

Install prerequisite packages:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake git clang libx11-dev libxrandr-dev libxrender-dev libglvnd-dev libxinerama-dev libxcursor-dev libxi-dev libomp-dev
```

### MacOS

- XCode 13 (or above)
- CMake 3.20 (or above)
- Git 2.1 (or above)

## Build VSoftRenderer

Clone this repository:

```bash
git clone --recursive git@github.com:zzxzzk115/VSoftRenderer.git
```

### Build on Windows

Build it automatically:

Just double-click `BuildWindows.bat ` or you can simply use Jetbrains CLion to debug or release.

Build it manually:

```bash
cmake -S . -B build
```

Then open the generated solution file with Visual Studio.

### Build on Linux / WSL2

Build it automatically:

```bash
chmod +x *.sh && ./BuildLinux.sh
```

### Build on MacOS

Build it automatically:

```bash
chmod +x *.sh && ./BuildMacOS.sh
```

Build it manually:

```bash
cmake -S . -B build -G "Xcode"
```

Then open the generated project file with XCode.
  
## Acknowledgement

We would like to thank the following projects for their invaluable contribution to our work:

- [tinyrenderer](https://github.com/ssloy/tinyrenderer)
- [raylib](https://github.com/raysan5/raylib)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)

## License

This project is licensed under the [MIT](https://github.com/zzxzzk115/VSoftRenderer/blob/master/LICENSE) license.