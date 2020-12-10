#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>

#include "graphedge.h"
#include "graphnode.h"
#include "chatbot.h"
#include "chatlogic.h"


ChatLogic::ChatLogic()
{
    //// STUDENT CODE
    ////

  	//task 5 - chatbot creation and etc not needed as part of chatlogic since it has to be created in LoadAnswerGraphFromFile
    // create instance of chatbot
    //_chatBot = new ChatBot("../images/chatbot.png");

    // add pointer to chatlogic so that chatbot answers can be passed on to the GUI
    //_chatBot->SetChatLogicHandle(this);

    ////
    //// EOF STUDENT CODE
}

ChatLogic::~ChatLogic()
{
    //// STUDENT CODE
    ////

    // delete chatbot instance
    //delete _chatBot;		//task 5 - since handling chatbot no more responsibility of chatlogic

	//task 3 -delete nodes not required since we have made them unique they get deleted automatically
  	/*
    // delete all nodes
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        delete *it;
    }
	*/
  	// Task 4 - not needed anymore as _edges is not used
  	/*
    // delete all edges
    for (auto it = std::begin(_edges); it != std::end(_edges); ++it)
    {
        delete *it;
    }
*/
    ////
    //// EOF STUDENT CODE
}

template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element)
{
    // find all occurences for current node
    auto token = tokens.begin();
    while (true)
    {
        token = std::find_if(token, tokens.end(), [&tokenID](const std::pair<std::string, std::string> &pair) { return pair.first == tokenID;; });
        if (token != tokens.end())
        {
            element.AddToken(token->second); // add new keyword to edge
            token++;                         // increment iterator to next element
        }
        else
        {
            break; // quit infinite while-loop
        }
    }
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename)
{
    // load file with answer graph elements
    std::ifstream file(filename);

    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            // extract all tokens from current line
            tokenlist tokens;
            while (lineStr.size() > 0)
            {
                // extract next token
                int posTokenFront = lineStr.find("<");
                int posTokenBack = lineStr.find(">");
                if (posTokenFront < 0 || posTokenBack < 0)
                    break; // quit loop if no complete token has been found
                std::string tokenStr = lineStr.substr(posTokenFront + 1, posTokenBack - 1);

                // extract token type and info
                int posTokenInfo = tokenStr.find(":");
                if (posTokenInfo != std::string::npos)
                {
                    std::string tokenType = tokenStr.substr(0, posTokenInfo);
                    std::string tokenInfo = tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

                    // add token to vector
                    tokens.push_back(std::make_pair(tokenType, tokenInfo));
                }

                // remove token from current line
                lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
            }

            // process tokens for current line
            auto type = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "TYPE"; });
            if (type != tokens.end())
            {
                // check for id
                auto idToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "ID"; });
                if (idToken != tokens.end())
                {
                    // extract id from token
                    int id = std::stoi(idToken->second);

                    // node-based processing
                    if (type->second == "NODE")
                    {
                        //// STUDENT CODE
                        ////

                        // check if node with this ID exists already
                        //auto newNode = std::find_if(_nodes.begin(), _nodes.end(), [&id](GraphNode *node) { return node->GetID() == id; });
						auto newNode = std::find_if(_nodes.begin(), _nodes.end(), [&id](const std::unique_ptr<GraphNode> &node) { return node->GetID() == id; });//task 3

                        // create new element if ID does not yet exist
                        if (newNode == _nodes.end())
                        {
                            //_nodes.emplace_back(new GraphNode(id));
                          	_nodes.emplace_back(std::make_unique<GraphNode>(id));//task 3
                            newNode = _nodes.end() - 1; // get iterator to last element

                            // add all answers to current node
                            AddAllTokensToElement("ANSWER", tokens, **newNode);
                        }

                        ////
                        //// EOF STUDENT CODE
                    }

                    // edge-based processing
                    if (type->second == "EDGE")
                    {
                        //// STUDENT CODE
                        ////

                        // find tokens for incoming (parent) and outgoing (child) node
                        auto parentToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "PARENT"; });
                        auto childToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "CHILD"; });

                        if (parentToken != tokens.end() && childToken != tokens.end())
                        {
                            // get iterator on incoming and outgoing node via ID search
                            auto parentNode = std::find_if(_nodes.begin(), _nodes.end(), [&parentToken](const std::unique_ptr<GraphNode> &node) { return node->GetID() == std::stoi(parentToken->second); }); //task 3
                            auto childNode = std::find_if(_nodes.begin(), _nodes.end(), [&childToken](const std::unique_ptr<GraphNode> &node) { return node->GetID() == std::stoi(childToken->second); }); //task 3
                          
	                         // create new edge
                            //GraphEdge *edge = new GraphEdge(id);
                            std::unique_ptr<GraphEdge> edge = std::make_unique<GraphEdge>(id);	//task 4 creating unique pointers of graph edge
                          	//edge->SetChildNode(*childNode);
                            edge->SetChildNode((*childNode).get());	//task 3
                          	//edge->SetParentNode(*parentNode);
                          	edge->SetParentNode((*parentNode).get()); //task 3
                            //_edges.push_back(edge);	//task 4 _edges need not be used anymore since we are transferring ownership to the graph nodes

                            // find all keywords for current node
                            AddAllTokensToElement("KEYWORD", tokens, *edge);

                            // store reference in child node and parent node
                            //(*childNode)->AddEdgeToParentNode(edge);
                          	(*childNode)->AddEdgeToParentNode(edge.get());	//task 4 passing the refernce only, not handle since parent edge of node is not owned by current node
                            (*parentNode)->AddEdgeToChildNode(std::move(edge));		//task 4 transfering handle to node, since child edges are owned by current node
                        }

                        ////
                        //// EOF STUDENT CODE
                    }
                }
                else
                {
                    std::cout << "Error: ID missing. Line is ignored!" << std::endl;
                }
            }
        } // eof loop over all lines in the file

        file.close();

    } // eof check for file availability
    else
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    //// STUDENT CODE
    ////

    // identify root node
    GraphNode *rootNode = nullptr;
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        // search for nodes which have no incoming edges
        if ((*it)->GetNumberOfParents() == 0)
        {

            if (rootNode == nullptr)
            {
                //rootNode = *it; // assign current node to root
                rootNode = (*it).get(); // assign current node to root //task 3
 
            }
            else
            {
                std::cout << "ERROR : Multiple root nodes detected" << std::endl;
            }
        }
    }

  	//task 5 - creating local chatbot instance
  	ChatBot ChatBot("../images/chatbot.png");
  	ChatBot.SetChatLogicHandle(this);	//setting current chatlogic as handle for chatbot
    // add chatbot to graph root node
    //_chatBot->SetRootNode(rootNode);
  	ChatBot.SetRootNode(rootNode);
  	//this->_chatBot = &ChatBot;
  	//rootNode->MoveChatbotHere(_chatBot);
  	rootNode->MoveChatbotHere(std::move(ChatBot));	//task 5 moving chatbot instance to root node
    //rootNode->MoveChatbotHere(chatbot);
    ////
    //// EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog)
{
    _panelDialog = panelDialog;
}

void ChatLogic::SetChatbotHandle(ChatBot *chatbot)
{
    _chatBot = chatbot;
}

void ChatLogic::SendMessageToChatbot(std::string message)
{
    _chatBot->ReceiveMessageFromUser(message);
}

void ChatLogic::SendMessageToUser(std::string message)
{
    _panelDialog->PrintChatbotResponse(message);
}

wxBitmap *ChatLogic::GetImageFromChatbot()
{
    return _chatBot->GetImageHandle();
}
