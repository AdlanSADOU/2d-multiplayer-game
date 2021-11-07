/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SystemManager.h
*/

#pragma once

#include "System.hpp"
#include "Types.hpp"

#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager
{
    private:
        std::unordered_map<const char*, EntitySignature> _Signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> _Systems{};

    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            const char* typeName = typeid(T).name();

            assert(_Systems.find(typeName) == _Systems.end() && "Registering system more than once.");

            auto system = std::make_shared<T>();
            _Systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void SetSignature(EntitySignature signature)
        {
            const char* typeName = typeid(T).name();

            assert(_Systems.find(typeName) != _Systems.end() && "System used before registered.");

            _Signatures.insert({typeName, signature});
        }

        void EntityDestroyed(Entity entity)
        {
            for (auto const& pair : _Systems)
            {
                auto const& system = pair.second;


                system->_Entities.erase(entity);
            }
        }

        /**
        * Adds & updates entities from systems that have matching signatures
        **/
        void EntitySignatureChanged(Entity entity, EntitySignature entitySignature)
        {
            for (auto const& pair : _Systems)
            {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = _Signatures[type];

                if ((entitySignature & systemSignature) == systemSignature)
                {
                    system->_Entities.insert(entity);
                }
                else
                {
                    system->_Entities.erase(entity);
                }
            }
        }
};
