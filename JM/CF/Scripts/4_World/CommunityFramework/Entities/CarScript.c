modded class CarScript
{
	autoptr CF_ModStorageBase m_CF_ModStorage = new CF_ModStorageObject<CarScript>(this);

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		m_CF_ModStorage.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}

		return m_CF_ModStorage.OnStoreLoad(ctx, version);
	}

	/**
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreSave
	 */
	void CF_OnStoreSave(CF_ModStorageMap storage)
	{
	}

	/**
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreLoad
	 */
	bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		return true;
	}
	
	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		return false;
	}
};
