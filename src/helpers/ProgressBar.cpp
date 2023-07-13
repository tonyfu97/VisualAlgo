#include <iostream>
#include "helpers/ProgressBar.hpp"

namespace VisualAlgo
{
    ProgressBar::ProgressBar(unsigned int steps, std::string info)
        : steps(steps), currentStep(0), info(info)
    {
    }

    ProgressBar::~ProgressBar()
    {
        if (DEBUG)
        {
            std::cout << std::endl;
        }
    }

    void ProgressBar::step(const std::string &step_info)
    {
        if (DEBUG)
        {
            currentStep++;
            printProgress(step_info);
        }
    }

    void ProgressBar::printProgress(const std::string &step_info)
    {
        float ratio = currentStep / (float)steps;
        int percent = static_cast<int>(ratio * 100.0f);
        int c = ratio * 50;

        std::cout << '\r';

        std::cout << info << " Progress: [";
        for (int x = 0; x < c; x++)
            std::cout << "=";
        for (int x = c; x < 50; x++)
            std::cout << " ";

        std::cout << "] " << percent << "%";

        // Display optional step info
        if (!step_info.empty())
        {
            std::cout << " - " << step_info;
        }

        // Append spaces to overwrite any remaining characters from previous line
        std::cout << "                                                                            ";

        std::cout << std::flush;
    }
}
