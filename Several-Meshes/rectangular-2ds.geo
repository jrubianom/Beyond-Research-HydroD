Point(1) = {0, 0, 0};
Point(2) = {10, 0, 0};
Point(3) = {10, 10, 0};
Point (4) = {0, 10, 0};//+
Line(1) = {4, 1};
//+
Line(2) = {1, 2};
//+
Line(3) = {2, 3};
//+
Line(4) = {4, 3};
//+
Curve Loop(1) = {4, -3, -2, -1};
//+
Plane Surface(1) = {1};
//+
Physical Curve("inlet", 1) = {1};
//+
Physical Curve("outlet", 3) = {3};
//+
Physical Curve("top", 2) = {4};
//+
Physical Curve("bottom", 4) = {2};
//+
Physical Surface("plane", 5) = {1};
//+
Transfinite Surface {1} = {4, 3, 2, 1};
//+
Transfinite Curve {1, 3} = 10 Using Progression 1;
//+
Transfinite Curve {4, 2} = 20 Using Progression 1;
//+
Recombine Surface {1};
//+
Recombine Surface {1};
//+
Mesh 2;
//+

