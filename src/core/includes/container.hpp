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
 * structures. It includes classes for containers, items, groups, templates,
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
 * which is used to store items in a key-value format.
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
#include "item.hpp"

namespace treecode {
    /**
     * @class container
     * @brief Represents a container for storing items in a key-value format.
     */
    class container {
    public:
        /**
         * @brief Default constructor for the container class.
         */
        container() = default;


        /**
         * @brief Destructor for the container class.
         */
        ~container() = default;


        /**
         * @brief Adds an item to the container.
         * @param key The key for the item.
         * @return A shared pointer to the added item.
         */
        template <typename T>
        std::shared_ptr<item<T>> add(
            const std::string& key
        );


        /**
         * @brief Adds an item to the container with a value.
         * @param key The key for the item.
         * @param value The value for the item.
         * @return A shared pointer to the added item.
         */
        template <typename T>
        std::shared_ptr<item<T>> add(
            const std::string& key,
            const T& value
        );


        /**
         * @brief Adds an item to the container with multi choice values.
         * @param key The key for the item.
         * @param choices The multi choice values for the item.
         * @return A shared pointer to the added item.
         */
        template <typename T>
        std::shared_ptr<item<T>> add(
            const std::string& key,
            const std::vector<T>& choices
        );


        /**
         * @brief Adds an item to the container.
         * @param key The key for the item.
         * @param ptr A shared pointer to the item.
         * @return A shared pointer to the added item.
         */
        std::shared_ptr<base> add(
            const std::string& key,
            const std::shared_ptr<base>& ptr
        );


        /**
         * This method is overloaded to allow for getting items by key
         * for both constant and non-constant containers.
         */
        /**
         * @brief Gets an base item from the container.
         * @param key The key for the item.
         * @return A shared pointer to the base.
         */
        /* non-constant version of the method */
        std::shared_ptr<base>& get(
            const std::string& key
        );

        /* constant version of the method */
        const std::shared_ptr<base>& get(
            const std::string& key
        ) const;


        /**
         * This method is overloaded to allow for getting items by key
         * for both constant and non-constant containers.
         */
        /**
         * @brief Gets an item from the container.
         * @param key The key for the item.
         * @return A shared pointer to the item.
         */
        /* non-constant version of the method */
        template <typename T>
        std::shared_ptr<item<T>> get(
            const std::string& key
        );

        /* constant version of the method */
        template <typename T>
        std::shared_ptr<item<T>> get(
            const std::string& key
        ) const;


        /**
         * @brief Gets the keys of the container.
         * @return A vector of keys.
         */
        std::vector<std::string> keys() const;


        /**
         * @brief Checks if an item exists in the container.
         * @param key The key of the item.
         * @return True if the item exists, false otherwise.
         */
        bool exists(const std::string& key) const;


        /**
         * @brief Removes an item from the container.
         * @param key The key of the item to remove.
         */
        bool remove(const std::string& key);

    private:
        /**
         * @var std::unordered_map<std::string, std::shared_ptr<base>> container::__items
         * The items of the container.
         */
        std::unordered_map<std::string, std::shared_ptr<base>> __items;

        /**
         * @var std::vector<std::string> container::__keys
         * The keys of the container.
         */
        std::vector<std::string> __keys;
    };


    /**
     * @brief Adds an item to the container.
     * @param key The key for the item.
     * @return A shared pointer to the added item.
     */
    template <typename T>
    std::shared_ptr<item<T>> container::add(
        const std::string& key 
    ) {
        auto itemPtr = std::make_shared<item<T>>();
        /* try to add the item to the container */
        auto result = this->__items.try_emplace(key, itemPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);
        return itemPtr;
    }


    /**
     * @brief Adds an item to the container with a value.
     * @param key The key for the item.
     * @param value The value for the item.
     * @return A shared pointer to the added item.
     */
    template <typename T>
    std::shared_ptr<item<T>> container::add(
        const std::string& key,
        const T& value
    ) {
        auto itemPtr = std::make_shared<item<T>>(value);
        /* try to add the item to the container */
        auto result = this->__items.try_emplace(key, itemPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);

        return itemPtr;
    }


    /**
     * @brief Adds an item to the container with multi choice values.
     * @param key The key for the item.
     * @param choices The multi choice values for the item.
     * @return A shared pointer to the added item.
     */
    template <typename T>
    std::shared_ptr<item<T>> container::add(
        const std::string& key,
        const std::vector<T>& choices
    ) {
        auto itemPtr = std::make_shared<item<T>>(choices);
        /* try to add the item to the container */
        auto result = this->__items.try_emplace(key, itemPtr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);

        return itemPtr;
    }


    /**
     * @brief Adds an item to the container.
     * @param key The key for the item.
     * @param ptr A shared pointer to the item.
     * @return A shared pointer to the added item.
     */
    /* non-constant version of the method */
    template <typename T>
    std::shared_ptr<item<T>> container::get(
        const std::string& key
    ) { 
        auto basePtr = get(key);
        return std::dynamic_pointer_cast<item<T>>(basePtr);
    }

    /* constant version of the method */
    template <typename T>
    std::shared_ptr<item<T>> container::get(
        const std::string& key
    ) const { 
        auto basePtr = get(key);
        return std::dynamic_pointer_cast<item<T>>(basePtr);
    }
} // namespace treecode

#endif // CONTAINER_H