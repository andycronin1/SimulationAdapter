
#include <iostream> 
#include <string>
#include <vector>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include "adapter.h"


int main() {
    
    // -----/Set up the simulation/------ //

    // 1. Create the necessary components:
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration(new btDefaultCollisionConfiguration());
    std::unique_ptr<btCollisionDispatcher> dispatcher(new btCollisionDispatcher(collisionConfiguration.get()));
    std::unique_ptr<btDbvtBroadphase> overlappingPairCache(new btDbvtBroadphase());
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver(new btSequentialImpulseConstraintSolver);

    // Create the dynamics world using a shared_ptr
    auto bulletSim = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());

    // 2. Set the gravity for the simulation
    bulletSim->setGravity(btVector3(0, -10, 0));

    //keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // ------/Simulation created/-----  //
    
    // Create adapters
    auto bullet3Adapter = std::make_unique<Bullet3Adapter>();

    double x = 50.;
    double y = 50.;
    double z = 50.;

    // Start sim
    bullet3Adapter->testSim(bulletSim);

    // Create Box 
    bullet3Adapter->createBoxRigidBody(bulletSim, x, y, z);

    // Create Second identical Box 
    bullet3Adapter->createBoxRigidBody(bulletSim, x, y, z);

    bullet3Adapter->showObjectPositions(bulletSim);

    return 0;
}



