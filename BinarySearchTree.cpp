
#include <iostream>
using namespace std;

struct Node
{
    Node * _pLeftNode;
    Node * _pRightNode;
    int _data;
};

class BinarySearchTree
{
public:
    BinarySearchTree(){}
    ~BinarySearchTree(){delete _pHeadNode;}

    void SetHeadNode(Node * pHeadNode){_pHeadNode = pHeadNode;}
    Node * GetHeadNode(){return _pHeadNode;}
    
    Node * CreateNewNode(int idata);
    void InsertNewNode(int iNodeData);
    
    // Tree Traversal
    void InOrderTraversal();
    void PostOrderTraversal();
    void PreOrderTraversal();
    
    void DeleteNodefromKey(int iNodedataTodelete);
    void SearchData(int iDataToSearch,bool &bdatafound);
private:
    Node * _Insert(Node * pNode, int idata);
    Node * _Search(Node * pNode, int idata, bool &found);
    Node * _Delete(Node * pNode, int idata);
    
    // Tree Traversal
    void _InOrder(Node * pNode);
    void _PostOrder(Node * pNode);
    void _PreOrder(Node * pNode);
    
    // Data Member
    Node * _pHeadNode;
};

Node * BinarySearchTree::CreateNewNode(int idata)
{
    Node * pNewNode = new Node();
    pNewNode->_data = idata;
    return pNewNode;
}

void BinarySearchTree::InsertNewNode(int iNodeData)
{
    if(!_pHeadNode)_pHeadNode = CreateNewNode(iNodeData);
    else _Insert(_pHeadNode,iNodeData);
}

void BinarySearchTree::InOrderTraversal()
{
    if(!_pHeadNode)return;
    _InOrder(_pHeadNode);
}

void BinarySearchTree::PostOrderTraversal()
{
    if(!_pHeadNode)return;
    _PostOrder(_pHeadNode);
}

void BinarySearchTree::PreOrderTraversal()
{
    if(!_pHeadNode)return;
    _PreOrder(_pHeadNode);
}

void BinarySearchTree::DeleteNodefromKey(int iNodedataTodelete)
{
    if(!_pHeadNode)return;
    _Delete(_pHeadNode,iNodedataTodelete);
}

void BinarySearchTree::SearchData(int iDataToSearch, bool & bdatafound)
{
    if(!_pHeadNode)return;
    _Search(_pHeadNode,iDataToSearch,bdatafound);
}

Node * BinarySearchTree::_Search(Node * pNode, int idata, bool &found)
{
    if(!pNode)return pNode;
    if(idata == pNode->_data)
    {
        found = true;
        return pNode;
    }
    
    if (idata > pNode->_data)
        pNode->_pRightNode = _Search(pNode->_pRightNode,idata,found);
    else if (idata < pNode->_data)
        pNode->_pLeftNode = _Search(pNode->_pLeftNode,idata,found);
    return pNode;
}

Node * BinarySearchTree::_Insert(Node * pNode, int idata)
{
    if(!pNode)
        return CreateNewNode(idata);
    if (idata > pNode->_data)
        pNode->_pRightNode = _Insert(pNode->_pRightNode,idata);
    else if (idata < pNode->_data)
        pNode->_pLeftNode = _Insert(pNode->_pLeftNode,idata);
    
    return pNode;
}


Node * BinarySearchTree::_Delete(Node * pNode, int idata)
{
    if(!pNode)return pNode;
    
    if(idata > pNode->_data)
    {
        pNode->_pRightNode =  _Delete(pNode->_pRightNode,idata);
        return pNode;
    }
    else if (idata < pNode->_data)
    {
        pNode->_pLeftNode = _Delete(pNode->_pLeftNode, idata);
        return pNode;
    }
    
    if (pNode->_pLeftNode == NULL)
    {
        Node* temp = pNode->_pRightNode;
        delete pNode;return temp;
    }
    else if (pNode->_pRightNode == NULL)
    {
        Node* temp = pNode->_pLeftNode;
        delete pNode;return temp;
    }
    else
    {
        Node* succParent = pNode;
        Node* succ = pNode->_pRightNode;
        while (succ->_pLeftNode != NULL)
        {
            succParent = succ;
            succ = succ->_pLeftNode;
        }
        
        if (succParent != pNode) succParent->_pLeftNode = succ->_pRightNode;
        else succParent->_pRightNode = succ->_pLeftNode;
        
        pNode->_data = succ->_data;
        delete succ;
        return pNode;
    }
}

void BinarySearchTree::_InOrder(Node * pNode)
{
    if(!pNode)return;
    _InOrder(pNode->_pLeftNode);
    cout << pNode->_data << endl;
    _InOrder(pNode->_pRightNode);
}

void BinarySearchTree::_PostOrder(Node * pNode)
{
    if(!pNode)return;
    _PostOrder(pNode->_pLeftNode);
    _PostOrder(pNode->_pRightNode);
    cout << pNode->_data << endl;
}

void BinarySearchTree::_PreOrder(Node * pNode)
{
    if(!pNode)return;
    cout << pNode->_data << endl;
    _PostOrder(pNode->_pLeftNode);
    _PostOrder(pNode->_pRightNode);
}

int main()
{
    int darr[] = {3,8,11,5,6,4,12,9};
    // Create a BST
    bool bIsFound = false;
    cout << "BST Class Created :"<< endl;
    BinarySearchTree * pBST = new BinarySearchTree();
    if(NULL == pBST)goto Escapeway;
    
    // Fill each elememt in BST
    cout << "Insert :"<< endl;
    for(int idx = 0; idx < 8; idx++)
        pBST->InsertNewNode(darr[idx]);
    
    // find An element in BST
    cout << "Search :"<< endl;
    pBST->SearchData(4,bIsFound);
    
    cout << "InOrder :"<< endl;
    pBST->InOrderTraversal();
    
    cout << "PostOrder :"<< endl;
    pBST->PostOrderTraversal();
    
    cout << "PreOrder :"<< endl;
    pBST->PreOrderTraversal();
    
    cout << "DeleteNode :"<< endl;
    pBST->DeleteNodefromKey(8);
    
    cout << "InOrder :"<< endl;
    pBST->InOrderTraversal();
    
    Escapeway:
    delete pBST;
    //delete pHead;
    
    return 0;
}

