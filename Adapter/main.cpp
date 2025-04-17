
#include <iostream> 
#include <string>
#include <vector>
#include <memory>
#include <iostream> 
#include "appInterface.h"
#include "Bullet3Base.h"
#include "btBulletDynamicsCommon.h"
#include <stdio.h>

// Bullet3 Adapter
class Bullet3Adapter : public AppInterface { 
    public:
        // CONSTRUCTOR

        // Adapter takes a pointer to an instance of the simultion object
        Bullet3Adapter(btDiscreteDynamicsWorld* c) : client{c} {}

        // Override the app method with the clients make rigid body method 
        virtual void createBoxRigidBody() override {

        // 1. Shape: Define the collision shape of the rigid body
        std::unique_ptr<btCollisionShape> groundShape = std::make_unique<btBoxShape>(btVector3(50., 50., 50.)); 

        // 2. Motion State:
        std::unique_ptr<btDefaultMotionState> groundMotionState = std::make_unique<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -56, 0))); 

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

        // 5. Create the Rigid Body:
        std::unique_ptr<btRigidBody> groundRigidBody = std::make_unique<btRigidBody>(groundRigidBodyCI);

        // 6. Add to the Simulation World:
        client->addRigidBody(groundRigidBody.get()); // Pass raw pointer to Bullet

        // When we call the local app method, we are actually calling the simulation
        // virtual void appMethod(int& data) override { obj->simMethod(data); }

         }

    
    private:

        // Initialise pointers
        btDiscreteDynamicsWorld* client = nullptr;

        int transformData(int input) {
            // Complex transformation logic here
            // Example
        }

    };

int main() {
    
    // ---- May need to set up a simulation here first ----

    // Create simulations and their pointers 
    std::unique_ptr<btDiscreteDynamicsWorld> bulletSim = std::make_unique<btDiscreteDynamicsWorld>();

    // Create adapters
    auto bullet3Adapter = std::make_unique<Bullet3Adapter>(bulletSim.get());

    // Run simulations
    bullet3Adapter->createBoxRigidBody();

    // std::cout << "Tank Sim Data Returned: " << data1 << std::endl;
    // std::cout << "Solider Sim Data Return: " << data2 << std::endl;

    return 0;
}



