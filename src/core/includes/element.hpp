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
 * @file element.h
 * @class Element
 * @brief Header file for the element class.
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
#ifndef ELEMENT_H
#define ELEMENT_H

/**
 * @brief Include necessary headers
*/
#include "common.hpp"

namespace TreeCode
{
    namespace Type
    {
        /**
         * @enum data_t
         * @brief Represents the type of data an element can hold.
         * 
         * This enumeration defines the various types of data that an element can represent.
         * The types include text, numerical, floating-point, multivalues, boolean, and unknown.
         */
        typedef enum {
            /**
             * @var TEXT
             * Represents a text element.
             */
            TEXT,

            /**
             * @var NUMERICAL
             * Represents a numerical element.
             */
            NUMERICAL,

            /**
             * @var FLOAT
             * Represents a floating-point element.
             */
            FLOAT,

            /**
             * @var MULTIVALUES
             * Represents an element that can hold multiple values.
             */
            MULTIVALUES,

            /**
             * @var BOOLEAN
             * Represents a boolean element.
             */
            BOOLEAN,

            /**
             * @var UNKNOWN
             * Represents an unknown element type.
             */
            UNKNOWN
        } data_t;
    } // namespace ELEMENT
    /**
     * @class element
     * @brief Represents an element with a label, description, type, and optional constraints.
     * 
     * The element class provides functionality to store and manage elements with various attributes
     * such as label, description, type, default value, required flag, and allowed values. It also 
     * supports serialization to and from JSON.
     */
    class element {
    public:
        /**
         * @brief Default constructor for the element class.
         */
        element();


        /**
         * @brief Constructs an element with the specified label, description, and type.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         */
        element(
            const std::string& label, 
            const std::string& description, 
            const Type::data_t& type
        );


        /**
         * @brief Constructs an element with the specified label, description, type, and default value.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param defaultValue The default value of the element.
         */
        element(
            const std::string& label, 
            const std::string& description, 
            const Type::data_t& type, 
            const std::string& defaultValue
        );


        /**
         * @brief Constructs an element with the specified label, description, type, and required flag.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param required Indicates whether the element is required.
         */
        element(
            const std::string& label, 
            const std::string& description, 
            const Type::data_t& type, 
            const bool& required
        );


        /**
         * @brief Constructs an element with the specified label, description, type, default value, and required flag.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param defaultValue The default value of the element.
         * @param required Indicates whether the element is required.
         */
        element(
            const std::string& label, 
            const std::string& description, 
            const Type::data_t& type, 
            const std::string& defaultValue, 
            const bool& required
        );


        /**
         * @brief Constructs an element with the specified label, description, type, and allowed values.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param allowedValues The allowed values for the element.
         */
        element(
            const std::string& label, 
            const std::string& description, 
            const Type::data_t& type, 
            const std::vector<std::string>& allowedValues
        );


        /**
         * @brief Sets the value of the element.
         * @param newValue The new value to set.
         */
        void setValue(
            const std::string& newValue
        );


        /**
         * @brief Gets the current value of the element.
         * @return The current value of the element.
         */
        std::string getValue() const;


        /**
         * @brief Gets the allowed values for the element.
         * @return A vector of allowed values.
         */
        std::vector<std::string> getAllowedValues() const;


        /**
         * @brief Gets the label of the element.
         * @return The label of the element.
         */
        std::string getLabel() const;


        /**
         * @brief Gets the description of the element.
         * @return The description of the element.
         */
        std::string getDescription() const;


        /**
         * @brief Gets the type of the element.
         * @return The type of the element.
         */
        Type::data_t getType() const;


        /**
         * @brief Checks if the element is required.
         * @return True if the element is required, false otherwise.
         */
        bool isRequired() const;


        /**
         * @brief Checks if the value of the element is set.
         * @return True if the value is set, false otherwise.
         */
        bool isValueSet() const;


    private:
        /**
         * @var std::string element::__label
         * The label of the element.
         */
        std::string __label;


        /** @var std::string element::__description
         * The description of the element.
         */
        std::string __description;


        /** @var Type::data_t element::__type
         * The type of the element.
         */
        Type::data_t __type;


        /** @var std::string element::__value
         * The current value of the element.
         */
        std::string __value;


        /** @var bool element::__isValueSet
         * Indicates whether the value of the element has been set.
         */
        bool __isValueSet;


        /** @var bool element::__required
         * Indicates whether the element is required.
         */
        bool __required;


        /** @var std::vector<std::string> element::__allowedValues
         * The allowed values for the element.
         */
        std::vector<std::string> __allowedValues;
    };
} // namespace TreeCode

#endif // ELEMENT_H