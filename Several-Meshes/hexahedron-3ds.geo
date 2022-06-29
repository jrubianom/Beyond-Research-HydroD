Point(1) = {0, 0, 0};
Point(2) = {2, 0, 0};
Point(3) = {2, 2, 0};
Point (4) = {0, 2, 0};//+
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
Physical Curve("inlet", 5) = {1};
//+
Physical Curve("outlet", 6) = {3};
//+
Physical Curve("top", 7) = {4};
//+
Physical Curve("bottom", 8) = {2};
//+
Transfinite Surface {1} = {4, 3, 2, 1};
//+
Transfinite Curve {1, 3} = 4 Using Progression 1;
//+
Transfinite Curve {4, 2} = 4 Using Progression 1;
//+
Recombine Surface {1};
//+
Recombine Surface {1};
//+
Extrude {0, 0, 1} {
  Surface{1};
  Layers{4};
  Recombine;
  }
//+
Physical Surface("inlet", 1) = {29};
//+
Physical Surface("outlet", 2) = {21};
//+
Physical Surface("top", 3) = {17};
//+
Physical Surface("bottom", 4) = {25};
//+
Physical Surface("back", 5) = {1};
//+
Physical Surface("front", 6) = {30};
//+
Physical Volume("volume", 7) = {1};
//+
Mesh 3;
