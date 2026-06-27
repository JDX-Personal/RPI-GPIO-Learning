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
#include <thread>
#include <functional>
#include <boost/python.hpp>

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

int GPIO::waitForEdge(int eventType, int timeout_ms){
    if(eventType < 1 || eventType > 3){
        throw std::runtime_error("Event must be 1 (Rising), 2 (Falling), 3 (Both)");
    }
    
    closeLine();
    
    chip = gpiod_chip_open_by_name("gpiochip0");
    if(!chip){
        throw std::runtime_error("Failed to open gpiochip0");
    }
    
    line = gpiod_chip_get_line(chip, gpioNumber);
    if(!line){
        closeLine();
        throw std::runtime_error("Failed to open gpio line");
    }
    
    int ret = -1;
    if(eventType == 1){
        std::cout << "Event Type 1\n";
        ret = gpiod_line_request_rising_edge_events(line, CONSUMER);
    }
    else if(eventType == 2){
        std::cout << "Event Type 2\n";
        ret = gpiod_line_request_falling_edge_events(line, CONSUMER);
    }
    else if(eventType == 3){
        std::cout << "Event Type 3\n";
        ret = gpiod_line_request_both_edges_events(line, CONSUMER);
    }
    
    if(ret < 0){
        throw std::runtime_error("Failed to request edge events");
    }
    
    struct timespec ts = {0,0};
    struct timespec* timeout_ptr = nullptr;
    
    if(timeout_ms >=0){
        ts.tv_sec = timeout_ms / 1000;
        ts.tv_nsec = (timeout_ms % 1000) * 1000000L;
        timeout_ptr = &ts;
    }
    
    ret = gpiod_line_event_wait(line, timeout_ptr);
    
    if(ret < 0){
        throw std::runtime_error("Error during edge wait");
    }
    if(ret == 0){
        return 0; //Timeout
    }
    
    struct gpiod_line_event event;
    gpiod_line_event_read(line, &event);
    
    return 1; //Event Detected
    
}


//Not using this method because Asynce does not play well with Python (Need to look into)
void GPIO::waitForEdgeAsync(int eventType, int timeout_ms, boost::python::object callback){
    std::thread([this, eventType, timeout_ms, callback](){
        try{
            int result = waitForEdge(eventType, timeout_ms);
            callback(result == 1);
        }
        catch(...){
            callback(false);
        }
    }).detach();
}

