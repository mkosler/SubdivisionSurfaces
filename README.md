# CSCE 645 / VIZA 675: Geometric Modeling

## Assignment 3: Subdivision Surfaces

Due 2013/4/9

### Purpose

Here you will learn about higher-order representations of surfaces in 3D. In particular, you will implement a variation on Catmull-Clark subdivision surfaces.

### Description

You will implement code that first loads a quadrilateral mesh. The surface will be specified using a simplified version of the OBJ file format. The file is a text-based, format where each line either starts with a

- "#": a comment meaning that the rest of the line should be ignored,
- "v": a vertex followed by 3 floats (separated by spaces) indicating the x, y, z positions of that vertex. These vertices are considered ordered and have an index equal to the order in which they appear...starting at 1.
- "f": a face followed by 4 position integers (separated by spaces) indicating the indices of this face from the vertex list

When the user presses the '+' key, you should subdivide the surface by first performing linear subdivision on the shape and then averaging as we discussed in class. If the user presses the 'L' key, you should linearly subdivide the surface. If the user presses the 'A' key, you should perform averaging on the surface (therefore '+' is a combination of 'L' and 'A').

You should render the object lit by at least one light, which means calculating normals of the faces (Flat Shading should be used). You should also use OpenGL to do all of the rendering and lighting as well as hidden surface removal. I have provided a [sample program](http://faculty.cs.tamu.edu/schaefer/teaching/645_Spring2013/assignments/TrackBall.cpp) that implements a trackball interface for rotating, translating, and zooming into a 3D object that you are free to use.

Here are some quad models for you to try: [cube](), [knot](), [monster frog]().

Note that implementing the assignment as specified will only provide 90 out of 100 points. To receive full credit, you must go above and beyond the basic requirements. You might add an interface to allow you to modify positions of the vertices of the shape. You could implement one of the other subdivision schemes that we talked about in class as well. You could use the parametric nature of subdivision surfaces to add (and subdivide) other attributes on the surface of the object. If you have access to a subdivision surface with a displacement map, you could easily implement displaced subdivision surfaces by sampling the displacement map and offsetting the vertices along the normal direction to build a very detailed shape. These are only some suggestions, and point will be given based on difficulty/creativity.

### Grading

- [15] Correctly loading the OBJ file and displaying the object
- [5] Proper lighting/hidden surface removal
- [35] Linear subdivision
- [35] Averaging
- [10] Extensions to basic requirements
