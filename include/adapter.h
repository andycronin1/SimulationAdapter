#pragma once
#include <memory>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "appInterface.h"

// Class Bullet3Adapter inherits from AppInterface
class Bullet3Adapter : public AppInterface {

    public:

        // Constructor for Bullet 3 adapter which takes in a pointer to btDiscreteDynamicsWorld (bullet physics world)
        Bullet3Adapter(std::shared_ptr<btDiscreteDynamicsWorld>& simulation);

        // ----------- Functions are defined below ---------- // 
        
        // Defining virtual function to be overridden from app interface 
        virtual void testSim() override;

        // Defining virtual function to be overridden from app interface 
        virtual void createBoxRigidBody(double& x, double& y, double& z) override;

        // Function to show object positions
        virtual void showObjectPositions() override;

        // Function to apply force to the rigid body
        virtual void applyForce(int x, int y, int z, int object_num) override;

    private:
        // Initialise member variables  
        std::shared_ptr<btDiscreteDynamicsWorld> sim = nullptr;
        std::vector<std::unique_ptr<btRigidBody>> rigidBodies_;

};

// class airSimAdapter : public AppInterface {

//     public:

//         // Constructor for AirSim adapter 
//         airSimAdapter();

// };

