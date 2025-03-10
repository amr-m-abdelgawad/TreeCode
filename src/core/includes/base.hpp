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
 * @file base.hpp
 * @class base
 * @brief Header file for the base class.
 * @ingroup Core
 * 
 * This file contains the definition of the base class, which is used to represent
 * the base item with a label, description, type, and optional constraints.
 * 
 * @version 0.0.1
 * @author Amr MOUSA
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 22, 2025
 * 
 * File History:
 * - Version 0.0.1: 
 *      - Initial Implementation of the base class
 */
#ifndef BASE_H
#define BASE_H

/**
 * @brief Include necessary headers
 */
#include "common.hpp"


namespace treecode {
    /**
     * @class base
     * @brief Represents the base item with a label, description, type, and optional constraints.
     */
    class base {
        
    public:
        /**
         * @brief Default constructor for the base class.
         */
        base() = default;

        /**
         * @brief Destructor for the base class.
         */
        virtual ~base() = default;


        /**
         * @brief Clone the base.
         * @return A shared pointer to the cloned base.
         */
        virtual std::shared_ptr<base> clone() const = 0;


        /**
         * @brief Checks if the base is required.
         * @return True if the base is required, false otherwise.
         */
        virtual bool is_required() const = 0;


        /**
         * @brief Sets the base as required.
         * @return void
         */
        virtual void required() = 0;

        protected:
        /**
         * @brief Copy constructor for the base class.
         */
        base(const base&) = default;


        /**
         * @brief Assignment operator for the base class.
         * @return A reference to the assigned base object.
         */
        base& operator=(const base&) = default;
    };
} // namespace treecode

#endif // BASE_H