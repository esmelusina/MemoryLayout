Very Important Things:

	vec2 : normal, magnitude, dot product, vector ops (-, +), scalar (*, /), comparison (==, !=), convert to vec3 for multiplying with mat3
	mat3 : multiplication, translation, rotation, scale, identity
	Shapes/collision : AABB, Circle, Draw(const AABB &), DrawCircle(const Circle &)        
    Components: Transform, Rigidbody, Collider       
                
    ***Project with drawing integration!
------------------
First, we can make it so that our math library outputs a static library.
    
    For both debug and release:
    properties->general configuration->configuration type-> Static Library (.lib)


In the solution of your math library we could create another project to test the math library.

    add->new Project (go ahead and add a main.cpp)
    
Then access the properties of the new project so that it links correctly to your math library.

    properties->linker->additional library directories-> (Match it to the math library's Properties->General Configuration->Output Directory)
    properties->linker->Input->Additional Dependencies (add the name of the .lib file)
    properties->C/C++->additional include directories-> The Math libraries project directory
    
You can also adjust the build dependencies so that the new project depends on the library.

You should then test it out to make sure that everything is accessible and works!
------------------	

Most of the other stuff is less essential.

For inverse matrix:
http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html


For a powerful C-style math library, Great for a reference of professional work!
https://github.com/ralcr/hxcocoa/tree/master/ios/glkit