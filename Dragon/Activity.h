#pragma once
#include "UI.h"
#include <string>


class Tiny2D;

class Activity : public ViewGroup
{
public:
	Activity(string id);
	
	//Override
	void AcceptEvent(ivec2 mousePosition, MouseMotion mouseMotion);
	void AcceptEvent(int keyCode, KeyMotion keyMotion);
	void AcceptEvent(unsigned int codePoint);
	bool isInitLayout(void) { return m_isInitLayout; }
	void RequestFocus(View *view) { m_focusView = view; }

	virtual void OnCreate(void) { m_isInitLayout = true; }

private:
	bool m_isInitLayout;
	View *m_focusView;
	View *m_preFocusView;
};

class DragonActivity : public Activity
{
protected:
	TextView *m_texView;
	Button *m_btnAddClip;
	Button *m_btnExport;
	Button *m_btnImport;
	ClipBar *m_clipBar;
	ListView *m_listView;
	EditText *m_editPath;

public:
	DragonActivity(string id);
	virtual void OnCreate();
};

class AddClipListener : public MouseListener
{
private:
	ClipBar *m_clip;
	ListView *m_lstView;

public:
	AddClipListener(ClipBar *clip, ListView *lstView);

	virtual bool onMouse(View &view, const Event &e);
};

class ImportModelListener : public MouseListener
{
private:


public:
	virtual bool onMouse(View &view, const Event &e);
};