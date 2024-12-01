#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file_path>" << std::endl;
        return 1;
    }

    // קריאת קובץ הקונפיג
    std::string configFilePath = argv[1];
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open configuration file: " << configFilePath << std::endl;
        return 1;
    }

    try {
        // יצירת הסימולציה על פי הקונפיג
        Simulation simulation(configFilePath);

        // התחלת הסימולציה
        simulation.start();

        // לולאה המדמה ריצת תוכנית
        std::cout << "Simulation started successfully. Enter commands below:" << std::endl;
        std::string command;
        while (std::getline(std::cin, command)) {
            if (command == "exit") {
                break;
            } else if (command == "step") {
                simulation.step();
            } else if (command == "print log") {
                    vector<BaseAction*> actions = simulation.getActionsLog();
                    for (BaseAction* action : actions) {
                        if (action) {
                            std::cout << action->toString() << std::endl;
                        }
                    }
                }

             else {
                std::cerr << "Unknown command: " << command << std::endl;
                std::cout << "Available commands: step, print log, exit" << std::endl;
            }
        }
        

        // סגירת הסימולציה
        simulation.close();
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
