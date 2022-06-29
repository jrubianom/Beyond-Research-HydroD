//Engine of Rigid Body Motion.
//Given a Torque get the angular velocity in each iteration
#ifndef _ENGINERIGIDBODY_H
#define _ENGINERIGIDBODY_H

#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;
class RigidBody{
        private:

                double mass;
                // attributes related with rotational movement
                Vector3d I; //Inertia vector
                Vector4d q; //quaternions
                Vector3d w; //omega in Non inertial frame
                Vector3d Omega; // omega in innertial frame
                Vector3d OmegaDot; // D Omega / Dt in inertial frame
                Vector3d T; //Torque
                Matrix3d A; //Change of basis from IF to NIF
                Matrix3d Ainv; //Change of basis from NIF to I

                // attributes related with translational movement
                Vector3d Force; //Force mmesured in Inertial Frame
                Vector3d Accel; // Aceleration mmeaasured in IF
                Vector3d Velocity; // Velocity measured in IF



        public:
                //angles are euler angles
                void Init(double mass0, double Ix,double Iy, double Iz,
                          Vector3d angles0,Vector3d w0,
                          Vector3d Accel0, Vector3d Velocity0);
                void UpdateA();
                void UpdateAinv();
                void Rotate(double dt);
                Vector3d GetVectorNIF(Vector3d X); // get vector in the non inertial frame
                Vector3d GetVectorIF(Vector3d X);//get vector in inertial frame
                void GetTorqueNIF(Vector3d Tif); ///get the torque in non-inertial-frame
                void GetForceIF(Vector3d Fif); //pass the net force in IF
                void UpdateRotational(double dt);
                void UpdateTranslational(double dt);
                void UpdateAll(double dt,Vector3d Tif,Vector3d Fif);
                Vector3d getW();
                Vector3d getOmega();
                Vector3d getOmegaDot();
                Vector3d getAccel();
                Vector3d getVelocity();
                double getTheta();
                double getPhi();
                double getPsi();
};

#endif
