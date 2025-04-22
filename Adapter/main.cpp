
#include <iostream> 
#include <string>
#include <vector>
#include <memory>
#include <iostream> 
#include "appInterface.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <stdio.h>

// Bullet3 Adapter
class Bullet3Adapter : public AppInterface { 
    public:
        // CONSTRUCTOR

        // Adapter takes a pointer to an instance of the simultion object
        Bullet3Adapter(btDiscreteDynamicsWorld* c) : client{c} {}

        // Override the app method with the clients make rigid body method 
        virtual void createBoxRigidBody(double& x, double& y, double& z) override {

        // 1. Shape: Define the collision shape of the rigid body
        std::shared_ptr<btCollisionShape> groundShape = std::make_shared<btBoxShape>(btVector3(x, y, z)); 

        // 2. Motion State:
        std::shared_ptr<btDefaultMotionState> groundMotionState = std::make_shared<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -56, 0))); 

        // 3. Mass and Inertia: Set physical properties (0 mass for static objects)
        btScalar mass = 0; // Mass in kilograms (0 for static ground)
        btVector3 inertia(0, 0, 0); 
        if (mass != 0.f) {
            groundShape->calculateLocalInertia(mass, inertia); // Calculate inertia if dynamic
        }

        // 4. Rigid Body Construction Info:
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
            mass, 
            groundMotionState.get(), // Get raw pointer from unique_ptr
            groundShape.get(),      // Get raw pointer from unique_ptr
            inertia
        );

        // Use a raw pointer here; btDiscreteDynamicsWorld manages the rigid body's lifetime
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI); 

        std::cout << "Attempting to create rigid body \n";

        // 6. Add to the Simulation World:
        client->addRigidBody(groundRigidBody); // Pass raw pointer to Bullet
        
        std::cout << "Succesfully ran the rigid body function \n";

         }

    
    private:

        // Initialise pointers
        btDiscreteDynamicsWorld* client = nullptr;

        // int transformData(int input) {
        //     // Complex transformation logic here
        //     // Example
        // }

    };

int main() {
    
    // ---- May need to set up a simulation here first ----

    // 1. Create the necessary components:
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btDbvtBroadphase* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // 2. Create btDiscreteDynamicsWorld using the components:  CORRECT WAY
    std::unique_ptr<btDiscreteDynamicsWorld> bulletSim(new btDiscreteDynamicsWorld(
        dispatcher, overlappingPairCache, solver, collisionConfiguration
    ));
    
    // Create adapters
    auto bullet3Adapter = std::make_unique<Bullet3Adapter>(bulletSim.get());

    double x = 50.;
    double y = 50.;
    double z = 50.;

    // Run simulations
    bullet3Adapter->createBoxRigidBody(x, y, z);

    // std::cout << "Tank Sim Data Returned: " << data1 << std::endl;
    // std::cout << "Solider Sim Data Return: " << data2 << std::endl;

    // 3. Important: Clean up (reverse order of creation)
    delete bulletSim.release(); // Release ownership before deleting underlying pointers
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;

    return 0;
}



