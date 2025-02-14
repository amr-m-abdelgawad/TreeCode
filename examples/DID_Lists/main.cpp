#include <treecode.hpp>
#include <iostream>
void printGroupInfo(const std::shared_ptr<TreeCode::group>& group, int indent = 0) {
    std::string indentStr(indent, '-');

    // Print group name
    std::cout << indentStr << "-> Group: " << group->getName() << std::endl;

    // Print elements in the container
    auto keys = group->getContainer().getKeys();
    for (const auto& key : keys) {
        try {
            auto& element = group->getContainer().getElement(key);
            if(element.getType() == TreeCode::Type::UNKNOWN)
                continue;
            std::cout << indentStr << "-> Element Key: " << key << std::endl;
            std::cout << indentStr << "     Label: " << element.getLabel() << std::endl;
            std::cout << indentStr << "     Description: " << element.getDescription() << std::endl;
            std::cout << indentStr << "     Value: " << element.getValue() << std::endl;
            if(element.getType() == TreeCode::Type::MULTIVALUES) {
                std::cout << indentStr << "     Allowed Values: ";
                for(const auto& value : element.getAllowedValues()) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
            std::cout << indentStr << "     Type: " << element.getType() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << indentStr << "  Error: " << e.what() << std::endl;
        }
    }

    // Recursively print child groups
    for (const auto& child : group->getChildren()) {
        printGroupInfo(child, indent + 4);
    }
}

int main() {
    using namespace TreeCode;

    try {
        // Create a template for DID List
        auto didTemplate = std::make_shared<groupTemplate>("DID LIST");
        auto elementTemplate = std::make_shared<groupTemplate>("ELEMENT LIST");

        // Create child groups for the template
        auto didGroup = std::make_shared<group>("DID");
        didGroup->getContainer().addElement("ID", element("DID ID", "The ID of the current DID", Type::TEXT, "FD01"));
        std::vector<std::string> allowedValues = {"NORMAL", "EXTENDED"};
        didGroup->getContainer().addElement("TYPE", element("DID Type", "Type of DID", Type::MULTIVALUES, allowedValues));
        
        auto elementGroup = std::make_shared<group>("ELEMENT");
        elementGroup->getContainer().addElement("NAME", element("Interface name", "Interface name as mentioned in the SYGLO", Type::TEXT, true));
        elementGroup->getContainer().addElement("TYPE", element("Interface type", "Type of interface", Type::TEXT, "uint8", true));
        // Add the DID group to the template
        didTemplate->addGroup(didGroup);
        
        // Add the ELEMENT group to the template
        elementTemplate->addGroup(elementGroup);

        // Create instances of the template
        auto DID_Ins1 = didTemplate->createInstance();
        
        auto DID_Ins2 = didTemplate->createInstance();

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
            newElementGroup2->getContainer().getElement("NAME").setValue("Interface3");
            newElementGroup2->getContainer().getElement("TYPE").setValue("uint16");
            didGroupInstance2->addChild(std::move(newElementGroup2));
        } catch (const std::exception& e) {
            std::cerr << "Error adding ELEMENT group to instance2: " << e.what() << std::endl;
        }

        // Print the instances
        printGroupInfo(didGroupInstance1);
        printGroupInfo(didGroupInstance2);
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }

    return 0;
}