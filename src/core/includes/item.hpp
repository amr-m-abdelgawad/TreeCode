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
 * @file item.h
 * @class Item
 * @brief Header file for the item class.
 * @ingroup Core
 * 
 * This file contains the implementation of the item class,
 * which is used to represent the base item with a label, description, type, and optional constraints.
 * 
 * @version Version 0.0.1
 * @author Amr MOUSA - https://github.com/amr-m-abdelgawad
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1:
 *      - Initial Implementation of the item class
 */
#ifndef ITEM_H
#define ITEM_H

/**
 * @brief Include necessary headers
*/
#include "common.hpp"
#include "base.hpp"

/**
 * @def FIRST_ITEM
 * The index of the first item in a list.
 */
#define FIRST_ITEM   0U


namespace treecode
{
    /**
     * @class item
     * @brief Represents the base item with optional constraints.
     */
    template <typename T>
    class item : public base {
    public:
        /**
         * @brief Default constructor for the item class.
         */
        item();


        /**
         * @brief Constructs an item with default value.
         * @param value The default value for the item.
         */
        item(
            const T& value
        );


        /**
         * @brief Constructs an item with multi choice values.
         * @param choices The allowed multi choice values for the item.
         */
        item(
            const std::vector<T>& choices
        );


        /**
         * @brief Sets the value of the item.
         * @param value The new value to set.
         */
        void value(
            const T& value
        );


        /**
         * @brief Gets the current data of the item.
         * @return The current value of the item.
         */
        std::optional<T> data() const;


        /**
         * @brief Gets the multi choice values for the item.
         * @return A vector of multi choice  values.
         */
        std::vector<T> choices() const;


        /**
         * @brief Checks if the item is required.
         * @return True if the item is required, false otherwise.
         */
        bool is_required() const override;


        /**
         * @brief Sets the item as required.
         * @return void
         */
        void required() override;

        /**
         * @brief Clone the item.
         * @return A shared pointer to the cloned item.
         */
        std::shared_ptr<base> clone() const override;

    private:
        /**
         * @var std::optional<T> item::__value
         * The value of the item.
         */
        std::optional<T> __value;

        /**
         * @var std::vector<T> item::__choices
         * The allowed values for the item.
         */
        std::vector<T> __choices;

        /**
         * @var bool item::__isChoices
         * The flag to check if the item is multivalues.
         */
        bool __isChoices;

        /**
         * @var bool item::__isRequired
         * The flag to check if the item is required.
         */
        bool __isRequired;
    };


    /**
     * @brief Default constructor for the item class.
     */
    template <typename T>
    item<T>::item() :
        __isChoices(false),
        __isRequired(false) {}


    /**
     * @brief Constructs an item with default value.
     * @param value The default value for the item.
     */
    template <typename T>
    item<T>::item(
        const T& value
    ) : item() { this->__value = value; }


    /**
     * @brief Constructs an item with multi choice values.
     * @param choices The allowed multi choice values for the item.
     */
    template <typename T>
    item<T>::item(
        const std::vector<T>& choices
    ) : __choices(choices),
        __isChoices(true) {
        if (!choices.empty()) {
            /* Set the default value to the first allowed value */
            this->__value = choices[FIRST_ITEM];
            /* Set the required flag */
            this->__isRequired = true;
        } else Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_ALLOWED_VALUES_EMPTY); /* Throw an exception if the allowed values list is empty */
    }


    /**
     * @brief Sets the value of the item.
     * @param value The new value to set.
     */
    template <typename T>
    void item<T>::value(
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
     * @brief Gets the current data of the item.
     * @return The current value of the item.
     */
    template <typename T>
    std::optional<T> item<T>::data() const { 
        return this->__value.has_value() ? this->__value : std::nullopt;
    }


    /**
     * @brief Gets the multi choice values for the item.
     * @return A vector of multi choice  values.
     */
    template <typename T>
    std::vector<T> item<T>::choices() const {
        /* throw an exception if the item type is not multivalues */
        if(!this->__isChoices) {
            Exception::Throw::Invalid("Multivalue Element", Exception::ELEMENT_MULTIVALUES_ALLOWED_MISSING);
            return {}; // Return an empty vector to satisfy the return type
        }
        /* return the allowed values */
        else return this->__choices;
    }


    /**
     * @brief Checks if the item is required.
     * @return True if the item is required, false otherwise.
     */
    template <typename T>
    bool item<T>::is_required() const { return this->__isRequired; }


    /**
     * @brief Sets the item as required.
     * @return void
     */
    template <typename T>
    void item<T>::required() { this->__isRequired = true; }


    /**
     * @brief Clone the item.
     * @return A shared pointer to the cloned item.
     */
    template <typename T>
    std::shared_ptr<base> item<T>::clone() const {
        return std::make_shared<item<T>>(*this);
    }
} // namespace treecode

#endif // ITEM_H