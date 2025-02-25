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
 * @file template.hpp
 * @class groupTemplate
 * @brief Declaration file for the groupTemplate class.
 * @ingroup Core
 * 
 * This file contains the declaration of the groupTemplate class, 
 * which represents a predefined structure of the tree.
 * 
 * @version 0.0.1
 * @author Amr MOUSA
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1:
 *      - Initial Implementation of the groupTemplate class
 */
#ifndef TEMPLATE_H
#define TEMPLATE_H

/**
 * @brief Include necessary headers
 */
#include "group.hpp"

namespace tc {
    /**
     * @brief The groupTemplate class represents a predefined structure of the tree.
     * 
     * This class is used to define a template for the structure of the tree,
     * which can be used to create instances of the tree. The template is defined
     * by a list of groups that define the structure of the tree.
     */
    class tmpl {
    public:
        /**
         * @brief Constructor for the groupTemplate class.
         * @param name The name of the template.
         * Initializes the template with the given name.
         */
        tmpl(
            const std::string& name
        );

        /**
         * @brief Method to add a group to the template.
         * @param group The group to add.
         * Adds the specified group to the template.
         */
        void add(
            const std::shared_ptr<group>& group
        );

        /**
         * @brief Method to get the name of the template.
         * @return The name of the template.
         */
        std::string getName() const;

        /**
         * @brief Method to get the groups in the template.
         * @return The groups in the template.
         */
        const std::vector<std::shared_ptr<group>>& getGroups() const;

        /**
         * @brief Method to create an instance of the template.
         * @return An instance of the template.
         */
        std::shared_ptr<group> clone() const;

        /**
         * @brief Method to create an instance of a group.
         * @param groupName The name of the group.
         * @return An instance of the group.
         */
        std::shared_ptr<group> clone(
            const std::string& groupName
        ) const;

    private:
        /**
         * @var std::string groupTemplate::__name
         * The name of the template.
         */
        std::string __name;


        /**
         * @var std::vector<std::shared_ptr<group>> groupTemplate::__groups
         * The groups in the template.
         */
        std::vector<std::shared_ptr<group>> __groups;


        /**
         * @brief Method to clone a group instance.
         * @param groupIns The group instance to clone.
         * @return The cloned group instance.
         */
        std::shared_ptr<group> __cloneGroupInstance(
            const std::shared_ptr<group>& instance
        ) const;
    };
} // namespace treecode

#endif // TEMPLATE_H