# TreeCode Project

![Build Status](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/CMake-Build.yml/badge.svg)
[![CodeQL](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/codeql.yml)
![GitHub License](https://img.shields.io/github/license/amr-m-abdelgawad/TreeCode)
![Static Badge](https://img.shields.io/badge/%40-Amr_MOUSA_2025-blue)

TreeCode is a C++ library for managing hierarchical data structures. It includes classes for containers, elements, groups, templates.

## Features
- Efficient tree traversal algorithms
- Tree manipulation functions
- Support for different types of trees (binary, AVL, etc.)

## Installation
To install the project, clone the repository and follow the build instructions:
```bash
git clone https://github.com/amr-m-abdelgawad/TreeCode.git
cd TreeCode
cmake -B build
cmake --build build --config Release
```

## Usage
Here is an example of how to use the TreeCode library:
```cpp
#include "core/includes/group.hpp"
#include "core/includes/template.hpp"

int main() {
    TreeCode::groupTemplate treeTemplate("ExampleTemplate");

    auto rootGroup = std::make_shared<TreeCode::group>("Root");
    treeTemplate.addGroup(rootGroup);

    auto childGroup = std::make_shared<TreeCode::group>("Child");
    rootGroup->addChild(std::move(childGroup));

    auto instance = treeTemplate.createInstance();
    return 0;
}
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License.
