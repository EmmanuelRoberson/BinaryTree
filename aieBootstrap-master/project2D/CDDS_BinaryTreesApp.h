#include "BinaryTree.h"
#include "Application.h"
#include "Font.h"

class CDDS_BinaryTreesApp : public aie::Application
{
protected:

	aie::Font* g_systemFont = nullptr;

	BinaryTree			m_binaryTree;
	TreeNode*			m_selectedNode;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			g_systemFont;

public:

	bool startup() override;

	void update(float deltaTime) override;

	void draw() override;

	void shutdown() override;

};