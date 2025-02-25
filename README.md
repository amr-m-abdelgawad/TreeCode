# TreeCode Project

![Build Status](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/CMake-Build.yml/badge.svg)
[![CodeQL](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/codeql.yml)
![GitHub License](https://img.shields.io/github/license/amr-m-abdelgawad/TreeCode)
![Static Badge](https://img.shields.io/badge/%40-Amr_MOUSA_2025-blue)

TreeCode is a C++ library for managing hierarchical data structures. It includes classes for containers, elements, groups, templates, and logging. The library can be built as a shared library and includes options for building tests and examples.

## Features
- Efficient tree traversal algorithms
- Tree manipulation functions
- Support for different types of trees (binary, AVL, etc.)
- Flexible template system for defining tree structures
- Comprehensive logging support

## Installation
To install the project, clone the repository and follow the build instructions:
```bash
git clone https://github.com/amr-m-abdelgawad/tc.git
cd tc
cmake -B build
cmake --build build --config Release
```

## Usage
Here is an example of how to use the TreeCode library:
```cpp
#include "core/includes/group.hpp"
#include "core/includes/template.hpp"
#include "includes/print.hpp"

tc::tmpl create_tmpl() {
    auto tmpl = tc::tmpl("ExampleTemplate");

    auto rootGroup = tc::group("Root");
    rootGroup.inside().add<std::string>("name")->setReq();
    tmpl.add(std::make_shared<tc::group>(rootGroup));

    auto childGroup = tc::group("Child");
    childGroup.inside().add<std::string>("name")->setReq();
    tmpl.add(std::make_shared<tc::group>(childGroup));

    return tmpl;
}

int main() {
    try {
        auto tmpl = create_tmpl();
        auto rootGroup = tc::group("RootGroup");

        auto instance = tmpl.clone("Root");
        instance->inside().get<std::string>("name")->set("RootName");
        rootGroup.add(instance);

        auto childInstance = tmpl.clone("Child");
        childInstance->inside().get<std::string>("name")->set("ChildName");
        instance->add(childInstance);

        print(rootGroup);
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }
    return 0;
}
```

## Examples
The repository includes several examples demonstrating how to use the TreeCode library. You can find them in the `examples` directory. To build and run the examples, use the following commands:
```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build --config Release
./build/bin/ExampleExecutable
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request. Make sure to follow the coding style and include tests for any new features or bug fixes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
