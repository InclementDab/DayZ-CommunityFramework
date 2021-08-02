class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected ref CF_TypeConverter _Text = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Checked = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(Checked, "Checked");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		
		_Text.ToVariable(m_Model, Text);
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		
		_Text.FromVariable(m_Model, Text);
		_CheckBoxWidget.SetText(_Text.GetString());
	}

	void OnView_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Checked", "" + sender, args.ToStr());
		
		_Checked.SetBool(_CheckBoxWidget.IsChecked());
		_Checked.ToVariable(m_Model, Checked);
	}

	void OnModel_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Checked", "" + sender, args.ToStr());
		
		_Checked.FromVariable(m_Model, Checked);
		_CheckBoxWidget.SetChecked(_Checked.GetBool());
	}

	override bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
		CF_Trace trace(this, "OnChange", args.ToStr());

		if (!args.Continue)
		{
			_CheckBoxWidget.SetChecked(!_CheckBoxWidget.IsChecked());
		}

		NotifyPropertyChanged(Checked);

		return true;
	}
};
