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
 * @file container.cpp
 * @class Container
 * @brief Implementation file for the container class.
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

/**
 * @brief Include necessary headers
*/
#include "includes/container.hpp"

namespace tc {
    std::shared_ptr<base> container::add(
        const std::string& key,
        const std::shared_ptr<base>& ptr
    ) {
        /* try to add the element to the container */
        auto result = this->__elements.try_emplace(key, ptr);
        /* throw an exception if the key already exists */
        if (!result.second) Exception::Throw::Invalid(key, Exception::CONTAINER_KEY_ALREADY_EXISTS);
        /* add the key to the list of keys */
        this->__keys.emplace_back(key);
        return ptr;
    }


    /**
     * This method is overloaded to allow for getting elements by key
     * for both constant and non-constant containers.
     */
    /**
     * @brief Gets the element with the specified key from the container.
     * @param key The key of the element to retrieve.
     * @return Pointer to the element with the specified key.
     * @throws std::out_of_range if the key is not found in the container.
     */
    #define GET_ELEMENT_IMPL() \
        /* find the element with the specified key */ \
        auto it = this->__elements.find(key); \
        /* return the element if found */ \
        if (it != this->__elements.end()) return it->second; \
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
     * @brief Gets the keys of the elements in the container.
     * @return A vector of keys in the container.
     */
    std::vector<std::string> container::getKeys() const {
        /* return an empty vector if the container is empty */
        if(this->__keys.empty()) return {};
        /* return the keys */
        return this->__keys;
    }
} // namespace treecode