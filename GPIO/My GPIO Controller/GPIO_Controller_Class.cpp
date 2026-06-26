/**
 * @file gpio_controller.cpp
 * @brief GPIO class using libgpiod for Raspberry Pi
 * @author Jared Hagemann
 * @date 2026-07-22 (updated)
 */

#include "GPIO_Controller_Class.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <gpiod.h>

#define CONSUMER "GPIO_Controller_Class"

GPIO::GPIO(int gpio) : gpioNumber(gpio){}

GPIO:: ~GPIO(){
    closeLine();
}

void GPIO::openAndRequest(bool asOutput){
    if (line) return;  // Already open

    chip = gpiod_chip_open_by_name("gpiochip0");  // Or detect dynamically
    if (!chip) {
        throw std::runtime_error("Failed to open gpiochip0");
    }

    line = gpiod_chip_get_line(chip, gpioNumber);
    if (!line) {
        gpiod_chip_close(chip);
        chip = nullptr;
        throw std::runtime_error("Failed to get line " + std::to_string(gpioNumber));
    }

    int ret;
    if (asOutput) {
        ret = gpiod_line_request_output(line, CONSUMER, 0);  // Default low
        isOutput = true;
    } else {
        ret = gpiod_line_request_input(line, CONSUMER);
        isOutput = false;
    }

    if (ret < 0) {
        closeLine();
        throw std::runtime_error("Failed to request line as " + std::string(asOutput ? "output" : "input"));
    }
}

void GPIO::closeLine(){
    if (line) {
        gpiod_line_release(line);
        line = nullptr;
    }
    if (chip) {
        gpiod_chip_close(chip);
        chip = nullptr;
    }
}

void GPIO::setHigh(){
    openAndRequest(true);
    gpiod_line_set_value(line, 1);
}

void GPIO::setLow(){
    openAndRequest(true);
    gpiod_line_set_value(line, 0);
}

int GPIO::getValue(){
    openAndRequest(false);
    return gpiod_line_get_value(line);
}

void GPIO::flash(int cycles, int delay_us){
    openAndRequest(true);
    for (int i = 0; i < cycles; ++i) {
        gpiod_line_set_value(line, 1);
        usleep(delay_us);
        gpiod_line_set_value(line, 0);
        usleep(delay_us);
    }
}

void GPIO::displayState(){
    if (!line) {
        std::cout << "Line not requested yet.\n";
        return;
    }
    std::cout << "Offset: " << gpiod_line_offset(line)
              << ", Name: " << (gpiod_line_name(line) ? gpiod_line_name(line) : "N/A")
              << ", Consumer: " << (gpiod_line_consumer(line) ? gpiod_line_consumer(line) : "N/A")
              << ", Direction: " << gpiod_line_direction(line)
              << ", Active State: " << gpiod_line_active_state(line)
              << ", Bias: " << gpiod_line_bias(line) << std::endl;
}

