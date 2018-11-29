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
class AdminMenuGuiSpawn extends ScriptedWidgetEventHandler
{
	protected Widget						m_Root;
	protected AdminMenuGui					m_Menu;
	TextListboxWidget m_classList;
	EditBoxWidget m_Spawn_SearchBox;
	protected ButtonWidget m_Spawn_btnSpawnGround;
	protected ButtonWidget m_Spawn_btnSpawnCursor;
	protected ButtonWidget m_Spawn_btnSpawnInventory;
	protected ButtonWidget m_Spawn_btnCancel;
	protected EditBoxWidget m_Spawn_QuantityItem;
	ItemPreviewWidget m_item_widget;

	//private ItemPreviewWidget m_item_widget;
	protected EntityAI previewItem;
	private int m_characterRotationX;
	private int m_characterRotationY; // Borrowed from inspectmenu
	private int m_characterScaleDelta;
	private vector m_characterOrientation;

	protected EditBoxWidget m_Spawn_editBox;
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void AdminMenuGuiSpawn( Widget parent, AdminMenuGui menu )
	{
		
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_spawn.layout", parent );
			
		m_Menu						= menu;
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_classList = TextListboxWidget.Cast( m_Root.FindAnyWidget( "classlist" ) );
		m_Spawn_SearchBox = EditBoxWidget.Cast( m_Root.FindAnyWidget( "search_input" ) );
		m_Spawn_btnSpawnGround = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_spawn_ground" ) );
		m_Spawn_btnSpawnCursor = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_spawn_cursorpos" ) );
		m_Spawn_btnSpawnInventory = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_spawn_inventory" ) );
		m_Spawn_btnCancel = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_cancel" ) );
		m_item_widget = ItemPreviewWidget.Cast( m_Root.FindAnyWidget( "ItemPrev" ) );
		m_Spawn_QuantityItem = EditBoxWidget.Cast( m_Root.FindAnyWidget( "quantity_items" ) );
		
		m_Spawn_editBox = m_Root.FindAnyWidget("className_spawner_box");
		
		UpdateList( "All" )
	}
	
	//TODO
	bool Click( Widget w, int x, int y, int button )
	{
	    string strSelection = GetCurrentSelection();
	    bool ai = false;
		
		int quantity = 0;
		string text = "";
		ItemBase oItem = NULL;
		string ai_new = ""
		if ( strSelection == "" ) 
		{
			strSelection = GetEditBoxInput();
		}

        if( strSelection != "" )
        {
        	strSelection.ToLower();
        	//ObjectEditor obEditor = GetModuleManager().GetModule( ObjectEditor );
        	if ( GetGame().IsKindOf( strSelection, "DZ_LightAI" ) ) 
        	{
        		ai = true;
				ai_new = "true"
        	}

            if( w == m_Spawn_btnSpawnCursor )
            {
                
				text = m_Spawn_QuantityItem.GetText();
				
				ScriptRPC Cursor_rpc = new ScriptRPC();
				Cursor_rpc.Write(strSelection);
				Cursor_rpc.Write(GetCursorPos())
				Cursor_rpc.Write(ai_new);
				Cursor_rpc.Write(text)
				Cursor_rpc.Send(NULL, M_RPCs.M_Admin_Menu_Spawn_Cursor, false, NULL);
				
				
				
				
				
				
					text = m_Spawn_QuantityItem.GetText();

            }
            else if ( w == m_Spawn_btnSpawnGround )
            {	
				EntityAI oObj = g_Game.CreateObject( strSelection, GetGame().GetPlayer().GetPosition(), false, ai );
				text = m_Spawn_QuantityItem.GetText();
				//RPC Build and Send
				ScriptRPC rpc = new ScriptRPC();
				rpc.Write(strSelection);
				rpc.Write(ai_new);
				rpc.Write(text)
				rpc.Send(NULL, M_RPCs.M_Admin_Menu_Spawn_Ground, false, NULL);

            }
            else if ( w == m_Spawn_btnSpawnInventory )
            {
					text = m_Spawn_QuantityItem.GetText();
				//RPC Build and Send
				ScriptRPC Inventory_rpc = new ScriptRPC();
				Inventory_rpc.Write(strSelection);
				Inventory_rpc.Write(ai_new);
				Inventory_rpc.Write(text)
				Inventory_rpc.Send(NULL, M_RPCs.M_Admin_Menu_Spawn_Inventory, false, NULL);
            }
        }
		if ( w.GetName().Contains( "btn_spawn_filter" ) ) 
        {
        	string buttonName = w.GetName();
        	buttonName.Replace("btn_spawn_filter_", "");
        	UpdateList( buttonName );

        	return true;
        }

        return false;
	}
	
	void UpdateList( string classFilter ) // All default
    {
        m_classList.ClearItems();
		TStringArray configs = new TStringArray;
		configs.Insert( CFG_VEHICLESPATH );
		configs.Insert( CFG_WEAPONSPATH );
		configs.Insert( CFG_MAGAZINESPATH );

        string strSearch = m_Spawn_SearchBox.GetText();

		strSearch.ToLower();

		for ( int nConfig = 0; nConfig < configs.Count(); ++nConfig )
		{
			string strConfigPath = configs.Get( nConfig );

			int nClasses = g_Game.ConfigGetChildrenCount( strConfigPath );

			for ( int nClass = 0; nClass < nClasses; ++nClass )
			{
				string strName;

				g_Game.ConfigGetChildName( strConfigPath, nClass, strName );

				int scope = g_Game.ConfigGetInt( strConfigPath + " " + strName + " scope" );

				if ( scope == 0 )
				{
					continue;
				}

				if ( strName == "Mag_Scout_5Rnd") continue; // fix crash for this dumb item. dont spawn it

				string strNameLower = strName;

				strNameLower.ToLower();

				if ( GetGame().IsKindOf( strNameLower, classFilter ) || classFilter == "All" ) // Fix for weapon_base not being child of "All"
				{
					
					if ( (strSearch != "" && (!strNameLower.Contains( strSearch ))) ) 
					{
						continue;
					}

					if ( strName == "ItemOptics" ) 
					{
						continue; // Fix crash
					}
					
					m_classList.AddItem( strName, NULL, 0 );
				}
			}
		}
    }
	
	string GetCurrentSelection()
	{
		if ( m_classList.GetSelectedRow() != -1 )
		{
			string result;
			m_classList.GetItemText( m_classList.GetSelectedRow(), 0, result );
			return result;
		}

		return "";
	}
	
	string GetEditBoxInput() 
	{
		return m_Spawn_editBox.GetText();
	}
	
	bool OnItemSelect( Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		
			if ( w == m_classList ) 
			{
				EntityAI item;
				item = g_Game.CreateObject( GetCurrentSelection(), vector.Zero, false, false, false );
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Spawn_ItemPrev, new Param1<string>( GetCurrentSelection() ), false, NULL );
				if (item)
				{
					//InspectMenuNew.UpdateItemInfo(m_Root, item);

					if (!m_item_widget)
					{
						if (m_item_widget)
						{
							float l;
							float h;
							m_item_widget.GetSize(l, h);
							m_item_widget = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, m_item_widget) );
						}
					}
					
					m_item_widget.SetItem(item);
					m_item_widget.SetView( item.GetViewIndex() );
					m_item_widget.SetModelPosition(Vector(0,0,1));
					
					float v, c;		
					m_item_widget.GetPos(v, c);

					m_item_widget.SetSize( 1.75, 1.75 );
				
					// align to center 
					m_item_widget.SetPos( -0.375, -0.375 );
					
					//m_item_widget.SetModelOrientation
					//PPEffects.SetBlurInventory(1);
				}
				return true;
			}
		return true;
		
	}
	
	void OnItemSelect2(EntityAI item)
	{
		


				if (item)
				{
					//InspectMenuNew.UpdateItemInfo(m_Root, item);

					if (!m_item_widget)
					{
						Widget preview_frame = m_Root.FindAnyWidget("ItemPrev");
						if (preview_frame)
						{
							float l;
							float h;
							preview_frame.GetSize(l, h);
							m_item_widget = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
						}
					}
					
					m_item_widget.SetItem(item);
					m_item_widget.SetView( item.GetViewIndex() );
					m_item_widget.SetModelPosition(Vector(0,0,1));
					
					float v, c;		
					m_item_widget.GetPos(v, c);

					m_item_widget.SetSize( 1.75, 1.75 );
				
					// align to center 
					m_item_widget.SetPos( -0.375, -0.375 );
					
					//m_item_widget.SetModelOrientation
					PPEffects.SetBlurInventory(1);
				}
	}
	
	override bool OnMouseButtonDown( Widget w, int x, int y, int button ) 
	{
		if (w == m_item_widget)
		{
			GetGame().GetDragQueue().Call(this, "UpdateRotation");
			g_Game.GetMousePos(m_characterRotationX, m_characterRotationY);
			return true;
		}
		return false;
	}
	
	override bool OnMouseWheel( Widget w, int x, int y, int wheel ) 
	{
		if ( w == m_item_widget )
		{
			GetGame().GetDragQueue().Call(this, "UpdateScale");
			m_characterScaleDelta = wheel ;
		}
		return false;
	}
	
	void UpdateScale(int mouse_x, int mouse_y, int wheel, bool is_dragging) // Borrowed from inspect menu
	{
		float w, h, x, y;		
		m_item_widget.GetPos(x, y);
		m_item_widget.GetSize(w,h);
		w = w + ( m_characterScaleDelta / 4);
		h = h + ( m_characterScaleDelta / 4 );
		if ( w > 0.5 && w < 4 )
		{
			m_item_widget.SetSize( w, h );
	
			//align to center 
			int screen_w, screen_h;
			GetScreenSize(screen_w, screen_h);
			float new_x = x - ( m_characterScaleDelta / 8 );
			float new_y = y - ( m_characterScaleDelta / 8 );
			m_item_widget.SetPos( new_x, new_y );
		}
	}
	
	void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging) // Borrowed from inspect menu
	{
		vector o = m_characterOrientation;
		o[0] = o[0] + (m_characterRotationY - mouse_y);
		o[1] = o[1] - (m_characterRotationX - mouse_x);
		
		m_item_widget.SetModelOrientation( o );
		
		if (!is_dragging)
		{
			m_characterOrientation = o;
		}
	}
	
	void ~AdminMenuGuiSpawn()
	{
		if ( previewItem ) 
		{
			GetGame().ObjectDelete( previewItem );
			delete m_item_widget
		}
	}
	
	void Focus()
	{
		
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
        if ( w == m_Spawn_SearchBox )
        {
            UpdateList( "All" );
            return true;
        }

        return false;
    }
	
	bool OnMouseLeave( Widget w, Widget enterW, int x, int y ) 
    {
    	if ( w == m_Spawn_SearchBox ) 
    	{
    		GetPlayer().GetInputController().OverrideMovementSpeed( false, 0 );
    	}
    	return false;
    }
	
	bool OnMouseEnter( Widget w , int x, int y ) 
    {
    	if ( w == m_Spawn_SearchBox ) 
    	{
    		GetPlayer().GetInputController().OverrideMovementSpeed( true, 0 );
    	}
    	return false;
    }
	
	void Message( string txt ) 
	{
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}

	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		switch(rpc_type)
		{
			
			case M_RPCs.M_Admin_Menu_Spawn_ItemPrev_ok:

				EntityAI PrevItem;
				ctx.Read(PrevItem);
				SetItem(PrevItem);
				
			break;
		}
	}
	
	void SetItem(EntityAI item)
	{
		if (item)
		{
			//InspectMenuNew.UpdateItemInfo(m_Root, item);
			//delete m_item_widget;
			if (item == NULL)
			{
				item = GetGame().CreateObject( "WaterBottle", vector.Zero, false, false );
			}
			if (!m_item_widget)
			{
				Widget preview_frame = m_Root.FindAnyWidget("ItemPrev");
				if (preview_frame)
				{
					float w;
					float h;
					preview_frame.GetSize(w, h);
					m_item_widget = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
				}
			}
			
			m_item_widget.SetItem(item);
			m_item_widget.SetView( item.GetViewIndex() );
			m_item_widget.SetModelPosition(Vector(0,0,1));
			
			float x, y;		
			m_item_widget.GetPos(x, y);

			m_item_widget.SetSize( 1.75, 1.75 );
		
			// align to center 
			m_item_widget.SetPos( -0.375, -0.375 );
			
			//m_item_widget.SetModelOrientation
			//PPEffects.SetBlurInventory(1);
		}
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( m_Menu )
			m_Menu.OnFocus( w, x, y );
		if( w )
		{
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p )
			{
				return true;
			}
		}
		return ( w != null );
		
		
	}
	
	
}
