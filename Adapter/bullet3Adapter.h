#include <iostream> 
#include "appInterface.h"

// Generic Adapter
class Bullet3Adapter : public AppInterface { 
    public:
        // CONSTRUCTOR

        // Adapter takes a pointer to an instance of the dummyAPI
        Bullet3Adapter(DummyApiClient* c) : client{c} {}

        // Override the app method with the clients make request method 
        virtual void appMethod(int& data) override {
            client->createObject(data); }

        // When we call the local app method, we are actually calling the simulation
        // virtual void appMethod(int& data) override { obj->simMethod(data); }

    
    private:

        // Initialise pointers
        DummyApiClient* client = nullptr;

        int transformData(int input) {
            // Complex transformation logic here
            // Example
        }

    };