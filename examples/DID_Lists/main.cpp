#include <treecode.hpp>
#include <iostream>
void printGroupInfo(const std::shared_ptr<treecode::group>& group, int indent = 0, bool lastChild = true, std::string parentIndentStr = "") {
    std::string indentStr = parentIndentStr;
    
    std::string label = "ROOT: ";
    
    if (indent == 0) {
        label = "ROOT: ";
    }
    else if (indent > 0) {
        indentStr += (lastChild ? "+-- " : "|-- ");
        label = "CHILD: ";
    }

    std::cout << indentStr <<label<< group->getName() << std::endl;

    auto keys = group->getContainer().getKeys();
    size_t numKeys = keys.size();
    size_t numChildren = group->getChildren().size();
    
    // Prepare indentation for children
    std::string nextIndentStr = parentIndentStr + (lastChild ? "    " : "|   ");

    for (size_t i = 0; i < numKeys; ++i) {
        try {
            auto& element = group->getContainer().getElement(keys[i]);
            if (element.getType() == treecode::type::UNKNOWN) continue;

            bool isLastElement = (i == numKeys - 1 && numChildren == 0);

            std::cout << nextIndentStr << (isLastElement ? "+-- " : "|-- ");

            std::string typeStr;
            switch (element.getType()) {
                case treecode::type::TEXT:       typeStr = "TEXT"; break;
                case treecode::type::NUMERICAL:  typeStr = "NUMERICAL"; break;
                case treecode::type::FLOAT:      typeStr = "FLOAT"; break;
                case treecode::type::BOOLEAN:    typeStr = "BOOLEAN"; break;
                case treecode::type::MULTIVALUES: typeStr = "MULTIVALUES"; break;
                default: typeStr = "unknown";
            }

            std::cout << keys[i] << " ==> Label: " << element.getLabel() << " - Description: " << element.getDescription() <<" - type: " << typeStr << " - Value: " << element.getValue() << std::endl;
            
        } catch (const std::exception& e) {
            std::cerr << nextIndentStr << "Error: " << e.what() << std::endl;
        }
    }

    for (size_t i = 0; i < numChildren; ++i) {
        bool isLast = (i == numChildren - 1);
        printGroupInfo(group->getChildren()[i], indent + 1, isLast, nextIndentStr);
    }
}

void printTree(const std::shared_ptr<treecode::group>& group) {
    std::cout << "+------------------------------------------------------------------------------------------------------+"<<std::endl;
    printGroupInfo(group);
    std::cout << "+------------------------------------------------------------------------------------------------------+"<<std::endl;
}

int main() {
    using namespace treecode;

    try {
        // Create a template for DID List
        auto didTemplate = std::make_shared<groupTemplate>("DidTemplate");
        auto elementTemplate = std::make_shared<groupTemplate>("ElementTemplate");

        // Create child groups for the template
        auto didGroup = std::make_shared<group>("DID");
        didGroup->getContainer().addElement("ID", element("DID ID", "The ID of the current DID", type::TEXT, "FD01"));
        std::vector<std::string> allowedValues = {"NORMAL", "EXTENDED"};
        didGroup->getContainer().addElement("TYPE", element("DID Type", "Type of DID", type::MULTIVALUES, allowedValues));
        
        auto elementGroup = std::make_shared<group>("ELEMENT");
        elementGroup->getContainer().addElement("NAME", element("Interface name", "Interface name as mentioned in the SYGLO", type::TEXT, true));
        elementGroup->getContainer().addElement("TYPE", element("Interface type", "Type of interface", type::TEXT, "uint8", true));
        // Add the DID group to the template
        didTemplate->addGroup(didGroup);
        
        // Add the ELEMENT group to the template
        elementTemplate->addGroup(elementGroup);

        // Create instances of the template
        auto DID_Ins1 = didTemplate->createInstance();
        
        auto DID_Ins2 = didTemplate->createInstance();

        auto didList = std::make_shared<group>("DID LIST");

        // Modify instance1
        auto didGroupInstance1 = DID_Ins1->getChildren()[0];
        try {
            
            didGroupInstance1->getContainer().getElement("ID").setValue("FD01");
            didGroupInstance1->getContainer().getElement("TYPE").setValue("NORMAL");
        } catch (const std::exception& e) {
            std::cerr << "Error modifying instance1: " << e.what() << std::endl;
        }

        // Add another ELEMENT group to instance1
        try {
            auto newElementGroup1 = elementTemplate->createGroupInstance("ELEMENT");
            newElementGroup1->getContainer().getElement("NAME").setValue("Interface1");
            didGroupInstance1->addChild(std::move(newElementGroup1));

            auto newElementGroup2 = elementTemplate->createGroupInstance("ELEMENT");
            newElementGroup2->getContainer().getElement("NAME").setValue("Interface2");
            newElementGroup2->getContainer().getElement("TYPE").setValue("uint16");
            didGroupInstance1->addChild(std::move(newElementGroup2));

            auto newElementGroup3 = elementTemplate->createGroupInstance("ELEMENT");
            newElementGroup3->getContainer().getElement("NAME").setValue("Interface3");
            newElementGroup3->getContainer().getElement("TYPE").setValue("uint16");
            didGroupInstance1->addChild(std::move(newElementGroup3));
        } catch (const std::exception& e) {
            std::cerr << "Error adding ELEMENT group to instance1: " << e.what() << std::endl;
        }

        // Modify instance2
        auto didGroupInstance2 = DID_Ins2->getChildren()[0];
        try {
            didGroupInstance2->getContainer().getElement("ID").setValue("FD10");
            didGroupInstance2->getContainer().getElement("TYPE").setValue("EXTENDED");
        } catch (const std::exception& e) {
            std::cerr << "Error modifying instance2: " << e.what() << std::endl;
        }

        // Add another ELEMENT group to instance2
        try {
            auto newElementGroup2 = elementTemplate->createGroupInstance("ELEMENT");
            newElementGroup2->getContainer().getElement("NAME").setValue("Interface4");
            newElementGroup2->getContainer().getElement("TYPE").setValue("uint16");
            didGroupInstance2->addChild(std::move(newElementGroup2));
        } catch (const std::exception& e) {
            std::cerr << "Error adding ELEMENT group to instance2: " << e.what() << std::endl;
        }

        didList->addChild(std::move(didGroupInstance1));
        didList->addChild(std::move(didGroupInstance2));
        // Print the instances
        printTree(didList);
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }

    return 0;
}