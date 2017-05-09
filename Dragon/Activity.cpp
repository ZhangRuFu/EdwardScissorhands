#include "Activity.h"
#include "MeshManager.h"
#include "AnimationModelDrawer.h"
#include "AnimationController.h"

Activity::Activity(string id) : ViewGroup(this, id, ivec2(0, 0), View::Dimension::MATCH_PARENT, View::Dimension::MATCH_PARENT)
{
	m_isInitLayout = false;
	m_preFocusView = m_focusView = this;
}

void Activity::AcceptEvent(ivec2 mousePosition, MouseMotion mouseMotion)
{
	Event e;
	e.m_mousePosition = mousePosition;
	e.m_mouseMotion = mouseMotion;
	DispatchEvent(e);

	//焦点控件是否更换
	//if (m_focusView != m_preFocusView)
	//	cout << m_focusView->GetViewID() << endl;
}

void Activity::AcceptEvent(int keyCode, KeyMotion keyMotion)
{
	Event e(keyCode, keyMotion);
	if(m_focusView != nullptr)
		m_focusView->DispatchEvent(e);
}

void Activity::AcceptEvent(unsigned int codePoint)
{
	Event e(codePoint);
	if (m_focusView != nullptr)
		m_focusView->DispatchEvent(e);
}

DragonActivity::DragonActivity(string id) : Activity(id)
{
	
}

void DragonActivity::OnCreate(void)
{
	m_texView = new TextView(this, "texView", ivec2(10, 10), "Edward-Scissorhands v1.0");
	m_editPath = new EditText(this, "editPath", ivec2(10, 200), "Input Model Path:");
	m_btnImport = new Button(this, "btnImport", ivec2(10, 150), "ImportModel");
	m_btnAddClip = new Button(this, "btnClip", ivec2(10, 50), "AddClip");
	m_btnExport = new Button(this, "btnExport", ivec2(10, 100), "ExportXML");
	m_clipBar = new ClipBar(this, "clpBar", 10, ivec2(210, 10));
	m_listView = new ListView(this, "listView", ivec2(470, 10));

	AddClipListener *addClipListener = new AddClipListener(m_clipBar, m_listView);
	m_btnAddClip->SetMouseListener(addClipListener);
	ImportModelListener *importModelListener = new ImportModelListener();
	m_btnImport->SetMouseListener(importModelListener);

	AddView(m_btnImport);
	AddView(m_editPath);
	AddView(m_texView);
	AddView(m_btnAddClip);
	AddView(m_btnExport);
	AddView(m_clipBar);
	AddView(m_listView);
	
	Activity::OnCreate();
}

AddClipListener::AddClipListener(ClipBar * clip, ListView *lstView)
{
	m_clip = clip;
	m_lstView = lstView;
}

bool AddClipListener::onMouse(View & view, const Event & e)
{
	if (e.m_mouseMotion == MouseMotion::LeftButtonUp)
	{
		float start = m_clip->GetStartValue();
		float end = m_clip->GetEndValue();
		string clipName = m_clip->GetClipName();
		ClipItem *item = new ClipItem(view.GetActivity(), clipName, start, end);
		m_lstView->AddItem(item);
	}
	return true;
}

bool ImportModelListener::onMouse(View & view, const Event & e)
{
	if (e.m_mouseMotion == MouseMotion::LeftButtonUp)
	{
		EditText *editText = dynamic_cast<EditText*>(view.GetActivity()->FindViewByID("editPath"));
		string path = editText->GetText();
		SkeletonModel *model = dynamic_cast<SkeletonModel*>(MeshManager::LoadModel(path, "main"));
		//===============================内存泄漏=============================
		Transform *transform = new Transform();
		AnimationModelDrawer *drawer = AnimationModelDrawer::Create(model, transform);
		AnimationController *controller = new AnimationController(drawer, model, "main");
	}
	return true;
}
