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

namespace treecode {
    /**
     * @brief Default constructor for the element class.
     * Initializes the element with default values.
     */
    element::element() :
        __label("NOT_SET"), 
        __description("NOT_SET"), 
        __type(type::UNKNOWN), 
        __isValueSet(false) {}


    /**
     * @brief Constructor for the element class.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * Initializes the element with the given label, description, and type.
     * Throws an exception if the type is MULTIVALUES.
     */
    element::element(
        const std::string& label, 
        const std::string& description, 
        const type::data_t& type
    ) :
        __label(label), 
        __description(description), 
        __type(type) {
        /* Throw an exception if the type is unknown */
        if(type >= type::UNKNOWN) Exception::Throw::Invalid(this->__label, Exception::ELEMENT_INVALID_TYPE);
        switch (type) {
            /* set the default value based on the type */
            case type::BOOLEAN:
                this->__value = "false";
                this->__isValueSet = true;
                break;
            case type::MULTIVALUES:
                /* throw an exception if the type is multivalues */
                Exception::Throw::Invalid(this->__label, Exception::ELEMENT_WRONG_TYPE_FOR_MULTIVALUES);
                break;
            default:
                /* set the default value to an empty string */
                this->__value = "";
                /* set the value set flag to false */
                this->__isValueSet = false;
                break;
        }
    }


    /**
     * @brief Constructor for the element class with a default value.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param defaultValue The default value of the element.
     * Initializes the element with the given label, description, type, and default value.
     */
    element::element(
        const std::string& label, 
        const std::string& description, 
        const type::data_t& type, 
        const std::string& defaultValue
    ) :
        element(label, description, type) {
        if(defaultValue.empty()) this->__isValueSet = false;
        else {
            /* set the value and the value set flag */
            this->__value = defaultValue;
            this->__isValueSet = true;
        }
    }


    /**
     * @brief Constructor for the element class with a required flag.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param required The required flag of the element.
     * Initializes the element with the given label, description, type, and required flag.
     */
    element::element(
        const std::string& label, 
        const std::string& description, 
        const type::data_t& type, 
        const bool& required
    ) :
        element(label, description, type) { this->__required = required; }


    /**
     * @brief Constructor for the element class with a default value and required flag.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param defaultValue The default value of the element.
     * @param required The required flag of the element.
     * Initializes the element with the given label, description, type, default value, and required flag.
     */
    element::element(
        const std::string& label, 
        const std::string& description, 
        const type::data_t& type, 
        const std::string& defaultValue, 
        const bool& required
    ) :
        element(label, description, type, defaultValue) { this->__required = required; }


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
        const std::string& label, 
        const std::string& description, 
        const type::data_t& type, 
        const std::vector<std::string>& allowedValues
    ) :
        __label(label), 
        __description(description), 
        __type(type), 
        __allowedValues(allowedValues) {
        /* Throw an exception if the type is unknown */
        if(type >= type::UNKNOWN) Exception::Throw::Invalid(this->__label, Exception::ELEMENT_TYPE_UNKNOWN);
        /* Throw an exception if the type is not multivalues */
        if(type != type::MULTIVALUES) Exception::Throw::Invalid(this->__label, Exception::ELEMENT_WRONG_TYPE_FOR_MULTIVALUES);
        if (!allowedValues.empty()) {
            /* Set the default value to the first allowed value */
            this->__value = allowedValues[0];
            /* Set the value set flag */
            this->__isValueSet = true;
        } else Exception::Throw::Invalid(this->__label, Exception::ELEMENT_ALLOWED_VALUES_EMPTY); /* Throw an exception if the allowed values list is empty */
    }


    /**
     * @brief Sets the value of the element.
     * @param newValue The new value to set.
     * Throws an exception if the value is not in the allowed values list for multivalues type or if the element type is unknown.
     */
    void element::setValue(
        const std::string& newValue
    ) {
        if (this->__type == type::MULTIVALUES) {
            /* check if value is in the allowed values list */
            if (std::find(this->__allowedValues.begin(), this->__allowedValues.end(), newValue) != this->__allowedValues.end()) {
                /* set the value and the value set flag */
                this->__value = newValue;
                /* set the value set flag */
                this->__isValueSet = true;
            }
            /* throw an exception if the value is not in the allowed values list */
            else Exception::Throw::Invalid(this->__label, Exception::ELEMENT_VALUE_NOT_ALLOWED);
        }
        /* throw an exception if the element type is unknown */
        else if (this->__type >= type::UNKNOWN) Exception::Throw::Invalid(this->__label, Exception::ELEMENT_TYPE_UNKNOWN);
        /* set the value for other types */
        else {
            /* check if value is empty*/
            if(newValue.empty()) this->__isValueSet = false;
            /* set the value and the value set flag */
            else this->__isValueSet = true;
            /* set the value */
            this->__value = newValue;
        }
    }


    /**
     * @brief Gets the value of the element.
     * @return The value of the element.
     */
    std::string element::getValue() const { return this->__value; }


    /**
     * @brief Gets the allowed values of the element.
     * @return The allowed values of the element.
     * Throws an exception if the element type is not MULTIVALUES.
     */
    std::vector<std::string> element::getAllowedValues() const {
        /* throw an exception if the element type is not multivalues */
        if(this->__type != type::MULTIVALUES) {
            Exception::Throw::Invalid(this->__label, Exception::ELEMENT_MULTIVALUES_ALLOWED_MISSING);
            return {}; // Return an empty vector to satisfy the return type
        }
        /* return the allowed values */
        else return this->__allowedValues;
    }


    /**
     * @brief Gets the label of the element.
     * @return The label of the element.
     */
    std::string element::getLabel() const { return this->__label; }


    /**
     * @brief Gets the description of the element.
     * @return The description of the element.
     */
    std::string element::getDescription() const { return this->__description; }


    /**
     * @brief Gets the type of the element.
     * @return The type of the element.
     */
    type::data_t element::getType() const { return this->__type; }


    /**
     * @brief Checks if the element is required.
     * @return True if the element is required, false otherwise.
     */
    bool element::isRequired() const { return this->__required; }


    /**
     * @brief Checks if the value of the element is set.
     * @return True if the value is set, false otherwise.
     */
    bool element::isValueSet() const { return this->__isValueSet; }
} // namespace treecode