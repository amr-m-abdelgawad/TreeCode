#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"

treecode::tmpl create_tmpl() {

    // Create a template for did and element
    auto tmpl = treecode::tmpl("Did_Tmpl");

    // Create DID group
    auto did_group = treecode::group("DID");
    did_group.items().add<std::string>("ID");
    did_group.items().add<std::string>("TYPE",{"NORMAL","EXTENDED"});
    
    // Create ELEMENT group
    auto ele_group = treecode::group("ELEMENT");
    ele_group.items().add<std::string>("NAME")->required();
    ele_group.items().add<std::string>("TYPE", {"uint8", "uint16"});
    ele_group.items().add<int>("VALUE",0);
    ele_group.items().add<bool>("SHARED",false)->required();


    // Add DID & ELEMENT to the "DidTmpl" template
    tmpl.add(did_group);
    tmpl.add(ele_group);

    return tmpl;
}

int main() {
    try {
        // Create a template for did and element
        auto tmpl = create_tmpl();
        // Create a root group for the DID LIST
        auto did_tree = treecode::group("DID TREE");

        treecode::group did;
        treecode::group elem;

        // Modify instance1 of DID
        did = tmpl.clone("DID");
        did.items().get<std::string>("ID")->value("FD09");
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem.items().get<std::string>("NAME")->value("Interface1");
        did.add(elem);
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem.items().get<std::string>("NAME")->value("Interface2");
        elem.items().get<std::string>("TYPE")->value("uint16");
        elem.items().get<int>("VALUE")->value(350);
        did.add(elem);
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem.items().get<std::string>("NAME")->value("Interface3");
        elem.items().get<std::string>("TYPE")->value("uint16");
        did.add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance2 of DID
        did = tmpl.clone("DID");
        if (did.items().exists("TEST")) {
            did.items().get<std::string>("TEST")->value("Hello");
        }
        else {
            did.items().add<std::string>("TEST")->value("Hello");
        }
        
        did.items().get<std::string>("ID")->value("FD10");
        did.items().get<std::string>("TYPE")->value("EXTENDED");
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem.items().get<std::string>("NAME")->value("Interface4");
        elem.items().get<std::string>("TYPE")->value("uint16");
        elem.items().get<int>("VALUE")->value(200);
        did.add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance3 of DID
        did = tmpl.clone("DID");
        did.items().get<std::string>("ID")->value("FD11");
        did.items().get<std::string>("TYPE")->value("NORMAL");
        // Add the instance to the root group
        did_tree.add(did);


        // Print Tree
        print(did_tree);
        std::cout<<"------------"<<std::endl;
        if(did_tree.children()[1]->items().remove("TEST")) {
            std::cout<<"Removed TEST"<<std::endl;
        }
        else {
            std::cout<<"TEST not found"<<std::endl;
        }
        std::cout<<"------------"<<std::endl;
        if(did_tree.children()[1]->items().remove("TEST")) {
            std::cout<<"Removed TEST"<<std::endl;
        }
        else {
            std::cout<<"TEST not found"<<std::endl;
        }
        std::cout<<"------------"<<std::endl;
        print(did_tree);

    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }
    return 0;
}
