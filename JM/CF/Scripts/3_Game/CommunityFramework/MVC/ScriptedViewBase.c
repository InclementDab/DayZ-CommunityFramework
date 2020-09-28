

class ScriptedViewBase: ScriptedWidgetEventHandler
{
	
	// Enable verbose logging
	reference bool Debug_Logging;
	
	// Source Widget
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	// Source Widget Controller
	autoptr ref WidgetController m_WidgetController;
	WidgetController GetWidgetController() {
		return m_WidgetController;
	}
	
	void ScriptedViewBase()
	{
		Log(Type().ToString());
	}
	
	void ~ScriptedViewBase()
	{	
		Log("~" + Type().ToString());

		if (m_LayoutRoot && m_LayoutRoot.GetParent()) {
			m_LayoutRoot.Unlink();
		}
	}
		
	void OnWidgetScriptInit(Widget w)
	{
		Trace("OnWidgetScriptInit %1", w.GetName());
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
		
		m_WidgetController = MVC.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController) {
			Error("Could not find WidgetController for type %1\n\nOverride MVC.RegisterWidgetControllers to register custom WidgetControllers", m_LayoutRoot.GetTypeName());
			return;
		}
	}
	
	protected ScriptedViewBase m_ParentScriptedViewBase;
	ref ScriptedViewBase GetParent() {
		return m_ParentScriptedViewBase;
	}
	
	void SetParent(ScriptedViewBase parent) {
		m_ParentScriptedViewBase = parent;
	}
		
	ScriptedViewBase GetScriptedRoot()
	{
		ScriptedViewBase view_base = this;
		FindScriptedRoot(view_base);
		return view_base;
	}
	
	static void FindScriptedRoot(out ScriptedViewBase view_base) 
	{
		if (view_base && view_base.GetParent()) {
			view_base = view_base.GetParent();
			FindScriptedRoot(view_base);
		}
	}
	
	void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging) // || MVCLogLevel >= LogLevel.TRACE
			PrintFormat("[Trace] %1 - %2 ", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
//#endif
	}
	
	
	void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging) // || MVCLogLevel >= LogLevel.INFO
			PrintFormat("[Log] %1 - %2", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
//#endif
	}
	
	
	void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		string header = string.Format("[Error] %1", Type());
		Error2(header, msg);
		
#ifdef COMPONENT_SYSTEM
		Workbench.Dialog(header, msg);
#endif
	}	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Trace("OnClick: %1", w.GetName());
		return false;
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		Trace("OnModalResult: %1", w.GetName());
		return false;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) 
	{
		Trace("OnDoubleClick: %1", w.GetName());		
		return false;
	}
	
	override bool OnSelect(Widget w, int x, int y) 
	{
		Trace("OnSelect: %1", w.GetName());		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		Trace("OnItemSelected: %1", w.GetName());		
		return false;
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		Trace("OnFocus: %1", w.GetName());		
		return false;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		Trace("OnFocusLost: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		Trace("OnMouseEnter: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		Trace("OnMouseLeave: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		Trace("OnMouseWheel: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonDown: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonUp: %1", w.GetName());		
		return false;
	}

	override bool OnController(Widget w, int control, int value)
	{
		Trace("OnController: %1", w.GetName());
		return false;
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		Trace("OnKeyDown: %1", w.GetName());		
		return false;
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		Trace("OnKeyUp: %1", w.GetName());		
		return false;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		Trace("OnKeyPress: %1", w.GetName());		
		return false;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		Trace("OnChange: %1", w.GetName());		
		return false;
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		Trace("OnDrag: %1", w.GetName());		
		return false;
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		// Disabled bc it wont stfu
		//Trace("OnDragging: %1", w.GetName());
		return false;
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		// Disabled bc it wont stfu
		//Trace("OnDraggingOver: %1", w.GetName());
		return false;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDrop: %1 - Reciever: %2", w.GetName(), reciever.ToString());	
		return false;
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDropReceived: %1 - Reciever: %2", w.GetName(), reciever.ToString());		
		return false;
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		// Disabled bc it wont stfu
		//Trace("OnResize: %1", w.GetName());		
		return false;
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		Trace("OnChildAdd: %1", w.GetName());		
		return false;
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		Trace("OnChildRemove: %1", w.GetName());		
		return false;
	}
	
	override bool OnUpdate(Widget w)
	{
		// Disabled bc it wont stfu
		//Trace("OnUpdate: %1", w.GetName());		
		return false;
	}
}