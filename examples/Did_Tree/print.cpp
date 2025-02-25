#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"
#include <variant>

void printTree(const tc::group& group, int indent = 0, bool lastChild = true, std::string parentIndentStr = "") {
    std::string indentStr = parentIndentStr;
    std::string label = "ROOT: ";
    
    // Prepare indentation for the current group
    if (indent == 0) label = "ROOT: ";
    else if (indent > 0) {
        std::cout << indentStr + "|   " << std::endl;
        indentStr += (lastChild ? "+-- " : "|-- ");
        label = "CHILD: ";
    }
    std::cout << indentStr << label << group.getName() << std::endl;

    // Get keys and children
    auto keys = group.inside().getKeys();
    size_t numKeys = keys.size();
    size_t numChildren = group.getChildren().size();

    // Prepare indentation for children
    std::string nextIndentStr = parentIndentStr + (lastChild ? "    " : "|   ");

    // Print elements
    for (size_t i = 0; i < numKeys; ++i) {
        try {
            auto baseElement = group.inside().get(keys[i]);
            bool isLastElement = (i == numKeys - 1 && numChildren == 0);
            std::cout << nextIndentStr << (isLastElement ? "+-- " : "|-- ");
            auto required = baseElement->isReq() ? " (Required)" : " (Optional)";

            // Attempt to cast to element<T> and print the value
            if (auto stringElement = std::dynamic_pointer_cast<tc::element<std::string>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << stringElement->data().value_or("none") << required << std::endl;
            } else if (auto intElement = std::dynamic_pointer_cast<tc::element<int>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << intElement->data().value_or(0) << required << std::endl;
            } else if (auto floatElement = std::dynamic_pointer_cast<tc::element<float>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << floatElement->data().value_or(0.0f) << required << std::endl;
            } else if (auto doubleElement = std::dynamic_pointer_cast<tc::element<double>>(baseElement)) {
                std::cout << keys[i] << " ==> Value: " << doubleElement->data().value_or(0.0) << required << std::endl;
            } else if (auto doubleElement = std::dynamic_pointer_cast<tc::element<bool>>(baseElement)) {
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
        printTree(*group.getChildren()[i], indent + 1, isLast, nextIndentStr);
    }
}

void print(const tc::group& group) {
    printTree(group);
}