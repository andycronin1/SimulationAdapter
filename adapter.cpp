// Bullet3 Adapter
#include <iostream>
#include "adapter.h"

// Construct the adpater and pass a pointer to the sim world 
Bullet3Adapter::Bullet3Adapter(std::shared_ptr<btDiscreteDynamicsWorld>& simulation) : sim(simulation) {
    std::cout << "Adapter Created\n";
}

// METHOD FOR STARTING SIMULATION IF WE WANT TO START THE SIM FROM INSIDE THE ADAPTER
// void Bullet3Adapter::startSim(){
//     // 1. Create the necessary components:
//     btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//     btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//     btDbvtBroadphase* overlappingPairCache = new btDbvtBroadphase();
//     btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

//     // 2. Create btDiscreteDynamicsWorld using the components. Reset the pointer as it is initally a null pointer
//     simworld.reset(new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration));

//     std::cout << "Bullet sim world created";

// }


void Bullet3Adapter::testSim() {
    if (sim) {
        std::cout << "Simulation world exists.\n";
        // ... any other actions we want to perform if the sim exists ...
    } else {
        std::cerr << "Error: Simulation world does not exist.\n";
        // ... any other actions we want to perform if the sim does *not* exist ...
    }
}


// Function to create box rigid body (overrides the appInterface method)
void Bullet3Adapter::createBoxRigidBody(double& x, double& y, double& z) {

    auto groundShape = std::make_shared<btBoxShape>(btVector3(x, y, z));
    auto groundMotionState = std::make_shared<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -56, 0)));

    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    if (mass != 0.f) {
        groundShape->calculateLocalInertia(mass, inertia);
    }

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
        mass,
        groundMotionState.get(),
        groundShape.get(),
        inertia
    );

    auto groundRigidBody = std::make_unique<btRigidBody>(groundRigidBodyCI);

    std::cout << "Attempting to create rigid body\n";
    // Add the body to the sim
    sim->addRigidBody(groundRigidBody.get());
    std::cout << "Successfully added rigid body to the world\n";

    // Store pointer to created box in the rigidBodies vector
    // std::move is required to transger ownership of the box memory location from the groundRigidBody pointer to the rigidBodies vector (uniqure pointer previously)
    rigidBodies_.push_back(std::move(groundRigidBody));
}   

void Bullet3Adapter::showObjectPositions() {

    int i;

    std::cout << "Address of sim: " << sim << std::endl;

		//print positions of all objects
		for (int j = sim->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = sim->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	

}

// Function to apply force to the rigid body
void Bullet3Adapter::applyForce(int x, int y, int z, int object_num) {
    // Move the first object by applying a central force
    btRigidBody* body = sim->getCollisionObjectArray()[0]->getInternalType() == btCollisionObject::CO_RIGID_BODY
        ? btRigidBody::upcast(sim->getCollisionObjectArray()[0])
        : nullptr;

    if (body) {
        body->applyCentralForce(btVector3(x, y, z)); // Apply a force to move the object
        std::cout << "Applied force to the first object.\n";
    }
}

    