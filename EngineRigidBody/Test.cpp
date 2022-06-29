#include <iostream>
#include "EngineRigidBody.h"

using namespace std;

const double dt = 0.0001;
const double l = 1;
const double g  = 1;

int main(int argc, char **argv){

    ///Initialization
    Vector3d I, angles0, w0, Accel0, Velocity0;
    I << 1.5, 1.5,0.5;
    angles0 << M_PI/6, -M_PI/2, 0;
    Accel0 << 0,0,0;
    Velocity0 << 0,0,0;
    w0 << 1,0,9;
    RigidBody My_Body;
    My_Body.Init(1.0,I(0),I(1),I(2),angles0,w0,Accel0,Velocity0);

    //Get iinitial torque
    Vector3d gravity = { 0,0,-g };
    Vector3d gravNI = My_Body.GetVectorNIF(gravity);
    Vector3d zNI(3); zNI << 0,0,l;
    Vector3d Torque = My_Body.GetVectorIF(zNI.cross(gravNI));
    Vector3d Force(3); Force <<0,0,0;

    //Evolve system
    double t;
    for(t = 0; t < 5; t += dt){
        cout << t << "\t" << My_Body.getTheta()*180/M_PI <<
             "\t"<< My_Body.getPhi()*180/M_PI <<
            "\t" << My_Body.getPsi()*180/M_PI << '\n';
        My_Body.UpdateAll(dt,Torque,Force);
        Torque = My_Body.GetVectorIF(zNI.cross(My_Body.GetVectorNIF(gravity)));
    }
    return 0;
}
