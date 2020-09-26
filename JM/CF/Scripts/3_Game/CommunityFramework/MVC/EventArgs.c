
// Event Args for Collection Changed
// 0: Collection that was changed
// 1: Collection Changed Action
// 2: Collection Changed Index
// 3: Collection Changed Value
class CollectionChangedEventArgs: Param4<Class, int, int, ref Param>
{
	Observable GetCollection() {
		return Observable.Cast(param1);
	}
	
	NotifyCollectionChangedAction GetChangedAction() {
		return param2;
	}
	
	int GetChangedIndex() {
		return param3;
	}
	
	Param GetChangedValue() {
		return param4;
	}
}



// Event Args for Property Changed
// 0: Name of property changed
// 1: New property value
class PropertyChangedEventArgs: Param2<string, Class>
{
	string GetPropertyName() {
		return param1;
	}
	
	Class GetPropertyValue() {
		return param2;
	}
}

// 0: Source Widget
// 1: Mouse Button
class ButtonCommandArgs: Param2<ButtonWidget, int>
{
	ButtonWidget GetButtonWidget() { 
		return param1; 
	}
	
	int GetMouseButton() {
		return param2;
	}
	
	bool GetButtonState() {
		return param1.GetState();
	}
}


// 0: Source Widget
// 1: CheckBox State
class CheckBoxCommandArgs: Param2<CheckBoxWidget, bool>
{
	CheckBoxWidget GetCheckBoxWidget() {
		return param1;
	}
	
	bool GetCheckBoxState() {
		return param2;
	}
}

// 0: Source Widget
// 1: Selected Item
class XComboBoxCommandArgs: Param2<XComboBoxWidget, int>
{
	XComboBoxWidget GetComboBoxWidget() {
		return param1;
	}
	
	int GetSelectedIndex() {
		return param2;
	}
}

// 0: Source Widget
// 1: Selected Widget
class WrapSpacerCommandArgs: Param2<WrapSpacerWidget, Widget>
{
	WrapSpacerWidget GetWrapSpacerWidget() {
		return param1;
	}
	
	Widget GetSelectedWidget() {
		return param2;
	}
}

