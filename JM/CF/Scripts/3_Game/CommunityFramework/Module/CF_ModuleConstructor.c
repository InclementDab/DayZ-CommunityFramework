static autoptr CF_ModuleConstructor g_CF_ModuleConstructor = null;
	
class CF_ModuleConstructor
{
	private void CF_ModuleConstructor()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

		CF_ModuleCoreManager._OnCreate();
	}

	/**
	 * @note	We can safely guarantee the destructor is called on script reload, 
	 * 			we can't do the same for 'OnGameDestroy'.
	 */
	void ~CF_ModuleConstructor()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

		CF_ModuleCoreManager._OnDestroy();
	}

#ifdef CF_FUNC_OLD
	[CF_EventSubscriber(CF_ModuleConstructor._Init, CF_LifecycleEvents.OnGameCreate)]
#else
	[CF_EventSubscriber(ScriptCaller.Create(CF_ModuleConstructor._Init), CF_LifecycleEvents.OnGameCreate)]
#endif
	static void _Init()
	{
		if (g_CF_ModuleConstructor)
		{
			return;
		}
		
		g_CF_ModuleConstructor = new CF_ModuleConstructor();
	}

#ifdef CF_FUNC_OLD
	[CF_EventSubscriber(CF_ModuleConstructor._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
#else
	[CF_EventSubscriber(ScriptCaller.Create(CF_ModuleConstructor._Cleanup), CF_LifecycleEvents.OnGameDestroy)]
#endif
	static void _Cleanup()
	{
		g_CF_ModuleConstructor = null;
	}
};
