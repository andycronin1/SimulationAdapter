
#include <iostream> 
#include <string>
#include <vector>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include "adapter.h"
#include <nlohmann/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>

#include "common/common_utils/StrictMode.hpp"
STRICT_MODE_OFF
#ifndef RPCLIB_MSGPACK
#define RPCLIB_MSGPACK clmdep_msgpack
#endif // !RPCLIB_MSGPACK
#include "rpc/rpc_error.h"
STRICT_MODE_ON

#include "vehicles/car/api/CarRpcLibClient.hpp"
#include "common/common_utils/FileSystem.hpp"

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

// ------------ Handler for HTTP requests ----------------- //

template<class Body, class Allocator, class Send>
void handle_request(Bullet3Adapter& adapter, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send)
{
    if (req.method() != http::verb::post || req.target() != "/control") {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::content_type, "text/plain");
        res.body() = "Not found";
        res.prepare_payload();
        return send(std::move(res));
    }

    // Parse JSON body
    nlohmann::json j = nlohmann::json::parse(req.body(), nullptr, false);
    std::string command = j.value("command", "");

    std::string result = "Unknown command";
    if (command == "drive_forward") {
        // Example: call your adapter logic here
        adapter.applyForce(10, 0, 0, 0); // Example: apply force to object 0
        result = "Driving forward!";
    } else if (command == "create_box") {
        adapter.createBoxRigidBody(50., 50., 50.);
        result = "Box created!";
    }

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.body() = nlohmann::json({{"result", result}}).dump();
    res.prepare_payload();
    send(std::move(res));
}

int main() {

    // ---- Set up Bullet simulation and adapter ----
    // 1. Create the necessary components:
    auto collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
    auto dispatcher = std::make_shared<btCollisionDispatcher>(collisionConfiguration.get());
    auto overlappingPairCache = std::make_shared<btDbvtBroadphase>();
    auto solver = std::make_shared<btSequentialImpulseConstraintSolver>();
    // Create the dynamics world using shared_ptrs to ensure proper lifetime management
    auto bulletSim = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());
    // Set the gravity for the simulation
    bulletSim->setGravity(btVector3(0, -10, 0));
    // Create the Bullet3Adapter, passing the simulation world pointer to its constructor  
    auto bullet3Adapter = Bullet3Adapter(bulletSim);

    // ---- Start HTTP server ----
    try {
        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};

        std::cout << "Listening on http://localhost:8080/control" << std::endl;

        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            boost::beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            // Lambda to send response
            auto send = [&](auto&& response) {
                http::write(socket, response);
            };

            handle_request(bullet3Adapter, std::move(req), send);
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
    return 0;
}


// ---------------------- Main function ---------------------- //
// int main() {
    
//     // -----/Set up the simulation/------ //

//     // 1. Create the necessary components:
//     auto collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
//     auto dispatcher = std::make_shared<btCollisionDispatcher>(collisionConfiguration.get());
//     auto overlappingPairCache = std::make_shared<btDbvtBroadphase>();
//     auto solver = std::make_shared<btSequentialImpulseConstraintSolver>();

//     // Create the dynamics world using shared_ptrs to ensure proper lifetime management
//     auto bulletSim = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());

//     // 2. Set the gravity for the simulation
//     bulletSim->setGravity(btVector3(0, -10, 0));

//     // //keep track of the shapes, we release memory at exit.
// 	// //make sure to re-use collision shapes among rigid bodies whenever possible!
//     // btAlignedObjectArray<btCollisionShape*> collisionShapes;

//     // ------/Simulation created/-----  //
    
//     // Create adapters
//     auto bullet3Adapter = std::make_shared<Bullet3Adapter>(bulletSim);

//     double x = 50.;
//     double y = 50.;
//     double z = 50.;

//     // Start sim
//     bullet3Adapter->testSim();

//     // Create Box 
//     bullet3Adapter->createBoxRigidBody(x, y, z);

//     // Create Second identical Box 
//     bullet3Adapter->createBoxRigidBody(x, y, z);

//     // Show positions
//     bullet3Adapter->showObjectPositions();

//     // Set a force vector 
//     int force_x = 10;
//     int force_y = 0; 
//     int force_z = 0;

//     // Select which object to apply force to
//     int object_num = 0;

//     // apply force to specific object
//     // WE NEED TO STEP THROUGH THE SIMULATION FOR THIS FORCE TO HAVE ANY EFFECT 
//     bullet3Adapter->applyForce(force_x, force_y, force_z, object_num);

//     // // step through simulation 
//     // bulletSim->stepSimulation(0.1);

//     bullet3Adapter->showObjectPositions();

//     // ready to run example: https://github.com/Microsoft/AirSim/blob/main/HelloCar/main.cpp

//     // AirSim example code
//     using namespace msr::airlib;

//     std::cout << "Make sure settings.json has \"SimMode\"=\"Car\" at root. Press Enter to continue." << std::endl;
//     std::cin.get();

//     // This assumes you are running DroneServer already on the same machine.
//     // DroneServer must be running first.
//     msr::airlib::CarRpcLibClient client;
//     typedef ImageCaptureBase::ImageRequest ImageRequest;
//     typedef ImageCaptureBase::ImageResponse ImageResponse;
//     typedef ImageCaptureBase::ImageType ImageType;
//     typedef common_utils::FileSystem FileSystem;

//     try {
//         client.confirmConnection();

//         std::cout << "Press Enter to get FPV image" << std::endl;
//         std::cin.get();
//         const std::vector<ImageRequest> request{ ImageRequest("0", ImageType::Scene), ImageRequest("1", ImageType::DepthPlanar, true) };
//         const std::vector<ImageResponse>& response = client.simGetImages(request);
//         std::cout << "# of images received: " << response.size() << std::endl;

//         if (!response.size()) {
//             std::cout << "Enter path with ending separator to save images (leave empty for no save)" << std::endl;
//             std::string path;
//             std::getline(std::cin, path);

//             for (const ImageResponse& image_info : response) {
//                 std::cout << "Image uint8 size: " << image_info.image_data_uint8.size() << std::endl;
//                 std::cout << "Image float size: " << image_info.image_data_float.size() << std::endl;

//                 if (path != "") {
//                     std::string file_path = FileSystem::combine(path, std::to_string(image_info.time_stamp));
//                     if (image_info.pixels_as_float) {
//                         Utils::writePFMfile(image_info.image_data_float.data(), image_info.width, image_info.height, file_path + ".pfm");
//                     }
//                     else {
//                         std::ofstream file(file_path + ".png", std::ios::binary);
//                         file.write(reinterpret_cast<const char*>(image_info.image_data_uint8.data()), image_info.image_data_uint8.size());
//                         file.close();
//                     }
//                 }
//             }
//         }

//         //enable API control
//         client.enableApiControl(true);
//         CarApiBase::CarControls controls;

//         std::cout << "Press enter to drive forward" << std::endl;
//         std::cin.get();
//         controls.throttle = 0.5f;
//         controls.steering = 0.0f;
//         client.setCarControls(controls);

//         std::cout << "Press Enter to activate handbrake" << std::endl;
//         std::cin.get();
//         controls.handbrake = true;
//         client.setCarControls(controls);

//         std::cout << "Press Enter to take turn and drive backward" << std::endl;
//         std::cin.get();
//         controls.handbrake = false;
//         controls.throttle = -0.5;
//         controls.steering = 1;
//         controls.is_manual_gear = true;
//         controls.manual_gear = -1;
//         client.setCarControls(controls);

//         std::cout << "Press Enter to stop" << std::endl;
//         std::cin.get();
//         client.setCarControls(CarApiBase::CarControls());
//     }
//     catch (rpc::rpc_error& e) {
//         const auto msg = e.get_error().as<std::string>();
//         std::cout << "Exception raised by the API, something went wrong." << std::endl
//                   << msg << std::endl;
//         std::cin.get();
//     }

//     return 0;
// }



