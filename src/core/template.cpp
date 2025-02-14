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
 * @class groupTemplate
 * @brief Implementation file for the groupTemplate class.
 * @ingroup Core
 * 
 * This file contains the implementation of the groupTemplate class, 
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

/**
 * @brief Include necessary headers
 */
#include "Includes/template.hpp"

namespace TreeCode {
    /**
     * @brief Constructor for the groupTemplate class.
     * @param name The name of the template.
     * Initializes the template with the given name.
     */
    groupTemplate::groupTemplate(
        const std::string& name
    ) : __name(name) {}


    /**
     * @brief Method to add a group to the template.
     * @param group The group to add.
     * Adds the specified group to the template.
     */
    void groupTemplate::addGroup(
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
    std::string groupTemplate::getName() const { return this->__name; }


    /**
     * @brief Method to get the groups in the template.
     * @return The groups in the template.
     */
    const std::vector<std::shared_ptr<group>>& groupTemplate::getGroups() const { return this->__groups; }


    /**
     * @brief Method to create an instance of the template.
     * @return The created instance of the template.
     */
    std::shared_ptr<group> groupTemplate::createInstance() const {
        /* create an instance of the template */
        auto instance = std::make_shared<group>(this->__name);
        /* add the groups to the instance */
        for (const auto& group : this->__groups) {
            /* clone the group instance and add it to the instance */
            if (group) instance->addChild(__cloneGroupInstance(group));
            else Exception::Throw::Invalid(this->__name, Exception::NULL_GROUP);
        }
        return instance;
    }


    /**
     * @brief Method to create an instance of a specific group within the template.
     * @param groupName The name of the group to create an instance of.
     * @return The created instance of the group.
     */
    std::shared_ptr<group> groupTemplate::createGroupInstance(
        const std::string& groupName
    ) const {
        /* find the group in the template */
        auto it = std::find_if(this->__groups.begin(), this->__groups.end(), [&groupName](
            const std::shared_ptr<group>& grp
        ) {
            /* return the group if found */
            return grp->getName() == groupName;
        });
        /* create an instance of the group if found */
        if (it != this->__groups.end()) return __cloneGroupInstance(*it);
        /* throw an exception if the group was not found */
        else {
            return nullptr;
            Exception::Throw::Invalid(groupName, Exception::TEMPLATE_GROUP_NOT_FOUND);
        }
        
    }


    /**
     * @brief Helper method to create an instance of a group.
     * @param groupIns The group instance to clone.
     * @return The cloned group instance.
     */
    std::shared_ptr<group> groupTemplate::__cloneGroupInstance(
        std::shared_ptr<group> groupIns
    ) const {
        /* create a new group instance */
        auto groupInstance = std::make_shared<group>(groupIns->getName());
        /* add the elements to the group instance */
        const auto& container = groupIns->getContainer();
        /* add the elements to the group instance */
        for (const auto& key : container.getKeys())
            groupInstance->getContainer().addElement(key, container.getElement(key));
        /* add the child groups to the group instance */
        auto children = groupIns->getChildren();
        /* return the group instance if no children */
        if (children.empty()) return groupInstance;
        /* add the children to the group instance */
        for (const auto& child : children) groupInstance->addChild(__cloneGroupInstance(child));
        return groupInstance;
    }
} // namespace TreeCode