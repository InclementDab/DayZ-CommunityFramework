modded class ModLoader
{	
	override static array<ref ModStructure> GetMods()
	{
		//if( !m_Loaded )
			LoadMods();
		return m_Mods;
	}
	
	override static void LoadMods()
	{
		m_Mods = new array<ref ModStructure>;
		
		int mod_count = GetGame().ConfigGetChildrenCount( "CfgMods" );
		
		for( int i = 0; i < mod_count; i++ )
		{
			string mod_name;
			GetGame().ConfigGetChildName( "CfgMods", i, mod_name );
			m_Mods.Insert( new ModStructure( i, "CfgMods " + mod_name ) );
		}
		
		m_Loaded = true;
	}
}