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
 * @file template.cpp
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
#include "includes/template.hpp"

namespace tc {
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
        const std::shared_ptr<group>& groupPtr
    ) {
        /* add the group to the list of groups */
        if (groupPtr) this->__groups.emplace_back(groupPtr);
        else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
    }


    /**
     * @brief Method to get the name of the template.
     * @return The name of the template.
     */
    std::string tmpl::getName() const { return this->__name; }


    /**
     * @brief Method to get the groups in the template.
     * @return The groups in the template.
     */
    const std::vector<std::shared_ptr<group>>& tmpl::getGroups() const { return this->__groups; }


    /**
     * @brief Method to create an instance of the template.
     * @return The created instance of the template.
     */
    std::shared_ptr<group> tmpl::clone() const {
        /* create an instance of the template */
        auto instance = std::make_shared<group>(this->__name);
        /* add the groups to the instance */
        for (const auto& group : this->__groups) {
            /* clone the group instance and add it to the instance */
            if (group) instance->add(__cloneGroupInstance(group));
            else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
        }
        return instance;
    }


    /**
     * @brief Method to create an instance of a specific group within the template.
     * @param groupName The name of the group to create an instance of.
     * @return The created instance of the group.
     */
    std::shared_ptr<group> tmpl::clone(
        const std::string& name
    ) const {
        /* find the group in the template */
        auto it = std::find_if(this->__groups.begin(), this->__groups.end(), [&name](
            const std::shared_ptr<group>& grp
        ) {
            /* return the group if found */
            return grp->getName() == name;
        });

        /* create an instance of the group if found */
        if (it != this->__groups.end())  {
            return __cloneGroupInstance(*it);
        }
        /* throw an exception if the group was not found */
        else {
            return nullptr;
            Exception::Throw::Invalid(name, Exception::TEMPLATE_GROUP_NOT_FOUND);
        }
        
    }


    /**
     * @brief Helper method to create an instance of a group.
     * @param groupIns The group instance to clone.
     * @return The cloned group instance.
     */
    std::shared_ptr<group> tmpl::__cloneGroupInstance(
        const std::shared_ptr<group>& instance
    ) const {
        /* create a new group instance */
        auto groupInstancePtr = std::make_shared<group>(instance->getName());
        for (const auto& element : instance->inside().getKeys()) {
            /* get the element from the group instance */
            auto elementPtr = instance->inside().get(element);
            /* add the element to the group instance */
            if (elementPtr) groupInstancePtr->inside().add(element, elementPtr->clone());
            else Exception::Throw::Invalid(element, "Exception::NULL_ELEMENT");
        }
        /* add the child groups to the group instance */
        auto children = groupInstancePtr->getChildren();
        /* return the group instance if no children */
        if (children.empty()) return groupInstancePtr;
        /* add the children to the group instance */
        for (const auto& child : children) groupInstancePtr->add(__cloneGroupInstance(child));
        return instance;
    }
} // namespace treecode