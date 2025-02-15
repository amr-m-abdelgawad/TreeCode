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
 * @file group.cpp
 * @class Group
 * @brief Implementation file for the group class.
 * @ingroup Core
 * 
 * This file contains the implementation of the group class, 
 * which represents a node in the tree structure.
 * 
 * @version 0.0.1
 * @author Amr MOUSA
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1: 
 *      - Initial Implementation of the group class
 */

/**
 * @brief Include necessary headers
*/
#include "includes/group.hpp"

namespace treecode {
    /**
     * @brief Constructor for the group class.
     * @param name The name of the group.
     * Initializes the group with the given name.
     */
    group::group(
        const std::string& name
    ) : __name(name) {}

    /**
     * @brief Adds a child group to the current group.
     * @param child The child group to add.
     */
    void group::addChild(
        std::shared_ptr<group>&& child
    ) {
        /* add the child to the list of children */
        if (std::find(this->__children.begin(), this->__children.end(), child) == this->__children.end())
            this->__children.emplace_back(std::move(child));
    }

    /**
     * @brief Removes a child group from the current group.
     * @param child The child group to remove.
     */
    void group::removeChild(
        const std::shared_ptr<group>& child
    ) {
        /* remove the child from the list of children */
        this->__children.erase(
            std::remove_if(this->__children.begin(), this->__children.end(),
            [&child](const std::shared_ptr<group>& g) { return g == child; }), this->__children.end()
        );
    }

    /**
     * @brief Gets the container of the group.
     * @return The container of the group.
     */
    container& group::getContainer() { return this->__container; }

    /**
     * @brief Gets the name of the group.
     * @return The name of the group.
     */
    std::string group::getName() const { return this->__name; }

    /**
     * @brief Gets the child groups of the current group.
     * @return A vector of shared pointers to the child groups.
     */
    const std::vector<std::shared_ptr<group>>& group::getChildren() const { return this->__children; }
} // namespace treecode