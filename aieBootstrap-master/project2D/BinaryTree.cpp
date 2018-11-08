#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

bool BinaryTree::isEmpty() const
{
	return (m_pRoot == nullptr);
}

void BinaryTree::insert(int a_nValue)
{
	TreeNode* temp;
	TreeNode* curr;
	TreeNode* parent;

	if (isEmpty())
		m_pRoot = new TreeNode(a_nValue);
	else
	{
		temp = new TreeNode(a_nValue);
		curr = m_pRoot;
	}


	while (curr != nullptr)
	{
		if (curr->getData() < a_nValue)
		{
			parent = curr;
			curr = curr->getLeft();
		}
		else if (curr->getData() > a_nValue)
		{
			parent = curr;
			curr = curr->getRight();
		}
		else if (curr->getData() == a_nValue)
			return;
	}

	if (a_nValue < parent->getData())
		parent->setLeft(temp);
	else if (a_nValue > parent->getData())
		parent->setRight(temp);

}

void BinaryTree::remove(int a_nValue)
{
	TreeNode** ppParent;
	TreeNode** ppOut;

	findNode(a_nValue, ppOut, ppParent);

	TreeNode* curr = *ppOut;
	TreeNode* parent = *ppParent;


	if (curr->hasRight())
	{
		TreeNode* iterCurr = *ppOut;
		TreeNode* iterParent = *ppParent;

		//moves curr right if it has one
		iterCurr = iterCurr->getRight();
		iterParent = iterCurr;

		//moves it all the way left, and keeps parent trailing
		while (iterCurr->hasLeft())
		{
			iterParent = iterCurr;
			iterCurr = iterCurr->getLeft();
		}

		//sets the the very left node value, to the current
		curr->setData(iterCurr->getData());

		if (iterParent->getLeft() == iterCurr)
		{
			//sets the iterCurr's right to iterParent's left
			iterParent->setLeft(iterCurr->getRight());
		}
		else if (iterParent->getRight() == iterCurr)
		{
			//sets the iterCurr's right to iterParent's right
			iterParent->setRight(iterCurr->getRight());
		}

		delete iterCurr;
	}
	else if (curr->hasLeft())
	{
		if (parent->getLeft() == curr)
		{
			//sets the Curr's right to Parent's left
			parent->setLeft(curr->getLeft());
		}
		else if (parent->getRight() == curr)
		{
			//sets the Curr's right to Parent's right
			parent->setRight(curr->getLeft());
		}

		delete curr;
	}
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* selected)
{

	draw(renderer, m_pRoot, 640, 680, 640, selected);

}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	TreeNode* curr = m_pRoot;
	TreeNode* parent;

	while (curr != nullptr)
	{
		if (curr->getData() < a_nSearchValue)
		{
			parent = curr;
			curr = curr->getLeft();
			ppOutNode = &curr;
			ppOutParent = &parent;
		}
		else if (curr->getData() > a_nSearchValue)
		{
			parent = curr;
			curr = curr->getRight();
			ppOutNode = &curr;
			ppOutParent = &parent;
		}
		else if (curr->getData() == a_nSearchValue)
			return true;
	}

	return false;

}

void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode * pNode, int x, int y, int horizontalSpacing, TreeNode * selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
					y - 80, horizontalSpacing, selected);
		}

		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
					y - 80, horizontalSpacing, selected);
		}

		pNode->draw(renderer, x, y, false, (selected == pNode));
	}

}
