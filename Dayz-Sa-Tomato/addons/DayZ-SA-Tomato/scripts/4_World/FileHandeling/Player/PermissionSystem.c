	/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato, 
	however this File is Execludet from  GNU GENERAL PUBLIC LICENSE
	Version 3, 29 June 2007 since it is 
	
	Originally from DayZ-CommunityOnlineTools
	Link : https://github.com/Jacob-Mango/DayZ-CommunityOnlineTools
	Created by Jacob-Mango
	and Published under license (CC BY SA 4.0) http://creativecommons.org/licenses/by-sa/4.0/ 
    which means this file is under CC BY SA 4.0) http://creativecommons.org/licenses/by-sa/4.0/ Licence.
	*/
static ref FPPlayer ClientAuthPlayer;

static ref array< ref FPPlayer > SELECTED_PLAYERS;

ref array< ref FPPlayer > GetSelectedPlayers()
{
    if ( SELECTED_PLAYERS == NULL )
    {
        SELECTED_PLAYERS = new ref array< ref FPPlayer >;
    }
    return SELECTED_PLAYERS;
}

bool PlayerAlreadySelected( ref FPPlayer player )
{
    int position = GetSelectedPlayers().Find( player );

    return position > -1;
}

int RemoveSelectedPlayer( ref FPPlayer player )
{
	int position = GetSelectedPlayers().Find( player );

	if ( position > -1 )
	{
		GetSelectedPlayers().Remove( position );
	}

    return position;
}

int AddSelectedPlayer( ref FPPlayer player )
{
    int position = GetSelectedPlayers().Find( player );
    
    if ( position > -1 )
        return position;

    return GetSelectedPlayers().Insert( player );
}

ref PlayerDataN SerializePlayer( ref FPPlayer player )
{
    player.ToPermArray();

    return player.Data;
}

ref FPPlayer DeserializePlayer( ref PlayerDataN data )
{
    return GetFileHandler().GetPlayer( data );
}

array< ref PlayerDataN > SerializePlayers( ref array< ref FPPlayer > players )
{
    array< ref PlayerDataN > output = new array< ref PlayerDataN >;

    for ( int i = 0; i < players.Count(); i++)
    {
        output.Insert( SerializePlayer( players[i] ) );
    }

    return output;
}

array< ref FPPlayer > DeserializePlayers( ref array< ref PlayerDataN > players )
{
    array< ref FPPlayer > output = new array< ref FPPlayer >;

    for ( int i = 0; i < players.Count(); i++)
    {
        output.Insert( DeserializePlayer( players[i] ) );
    }

    return output;
}

ref array< string > SerializePlayersGUID( array< ref FPPlayer > players )
{
    ref array< string > output = new ref array< string >;

    for ( int i = 0; i < players.Count(); i++)
    {
        output.Insert( players[i].GetGUID() );
    }

    return output;
}

array< ref FPPlayer > DeserializePlayersGUID( ref array< string > guids )
{
    return GetFileHandler().GetPlayers( guids );
}