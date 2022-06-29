//square-disc1

mesh_size  = 1.0;
refined_mesh_size = 0.1;
radio = 2;

Point(1) = {0, 0, 0, mesh_size};
//+
Point(2) = {10, 0, 0, mesh_size};
//+
Point(3) = {10, 10, 0, mesh_size};
//+
Point(4) = {0, 10, 0, mesh_size};
//+
Point(5) = {0, 10, 10, mesh_size};
//+
Point(6) = {10, 10, 10, mesh_size};
//+
Point(7) = {10, 0, 10, mesh_size};
//+
Point(8) = {0, 0, 10, mesh_size};
//+
Point(9) = {5, 5, 5};
//+
Point(10) = {5, 5, 5 + radio, refined_mesh_size}; 
//+
Point(11) = {5, 5, 5 - radio, refined_mesh_size}; 
//+
Point(12) = {5 , 5 - radio, 5, refined_mesh_size}; 
//+
Point(13) = {5 + radio, 5, 5, refined_mesh_size}; 
//+
Point(14) = {5, 5 + radio, 5, refined_mesh_size}; 
//+
Point(15) = {5 - radio, 5, 5, refined_mesh_size}; 
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 5};
//+
Line(5) = {5, 6};
//+
Line(6) = {6, 7};
//+
Line(7) = {7, 8};
//+
Line(8) = {8, 1};
//+
Line(9) = {2, 7};
//+
Line(10) = {3, 6};
//+
Line(11) = {4, 1};
//+
Line(12) = {5, 8};
//+
Circle(13) = {10, 9, 12};
//+
Circle(14) = {10, 9, 13};
//+
Circle(15) = {10, 9, 14};
//+
Circle(16) = {10, 9, 15};
//+
Circle(17) = {11, 9, 12};
//+
Circle(18) = {11, 9, 13};
//+
Circle(19) = {11, 9, 14};
//+
Circle(20) = {11, 9, 15};
//+
Circle(21) = {12, 9, 13};
//+
Circle(22) = {13, 9, 14};
//+
Circle(23) = {14, 9, 15};
//+
Circle(24) = {15, 9, 12};
//+
Curve Loop(1) = {1, 2, 3, 11};
//+
Curve Loop(2) = {1, 9, 7, 8};
//+
Curve Loop(3) = {2, 10, 6, -9};
//+
Curve Loop(4) = {3, 4, 5, -10};
//+
Curve Loop(5) = {4, 12, 8, -11};
//+
Curve Loop(6) = {5, 6, 7, -12};
//+
Curve Loop(7) = {13, 21, -14};
//+
Curve Loop(8) = {14, 22, -15};
//+
Curve Loop(9) = {15, 23, -16};
//+
Curve Loop(10) = {16, 24, -13};
//+
Curve Loop(11) = {-17, 18, -21};
//+
Curve Loop(12) = {-18, 19, -22};
//+
Curve Loop(13) = {-19, 20, -23};
//+
Curve Loop(14) = {-20, 17, -24};
//+
Plane Surface(1) = {1};
//+
Plane Surface(2) = {2};
//+
Plane Surface(3) = {3};
//+
Plane Surface(4) = {4};
//+
Plane Surface(5) = {5};
//
Plane Surface(6) = {6};
//+
Ruled Surface(7) = {7} In Sphere {9};
//+
Ruled Surface(8) = {8} In Sphere {9};
//+
Ruled Surface(9) = {9} In Sphere {9};
//+
Ruled Surface(10) = {10} In Sphere {9};
//+
Ruled Surface(11) = {11} In Sphere {9};
//+
Ruled Surface(12) = {12} In Sphere {9};
//+
Ruled Surface(13) = {13} In Sphere {9};
//+
Ruled Surface(14) = {14} In Sphere {9};
//+
Surface Loop(1) = {1, 2, 3, 4, 5, 6};
//+
Surface Loop(2) = {7, 8, 9, 10, 11, 12, 13, 14};
//+
Volume(1) = {1,2};
//+
Physical Surface("tangent1", 1) = {1, 2};
//+
Physical Surface("tangent2", 2) = {6, 4};
//+
Physical Surface("in", 3) = {5};
//+
Physical Surface("out", 4) = {3};
//+
Physical Surface("sphere", 5) = {7, 10, 9, 8, 12, 13, 11, 14};
//+
Physical Volume("air", 6) = {1};
//+
//Mesh 3;
//+
//Mesh.SurfaceFaces = 1;
//+
//Mesh.Points = 1;
