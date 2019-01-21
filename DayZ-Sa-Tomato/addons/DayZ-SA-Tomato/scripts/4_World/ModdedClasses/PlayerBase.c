	/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato.
	
    DayZ SA Tomato is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DayZ SA Tomato is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DayZ SA Tomato.  If not, see <https://www.gnu.org/licenses/>.
	*/
modded class PlayerBase
{
	ref FPPlayer authentiPlayer;

	ref DeathHandler m_DeathHandler;
	
    override void OnConnect()
    {
		m_DeathHandler = new ref DeathHandler;
        // TL().cons("Player connected: " + this.ToString());
        ref SurvivorBase m_SurBase = SurvivorBase.Cast(this);
        m_SurBase.SetPID(this.GetIdentity().GetPlainId());
        m_SurBase.SetPFullName(this.GetIdentity().GetName());
        
		// NEW STATS API
        // StatRegister("playtime");
        // StatRegister("dist");
		
		Debug.Log("Player connected:"+this.ToString(),"Connect");
		m_DeathHandler.ConnectHandler(this.GetIdentity());
		// NEW STATS API
		StatRegister("playtime");
		StatRegister("dist");
		
		m_PlayerOldPos = GetPosition();
		if( m_AnalyticsTimer )
			m_AnalyticsTimer.Run( 60, this, "UpdatePlayerMeasures", null, true );
		
    }
	override void EEKilled( Object killer )
	{
		PlayerBase	Killer_Playerbase;                       // Killer PlayerBase
		m_DeathHandler.KilledHandler(killer, this);
		
		if( GetBleedingManagerServer() ) delete GetBleedingManagerServer();
		
		
		
		// kill character in database
		if (GetHive())
		{
			GetHive().CharacterKill(this);
		}
	
		// disable voice communication
		GetGame().EnableVoN(this, false);
		
		
		
		GetSymptomManager().OnPlayerKilled();
		
		super.EEKilled(killer);
	}
	
	bool selfkill = false;
    void issic(bool Yep)
    {
        selfkill = Yep;
    }
	
    bool CanBeDeleted()
    {
        return IsAlive() && !IsRestrained() && !IsUnconscious();
    }
}