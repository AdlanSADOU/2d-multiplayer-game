/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** widget.hpp
*/

#pragma once

#include "EcsComponents/SpriteComponent.hpp"
#include "EcsComponents/TransformComponent.hpp"
#include "EcsComponents/WidgetComponent.hpp"

#include "GameObject.hpp"

//TestInclude TODO: delete
#include <SFML/Graphics.hpp>

namespace nuts::UI {

    class Widget
    {
    private:
        nuts::GameObject        _gameObject;
        std::string             _name;
        std::shared_ptr<Widget> _parent;
        std::shared_ptr<Widget> _child;

    public:
        Widget() {};

        Widget(std::string name)
        {
            Create(name);
        }

        void Create(std::string name)
        {

            _name = name;
            _gameObject.Create(name);
            _gameObject.AddComponent<WidgetComponent>();
        }

        void SetParent(Widget &parent)
        {
            _parent = std::make_shared<Widget>(parent);
            parent.SetChild(*this);
        }

        void SetChild(Widget &child)
        {
            _child = std::make_shared<Widget>(child);
        }

        std::shared_ptr<Widget> GetParent() const
        {
            return _parent;
        }

        void SetImageFromFile(std::string filename)
        {
            Texture *texture = new Texture();
            texture->LoadFromFile(filename);

            auto &sprite = _gameObject.GetComponent<WidgetComponent>().sprite;
            sprite.SetTexture(*texture);
        }

        void SetPosition(Vector2f position)
        {
            auto &sprite = _gameObject.GetComponent<WidgetComponent>().sprite;

            sprite.SetPosition(position);

            if (_parent) {
                auto &parentSprite = _parent->GetSPrite();

                Vector2f relativePosition {
                    position.x + sprite.GetPosition().x + parentSprite.GetPosition().x,
                    position.y + sprite.GetPosition().y + parentSprite.GetPosition().y
                };

                sprite.SetPosition(relativePosition);
            }

            if (_child) {
                auto &childSprite = _child->GetSPrite();

                Vector2f relativePosition {
                    position.x + sprite.GetPosition().x + childSprite.GetPosition().x,
                    position.y + sprite.GetPosition().y + childSprite.GetPosition().y
                };

                childSprite.SetPosition(relativePosition);
            }
        }

        void SetScale(Vector2f factors)
        {
            auto &sprite = _gameObject.GetComponent<WidgetComponent>().sprite;

            sprite.SetScale(factors);
            
            if (_child)
                _child->SetScale(factors);
        }

        Sprite &GetSPrite()
        {
            return _gameObject.GetComponent<WidgetComponent>().sprite;
        }

        void TEST_DRAW(sf::RenderWindow &window)
        {
            window.draw(_gameObject.GetComponent<WidgetComponent>().sprite.GetSprite());
        }
    };
}