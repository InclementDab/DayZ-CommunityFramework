modded class MissionServer
{
	void MissionServer()
	{
		bool enabled = GetGame().ServerConfigGetInt("cfDebugUI") != 0;
		CF_Debug.SetAllowed(enabled);

		GetRPCManager().AddRPC( "CF", "RecieveModList", this, SingeplayerExecutionType.Server );
	}

	void ~MissionServer()
	{
		CF_Debug.SetAllowed(false);
	}

	override void OnEvent( EventType eventTypeId, Param params ) 
	{
		super.OnEvent( eventTypeId, params );

		switch( eventTypeId )
		{
		case ClientPrepareEventTypeID:
			ClientPrepareEventParams clientPrepareParams;
			Class.CastTo(clientPrepareParams, params);
			CF_SendDebugUIState(clientPrepareParams.param1);
			break;
		case ClientNewEventTypeID:
			ClientNewEventParams newParams;
			Class.CastTo(newParams, params);
			CF_SendDebugUIState(newParams.param1);
			break;
		case ClientReadyEventTypeID:
			ClientReadyEventParams readyParams;
			Class.CastTo(readyParams, params);
			CF_SendDebugUIState(readyParams.param1);
			break;
		case ClientReadyEventTypeID:
			ClientReconnectEventParams reconnectParams;
			Class.CastTo(reconnectParams, params);
			CF_SendDebugUIState(reconnectParams.param1);
			break;
		case LogoutCancelEventTypeID:
			LogoutCancelEventParams logoutCancelParams;
			
			Class.CastTo( logoutCancelParams, params );

			auto logoutCancelArgs = new CF_EventPlayerArgs();
			Class.CastTo(logoutCancelArgs.Player, logoutCancelParams.param1);
			CF_ModuleWorldManager.OnClientLogoutCancelled(this, logoutCancelArgs);

			break;
		}
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		CF_ModuleCoreManager.OnSettingsChanged(this, CF_EventArgs.Empty);
		CF_ModuleCoreManager.OnMissionStart(this, CF_EventArgs.Empty);
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_ModuleCoreManager.OnMissionFinish(this, CF_EventArgs.Empty);
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		CF_ModuleCoreManager.OnMissionLoaded(this, CF_EventArgs.Empty);
	}

	override void OnUpdate( float timeslice )
	{
		CF_OnUpdate(timeslice);

		super.OnUpdate( timeslice );
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect( player, identity );

		CF_ModuleWorldManager.OnInvokeConnect(this, new CF_EventPlayerArgs(player, identity));
	}

	override void InvokeOnDisconnect( PlayerBase player )
	{
		super.InvokeOnDisconnect( player );

		CF_ModuleWorldManager.OnInvokeDisconnect(this, new CF_EventPlayerArgs(player));
	}

	override void OnClientReadyEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReadyEvent( identity, player );

		CF_ModuleWorldManager.OnClientReady(this, new CF_EventPlayerArgs(player, identity));
	}
	
	override void OnClientReconnectEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReconnectEvent( identity, player );

		CF_ModuleWorldManager.OnClientReconnect(this, new CF_EventPlayerArgs(player, identity));
	}
	
	override void OnClientRespawnEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientRespawnEvent( identity, player );

		CF_ModuleWorldManager.OnClientRespawn(this, new CF_EventPlayerArgs(player, identity));
	}
	
	override void OnClientDisconnectedEvent( PlayerIdentity identity, PlayerBase player, int logoutTime, bool authFailed )
	{
		super.OnClientDisconnectedEvent( identity, player, logoutTime, authFailed );

		auto args = new CF_EventPlayerDisconnectedArgs(player, identity);
		args.LogoutTime = logoutTime;
		args.AuthFailed = authFailed;

		CF_ModuleWorldManager.OnClientLogout(this, args);
	}

	override void PlayerDisconnected( PlayerBase player, PlayerIdentity identity, string uid )
	{
		auto args = new CF_EventPlayerDisconnectedArgs(player, identity);
		args.UID = uid;

		// must call before vanilla
		CF_ModuleWorldManager.OnClientDisconnect(this, args);

		super.PlayerDisconnected( player, identity, uid );
	}

	override PlayerBase OnClientNewEvent( PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		PlayerBase player = super.OnClientNewEvent( identity, pos, ctx );

		auto args = new CF_EventNewPlayerArgs(player, identity, pos, ctx);
		CF_ModuleWorldManager.OnClientNew(this, args);
		player = args.Player;

		return player;
	} 

	override void OnClientPrepareEvent( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		auto args = new CF_EventPlayerPrepareArgs();
		args.Identity = identity;
		args.UseDatabase = useDB;
		args.Position = pos;
		args.Yaw = yaw;
		args.PreloadTimeout = preloadTimeout;

		CF_ModuleWorldManager.OnClientPrepare(this, args);
		
		//identity = args.Identity;
		useDB = args.UseDatabase;
		pos = args.Position;
		yaw = args.Yaw;
		preloadTimeout = args.PreloadTimeout;

		// must call before vanilla
		super.OnClientPrepareEvent(identity, useDB, pos, yaw, preloadTimeout);
	}
};
