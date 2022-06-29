L = 1;
//+
lcm = 0.05;
//+
Point(1) = {1, 0, 0, lcm};
//+
Point(2) = {0.8, 0.027, 0, lcm};
//+
Point(3) = {0.55, 0.058, 0, lcm};
//+
Point(4) = {0.3, 0.08, 0, lcm};
//+
Point(5) = {0.15, 0.078, 0, lcm};
//+
Point(6) = {0, 0.052, 0, lcm};
//+
Point(7) = {0, 0, 0, lcm};
//+
Point(8) = {0, -0.052, 0, lcm};
//+
Point(9) = {0.15, -0.078, 0, lcm};
//+
Point(10) = {0.3, -0.08, 0, lcm};
//+
Point(11) = {0.55, -0.058, 0, lcm};
//+
Point(12) = {0.8, -0.027, 0, lcm};
//+
BSpline(1) = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 1};
//+
//Transfinite Curve(1) = 100;
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
Recombine Surface {1};
//+
ss[] = Extrude {0, 0, 0.5} {Surface{1}; Layers{1}; Recombine;};
//+
Surface Loop(1) = {27, 1, 15, 19, 23, 32, 31};
//+
Volume(2) = {1};
//+
Physical Surface("in", 1) = {27};
//+
Physical Surface("out", 2) = {19};
//+
Physical Surface("walls", 3) = {23, 32, 1, 31, 15};
//+
//Mesh 3;
//+
//Mesh.SurfaceFaces = 1;
//+
//Mesh.Points = 1;


