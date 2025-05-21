#include <iostream> 
#include <string>
#include <vector>

class AppInterface 
{
    public: 

        virtual ~AppInterface() = default; // Virtual destructor
        virtual void testSim() = 0; 
        virtual void createBoxRigidBody(double x, double y, double z) = 0; //pure virtual function
        virtual void showObjectPositions() = 0; 
        virtual void applyForce(int x, int y, int z, int object_num) = 0; 
        
    
}; 

// Class AppObject which implements the App Interface
class AppObject : public AppInterface
{
    public: 
    // Methods to do something in the app. Virtual so that they can be overridden by the adapter 

        // Methods to do something in the app. Virtual so that they can be overridden by the adapter 
        virtual void testSim() override {}    

        // Method to create box rigid body
        virtual void createBoxRigidBody(double x, double y, double z) override {}

        virtual void showObjectPositions() override {}

        virtual void applyForce(int x, int y, int z, int object_num) override {}

}; 

