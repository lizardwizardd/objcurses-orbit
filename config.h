/*
 * config.h
 */

#pragma once

// cli draw
inline constexpr char CHARS_LUM[] = " .'`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
inline constexpr float CHAR_ASPECT_RATIO = 2.0F;

// view
inline constexpr float ANGLE_STEP = 5.0F;
inline constexpr float ZOOM_START = 1.0F;
inline constexpr float ZOOM_STEP = 0.1F;
inline constexpr float ZOOM_MIN = 0.10F;
inline constexpr float ZOOM_MAX = 8.00F;

// animation
inline constexpr float FRAME_DURATION = 1.0F / 60.0F;  // 60 fps
inline constexpr float ANIMATION_STEP = 30.0F;
