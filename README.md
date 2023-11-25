# learn 3d programming
        A project to learn 3d programming using directx11, directx12 and vulkan。DirectX 11 and DirectX 12 are currently fully
    functional, while Vulkan is still under development. The rendering engine of this project references Ogre 13.6,
    but many files only share the same names, and the implementation has significant differences. Moreover, many codes 
    have been simplified extensively, resulting in less than one-fourth of the code volume compared to the original
    version of Ogre.
       On the basis of Ogre, some new features have been added, such as DirectX 12 renderer, glTF model loading, video texture, etc. 
    The material section has been significantly simplified by removing the original concepts of technique and pass. To differentiate 
    between GLSL and HLSL, a simple shader script has been implemented.
        The "middle" directory in the project mainly comes from Sword Online, which is available on the Internet. The original code was 
    based on DirectX 9 and was 32-bit. The current project has been changed to be 64-bit and no longer supports DirectX 9. 
    The referenced code is primarily used for file reading, and most of the code will not actually run.
    This project is primarily used for my own study of 3D programming, so the "middle" part of the code will not be modified in 
    the future except for some compilation and adaptation changes. If there is any infringement, please contact me to delete it. O
    nly one scene has been used in the resource section as well.
    
    my email: bushlionzs@gmail.com
    qq:1787964623
    wechat: bushlion
# how to run
git clone https://github.com/bushlionzs/learn3D.git

enter into bin_release directory

Extract the DLL file from "dll.7z" and place it in the same directory as "fulldemo.exe"

run fulldemo.exe

If everything goes smoothly, you will see the following picture.

If there is a prompt indicating that vulkan-1.dll is missing, please Update the graphics card driver.

![screenshot](https://github.com/bushlionzs/learn3D/blob/main/resources/screenshot/fulldemo.jpg)

# how to compile in windows(only 64bit supported)

git clone https://github.com/bushlionzs/learn3D.git

enter into 3rd directory

Extract the "lib.7z" file to the current directory

open learn3d.sln using vs2019, then start to compile

# Example Illustration
## VideoTexture   
   You can use video texture objects in the same way as image textures.
   
   In this example, you can watch 2 minutes of Avatar.
  ![screenshot](https://github.com/bushlionzs/learn3D/blob/main/resources/screenshot/video_texture.jpg)
  
## RendertoTexture   
  This example renders a 3D model, while rendering the 3D model onto a texture, then assigns it to all six faces of a box
  ![screenshot](https://github.com/bushlionzs/learn3D/blob/main/resources/screenshot/rendertotexture.jpg)

## GameUI
  This example demonstrates using MyGUI to develop a simple game interface, and using the technique of rendering to texture to render 3D models onto a 2D interface.
  ![screenshot](https://github.com/bushlionzs/learn3D/blob/main/resources/screenshot/gameui.jpg)
  
## AnimTexture   
  This example implements two texture animations. The rectangle on the left moves the texture coordinates to form an animation, while the rectangle on the right    switches images to achieve animation.
  ![screenshot](https://github.com/bushlionzs/learn3D/blob/main/resources/screenshot/animTexture.jpg)
  
# Next Steps:
    Add PBR materials.
    Add specular reflection IBL.
    Implement deferred rendering.
