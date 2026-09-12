#include "waterfall.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <span>
#include <chrono>
#include <thread>
#include <iterator>
#include <stdexcept>


/*  Implementation details:
    - creates vector of size (background_height * background_width) that is
        stored in Waterfall.background
*/

// ============================================================================
//                              Updated Version
// ============================================================================
// Constructors

void Waterfall::setBackgroundChar(char input) {
    m_background_char = input;
}

void Waterfall::setBackgroundHeight(std::size_t input) {
    m_background_height = input;
}

void Waterfall::setBackgroundWidth(std::size_t input) {
    m_background_width = input;
}

void Waterfall::createBackground() {
    // don't use .pushback unless you want a bajillion elements!!
    m_background.assign(
        m_background_height * m_background_width,
        m_background_char
    );
}

void Waterfall::drawMotionObjects(const std::vector<Motion_Object>& objects_list) {
    for (const Motion_Object& obj : objects_list) {
        m_background[obj.position.y * m_background_width + obj.position.x] = obj.motion_char;
    }
}

void Waterfall::displayBackground() {
    
    for (std::size_t i = 0; i < m_background_height; ++i) {

        // Get slice of the vector with length == m_background_width
        std::span<const char> vectorSlice{
            m_background.data() + (i * m_background_width),
            m_background_width
        };

        // Print each char of slice
        for (char c : vectorSlice) {
            std::cout << c;
        }
        std::cout << '\n';
    }
}

/**
 * Updates each Motion_Object's position by its velocity
 * 
 * Hopefully mutating each object does not break this
 */
void Waterfall::updateMotionObjects(std::vector<Motion_Object>& objects_list) {
    for (Motion_Object& obj : objects_list) {
        obj.position.x += (obj.position.x + obj.velocity.x) % m_background_width;
        obj.position.y = (obj.position.y + obj.velocity.y) % m_background_height;
    }
}

// Monster function incoming; definitely broke a few best practices here
void Waterfall::generateMotionObjectCopies(
    int obj_count, 
    const Vec2<int>& offset,
    char motion_char,
    const Vec2<int>& position,
    const Vec2<int>& velocity
) {
    // TODO : add negative bounds checking
    if (position.x + (obj_count * offset.x) >= (int)m_background_width) {
        throw std::invalid_argument("Position offset cannot exceed background width.");
    }
    if (position.y + (obj_count * offset.y) >= (int)m_background_height) {
        throw std::invalid_argument("Position offset cannot exceed background height.");
    }
    for (int i = 0; i < obj_count; ++i) {
        m_object_list.push_back({
            motion_char,                                                        // motion_char
            {position.x + (i * offset.x), position.y + (i * offset.y)},         // position
            {velocity.x, velocity.y}                                            // velocity
        });
    }
}

/** 
 * runProject follows a predefined structure to make showcasing easy and
 * because it will likely only be ran once and forgotten about.
 */
void Waterfall::runWaterfall() {
    int loop_count = 20;
    Motion_Object wave = {
        .motion_char = '~',
        .position = {0, 0},
        .velocity = {0, 1}
    };
    m_object_list.push_back(wave);
    Waterfall::setBackgroundChar(' ');
    Waterfall::setBackgroundHeight(16);
    Waterfall::setBackgroundWidth(9);
    
    // Primary loop
    for (int i = 0; i < loop_count; ++i) {
        // Reset background
        Waterfall::createBackground();

        Waterfall::drawMotionObjects(m_object_list);
        
        Waterfall::displayBackground();
        
        Waterfall::updateMotionObjects(m_object_list);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // Reset cursor (avoids continuously printing new lines)
        if (i < 19) {
            std::cout << "\033[" << m_background_height << "A";
        }
    }
}