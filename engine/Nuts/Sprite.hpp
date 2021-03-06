/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Sprite
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "EcsComponents/TransformComponent.hpp"
#include "EcsComponents/SpriteComponent.hpp"

#include "GameObject.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Vect.hpp"
#include "Clock.hpp"

#include <iostream>

extern Scene scene;

namespace nuts {
    class Sprite {
    private:
        sf::Sprite   _sprite;
        nuts::Clock *_animation_clock = nullptr;

        bool          _is_animated     = false;
        bool          _is_looping      = false;
        int           _frame_count     = 0;
        int           _frame_in_flight = 0;
        float         _frame_time      = 0;
        nuts::IntRect _first_frame     = { 0, 0, 0, 0 };
        nuts::IntRect _current_frame   = { 0, 0, 0, 0 };

    public:
        /**
         * @brief Construct a new Sprite object,
         * It is not animated by default, if you want to set it to animated
         * use the SetAnimated method
         *
         */
        Sprite() { }

        ~Sprite() { }

        /**
         * @brief Set the position of the sprite
         *
         * @param pos
         */
        void SetPosition(const nuts::Vector2f &pos)
        {
            _sprite.setPosition({ pos.x, pos.y });
        }

        /**
         * @brief Set the position of the sprite
         *
         * @param pos
         */

        void Move(float offsetX, float offsetY)
        {
            _sprite.move(offsetX, offsetY);
        }

        /**
         * @brief Get the position of the sprite
         *
         * @param pos
         */
        nuts::Vector2f GetPosition() const
        {
            return { _sprite.getPosition().x, _sprite.getPosition().y };
        }

        /**
         * @brief Set the origin of the sprite
         *
         * @param origin
         */
        void SetOrigin(const nuts::Vector2f &origin)
        {
            _sprite.setOrigin({ origin.x, origin.y });
        }

        /**
         * @brief Set the scaling factor of the sprite
         *
         * @param factors
         */
        void SetScale(const nuts::Vector2f &factors)
        {
            _sprite.setScale({ factors.x, factors.y });
        }

        /**
         * @brief Set the Texture to the sprite
         *
         * @param texture New texture
         */
        void SetTexture(nuts::Texture &texture)
        {
            _sprite.setTexture(texture.GetTexture());
        }

        /**
         * @brief Set the Texture Rect to the rectangle given as parameter
         *
         * @param rect Rectangle
         */
        void SetTextureRect(nuts::IntRect rect)
        {
            _sprite.setTextureRect({ rect.left, rect.top, rect.width, rect.height });
        }

        /**
         * @brief Set the current frame to rect
         *
         * @param rect
         */
        void SetCurrentFrame(const nuts::IntRect &rect)
        {
            _current_frame = { rect.left, rect.top, rect.width, rect.height };
        }

        /**
         * @brief Set the Sprite to an animated sprite if parameter is true
         *
         * @param animate true or false
         */
        void SetAnimated(bool animate)
        {
            _is_animated = animate;
        }

        /**
         * @brief Returns true if the sprite is an animated sprite,
         * returns false if it's a fixed sprite
         *
         * @return true if animated is set to true
         */
        bool IsAnimated() const
        {
            return (_is_animated);
        }

        /**
         * @brief Set the animated sprite so that it loops over all the frames.
         * By default, an animated sprite doesn't loop.
         *
         * @param loop true or false
         */
        void SetLooped(bool loop)
        {
            _is_looping = loop;
        }

        /**
         * @brief Returns true of the sprite is looping, the sprite must
         * be animated in order for the loop to be used
         *
         * @return true if loop is set to true
         */
        bool IsLooped() const
        {
            return (_is_looping);
        }

        /**
         * @brief Get the sf::Sprite variable from the nuts::Sprite object
         *
         * @return sf::Sprite
         */
        sf::Sprite &GetSprite()
        {
            return (_sprite);
        }

        /**
         * @brief Set the frame count in the animation
         *
         * @param count number of frame in the animation
         */
        void SetFrameCount(int count)
        {
            _frame_count = count;
        }

        /**
         * @brief Set the current frame to the next one.
         * If the animation should loop and it reaches the
         * end of the animation it loops back to the first frame.
         *
         */

          void NextFrame()
        {
            bool is_last_frame = (_frame_in_flight >= _frame_count);

            if (!_is_looping && is_last_frame)
                return;

            if (_is_looping && is_last_frame) {
                _frame_in_flight    = 0;
                _current_frame.left = _first_frame.left;
            }

            _current_frame.left = _first_frame.left + _first_frame.width * _frame_in_flight;

            ++_frame_in_flight;
        }

        nuts::IntRect GetCurrentFrame() const
        {
            return (_current_frame);
        }

        /**
         * @brief Set the time that the animation should wait before
         * switching to the next frame. Only works if the sprite is
         * animated.
         *
         * @param time time to wait before switching to the next frame
         */
        void SetFrameTime(float time)
        {
            _frame_time = time;
        }

        /**
         * @brief Get the time to wait before switching to the next
         * frame
         *
         * @return float
         */
        float GetFrameTime() const
        {
            return (_frame_time);
        }

        /**
         * @brief Returns true if the animation should switch
         * to the next frame
         *
         * @param time
         * @return true
         * @return false
         */
        bool ShouldGetNextFrame(float time)
        {
            return (time >= _frame_time);
        }

        /**
         * @brief Set the first frame rectangle of an animation
         * if the animation is set to loop
         *
         * @param rect
         */
        void SetFirstFrame(const nuts::IntRect &rect)
        {
            SetCurrentFrame(rect);
            _first_frame = rect;
        }

        /**
         * @brief Get the first frame rectangle of the animation
         *
         * @return nuts::IntRect
         */
        nuts::IntRect GetFirstFrame() const
        {
            return (_first_frame);
        }

        void InitAnimationClock()
        {
            _animation_clock = new nuts::Clock();
        }

        nuts::Clock *GetAnimationClock()
        {
            return (_animation_clock);
        }

        float ResetAnimationClock()
        {
            return (_animation_clock->Restart());
        }

        nuts::FloatRect GetGlobalBounds()
        {
            sf::FloatRect   rect = _sprite.getGlobalBounds();
            nuts::FloatRect res;
            res.left   = rect.left;
            res.top    = rect.top;
            res.width  = rect.width;
            res.height = rect.height;
            return (res);
        }

        bool IsLastFrame()
        {
            if (_frame_in_flight >= _frame_count)
                return true;
            return false;
        }
    };
}