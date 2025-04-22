#include <iostream> 
#include <string>
#include <vector>

class AppInterface 
{
    public: 
    

        virtual void testSim(const std::shared_ptr<btDiscreteDynamicsWorld>& world) = 0; 
        virtual void createBoxRigidBody(const std::shared_ptr<btDiscreteDynamicsWorld>& sim, double& x, double& y, double& z) = 0; //pure virtual function
    
}; 

// Class AppObject which implements the App Interface
class AppObject : public AppInterface
{
    public: 
    // Methods to do something in the app. Virtual so that they can be overridden by the adapter 

        // Methods to do something in the app. Virtual so that they can be overridden by the adapter 
        virtual void testSim(const std::shared_ptr<btDiscreteDynamicsWorld>& world) override {}    

        // Method to create box rigid body
        virtual void createBoxRigidBody(const std::shared_ptr<btDiscreteDynamicsWorld>& sim, double& x, double& y, double& z) override {}

}; 

