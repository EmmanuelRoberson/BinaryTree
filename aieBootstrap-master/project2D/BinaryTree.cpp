#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
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

		while (curr != nullptr)
		{
			if (a_nValue > curr->getData())
			{
				parent = curr;
				curr = curr->getRight();
			}
			else if (a_nValue < curr->getData())
			{
				parent = curr;
				curr = curr->getLeft();
			}
			else if (curr->getData() == a_nValue)
				return;
		}

		if (a_nValue < parent->getData())
			parent->setLeft(temp);
		else if (a_nValue > parent->getData())
			parent->setRight(temp);

	}
}

void BinaryTree::remove(int a_nValue)
{
	TreeNode* curr = m_pRoot;
	TreeNode* parent = m_pRoot;

	TreeNode** ppOut = &curr;
	TreeNode** ppParent = &parent;
	

	if (findNode(a_nValue, ppOut, ppParent))
	{
		if (curr->hasRight())
		{
			TreeNode* iterCurr = (*ppOut);
			TreeNode* iterParent = (*ppParent);

			// the next if and while statements are the ' go right, then B-line'

			//moves curr right if it has one
			if (iterCurr->hasRight())
			{
				iterParent = iterCurr;
				iterCurr = iterCurr->getRight();
			}

			//moves it all the way left, and keeps parent trailing
			//also works if it doesnt have a left problem
			while (iterCurr->hasLeft())
			{
				iterParent = iterCurr;
				iterCurr = iterCurr->getLeft();
			}

			//copies value from minimum node to current node
			curr->setData(iterCurr->getData());

			if (iterParent->getLeft() == iterCurr)
			{
				//sets the minimum's right to minimum's parent's left
				iterParent->setLeft(iterCurr->getRight());
			}
			else if (iterParent->getRight() == iterCurr)
			{
				//sets the minimum's right to minimum's parent's right
				iterParent->setRight(iterCurr->getRight());
			}

			delete iterCurr;
		}
		else
		{
			//if we are deleting the parent's left child
			if (parent->getLeft() == curr)
			{
				//sets curr's left to parent's left
				parent->setLeft(curr->getLeft());
			}
			else if (parent->getRight() == curr)
			{
				//sets curr's left to parent's right
				parent->setRight(curr->getLeft());
			}
			else if (m_pRoot == curr)
				m_pRoot = curr->getLeft();

			delete curr;
		}
	}
}

TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode* curr = m_pRoot;

	while (curr != nullptr)
	{
		if (curr->getData() > a_nValue)
		{
			if (curr->hasLeft())
				curr = curr->getLeft();
			else
				//if no value is found, then return the root
				return m_pRoot;
		}
		else if (curr->getData() < a_nValue)
		{
			if (curr->hasRight())
				curr = curr->getRight();
			else
				//if no value is found, then return the root
				return m_pRoot;
		}

		if (curr->getData() == a_nValue)
		{
			return curr;
		}
	}


}

void BinaryTree::draw(aie::Renderer2D* renderer, aie::Font* g_systemFont,TreeNode* selected)
{

	draw(renderer, m_pRoot, 640, 680, 640,  g_systemFont, selected);

}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	//TreeNode* curr = m_pRoot;
	//TreeNode* parent = curr;

	//ppOutNode = &curr;
	//ppOutParent = &parent;

	while (*ppOutNode != nullptr)
	{
		if ((*ppOutNode)->getData() < a_nSearchValue)
		{
			//checks to see if it is a dead end
			if ((*ppOutNode)->hasRight())
			{
				*ppOutParent = *ppOutNode;
				*ppOutNode = (*ppOutNode)->getRight();
			}
			else
				return false;
		}
		else if ((*ppOutNode)->getData() > a_nSearchValue)
		{
			//checks to see if it is a dead end
			if ((*ppOutNode)->hasLeft())
			{
				*ppOutParent = *ppOutNode;
				*ppOutNode = (*ppOutNode)->getLeft();
			}
			else
				return false;
		}
		else if ((*ppOutNode)->getData() == a_nSearchValue)
		{
			return true;
		}
	}

	return false;

}

void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode * pNode, int x, int y, int horizontalSpacing, aie::Font* g_systemFont, TreeNode * selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
					y - 80, horizontalSpacing, g_systemFont,selected);
		}

		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing,
					y - 80, horizontalSpacing, g_systemFont, selected);
		}

		pNode->draw(renderer, x, y, g_systemFont , (selected == pNode));
	}

}
