#pragma once
#include <memory>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "appInterface.h"

// Class Bullet3Adapter inherits from AppInterface
class Bullet3Adapter : public AppInterface {

    public:

        // Constructor for Bullet 3 adapter which takes in a pointer to btDiscreteDynamicsWorld (bullet physics world)
        Bullet3Adapter();
        

        // Defining virtual function to be overridden from app interface 
        virtual void testSim(const std::shared_ptr<btDiscreteDynamicsWorld>& sim) override;

        // Defining virtual function to be overridden from app interface 
        virtual void createBoxRigidBody(std::shared_ptr<btDiscreteDynamicsWorld>& sim, double& x, double& y, double& z) override;

        virtual void showObjectPositions(std::shared_ptr<btDiscreteDynamicsWorld>& sim) override;

    private:
        // Initialise member variables  
        std::unique_ptr<btDiscreteDynamicsWorld> sim = nullptr;
        std::vector<std::unique_ptr<btRigidBody>> rigidBodies_;

};
