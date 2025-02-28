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
 * @file container.cpp
 * @class Container
 * @brief Implementation file for the container class.
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

/**
 * @brief Include necessary headers
*/
#include "includes/container.hpp"

namespace treecode {
    std::shared_ptr<base> container::add(
        const std::string& key,
        const std::shared_ptr<base>& ptr
    ) {
        /* try to add the item to the container */
        auto result = this->__items.try_emplace(key, ptr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);
        return ptr;
    }


    /**
     * This method is overloaded to allow for getting items by key
     * for both constant and non-constant containers.
     */
    /**
     * @brief Gets the item with the specified key from the container.
     * @param key The key of the item to retrieve.
     * @return Pointer to the item with the specified key.
     * @throws std::out_of_range if the key is not found in the container.
     */
    #define GET_ELEMENT_IMPL() \
        /* find the item with the specified key */ \
        auto it = this->__items.find(key); \
        /* return the item if found */ \
        if (it != this->__items.end()) return it->second; \
        /* throw an exception if the key is not found */ \
        Exception::Throw::Range(key, Exception::CONTAINER_KEY_NOT_FOUND); \
        throw std::runtime_error("Unreachable code"); /* unreachable code */


    /* non-constant version of the method */
    std::shared_ptr<base>& container::get(
        const std::string& key
    ) { 
        GET_ELEMENT_IMPL() 
    }

    /* constant version of the method */
    const std::shared_ptr<base>& container::get(
        const std::string& key
    ) const { 
        GET_ELEMENT_IMPL()
    }


    /**
     * @brief Gets the keys of the items in the container.
     * @return A vector of keys in the container.
     */
    std::vector<std::string> container::keys() const {
        /* return an empty vector if the container is empty */
        if(this->__keys.empty()) return {};
        /* return the keys */
        return this->__keys;
    }


    /**
     * @brief Checks if an item with the specified key exists in the container.
     * @param key The key to check for existence.
     * @return True if the key exists in the container, false otherwise.
     */
    bool container::exists(const std::string& key) const {
        return this->__items.count(key) > 0;
    }


    /**
     * @brief Removes an item from the container.
     *        Does not throw an exception if the key is not found.
     * @param key The key of the item to remove.
     * @return True if the item was removed, false otherwise.
     */
    bool container::remove(const std::string& key) {
        /* find the item with the specified key */
        auto it = this->__items.find(key);
        /* remove the item if found */
        if (it != this->__items.end()) {
            this->__items.erase(it);
            /* remove the key from the list of keys */
            this->__keys.erase(
                std::remove(this->__keys.begin(), this->__keys.end(), key), this->__keys.end()
            );
            return true;
        } else return false;
    }
} // namespace treecode