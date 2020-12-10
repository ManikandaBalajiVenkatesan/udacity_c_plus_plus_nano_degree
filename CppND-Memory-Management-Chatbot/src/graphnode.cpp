#include "graphedge.h"
#include "graphnode.h"



GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

    //delete _chatBot; 

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}
/*
void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{
    _childEdges.push_back(edge);
}
*/
//task 4 - we will be storing unique pointers in child edges of current node
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));		
}



//// STUDENT CODE
////
/*
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    _chatBot->SetCurrentNode(this);
}
*/
//task 5 - since we are moving chatbot object on stack and not pointer
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    _chatBot = std::move(chatbot);	//task 5 - to convert lvalue into rvalue so that move assignment operator gets into action instead of copy assignment 
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
    //_chatBot = nullptr; // invalidate pointer at source
  	//newNode->MoveChatbotHere(std::move(_chatBot));	//since we move the chatbot object to new node 
  
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    //return _childEdges[index];
	return _childEdges[index].get();	//task 4 since we will return the refrence only 
    ////
    //// EOF STUDENT CODE
}