#include <treecode.hpp>
#include <iostream>
#include "includes/print.hpp"

tc::tmpl create_tmpl() {

    // Create a template for did and element
    auto tmpl = tc::tmpl("Did_Tmpl");

    // Create DID group
    auto did_group = tc::group("DID");
    did_group.inside().add<std::string>("ID");
    did_group.inside().add<std::string>("TYPE",{"NORMAL","EXTENDED"});
    
    // Create ELEMENT group
    auto ele_group = tc::group("ELEMENT");
    ele_group.inside().add<std::string>("NAME")->setReq();
    ele_group.inside().add<std::string>("TYPE", {"uint8", "uint16"});
    ele_group.inside().add<int>("VALUE",0);
    ele_group.inside().add<bool>("SHARED",false)->setReq();


    // Add DID & ELEMENT to the "DidTmpl" template
    tmpl.add(std::make_shared<tc::group>(did_group));
    tmpl.add(std::make_shared<tc::group>(ele_group));

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
        did = tmpl.clone("DID");
        did->inside().get<std::string>("ID")->set("FD09");
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem->inside().get<std::string>("NAME")->set("Interface1");
        did->add(elem);
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem->inside().get<std::string>("NAME")->set("Interface2");
        elem->inside().get<std::string>("TYPE")->set("uint16");
        elem->inside().get<int>("VALUE")->set(350);
        did->add(elem);
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem->inside().get<std::string>("NAME")->set("Interface3");
        elem->inside().get<std::string>("TYPE")->set("uint16");
        did->add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance2 of DID
        did = tmpl.clone("DID");
        did->inside().get<std::string>("ID")->set("FD10");
        did->inside().get<std::string>("TYPE")->set("EXTENDED");
        // Add elements to the DID
        elem = tmpl.clone("ELEMENT");
        elem->inside().get<std::string>("NAME")->set("Interface4");
        elem->inside().get<std::string>("TYPE")->set("uint16");
        elem->inside().get<int>("VALUE")->set(200);
        did->add(elem);
        // Add the instance to the root group
        did_tree.add(did);


        // Modify instance3 of DID
        did = tmpl.clone("DID");
        did->inside().get<std::string>("ID")->set("FD11");
        did->inside().get<std::string>("TYPE")->set("NORMAL");
        // Add the instance to the root group
        did_tree.add(did);


        // Print Tree
        print(did_tree);
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }
    return 0;
}
