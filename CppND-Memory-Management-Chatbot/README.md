# CPPND: Memory Management Chatbot

This project deals with optimization of memory and management through effective implementation of smart pointers and memory ownership concepts in a chatbot application. The project starter code was provided by Udacity which contains the chatbot application code.

<img src="images/chatbot_demo.gif"/>

The ChatBot code creates a dialogue where users can ask questions about some aspects of memory management in C++. After the knowledge base of the chatbot has been loaded from a text file, a knowledge graph representation is created in computer memory, where chatbot answers represent the graph nodes and user queries represent the graph edges. After a user query has been sent to the chatbot, the Levenshtein distance is used to identify the most probable answer. The code is fully functional as-is and uses raw pointers to represent the knowledge graph and interconnections between objects throughout the project.

## Dependencies for Running Locally
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-dev libwxgtk3.0-0v5-dbg`
  * Mac: There is a [homebrew installation available](https://formulae.brew.sh/formula/wxmac).
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Some version numbers may need to be changed in instructions to install v3.0 or greater.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./membot`.

![](images/chatbot_output_gif.gif)

## Project Task Details

Core modifications done are as follows

1. The starter code will crash while closing the window, this is due to destructor of "ChatBot" being called twice.

2. Making object of "ChatLogic" class exclusive to "ChatbotPanelDialog" using smart pointers.

3. Implementing "Rule of Five" to ChatBot class.

4. Making objects of "GraphNodes" class exclusive to "ChatLogic" class's object.

5. Modification in GraphNode class so that each GraphNode class's object will have exclusive ownership to outgoing edges (objects of "GraphEdge" class) and reference to incoming edges. This is done using smart pointers and appropriate move semantics.

6. Modifying the code such that the object of "ChatBot" logic is created in chatlogic.cpp but it no longer holds responsible for its memory and instead it is being passed to the current node through move semantics and as the user interacts with the chatbot , that object moves to the latest node.

![](images/message_1.png) ![](images/message_2.png)
