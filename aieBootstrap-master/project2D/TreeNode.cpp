#include "TreeNode.h"
#include <iostream>
#include "Font.h"

TreeNode::TreeNode(int value)
{
	m_value = value;
}

void TreeNode::draw(aie::Renderer2D* renderer, int x, int y, aie::Font* g_systemFont, bool selected = false)
{

	extern aie::Font* g_systemFont;

	static char buffer[10];

	sprintf_s(buffer, "%d", m_value);


	renderer->setRenderColour(1, 1, 0);
	renderer->drawCircle(x, y, 30);

	if (selected == true)
		renderer->setRenderColour(.5, .5, 0);
	else
		renderer->setRenderColour(0, 0, 0);
	renderer->drawCircle(x, y, 28);

	renderer->setRenderColour(1, 1, 1);
	renderer->drawText(g_systemFont, buffer, x - 12, y - 10);

}