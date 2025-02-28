#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"
#include <variant>

void printTree(const treecode::group& group, int indent = 0, bool lastChild = true, std::string parentIndentStr = "") {
    std::string indentStr = parentIndentStr;
    std::string label = "ROOT: ";
    
    // Prepare indentation for the current group
    if (indent == 0) label = "ROOT: ";
    else if (indent > 0) {
        std::cout << indentStr + "|   " << std::endl;
        indentStr += (lastChild ? "+-- " : "|-- ");
        label = "CHILD: ";
    }
    std::cout << indentStr << label << group.name() << std::endl;

    // Get keys and children
    auto keys = group.items().keys();
    size_t numKeys = keys.size();
    size_t numChildren = group.children().size();

    // Prepare indentation for children
    std::string nextIndentStr = parentIndentStr + (lastChild ? "    " : "|   ");

    // Print elements
    for (size_t i = 0; i < numKeys; ++i) {
        try {
            auto baseElement = group.items().get(keys[i]);
            bool isLastElement = (i == numKeys - 1 && numChildren == 0);
            std::cout << nextIndentStr << (isLastElement ? "+-- " : "|-- ");
            auto required = baseElement->is_required() ? " (Required)" : " (Optional)";

            // Attempt to cast to item<T> and print the value
            if (auto stringElement = std::dynamic_pointer_cast<treecode::item<std::string>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << stringElement->data().value_or("none") << required << std::endl;
            } else if (auto intElement = std::dynamic_pointer_cast<treecode::item<int>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << intElement->data().value_or(0) << required << std::endl;
            } else if (auto floatElement = std::dynamic_pointer_cast<treecode::item<float>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << floatElement->data().value_or(0.0f) << required << std::endl;
            } else if (auto doubleElement = std::dynamic_pointer_cast<treecode::item<double>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << doubleElement->data().value_or(0.0) << required << std::endl;
            } else if (auto doubleElement = std::dynamic_pointer_cast<treecode::item<bool>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << doubleElement->data().value_or(0.0) << required << std::endl;
            } else {
                std::cout << keys[i] << " ==> Value: unknown type" << required << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << nextIndentStr << "Error: " << e.what() << std::endl;
        }
    }

    for (size_t i = 0; i < numChildren; ++i) {
        bool isLast = (i == numChildren - 1);
        printTree(*group.children()[i], indent + 1, isLast, nextIndentStr);
    }
}

void print(const treecode::group& group) {
    printTree(group);
}