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
 * @file tmpl.cpp
 * @class tmpl
 * @brief Implementation file for the tmpl class.
 * @ingroup Core
 * 
 * This file contains the implementation of the tmpl class, 
 * which represents a predefined structure of the tree.
 * 
 * @version 0.0.1
 * @author Amr MOUSA
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1: 
 *      - Initial Implementation of the tmpl class
 */

/**
 * @brief Include necessary headers
 */
#include "includes/tmpl.hpp"

namespace treecode {
    /**
     * @brief Constructor for the tmpl class.
     * @param name The name of the template.
     * Initializes the template with the given name.
     */
    tmpl::tmpl(
        const std::string& name
    ) : __name(name) {}


    /**
     * @brief Method to add a group to the template.
     * @param group The group to add.
     * Adds the specified group to the template.
     */
    void tmpl::add(
        const std::shared_ptr<group>& grp
    ) {
        /* add the group to the list of groups */
        if (grp) this->__groups.emplace_back(grp);
        else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
    }


    void tmpl::add(
        const group& grp
    ) {
        std::shared_ptr<group> group_ptr = std::make_shared<group>(grp);
        /* add the group to the list of groups */
        if (group_ptr) this->__groups.emplace_back(group_ptr);
        else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
    }


    /**
     * @brief Method to get the name of the template.
     * @return The name of the template.
     */
    std::string tmpl::name() const { return this->__name; }


    /**
     * @brief Method to get the groups in the template.
     * @return The groups in the template.
     */
    const std::vector<std::shared_ptr<group>>& tmpl::groups() const { return this->__groups; }


    /**
     * @brief Method to create an instance of the template.
     * @return The created instance of the template.
     */
    group tmpl::clone() const {
        auto instance = std::make_shared<group>(group(this->__name));
        /* add the groups to the instance */
        for (const auto& grp : this->__groups) {
            /* clone the group instance and add it to the instance */
            if (grp) {
                
                grp->add(__clone_group(instance));
            } else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
        }
        return *instance;
    }


    /**
     * @brief Method to create an instance of a specific group within the template.
     * @param groupName The name of the group to create an instance of.
     * @return The created instance of the group.
     */
    group tmpl::clone(
        const std::string& name
    ) const {
        /* find the group in the template */
        auto it = std::find_if(this->__groups.begin(), this->__groups.end(), [&name](
            const std::shared_ptr<group>& grp
        ) {
            /* return the group if found */
            return grp->name() == name;
        });


        /* create an instance of the group if found */
        if (it != this->__groups.end())  {
            return __clone_group(*it);
        }
        /* throw an exception if the group was not found */
        else {
            return group();
            Exception::Throw::Invalid(name, Exception::TEMPLATE_GROUP_NOT_FOUND);
        }
        
    }


    /**
     * @brief Helper method to create an instance of a group.
     * @param groupIns The group instance to clone.
     * @return The cloned group instance.
     */
    group tmpl::__clone_group(
        const std::shared_ptr<group>& grp
    ) const {
        /* create a new group instance */
        auto group_instance = std::make_shared<group>(grp->name());
        for (const auto& item : grp->items().keys()) {
            /* get the item from the group instance */
            auto itemPtr = grp->items().get(item);
            /* add the item to the group instance */
            if (itemPtr) group_instance->items().add(item, itemPtr->clone());
            else Exception::Throw::Invalid(item, "Exception::NULL_ELEMENT");
        }
        /* add the child groups to the group instance */
        auto children = group_instance->children();
        /* return the group instance if no children */
        if (children.empty()) return *group_instance;
        /* add the children to the group instance */
        for (const auto& child : children) group_instance->add(__clone_group(child));
        return *group_instance;
    }
} // namespace treecode