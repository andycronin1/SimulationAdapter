
#include <iostream> 
#include <string>
#include <vector>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include "adapter.h"


int main() {
    
    // -----/Set up the simulation/------ //

    // 1. Create the necessary components:
    auto collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
    auto dispatcher = std::make_shared<btCollisionDispatcher>(collisionConfiguration.get());
    auto overlappingPairCache = std::make_shared<btDbvtBroadphase>();
    auto solver = std::make_shared<btSequentialImpulseConstraintSolver>();

    // Create the dynamics world using shared_ptrs to ensure proper lifetime management
    auto bulletSim = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());

    // 2. Set the gravity for the simulation
    bulletSim->setGravity(btVector3(0, -10, 0));

    // //keep track of the shapes, we release memory at exit.
	// //make sure to re-use collision shapes among rigid bodies whenever possible!
    // btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // ------/Simulation created/-----  //
    
    // Create adapters
    auto bullet3Adapter = std::make_shared<Bullet3Adapter>(bulletSim);

    double x = 50.;
    double y = 50.;
    double z = 50.;

    // Start sim
    bullet3Adapter->testSim();

    // Create Box 
    bullet3Adapter->createBoxRigidBody(x, y, z);

    // Create Second identical Box 
    bullet3Adapter->createBoxRigidBody(x, y, z);

    // Show positions
    bullet3Adapter->showObjectPositions();

    // Set a force vector 
    int force_x = 10;
    int force_y = 0; 
    int force_z = 0;

    // Select which object to apply force to
    int object_num = 0;

    // apply force to specific object
    // WE NEED TO STEP THROUGH THE SIMULATION FOR THIS FORCE TO HAVE ANY EFFECT 
    bullet3Adapter->applyForce(force_x, force_y, force_z, object_num);

    // // step through simulation 
    // bulletSim->stepSimulation(0.1);

    bullet3Adapter->showObjectPositions();

    return 0;
}



