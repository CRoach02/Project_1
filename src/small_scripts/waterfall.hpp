#pragma once

#include <vector>
#include <string>


// ============================================
//                  UTILS
// ============================================

/// @brief 
/// @tparam T 
template <typename T>
struct Vec2 {
    T x; 
    T y;
};

/* 
 * @brief Represents a single renderable ASCII entity with spatial movement data.
 *
 * @param motion_char The ASCII character to be rendered.
 * @param position The position vector in 2D that determines the object's location.
 * @param velocity The velocity vector in 2D that determines the object's movement.
 * @param movement_rule The name of the movement defined by the velocity vector.
 */
struct Motion_Object
{
    char motion_char;
    Vec2<int> position;
    Vec2<int> velocity;
    std::string movement_rule;
};

class Waterfall
{
private:
    char m_background_char;
    std::size_t m_background_width;
    std::size_t m_background_height;
    std::vector<char> m_background{};

public:
    void setBackgroundChar(char input);
    void setBackgroundHeight(std::size_t input);
    void setBackgroundWidth(std::size_t input);
    
    // rendering
    void createBackground();
    void drawMotionObjects(const std::vector<Motion_Object>& objects_list);
    void displayBackground();

    // simulation

    ///@brief Singular run call for Waterfall to be used in main.cpp
    void runWaterfall();

};