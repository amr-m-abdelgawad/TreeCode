#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"

std::shared_ptr<tc::tmpl> create_tmpl() {

    // Create a template for did and element
    auto tmpl = std::make_shared<tc::tmpl>("DidTmpl");

    // Create DID group
    auto did_group = std::make_shared<tc::group>("DID");
    did_group->inside().add("ID");
    did_group->inside().add("TYPE",tc::multi({std::string("NORMAL"), std::string("EXTENDED")}));
    
    // Create ELEMENT group
    auto ele_group = std::make_shared<tc::group>("ELEMENT");
    ele_group->inside().add("NAME")->setReq();
    ele_group->inside().add("TYPE", tc::multi({std::string("uint8"), std::string("uint16")}));

    // Add DID & ELEMENT to the "DidTmpl" template
    tmpl->add(did_group);
    tmpl->add(ele_group);

    return tmpl;
}

int main() {
    try {
        // Create a template for did and element
        auto tmpl = create_tmpl();
        // Create a root group for the DID LIST
        auto did_tree = tc::group("DID TREE");

        std::shared_ptr<tc::group> did;
        std::shared_ptr<tc::group> elem;

        // Modify instance1 of DID
        did = tmpl->clone("DID");
        did->inside().get("ID")->set(std::string("FD09"));
        // Add elements to the DID
        elem = tmpl->clone("ELEMENT");
        elem->inside().get("NAME")->set(std::string("Interface1"));
        did->add(elem);
        // Add elements to the DID
        elem = tmpl->clone("ELEMENT");
        elem->inside().get("NAME")->set(std::string("Interface2"));
        elem->inside().get("TYPE")->set(std::string("uint16"));
        did->add(elem);
        // Add elements to the DID
        elem = tmpl->clone("ELEMENT");
        elem->inside().get("NAME")->set(std::string("Interface3"));
        elem->inside().get("TYPE")->set(std::string("uint16"));
        did->add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance2 of DID
        did = tmpl->clone("DID");
        did->inside().get("ID")->set(std::string("FD10"));
        did->inside().get("TYPE")->set(std::string("EXTENDED"));
        // Add elements to the DID
        elem = tmpl->clone("ELEMENT");
        elem->inside().get("NAME")->set(std::string("Interface4"));
        elem->inside().get("TYPE")->set(std::string("uint16"));
        did->add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance3 of DID
        did = tmpl->clone("DID");
        did->inside().get("ID")->set(std::string("FD11"));
        did->inside().get("TYPE")->set(std::string("NORMAL"));
        // Add the instance to the root group
        did_tree.add(did);


        // Print Tree
        print(did_tree);
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }
    return 0;
}
