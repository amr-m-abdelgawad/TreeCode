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
 * @file base.hpp
 * @class base
 * @brief Header file for the base class.
 * @ingroup Core
 * 
 * This file contains the definition of the base class, which is used to represent
 * the base element with a label, description, type, and optional constraints.
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

namespace tc {
    /**
     * @class base
     * @brief Represents the base element with a label, description, type, and optional constraints.
     */
    class base {
        
    public:
        /**
         * @brief Destructor for the base class.
         */
        virtual ~base() = default;


        virtual std::shared_ptr<base> clone() const = 0;

        /**
         * @brief Checks if the element is required.
         * @return True if the element is required, false otherwise.
         */
        virtual bool isReq() const = 0;


        /**
         * @brief Sets the element as required.
         * @return void
         */
        virtual void setReq() = 0;
    };
} // namespace tc

#endif // BASE_H