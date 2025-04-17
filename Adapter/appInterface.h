#include <iostream> 
#include <string>
#include <vector>

class AppInterface 
{
    public: 
        virtual void createBoxRigidBody(double& x, double& y, double& z) = 0; //pure virtual function
    
}; 

// Class AppObject which implements the App Interface
class AppObject : public AppInterface
{
    public: 
    // Methods to do something in the app. Virtual so that they can be overridden by the adapter 
        virtual void createBoxRigidBody(double& x, double& y, double& z) override {}

}; 

// // AppCodebaseMethod Function that takes a pointer to an object that implements the AppInterface as input.
// // We are essentially calling a function within the app code base and passing it an object that adheres to 
// // the app interface 
// void AppCodebaseMethod(AppInterface* obj) {}