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
 * 
 * This project is a C++ library for managing hierarchical data
 * structures. It includes classes for containers, elements, groups, templates,
 * and logging. The library can be built as a shared library and includes options
 * for building tests and examples.
 * 
 * +--------------------------------------------------------------------------+
 * 
 * @file element.cpp
 * @class Element
 * @brief Implementation file for the element class.
 * @ingroup Core
 * 
 * This file contains the definition of the element class, which is used to represent
 * an element with a label, description, type, and optional constraints.
 * 
 * @version Version 0.0.1
 * @author Amr MOUSA - https://github.com/amr-m-abdelgawad
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1: 
 *      - Initial Implementation of the element class
 */

/**
 * @brief Include necessary headers
*/
#include "includes/element.hpp"

namespace tc {
    /**
     * @brief Default constructor for the element class.
     * Initializes the element with default values.
     */
    element::element() :
        __isChoices(false),
        __isRequired(false) {}


    /**
     * @brief Constructor for the element class with a default value.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param defaultValue The default value of the element.
     * Initializes the element with the given label, description, type, and default value.
     */
    element::element(
        const type& defaultValue
    ) : element() { this->__value = defaultValue; }


    /**
     * @brief Constructor for the element class with allowed values.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param allowedValues The allowed values for the element.
     * Initializes the element with the given label, description, type, and allowed values.
     * Throws an exception if the type is not MULTIVALUES or if the allowed values list is empty.
     */
    element::element(
        const multi& choices
    ) : __choices(choices),
        __isChoices(true) {
        if (!choices.empty()) {
            /* Set the default value to the first allowed value */
            this->__value = choices[FIRST_ELEMENT];
            /* Set the required flag */
            this->__isRequired = true;
        } else Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_ALLOWED_VALUES_EMPTY); /* Throw an exception if the allowed values list is empty */
    }


    /**
     * @brief Sets the value of the element.
     * @param newValue The new value to set.
     * Throws an exception if the value is not in the allowed values list for multivalues type or if the element type is unknown.
     */
    void element::set(
        const type& newValue
    ) {
        if (this->__isChoices) {
            /* check if value is in the allowed values list */
            if (std::find(this->__choices.begin(), this->__choices.end(), newValue) != this->__choices.end()) {
                /* set the value and the value set flag */
                this->__value = newValue;
            }
            /* throw an exception if the value is not in the allowed values list */
            else Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_VALUE_NOT_ALLOWED);
        }
        /* set the value for other types */
        else {
            /* set the value */
            this->__value = newValue;
        }
    }


    /**
     * @brief Gets the value of the element.
     * @return The value of the element.
     */
    std::optional<base::type> element::data() const { 
        return this->__value.has_value() ? this->__value : std::nullopt;
    }


    /**
     * @brief Gets the allowed values of the element.
     * @return The allowed values of the element.
     * Throws an exception if the element type is not MULTIVALUES.
     */
    multi element::choices() const {
        /* throw an exception if the element type is not multivalues */
        if(!this->__isChoices) {
            Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_MULTIVALUES_ALLOWED_MISSING);
            return {}; // Return an empty vector to satisfy the return type
        }
        /* return the allowed values */
        else return this->__choices;
    }


    /**
     * @brief Checks if the element is required.
     * @return True if the element is required, false otherwise.
     */
    bool element::isReq() const { return this->__isRequired; }


    /**
     * @brief Sets the element as required.
     * @return void
     */
    void element::setReq() {
        this->__isRequired = true;
    }
} // namespace treecode