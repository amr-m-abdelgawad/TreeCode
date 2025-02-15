# TreeCode Project

![MIT License](https://img.shields.io/github/license/amr-m-abdelgawad/TreeCode)
![Build Status](https://github.com/amr-m-abdelgawad/TreeCode/actions/workflows/CMake-Build.yml/badge.svg)

## Overview
TreeCode is a C++ library for managing hierarchical data structures. It includes classes for containers, elements, groups, templates, and logging. The library can be built as a shared library and includes options for building tests and examples.

## Features
- Efficient tree traversal algorithms
- Tree manipulation functions
- Support for different types of trees (binary, AVL, etc.)

## Installation
To install the project, clone the repository and follow the build instructions:
```bash
git clone https://github.com/yourusername/TreeCode.git
cd TreeCode
cmake -B build
cmake --build build --config release
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
