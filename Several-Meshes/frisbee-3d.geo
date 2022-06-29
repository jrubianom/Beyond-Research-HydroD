//****************
//** Parameters **
//****************
//+
R = 0.8; // Radius of border of the RBC
//+
Lcent = 20; // Length of the central part of the RBC
//+
depr = R/4; //magnitude of the depression of central part of the RBC
//+
th = 2*R/5; //Thickness of the cell
//+
lcm = R/4; //Characteristic length of the mesh
//+
mesh_size = 4; //characteristic length near the bounders
//+
theta = Pi/6;
//**************
//** Geometry **
//**************
//+
x1 = -Lcent/2;
y1 = -R;		 
Point(1) = {x1*Cos(theta) + y1*Sin(theta), -x1*Sin(theta) + y1*Cos(theta), 0};
//+
x2 = -Lcent/2;
y2 = 0;
Point(2) = {x2*Cos(theta) + y2*Sin(theta), -x2*Sin(theta) + y2*Cos(theta), 0};
//+
x3 = -Lcent/2;
y3 = R;
Point(3) = {x3*Cos(theta) + y3*Sin(theta), -x3*Sin(theta) + y3*Cos(theta), 0};
//+
x4 = -R-Lcent/2;
y4 = 0;
Point(4) = {x4*Cos(theta) + y4*Sin(theta), -x4*Sin(theta) + y4*Cos(theta), 0};
//+
Circle(1) = {3, 2, 4};
//+
Circle(2) = {4, 2, 1};
//+
//Top central line (with Spline)
//+
x5 = -Lcent/4;
y5 = R + 1.5*depr;
Point(5) = {x5*Cos(theta) + y5*Sin(theta), -x5*Sin(theta) + y5*Cos(theta), 0};
//+
x6 = 0;
y6 = R + 2*depr;
Point(6) = {x6*Cos(theta) + y6*Sin(theta), -x6*Sin(theta) + y6*Cos(theta), 0};
//+
Spline(3) = {3, 5, 6};
//+
//Bottom central line
//+
//inner frisbee
//+
x9 = -Lcent/2;
y9 = -R + th;
Point(9) = {x9*Cos(theta) + y9*Sin(theta), -x9*Sin(theta) + y9*Cos(theta), 0, lcm};
//+
x10 = -Lcent/2;
y10 = 0;
Point(10) = {x10*Cos(theta) + y10*Sin(theta), -x10*Sin(theta) + y10*Cos(theta), 0, lcm};
//+
x11 = -Lcent/2;
y11 = R - th;
Point(11) = {x11*Cos(theta) + y11*Sin(theta), -x11*Sin(theta) + y11*Cos(theta), 0, lcm};
//+
x12 = -R + th-Lcent/2;
y12 = 0;
Point(12) = {x12*Cos(theta) + y12*Sin(theta), -x12*Sin(theta) + y12*Cos(theta), 0, lcm};
//+
Circle(5) = {11, 10, 12};
//+
Circle(6) = {12, 10, 9};
//+
//Top central line (with Spline)
//+
x13 = -Lcent/4;
y13 = R - th*0.7 +  1.5*depr;
Point(13) = {x13*Cos(theta) + y13*Sin(theta), -x13*Sin(theta) + y13*Cos(theta), 0, lcm};
//+
x14 = 0;
y14 = R - th + 2*depr;
Point(14) = {x14*Cos(theta) + y14*Sin(theta), -x14*Sin(theta) + y14*Cos(theta), 0, lcm};
//+
Spline(7) = {11, 13, 14};
//+
x15 = -Lcent/2;
y15 = -R + th/2;
Point(15) = {x15*Cos(theta) + y15*Sin(theta), -x15*Sin(theta) + y15*Cos(theta), 0, lcm};
//+
x16 = th/2-Lcent/2;
y16 = -R + th/2;
Point(16) = {x16*Cos(theta) + y16*Sin(theta), -x16*Sin(theta) + y16*Cos(theta), 0, lcm};
//+
Circle(4) = {1, 15, 16};
//+
Circle(8) = {16, 15, 9};
//+
//surroundings
//+
Point(17) = {-50, -20, -20, mesh_size};
//+
Point(18) = {50, -20, -20, mesh_size};
//+
Point(19) = {50, 20, -20, mesh_size};
//+
Point(20) = {-50, 20, -20, mesh_size};
//+
Point(21) = {-50, 20, 20, mesh_size};
//+
Point(22) = {50, 20, 20, mesh_size};
//+
Point(23) = {50, -20, 20, mesh_size};
//+
Point(24) = {-50, -20, 20, mesh_size};
//+
Line(9) = {17, 18};
//+
Line(10) = {18, 19};
//+
Line(11) = {19, 20};
//+
Line(12) = {20, 21};
//+
Line(13) = {21, 22};
//+
Line(14) = {22, 23};
//+
Line(15) = {23, 24};
//+
Line(16) = {24, 17};
//+
Line(17) = {18, 23};
//+
Line(18) = {19, 22};
//+
Line(19) = {20, 17};
//+
Line(20) = {21, 24};
//+
Curve Loop(1) = {9, 10, 11, 19};
//+
Curve Loop(2) = {9, 17, 15, 16};
//+
Curve Loop(3) = {10, 18, 14, -17};
//+
Curve Loop(4) = {11, 12, 13, -18};
//+
Curve Loop(5) = {12, 20, 16, -19};
//+
Curve Loop(6) = {13, 14, 15, -20};
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
//**********
//** Mesh **
//**********
//Number of divisions on the circular lines
//+
Transfinite Curve {1, 2, 4, 8, 6, 5} = 20*R;
//+
//Extrussions by 90º each
//+
For i In {1:8}
    	ss[] = Extrude {{Sin(theta), Cos(theta), 0}, {0, 0, 0}, Pi/2} {Curve{i}; Layers{20};};
	//+
	ss1[] = Extrude {{Sin(theta), Cos(theta), 0}, {0, 0, 0}, Pi/2} {Curve{ss[0]}; Layers{20};};
	//+
	ss2[] = Extrude {{Sin(theta), Cos(theta), 0}, {0, 0, 0}, Pi/2} {Curve{ss1[0]}; Layers{20};};
	//+
	ss3[] = Extrude {{Sin(theta), Cos(theta), 0}, {0, 0, 0}, Pi/2} {Curve{ss2[0]}; Layers{20};};
	//+
	Printf("Generated surfices = %g, %g, %g, %g ", ss[1], ss1[1], ss2[1], ss3[1]);
EndFor
//+
//define volume
//+
Surface Loop(1) = {1, 2, 3, 4, 5, 6};
//+
Surface Loop(2) = {24, 28, 32, 36, 40, 44, 48, 52, 55, 58, 61, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 115, 118, 121, 124, 128, 132, 136, 140};
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
Physical Surface("frisbee", 5) = {24, 28, 32, 36, 40, 44, 48, 52, 55, 58, 61, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 115, 118, 121, 124, 128, 132, 136, 140};
//+
Physical Volume("air", 6) = {1};
//+
Mesh 3;
//+
//Mesh.SurfaceFaces = 1;
//+
Mesh.Points = 1;