#include "waterfall.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <span>
#include <chrono>
#include <thread>
#include <iterator>


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
 * runProject follows a predefined structure to make showcasing easy and
 * because it will likely only be ran once and forgotten about.
 */
void Waterfall::runWaterfall() {
    Motion_Object wave = {
        .motion_char = '~',
        .position = {0, 0},
        .velocity = {0, 1},       
        .movement_rule = "vertical shift down"
    };
    std::vector<Motion_Object> obj_list{wave};
    Waterfall::setBackgroundChar('#');
    Waterfall::setBackgroundHeight(16);
    Waterfall::setBackgroundWidth(9);
    
    Waterfall::createBackground();
    Waterfall::drawMotionObjects(obj_list);
    Waterfall::displayBackground();
}