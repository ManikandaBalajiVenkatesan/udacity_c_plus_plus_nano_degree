#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include "chatbot.h"
#include <memory>

// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    //std::vector<GraphEdge *> _childEdges;  // edges to subsequent nodes
	std::vector<std::unique_ptr<GraphEdge>> _childEdges;
    // data handles (not owned)
    std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes 
    //ChatBot *_chatBot;
	ChatBot _chatBot;	//task 5 - since we are no more moving heap memory
    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    std::vector<std::string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _parentEdges.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    //void AddEdgeToChildNode(GraphEdge *edge);
	void AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge);	//task 4 since we will be passing unique pointer to save in child edges of current node
    //// STUDENT CODE
    ////

    //void MoveChatbotHere(ChatBot *chatbot);
    void MoveChatbotHere(ChatBot chatbot);	//task 5 - since we are not passing chatbot object on stack

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */