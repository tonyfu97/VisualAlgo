#pragma once

#include <string>

#ifndef DEBUG
#define DEBUG 1
#endif

namespace VisualAlgo {
    class ProgressBar {
    public:
        ProgressBar(unsigned int steps, std::string info);

        void step(const std::string& step_info = "");

    private:
        unsigned int steps;
        unsigned int currentStep;
        std::string info;

        void printProgress(const std::string& step_info);
    };
}
