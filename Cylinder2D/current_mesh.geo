mesh_size  = 2.0;
refined_mesh_size = 1.0;
radius = 2.0;
Side = 10.0;

Point(1) = {-Side, -Side, 0, mesh_size};
//+
Point(2) = {Side, -Side, 0, mesh_size};
//+
Point(3) = {Side, Side, 0, mesh_size};
//+
Point(4) = {-Side, Side, 0, mesh_size};
//+
Point(5) = {0, 0, 0};
//+
Point(6) = {-radius, 0, 0, refined_mesh_size};
//+
Point(7) = {radius, 0, 0, refined_mesh_size};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
Circle(5) = {6, 5, 7};
//+
Circle(6) = {7, 5, 6};
//+
Curve Loop(1) = {1, 2, 3, 4};
//+
Curve Loop(2) = {5,6};
//+
Plane Surface(1) = {1, 2};
//+
Physical Curve("down", 1) = {1};
//+
Physical Curve("up", 2) = {3};
//+
Physical Curve("left", 3) = {4};
//+
Physical Curve("right", 4) = {2};
//+
Physical Curve("Ring", 5) = {6, 5};
//+
Physical Surface("Wind",6) = {1};
