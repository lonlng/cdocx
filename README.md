<p align="center"><img src="https://github.com/amiremohamadi/DuckX/blob/master/img/logo.png" width="380"></p>

[![Build Status](https://travis-ci.com/amiremohamadi/DuckX.svg?branch=master)](https://travis-ci.com/amiremohamadi/DuckX)
[![GitHub license](https://img.shields.io/github/license/amiremohamadi/duckx)](https://github.com/amiremohamadi/duckx/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/v/release/amiremohamadi/duckx)](https://github.com/amiremohamadi/DuckX/releases)
[![Twitter follow](https://img.shields.io/twitter/follow/amiremohamadi?style=social)](https://twitter.com/amiremohamadi)


# CDocx

Create, read and write Microsoft Office Word docx files.
More informations are available in [this](https://duckx.readthedocs.io/en/latest/) documentation.


> CDocx was created when I was looking for a C++ library which can properly parse MS Word .docx files, but couldn't find any

## Status ##

- Documents (docx) [Word]
	- Read/Write/Edit
	- Change document properties

## Quick Start

Here's an example of how to use CDocx to read a docx file; It opens a docx file named **file.docx** and goes over paragraphs and runs to print them:
```c++
#include <iostream>
#include <cdocx.hpp>

int main() {

    cdocx::Document doc("file.docx");   

    doc.open();

    for (auto p : doc.paragraphs())
	for (auto r : p.runs())
            std::cout << r.get_text() << std::endl;
}
```

<br/>
And compile your file like this:

```bash
g++ sample1.cpp -lcdocx
```

* See other [Examples](https://github.com/amiremohamadi/DuckX/tree/master/samples)

### Template Replacement Example

CDocx includes powerful template replacement features. Here's an example that demonstrates 
employee performance report generation:

```cpp
#include <cdocx.h>

int main() {
    // Open a template document with placeholders
    cdocx::Document doc("template.docx");
    doc.open();
    
    // Create template processor
    cdocx::Template tmpl(&doc);
    
    // Set placeholder values
    tmpl.set("employee_name", "Alice Johnson");
    tmpl.set("department", "Engineering");
    tmpl.set("rating", "5");
    
    // Replace all placeholders in the document
    tmpl.replace_all();
    
    // Save the generated document
    doc.save("output.docx");
}
```

For a complete example with batch processing, custom patterns, and advanced features, 
see the [Employee Report Template Sample](https://github.com/amiremohamadi/DuckX/tree/master/samples/employee_report_template.cpp).


## Install ##

Easy as pie!

#### Compiling

The preferred way is to create a build folder
```bash
git clone https://github.com/amiremohamadi/DuckX.git
cd DuckX
mkdir build
cd build
cmake ..
cmake --build .
```

## Requirements ##

- [zip](https://github.com/kuba--/zip)
- [pugixml](https://github.com/zeux/pugixml)


### Donation
> Please consider donating to sustain our activities.
<p align="left"><img src="img/btcqr.png" width="280"></p>

BITCOIN: bc1qex0wdwp22alnmvncxs3gyj5q5jaucsvpkp4d6z


### Licensing

This library is available to anybody free of charge, under the terms of MIT License (see LICENSE.md).
