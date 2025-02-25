/**
 * +--------------------------------------------------------------------------+
 *  _____ ____  _____ _____ ____ ___  ____  _____ 
 * |_   _|  _ \| ____| ____/ ___/ _ \|  _ \| ____|
 *   | | | |_) |  _| |  _|| |  | | | | | | |  _|  
 *   | | |  _ <| |___| |__| |__| |_| | |_| | |___ 
 *   |_| |_| \_|_____|_____\____\___/|____/|_____|
 * 
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * SPDX-License-Identifier: MIT
 * TREECODE - Copyright (c) - Amr MOUSA 2025-2026
 * 
 * Version 0.0.1
 * 
 * This project is a C++ library for managing hierarchical data
 * structures. It includes classes for containers, elements, groups, templates,
 * and logging. The library can be built as a shared library and includes options
 * for building tests and examples.
 * 
 * +--------------------------------------------------------------------------+
 * 
 * @file container.hpp
 * @class Container
 * @brief Header file for the container class.
 * @ingroup Core
 * 
 * This file contains the implementation of the container class, 
 * which is used to store elements in a key-value format.
 * 
 * @version Version 0.0.1
 * @author Amr MOUSA - https://github.com/amr-m-abdelgawad
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1: 
 *     - Initial Implementation of the container class
 */
#ifndef CONTAINER_H
#define CONTAINER_H

/**
 * @brief Include necessary headers
 */
#include "element.hpp"

namespace tc {
    /**
     * @class container
     * @brief Represents a container for storing elements in a key-value format.
     * 
     * The container class provides functionality to store and manage elements in a key-value format.
     * It supports adding elements to the container, retrieving elements by key, and getting a list of keys.
     * The class also supports serialization to and from JSON.
     */
    class container {
    public:
        /**
         * @brief Adds an element to the container with the specified key.
         * @param key The key associated with the element to be added.
         * @param element The pointer of the element to be added to the container.
         * @throws std::invalid_argument if the key already exists in the container.
         */
        template <typename T>
        std::shared_ptr<element<T>> add(
            const std::string& key
        );

        template <typename T>
        std::shared_ptr<element<T>> add(
            const std::string& key,
            const T& value
        );
    
        template <typename T>
        std::shared_ptr<element<T>> add(
            const std::string& key,
            const std::vector<T>& choices
        );

        // template <typename T>
        std::shared_ptr<base> add(
            const std::string& key,
            const std::shared_ptr<base>& ptr
        );

        /**
         * This method is overloaded to allow for getting elements by key
         * for both constant and non-constant containers.
         */
        /**
         * @brief Gets the element with the specified key from the container.
         * @param key The key of the element to retrieve.
         * @return pointer to the element with the specified key.
         * @throws std::out_of_range if the key is not found in the container.
         */
        /* non-constant version of the method */
        std::shared_ptr<base>& get(
            const std::string& key
        );

        /* constant version of the method */
        const std::shared_ptr<base>& get(
            const std::string& key
        ) const;

        template <typename T>
        std::shared_ptr<element<T>> get(
            const std::string& key
        );

        template <typename T>
        std::shared_ptr<element<T>> get(
            const std::string& key
        ) const;

        /**
         * @brief Gets the keys of the elements in the container.
         * @return A vector of keys in the container.
         */
        std::vector<std::string> getKeys() const;


    private:
        /**
         * @var std::unordered_map<std::string, element> container::__elements
         * The elements stored in the container.
         */
        std::unordered_map<std::string, std::shared_ptr<base>> __elements;


        /**
         * @var std::vector<std::string> container::__keys
         * The keys of the elements in the container.
         */
        std::vector<std::string> __keys;
    };


    /**
     * @brief Adds an element to the container with the specified key.
     * @param key The key associated with the element to be added.
     * @param element The pointer of the element to be added to the container.
     * @throws std::invalid_argument if the key already exists in the container.
     */
    template <typename T>
    std::shared_ptr<element<T>> container::add(
        const std::string& key 
    ) {
        auto elementPtr = std::make_shared<element<T>>();
        /* try to add the element to the container */
        auto result = this->__elements.try_emplace(key, elementPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);
        return elementPtr;
    }


    template <typename T>
    std::shared_ptr<element<T>> container::add(
        const std::string& key,
        const T& value
    ) {
        auto elementPtr = std::make_shared<element<T>>(value);
        /* try to add the element to the container */
        auto result = this->__elements.try_emplace(key, elementPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);

        return elementPtr;
    }


    template <typename T>
    std::shared_ptr<element<T>> container::add(
        const std::string& key,
        const std::vector<T>& choices
    ) {
        auto elementPtr = std::make_shared<element<T>>(choices);
        /* try to add the element to the container */
        auto result = this->__elements.try_emplace(key, elementPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);

        return elementPtr;
    }


    /* non-constant version of the method */
    template <typename T>
    std::shared_ptr<element<T>> container::get(
        const std::string& key
    ) { 
        auto basePtr = get(key);
        return std::dynamic_pointer_cast<element<T>>(basePtr);
    }

    /* constant version of the method */
    template <typename T>
    std::shared_ptr<element<T>> container::get(
            const std::string& key
    ) const { 
        auto basePtr = get(key);
        return std::dynamic_pointer_cast<element<T>>(basePtr);
    }
} // namespace treecode

#endif // CONTAINER_H