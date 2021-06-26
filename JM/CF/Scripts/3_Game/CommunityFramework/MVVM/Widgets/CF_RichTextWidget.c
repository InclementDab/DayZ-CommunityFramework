class CF_RichTextWidget : CF_TextWidget
{
	reference string ContentHeight;
	reference string ContentOffset;
	reference string ContentSnapToLine;
	reference string LineWidths;

	protected RichTextWidget _RichTextWidget;
	protected bool _ContentSnapToLine;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(ContentHeight, "ContentHeight");
		AddProperty(ContentOffset, "ContentOffset");
		AddProperty(ContentSnapToLine, "ContentSnapToLine");
		AddProperty(LineWidths, "LineWidths");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RichTextWidget, w);
	}

	void OnView_ContentHeight(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, ContentHeight, 0, _RichTextWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase model, CF_Event evt)
	{
		OnView_ContentHeight(model, evt);
	}

	void OnView_ContentOffset(CF_ModelBase model, CF_Event evt)
	{
		float _value = _RichTextWidget.GetContentOffset();
		EnScript.SetClassVar(model, ContentOffset, 0, _value);
	}

	void OnModel_ContentOffset(CF_ModelBase model, CF_Event evt)
	{
		float _value;
		EnScript.GetClassVar(model, ContentOffset, 0, _value);
		_RichTextWidget.SetContentOffset(_value, _ContentSnapToLine);
	}

	void OnView_ContentSnapToLine(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
	}

	void OnModel_ContentSnapToLine(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
		_RichTextWidget.SetContentOffset(_RichTextWidget.GetContentOffset(), _ContentSnapToLine);
	}

	void OnView_LineWidths(CF_ModelBase model, CF_Event evt)
	{
		array<float> _value;
		EnScript.GetClassVar(model, LineWidths, 0, _value);

		_value.Clear();
		for (int i = 0; i < _RichTextWidget.GetNumLines(); i++)
		{
			_value.Insert(_RichTextWidget.GetLineWidth(i));
		}
	}

	void OnModel_LineWidths(CF_ModelBase model, CF_Event evt)
	{
		OnView_LineWidths(model, evt);
	}
};
