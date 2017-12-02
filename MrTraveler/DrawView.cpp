#include "stdafx.h"
#include "DrawView.h"


DrawView::DrawView()
{

}
DrawView::~DrawView()
{
}
void DrawView::StartView(CRect viewRect)
{
	this->viewRect = viewRect;
}
void DrawView::OnDraw(CDC * dc)
{

}
void DrawView::EndView()
{
	
}