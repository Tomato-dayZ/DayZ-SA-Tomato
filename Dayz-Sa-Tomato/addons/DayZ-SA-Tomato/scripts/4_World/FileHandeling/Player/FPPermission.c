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

class FPPermission
{
	ref FPPermission Parent;
    ref array< ref FPPermission > Children;
    string Name;
    PermissionType Type;
	
	
	void FPPermission( string name, ref FPPermission parent = NULL )
    {
        Name = name;
        Parent = parent;

        Type = PermissionType.DISALLOW;

        if ( Parent == NULL )
        {
            Type = PermissionType.DISALLOW;
        }

        Children = new ref array< ref FPPermission >;
    }
	
	void SetPermissionType(string name, PermissionType type)
	{
		Print("Permission");
		for ( int i = 0; i < Children.Count(); i++ )
		{
			Print("Name 1 = " + Name + " Name 2 = " + name);
			if(Children[i].Name == name)
			{
				Print("Permission Found Changeing");
				Children[i].SetPermissionInternal(type)
				return;
			}
		}
		

	}
	
	void SetPermissionInternal(PermissionType type)
	{
		Print("Type Set");
		Type = type;
	}
	
	void AddPermission( string inp, PermissionType permType = PermissionType.DISALLOW )
    {
        array<string> tokens = new array<string>;

        array<string> spaces = new array<string>;
        inp.Split( " = ", spaces );
		
        PermissionType type;
		for ( int i = 0; i < spaces.Count(); i++ )
		{Print(spaces[i]);}
        if (spaces.Count() == 2 )
        {
            if ( spaces[1].Contains( "1" ) )
            {
                type = PermissionType.ALLOW;
            } else if ( spaces[1].Contains( "0" ) )
            {
                type = PermissionType.DISALLOW;
            } else 
            {
                type = PermissionType.DISALLOW;
            }

            spaces[0].Split( "_", tokens );
        } else if ( spaces.Count() < 2 )
        {
            type = permType;

            inp.Split( "_", tokens );
        } else {
            Print( "Warning, permission line improperly formatted! Read as \"" + inp + "\" but meant to be in format \"Perm_Perm {n}\"." );
            return;
        }
        
        int depth = tokens.Find( Name );

        if ( depth > -1 )
        {
            AddPermissionInternal( tokens, depth + 1, type );
        } else 
        {
            AddPermissionInternal( tokens, 0, type );
        }
    }
	
	private ref FPPermission VerifyAddPermission( string name )
    {
        ref FPPermission nChild = NULL;

        for ( int i = 0; i < Children.Count(); i++ )
        {
            if ( name == Children[i].Name )
            {
                nChild = Children[i];
                break;
            }
        }
            
        if ( nChild == NULL )
        {
            nChild = new FPPermission( name, this );
            nChild.Type = PermissionType.DISALLOW;

            Children.Insert( nChild );
        }

        return nChild;
    }
	
	void ToPermArray( ref array< string > output, string prepend = "" )
    {
        for ( int i = 0; i < Children.Count(); i++ )
        {
            string serialize = prepend + Children[i].Name;
                //TODO " = "
            output.Insert( serialize + " = " + Children[i].Type );

            if ( Children[i].Children.Count() > 0 ) 
            {
                Children[i].ToPermArray( output, serialize + "_" );
            }
        }
    }
	
	bool HasPermission( string inp )
    {
        array<string> tokens = new array<string>;
        inp.Split( "_", tokens );

        if ( tokens.Count() == 0 ) return false;
        
        int depth = tokens.Find(Name);

        bool parentDisallowed = false;

        if ( Type == PermissionType.DISALLOW )
        {
            parentDisallowed = true;
        } 

        if ( depth > -1 )
        {
            return Check( tokens, depth + 1, parentDisallowed );
        } else 
        {
            return Check( tokens, 0, parentDisallowed );
        }
    }
	
	bool Check( array<string> tokens, int depth, bool parentDisallowed )
    {
        bool ifReturnAs = false;

        if ( Type == PermissionType.ALLOW )
        {
            ifReturnAs = true;
        }

        if ( Type == PermissionType.DISALLOW )
        {
            parentDisallowed = true;
        }

        if ( Type == PermissionType.ALLOW )
        {
            parentDisallowed = false;
        }

        if ( depth < tokens.Count() )
        {
            ref FPPermission nChild = NULL;

            for ( int i = 0; i < Children.Count(); i++ )
            {
                if ( Children[i].Name == tokens[depth] )
                {
                    nChild = Children[i]; 
                }
            }

            if ( nChild )
            {
                return nChild.Check( tokens, depth + 1, parentDisallowed );
            }
        }

        return ifReturnAs;
    }
	
	private ref FPPermission Get( array<string> tokens, int depth )
    {
        if ( depth < tokens.Count() )
        {
            ref FPPermission nChild = NULL;

            for ( int i = 0; i < Children.Count(); i++ )
            {
                if ( Children[i].Name == tokens[depth] )
                {
                    nChild = Children[i]; 
                }
            }

            if ( nChild )
            {
                return nChild.Get( tokens, depth + 1 );
            }
        }

        return this;
    }
	
	ref FPPermission GetPermission( string inp )
    {
        array<string> tokens = new array<string>;
        inp.Split( "_", tokens );
        
        int depth = tokens.Find(Name);

        if ( depth > -1 )
        {
            return Get( tokens, depth + 1 );
        } else 
        {
            return Get( tokens, 0 );
        }
    }
	
	private void AddPermissionInternal( array<string> tokens, int depth, PermissionType value )
    {
        if ( depth < tokens.Count() )
        {
            string name = tokens[depth];

            ref FPPermission nChild = VerifyAddPermission( name );

            nChild.AddPermissionInternal( tokens, depth + 1, value );
        } else {
            Type = value;
        }
    }
	
	
	void ~FPPermission()
    {
        delete Children;
    }
}