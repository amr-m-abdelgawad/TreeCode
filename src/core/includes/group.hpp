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
 * @file group.hpp
 * @class Group
 * @brief Header file for the group class.
 * @ingroup Core
 * 
 * This file contains the definition of the group class, which represents a node in the tree structure.
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
#ifndef GROUP_H
#define GROUP_H

/**
 * @brief Include necessary headers
*/
#include "container.hpp"

namespace tc {
    /**
     * @class group
     * @brief Represents a node in the tree structure.
     * 
     * The group class represents a node in the tree structure. It contains a container for storing elements
     * and a list of child groups. The class provides methods for adding and removing child groups, getting the
     * container, and serializing to and from JSON.
     */
    class group {
    public:
        /**
         * @brief Constructor for the group class.
         * @param name The name of the group.
         * Initializes the group with the given name.
         */
        group(const std::string& name);

        /**
         * @brief Adds a child group to the current group.
         * @param child The child group to add.
         */
        void add(const std::shared_ptr<group>& child);

        /**
         * @brief Removes a child group from the current group.
         * @param child The child group to remove.
         */
        void remove(const std::shared_ptr<group>& child);

        /**
         * @brief Gets the container of the group.
         * @return The container of the group.
         */
        container& inside();

        const container& inside() const;

        /**
         * @brief Gets the name of the group.
         * @return The name of the group.
         */
        std::string getName() const;

        /**
         * @brief Gets the child groups of the current group.
         * @return The child groups of the current group.
         */
        const std::vector<std::shared_ptr<group>>& getChildren() const;


    private:
        /**
         * @var std::string group::__name
         * The name of the group.
         */
        std::string __name;

        /**
         * @var container group::__container
         * The container of the group.
         */
        container __container;

        /**
         * @var std::vector<std::shared_ptr<group>> group::__children
         * The child groups of the current group.
         */
        std::vector<std::shared_ptr<group>> __children;
    };
} // namespace treecode

#endif // GROUP_H