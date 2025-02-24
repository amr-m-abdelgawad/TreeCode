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
 * @file exception.hpp
 * @class Exception
 * @brief Header file for exception messages.
 * @ingroup Core
 * 
 * This file contains the definition of the exception messages used throughout the library.
 * 
 * @version Version 0.0.1
 * @author Amr MOUSA - https://github.com/amr-m-abdelgawad
 * @copyright Copyright (c) - Amr MOUSA 2025
 * @date February 7, 2025
 * 
 * File History:
 * - Version 0.0.1:
 *      - Initial Implementation of the exception messages
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
 * @brief Include necessary headers
 */
#include "common.hpp"

namespace tc {
    /**
     * @namespace Exception
     * @brief Contains exception messages used throughout the library.
     */

    namespace Exception {
        /* General Error messages */
        const std::string GENERAL_ERROR = "An unexpected error has occurred.";


        /* Container Errors */
        const std::string CONTAINER_KEY_ALREADY_EXISTS = "The key already exists in the container.";
        const std::string CONTAINER_KEY_NOT_FOUND = "The key was not found in the container.";
    
    
        /* Element Errors */
        const std::string ELEMENT_INVALID_TYPE = "The element type is invalid.";
        const std::string ELEMENT_WRONG_MULTIVALUES_CONSTRUCTOR = "Incorrect constructor used for multivalues type.";
        const std::string ELEMENT_MULTIVALUES_ALLOWED_MISSING = "Allowed values can only be set for multivalues type.";
        const std::string ELEMENT_WRONG_TYPE_FOR_MULTIVALUES = "Allowed values are only applicable for multivalues type.";
        const std::string ELEMENT_VALUE_NOT_ALLOWED = "The value is not in the allowed values list.";
        const std::string ELEMENT_TYPE_UNKNOWN = "The element type is unknown.";
        const std::string ELEMENT_ALLOWED_VALUES_EMPTY = "The allowed values list is empty.";
    
    
        /* Template Errors */
        const std::string TEMPLATE_GROUP_NOT_FOUND = "The group was not found in the template.";
        const std::string NULL_GROUP = "Null pointer error: expected a non-null pointer to a group.";
    
    
        /* File Errors */
        const std::string FILE_OPEN_ERROR = "Unable to open the specified file.";
    
        struct Throw {
            /**
             * @brief Throws an invalid argument exception with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::invalid_argument
             */
            static void Invalid(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::invalid_argument(
                    "\"" + label + "\" - " + message
                );
            };


            /**
             * @brief Throws a runtime error with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::runtime_error
             */
            static void Runtime(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::runtime_error(
                    "\"" + label + "\" - " + message
                );
            };


            /**
             * @brief Throws a logic error with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::logic_error
             */
            static void Logic(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::logic_error(
                    "\"" + label + "\" - " + message
                );
            };


            /**
             * @brief Throws a domain error with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::domain_error
             */
            static void Range(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::out_of_range(
                    "\"" + label + "\" - " + message
                );
            };


            /**
             * @brief Throws an overflow error with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::overflow_error
             */
            static void Overflow(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::overflow_error(
                    "\"" + label + "\" - " + message
                );
            };


            /**
             * @brief Throws an underflow error with the specified label and message.
             * @param label The label of the element.
             * @param message The message to include in the exception.
             * @throws std::underflow_error
             */
            static void Underflow(
                const std::string& label, 
                const std::string& message
            ) {
                throw std::underflow_error(
                    "\"" + label + "\" - " + message
                );
            };
        }; // struct Throw
    } // namespace Exception
} // namespace treecode

#endif // EXCEPTION_H