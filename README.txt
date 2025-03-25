Ray Tracer - Computer Graphics Assignment UCSD

Valli Nachiappan

Tools and Languages Used: C/C++, Visual Studio Code


Note: This was a course project for a Computer Graphics course at UCSD, and this was a partner project, however, I implemented the majority of the code. 

Only the octree files and the files in the /UCSD files were provided starter code and written by my partner. The rest are all written by me.   

Project Overview:
This repository is a ray tracer that uses the behavior of light to generate 3D images. It takes in light rays from the camera, and projects them into the scene, calculates intersection with various objects (for shadows, and mirroring effects), and applys lighting, shading and reflection to produce renderings. It also accounts for material properties. We attempted a octree implementation to speed up processing, however, it doesn't fully work. Check out image grader, and our website and google doc that goes through the implementation process. 


Features:
    - Shadows
    - Phong Shading Model
    - Reflection and Recursive Ray Tracing (Mirroring)
    - OpenMP parallelization techniques to speed up processing
    - Data Structures to handle various particles, triangles, light sources, rays, and their interactions
  

Image Grader File from Project:
https://raviucsdgroup.s3.amazonaws.com/hw3/6b943cd9308344ad6064c5f30d6b22be/20230322033111/index.html


Set up:
Visual Studio Code on Windows

Website and PDF with images and documentation of our raytracer 

    Website: https://ubiquitous-bombolone-613ee1.netlify.app/

    PDF Link: https://docs.google.com/document/d/1c4JlHD4eMzvk6LtxqXLvTMGCUiPVKiQdfPps1_hFhFs/edit?usp=sharing

      - this PDF outlines our implementation process, errors I encountered, and testing methodologies. 


My partner attempted to implement the Octree acceleration feature, but we are having some implementation issues. However we have the code for it written, even though it doesn't fully work! 
