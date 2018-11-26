modded class DayZSpectator 
{
	protected float forwardVelocity;
	protected float strafeVelocity;
	protected float altitudeVelocity;

	protected float yawVelocity;
	protected float pitchVelocity;

	protected float m_CamDrag = 0.95;

	protected float m_CamFOV = 1.0; // default FOV
	protected float m_TargetFOV = 1.0;
	protected float m_TargetRoll;
	protected float m_DistanceToObject;
	protected bool m_FollowTarget = false;
	protected bool m_FreezePlayer = false;
	protected bool m_OrbitalCam = false;
	protected bool m_FreezeCam = false;

	protected bool m_FreezeMouse = false;
	
	static float CAMERA_FOV = 1.0;
	static float CAMERA_TARGETFOV = 1.0;
	static float CAMERA_FOV_SPEED_MODIFIER = 6.0;
	static float CAMERA_SPEED = 2.0;
	static float CAMERA_MAXSPEED = 1.0;
	static float CAMERA_VELDRAG;
	static float CAMERA_MSENS = 0.8; // acceleration
	static float CAMERA_SMOOTH = 0.8; // drag

	static bool  CAMERA_DOF = false;
	static bool  CAMERA_AFOCUS = true;
	static float CAMERA_BLUR = 0.0; // modified via ui
	static float CAMERA_FLENGTH = 50.0; // modified via ui
	static float CAMERA_FNEAR = 50.0; // modified via ui
	static float CAMERA_FDIST = 0.0;
	static float CAMERA_DOFFSET = 0.0;

	static float CAMERA_SMOOTH_BLUR = 0.0;
	
	protected vector m_CamOffset;
	
	protected Object m_Target;
	protected vector m_TargetPos; // Static position
	
	protected float m_CurrentSmoothBlur;

	override void EOnFrame(IEntity other, float timeSlice) 
	{
		// zoom camera
		int i = GetMouseState( MouseState.WHEEL );

		if ( i != 0 ) 
		{
			if ( CTRL() ) 
			{
				vector ori = GetOrientation();
				m_TargetRoll = ori[2] - Math.RAD2DEG * i*0.06;
			}
			else 
			{
				m_TargetFOV-=i*0.06; // invert
				if ( m_TargetFOV < 0.01 ) 
				{
					m_TargetFOV = 0.01;
				}
			}
		}

		if ( m_CamFOV != m_TargetFOV ) 
		{
			m_CamFOV = Math.Lerp( m_CamFOV, m_TargetFOV, timeSlice*CAMERA_FOV_SPEED_MODIFIER );
			SetFOV( m_CamFOV );
		}

		vector oldOrient = GetOrientation();
		if ( oldOrient[2] != m_TargetRoll ) 
		{
			oldOrient[2] = Math.Lerp( oldOrient[2], m_TargetRoll, timeSlice*CAMERA_FOV_SPEED_MODIFIER );
			SetOrientation( oldOrient );
		}

		// Camera movement
		Input input = GetGame().GetInput();

		if ( !m_FreezeCam ) 
		{
			float forward = input.GetAction(UAMoveForward) - input.GetAction(UAMoveBack); // -1, 0, 1
			float strafe = input.GetAction(UATurnRight) - input.GetAction(UATurnLeft);

			float altitude = input.GetAction(UACarShiftGearUp) - input.GetAction(UACarShiftGearDown);
			altitudeVelocity = altitudeVelocity + altitude * CAMERA_SPEED * timeSlice;

			Math.Clamp( altitudeVelocity, -CAMERA_MAXSPEED, CAMERA_MAXSPEED);
			vector up = vector.Up * altitudeVelocity;

			vector direction = GetDirection();
			vector directionAside = vector.Up * direction;

			altitudeVelocity *= m_CamDrag;

			vector oldPos = GetPosition();

			forwardVelocity = forwardVelocity + forward * CAMERA_SPEED * timeSlice;
			strafeVelocity = strafeVelocity + strafe * CAMERA_SPEED * timeSlice;

			Math.Clamp ( forwardVelocity, -CAMERA_MAXSPEED, CAMERA_MAXSPEED);
			Math.Clamp ( strafeVelocity, -CAMERA_MAXSPEED, CAMERA_MAXSPEED);

			vector forwardChange = forwardVelocity * direction;
			vector strafeChange = strafeVelocity * directionAside;

			forwardVelocity *= m_CamDrag;
			strafeVelocity *= m_CamDrag;

			vector newPos = oldPos + forwardChange + strafeChange + up;

			float surfaceY = GetGame().SurfaceY( newPos[0], newPos[2] ) + 0.25;
			if ( newPos[1] < surfaceY ) 
			{
				newPos[1] = surfaceY;
			}

			SetPosition(newPos);
		}

		if ( !m_FreezeMouse ) 
		{
			float yawDiff = input.GetAction(UAAimHeadLeft) - input.GetAction(UAAimHeadRight);
			float pitchDiff = input.GetAction(UAAimHeadDown) - input.GetAction(UAAimHeadUp);

			yawVelocity = yawVelocity + yawDiff * CAMERA_MSENS;
			pitchVelocity = pitchVelocity + pitchDiff * CAMERA_MSENS; // 0.8

			vector newOrient = oldOrient;

			Math.Clamp ( yawVelocity, -1.5, 1.5);
			Math.Clamp ( pitchVelocity, -1.5, 1.5);

			newOrient[0] = newOrient[0] - Math.RAD2DEG * yawVelocity * timeSlice;
			newOrient[1] = newOrient[1] - Math.RAD2DEG * pitchVelocity * timeSlice;

			yawVelocity *= CAMERA_SMOOTH; // drag 0.9
			pitchVelocity *= CAMERA_SMOOTH;

			if( newOrient[1] < -89 )
				newOrient[1] = -89;
			if( newOrient[1] > 89 )
				newOrient[1] = 89;

			SetOrientation( newOrient );
		}


		// Camera targetting
		float dist = 0.0;
		vector from = GetGame().GetCurrentCameraPosition();

		if ( m_Target ) 
		{
			vector targetPos;
			
			if ( m_Target.IsInherited( SurvivorBase ) ) 
			{
				targetPos = GetTargetCenter();
			}
			else 
			{
				vector pos = m_Target.GetPosition();
				pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
				
				vector clippingInfo;
				vector objectBBOX;
				
				m_Target.GetCollisionBox(objectBBOX);
				
				pos[1] = (pos[1] - objectBBOX[1] + clippingInfo[1] - objectBBOX[1]) + 1.5;
				
				targetPos = pos;
			}
			
			if ( m_OrbitalCam ) 
			{
				LookAt( targetPos );
			}
			
			dist = vector.Distance( from, targetPos );
			
			if ( m_FollowTarget ) 
			{
				if ( m_DistanceToObject == 0.0 )
				{
					m_DistanceToObject = vector.Distance(GetTargetCenter(), GetPosition());
					m_CamOffset = vector.Direction( GetTargetCenter() , GetPosition() );
					m_CamOffset.Normalize();
				}
				
				if ( m_OrbitalCam ) 
				{
					direction = vector.Direction( GetTargetCenter() , GetPosition() );
					direction.Normalize();
					newPos = GetTargetCenter() + ( direction * m_DistanceToObject );
				} 
				else 
				{
					newPos = GetTargetCenter() + ( m_CamOffset * m_DistanceToObject );
				}
				
				SetPosition( newPos );
				dist = m_DistanceToObject;
			}
		}
		else if ( m_TargetPos != vector.Zero ) 
		{
			LookAt( m_TargetPos ); // auto orbital
			dist = vector.Distance( from, m_TargetPos );
		}
		
		if ( CAMERA_DOF ) // DOF enabled
		{
			if ( CAMERA_AFOCUS && !m_Target ) //auto focus
			{
				vector to = from + (GetGame().GetCurrentCameraDirection() * 9999);
				vector contact_pos;
				
				DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, NULL , NULL, NULL, false, false, ObjIntersectIFire);
				dist = vector.Distance( from, contact_pos );
			}
			if ( dist > 0 ) CAMERA_FDIST = dist;
			
			PPEffects.OverrideDOF(true, CAMERA_FDIST, CAMERA_FLENGTH, CAMERA_FNEAR, CAMERA_BLUR, CAMERA_DOFFSET);
		}
	}

	vector GetTargetCenter() 
	{
		vector targetPosition;
		
		if ( m_Target.IsInherited( SurvivorBase )) 
		{
			targetPosition = m_Target.GetPosition();
			targetPosition[1] = targetPosition[1] + 1.5;
		}
		else 
		{
			targetPosition = m_Target.GetPosition();
			targetPosition[1] = GetGame().SurfaceY(targetPosition[0], targetPosition[2]);
			
			vector clippingInfo;
			vector objectBBOX;
			
			m_Target.GetCollisionBox(objectBBOX);
			
			targetPosition[1] = (targetPosition[1] - objectBBOX[1] + clippingInfo[1] - objectBBOX[1]) + 1.5;
		}
				
		return targetPosition;
	}
}

static bool CTRL() // static functions arent scope global?
{
    return( ( KeyState( KeyCode.KC_LCONTROL ) > 0 ) || ( KeyState( KeyCode.KC_RCONTROL ) > 0 ) );
}