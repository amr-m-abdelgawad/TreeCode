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
#include "base.hpp"

#define FIRST_ELEMENT   0U

namespace tc
{
    

    /**
     * @class element
     * @brief Represents an element with a label, description, type, and optional constraints.
     * 
     * The element class provides functionality to store and manage elements with various attributes
     * such as label, description, type, default value, required flag, and allowed values. It also 
     * supports serialization to and from JSON.
     */
    class element : public base {
    public:
        /**
         * @brief Default constructor for the element class.
         */
        element();


        /**
         * @brief Constructs an element with the specified label, description, type, and default value.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param defaultValue The default value of the element.
         */
        element(
            const type& defaultValue
        );


        /**
         * @brief Constructs an element with the specified label, description, type, and allowed values.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param allowedValues The allowed values for the element.
         */
        element(
            const multi& choices
        );


        /**
         * @brief Sets the value of the element.
         * @param newValue The new value to set.
         */
        void set(
            const type& newValue
        ) override;


        /**
         * @brief Gets the current value of the element.
         * @return The current value of the element.
         */
        std::optional<type> data() const override;


        /**
         * @brief Gets the allowed values for the element.
         * @return A vector of allowed values.
         */
        multi choices() const;


        /**
         * @brief Checks if the element is required.
         * @return True if the element is required, false otherwise.
         */
        bool isReq() const override;


        /**
         * @brief Sets the element as required.
         * @return void
         */
        void setReq() override;

    private:
        /** @var std::string element::__value
         * The current value of the element.
         */
        std::optional<type> __value;


        /** @var std::vector<std::string> element::__allowedValues
         * The allowed values for the element.
         */
        multi __choices;


        /** @var type::data_t element::__type
         * The type of the element.
         */
        bool __isChoices;


        /** @var bool element::__required
         * Indicates whether the element is required.
         */
        bool __isRequired;
    };
} // namespace treecode

#endif // ELEMENT_H