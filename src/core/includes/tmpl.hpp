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
#ifndef TMPL_H
#define TMPL_H

/**
 * @brief Include necessary headers
 */
#include "group.hpp"

namespace treecode {
    /**
     * @class tmpl
     * @brief A class representing a template that contains groups.
     * 
     * The tmpl class provides methods to manage and clone groups within a template.
     * It allows adding groups, retrieving the name and groups, and cloning the template or specific groups.
     */
    class tmpl {
    public:
        /**
         * @brief Default constructor for the groupTemplate class.
         */
        tmpl() = default;


        /**
         * @brief Destructor for the groupTemplate class.
         */
        ~tmpl() = default;


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
         * @param grp shared pointer to the group to add.
         * Adds the specified group to the template.
         */
        void add(
            const std::shared_ptr<group>& grp
        );


        /**
         * @brief Method to add a group to the template.
         * @param group The group to add.
         * Adds the specified group to the template.
         */
        void add(
            const group& grp
        );


        /**
         * @brief Method to get the name of the template.
         * @return The name of the template.
         */
        std::string name() const;


        /**
         * @brief Method to get the groups in the template.
         * @return The groups in the template.
         */
        const std::vector<std::shared_ptr<group>>& groups() const;


        /**
         * @brief Method to create an instance of the template.
         * @return The created instance of the template.
         */
        group clone() const;


        /**
         * @brief Method to create an instance of a specific group within the template.
         * @param name The name of the group to create an instance of.
         * @return The created instance of the group.
         */
        group clone(
            const std::string& name
        ) const;

    private:
        /**
         * @var std::string tmpl::__name
         * The name of the template.
         */
        std::string __name;

        /**
         * @var std::vector<std::shared_ptr<group>> tmpl::__groups
         * The groups in the template.
         */
        std::vector<std::shared_ptr<group>> __groups;

        /**
         * @brief Clone the group.
         * @param instance The instance to clone.
         * @return A shared pointer to the cloned group.
         */
        group __clone_group(
            const std::shared_ptr<group>& grp
        ) const;
    };
} // namespace treecode

#endif // TMPL_H