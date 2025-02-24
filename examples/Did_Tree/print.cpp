#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"


void printTree(const tc::group& group, int indent = 0, bool lastChild = true, std::string parentIndentStr = "") {
    std::string indentStr = parentIndentStr;
    std::string label = "ROOT: ";
    
    // Prepare indentation for the current group
    if (indent == 0)label = "ROOT: ";
    else if (indent > 0) {
        std::cout << indentStr + "|   " << std::endl;
        indentStr += (lastChild ? "+-- " : "|-- ");
        label = "CHILD: ";
    }
    std::cout << indentStr <<label<< group.getName() << std::endl;

    // Get keys and children
    auto keys = group.inside().getKeys();
    size_t numKeys = keys.size();
    size_t numChildren = group.getChildren().size();

    // Prepare indentation for children
    std::string nextIndentStr = parentIndentStr + (lastChild ? "    " : "|   ");

    // Print elements
    for (size_t i = 0; i < numKeys; ++i) {
        try {
            auto element = group.inside().get(keys[i]);
            bool isLastElement = (i == numKeys - 1 && numChildren == 0);
            std::cout << nextIndentStr << (isLastElement ? "+-- " : "|-- ");
            auto required = element->isReq() ? " (Required)" : " (Optional)";
            if (element->data()) {
                std::visit([&](auto&& value) {
                    std::cout << keys[i] << " ==> Value: " << value << required << std::endl;
                }, element->data().value());
            } else {
                std::cout << keys[i] << " ==> Value: none" << required << std::endl;
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