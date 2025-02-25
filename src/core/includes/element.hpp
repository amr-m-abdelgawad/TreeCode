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
    template <typename T>
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
            const T& value
        );


        /**
         * @brief Constructs an element with the specified label, description, type, and allowed values.
         * @param label The label of the element.
         * @param description The description of the element.
         * @param type The type of the element.
         * @param allowedValues The allowed values for the element.
         */
        element(
            const std::vector<T>& choices
        );

        /**
         * @brief Sets the value of the element.
         * @param newValue The new value to set.
         */
        void set(
            const T& value
        );


        /**
         * @brief Gets the current value of the element.
         * @return The current value of the element.
         */
        std::optional<T> data() const;


        /**
         * @brief Gets the allowed values for the element.
         * @return A vector of allowed values.
         */
        std::vector<T> choices() const;


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

        std::shared_ptr<base> clone() const override;

    private:
        /** @var std::string element::__value
         * The current value of the element.
         */
        std::optional<T> __value;


        /** @var std::vector<std::string> element::__allowedValues
         * The allowed values for the element.
         */
        std::vector<T> __choices;


        /** @var type::data_t element::__type
         * The type of the element.
         */
        bool __isChoices;


        /** @var bool element::__required
         * Indicates whether the element is required.
         */
        bool __isRequired;
    };

    /**
     * @brief Default constructor for the element class.
     * Initializes the element with default values.
     */
    template <typename T>
    element<T>::element() :
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
    template <typename T>
    element<T>::element(
        const T& value
    ) : element() { this->__value = value; }


    /**
     * @brief Constructor for the element class with allowed values.
     * @param label The label of the element.
     * @param description The description of the element.
     * @param type The type of the element.
     * @param allowedValues The allowed values for the element.
     * Initializes the element with the given label, description, type, and allowed values.
     * Throws an exception if the type is not MULTIVALUES or if the allowed values list is empty.
     */
    template <typename T>
    element<T>::element(
        const std::vector<T>& choices
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
    template <typename T>
    void element<T>::set(
        const T& value
    ) {
        if (this->__isChoices) {
            /* check if value is in the allowed values list */
            if (std::find(this->__choices.begin(), this->__choices.end(), value) != this->__choices.end()) {
                /* set the value and the value set flag */
                this->__value = value;
            }
            /* throw an exception if the value is not in the allowed values list */
            else Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_VALUE_NOT_ALLOWED);
        }
        /* set the value for other types */
        else {
            /* set the value */
            this->__value = value;
        }
    }


    /**
     * @brief Gets the value of the element.
     * @return The value of the element.
     */
    template <typename T>
    std::optional<T> element<T>::data() const { 
        return this->__value.has_value() ? this->__value : std::nullopt;
    }


    /**
     * @brief Gets the allowed values of the element.
     * @return The allowed values of the element.
     * Throws an exception if the element type is not MULTIVALUES.
     */
    template <typename T>
    std::vector<T> element<T>::choices() const {
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
    template <typename T>
    bool element<T>::isReq() const { return this->__isRequired; }


    /**
     * @brief Sets the element as required.
     * @return void
     */
    template <typename T>
    void element<T>::setReq() { this->__isRequired = true; }


    template <typename T>
    std::shared_ptr<base> element<T>::clone() const {
        return std::make_shared<element<T>>(*this);
    }
} // namespace treecode

#endif // ELEMENT_H