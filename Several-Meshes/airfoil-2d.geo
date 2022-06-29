L = 1;
//+
Point(1) = {1, 0, 0};
//+
Point(2) = {0.8, 0.027, 0};
//+
Point(3) = {0.55, 0.058, 0};
//+
Point(4) = {0.3, 0.08, 0};
//+
Point(5) = {0.15, 0.078, 0};
//+
Point(6) = {0, 0.052, 0};
//+
Point(7) = {0, 0, 0};
//+
Point(8) = {0, -0.052, 0};
//+
Point(9) = {0.15, -0.078, 0};
//+
Point(10) = {0.3, -0.08, 0};
//+
Point(11) = {0.55, -0.058, 0};
//+
Point(12) = {0.8, -0.027, 0};
//+
BSpline(1) = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 1};
//+
Transfinite Curve(1) = 301;
//+
Curve Loop(1) = {1};
//+
Point(13) = {0.5 - L, -L, 0};
//+
Point(14) = {0.5 + L, -L, 0};
//+
Point(15) = {0.5 + L, L, 0};
//+
Point(16) = {0.5 - L, L, 0};
//+
Line(2) = {13, 14};
//+
Line(3) = {14, 15};
//+
Line(4) = {15, 16};
//+
Line(5) = {16, 13};
//+
Curve Loop(2) = {2, 3, 4, 5};
//+
Plane Surface(1) = {2, 1};
//+
Physical Curve("down", 1) = {2};
//+
Physical Curve("up", 2) = {4};
//+
Physical Curve("left", 3) = {5};
//+
Physical Curve("right", 4) = {3};
//+
Physical Curve("airfoil", 5) = {1};
//+
Physical Surface("wind",6) = {1};
//+
Mesh 2;
//+
Mesh.SurfaceFaces = 1;
//+
Mesh.Points = 1;