
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
    
    return 0;
}



