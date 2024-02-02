# TODO
## Description
	The project implements a simple To do list. A simple GUI is provided using a terminal.
# Components
	There are 3 main components in the project:
		1. ToDo class (impliments the entries).
		2. Table class (groups the entries together).
		3. GUI class (provides the gui).

	Together they make up a hierarchy each lvl depends on lvl above it.
# Demo
![Demo](https://github.com/BuDavid/ToDo/blob/master/images/Demo.png)

Entry colors represent their states:
	Red: Failed
	Green: Accomplished
	White: In progress

For more information the I| Info option can be used.

# How to use
```C++
#include "gui.hpp"

int main() {
	GUI obj;
	obj.start();
}
	
