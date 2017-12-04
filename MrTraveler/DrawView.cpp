#include "stdafx.h"
#include "DrawView.h"
#include "MrTravelerView.h"

DrawView::DrawView()
{

}
DrawView::~DrawView()
{
}
void DrawView::StartView(CRect viewRect , CMrTravelerView * parent)
{
	this->viewRect = viewRect;
	this->parentView = parent;

}
void DrawView::OnDraw(CDC * dc)
{

}
void DrawView::EndView()
{
	
}
void DrawView::OnLButtonDown(CPoint point) {}
void DrawView::OnRButtonDown(CPoint point) {}