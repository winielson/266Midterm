#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "../Game_local.h"
#include "../Weapon.h"

class rvWeaponBlaster : public rvWeapon {
public:

	CLASS_PROTOTYPE(rvWeaponBlaster);

	rvWeaponBlaster(void);

	virtual void		Spawn(void);
	virtual void		Think(void);
	void				Save(idSaveGame *savefile) const;
	void				Restore(idRestoreGame *savefile);
	void					PreSave(void);
	void					PostSave(void);

protected:

	float				spreadZoom;
	bool				fireHeld;

	bool				UpdateFlashlight(void);
	void				Flashlight(bool on);

private:

	stateResult_t		State_Idle(const stateParms_t& parms);
	stateResult_t		State_Fire(const stateParms_t& parms);
	stateResult_t		State_Reload(const stateParms_t& parms);
	stateResult_t		State_Flashlight(const stateParms_t& parms);

	CLASS_STATES_PROTOTYPE(rvWeaponBlaster);
};

CLASS_DECLARATION(rvWeapon, rvWeaponBlaster)
END_CLASS

/*
================
rvWeaponBlaster::rvWeaponBlaster
================
*/
rvWeaponBlaster::rvWeaponBlaster(void) {
}

/*
================
rvWeaponBlaster::Spawn
================
*/
void rvWeaponBlaster::Spawn(void) {
	spreadZoom = spawnArgs.GetFloat("spreadZoom");
	fireHeld = false;

	SetState("Raise", 0);

	Flashlight(owner->IsFlashlightOn());
}

/*
================
rvWeaponBlaster::Save
================
*/
void rvWeaponBlaster::Save(idSaveGame *savefile) const {
	savefile->WriteFloat(spreadZoom);
	savefile->WriteBool(fireHeld);
}

/*
================
rvWeaponBlaster::Restore
================
*/
void rvWeaponBlaster::Restore(idRestoreGame *savefile) {
	savefile->ReadFloat(spreadZoom);
	savefile->ReadBool(fireHeld);
}

/*
================
rvWeaponBlaster::PreSave
================
*/
void rvWeaponBlaster::PreSave(void) {
}

/*
================
rvWeaponBlaster::PostSave
================
*/
void rvWeaponBlaster::PostSave(void) {
}


/*
================
rvWeaponBlaster::Think
================
*/
void rvWeaponBlaster::Think()
{
	rvWeapon::Think();
	if (zoomGui && owner == gameLocal.GetLocalPlayer()) {
		zoomGui->SetStateFloat("playerYaw", playerViewAxis.ToAngles().yaw);
	}
}

/*
================
rvWeaponBlaster::UpdateFlashlight
================
*/
bool rvWeaponBlaster::UpdateFlashlight(void) {
	if (!wsfl.flashlight) {
		return false;
	}

	SetState("Flashlight", 0);
	return true;
}

/*
================
rvWeaponBlaster::Flashlight
================
*/
void rvWeaponBlaster::Flashlight(bool on) {
	owner->Flashlight(on);

	if (on) {
		viewModel->ShowSurface("models/weapons/blaster/flare");
		worldModel->ShowSurface("models/weapons/blaster/flare");
	}
	else {
		viewModel->HideSurface("models/weapons/blaster/flare");
		worldModel->HideSurface("models/weapons/blaster/flare");
	}
}

/*
===============================================================================

States

===============================================================================
*/

CLASS_STATES_DECLARATION(rvWeaponBlaster)
STATE("Idle", rvWeaponBlaster::State_Idle)
STATE("Fire", rvWeaponBlaster::State_Fire)
STATE("Reload", rvWeaponBlaster::State_Reload)
STATE("Flashlight", rvWeaponBlaster::State_Flashlight)
END_CLASS_STATES

/*
================
rvWeaponBlaster::State_Idle
================
*/
stateResult_t rvWeaponBlaster::State_Idle(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		if (!AmmoAvailable()) {
			SetStatus(WP_OUTOFAMMO);
		}
		else {
			SetStatus(WP_READY);
		}

		PlayCycle(ANIMCHANNEL_ALL, "idle", parms.blendFrames);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (wsfl.lowerWeapon) {
			SetState("Lower", 4);
			return SRESULT_DONE;
		}
		if (UpdateFlashlight()) {
			return SRESULT_DONE;
		}

		if (fireHeld && !wsfl.attack) {
			fireHeld = false;
		}
		if (!clipSize) {
			if (!fireHeld && gameLocal.time > nextAttackTime && wsfl.attack && AmmoAvailable()) {
				SetState("Fire", 0);
				return SRESULT_DONE;
			}
		}
		else {
			if (!fireHeld && gameLocal.time > nextAttackTime && wsfl.attack && AmmoInClip()) {
				SetState("Fire", 0);
				return SRESULT_DONE;
			}
			if (wsfl.attack && AutoReload() && !AmmoInClip() && AmmoAvailable()) {
				SetState("Reload", 4);
				return SRESULT_DONE;
			}
			if (wsfl.netReload || (wsfl.reload && AmmoInClip() < ClipSize() && AmmoAvailable()>AmmoInClip())) {
				SetState("Reload", 4);
				return SRESULT_DONE;
			}
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}

/*
================
rvWeaponBlaster::State_Fire
================
*/
stateResult_t rvWeaponBlaster::State_Fire(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		if (wsfl.zoom) {
			nextAttackTime = gameLocal.time + (altFireRate * owner->PowerUpModifier(PMOD_FIRERATE));
			Attack(true, 1, spreadZoom, 0, 1.0f); // BIGBOY
			fireHeld = true; //changed from true
		}
		else {
			//nextAttackTime = gameLocal.time + (fireRate * owner->PowerUpModifier ( PMOD_FIRERATE ));
			nextAttackTime = gameLocal.time + (fireRate * owner->PowerUpModifier(PMOD_FIRERATE)); // BIGBOY
			Attack(false, 1, spread, 0, 1.0f); //Shoots in burst of 3
			fireHeld = true;
		}
		PlayAnim(ANIMCHANNEL_ALL, "fire", 0);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (!fireHeld && wsfl.attack && gameLocal.time >= nextAttackTime && AmmoInClip() && !wsfl.lowerWeapon) {
			SetState("Fire", 0);
			return SRESULT_DONE;
		}
		if (AnimDone(ANIMCHANNEL_ALL, 0)) {
			SetState("Idle", 0);
			return SRESULT_DONE;
		}
		if (UpdateFlashlight()) {
			return SRESULT_DONE;
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}

/*
================
rvWeaponBlaster::State_Reload
================
*/
stateResult_t rvWeaponBlaster::State_Reload(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		if (wsfl.netReload) {
			wsfl.netReload = false;
		}
		else {
			NetReload();
		}

		SetStatus(WP_RELOAD);
		PlayAnim(ANIMCHANNEL_ALL, "reload", parms.blendFrames);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (AnimDone(ANIMCHANNEL_ALL, 4)) {
			AddToClip(ClipSize());
			SetState("Idle", 4);
			return SRESULT_DONE;
		}
		if (wsfl.lowerWeapon) {
			SetState("Lower", 4);
			return SRESULT_DONE;
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}


/*
================
rvWeaponBlaster::State_Flashlight
================
*/
stateResult_t rvWeaponBlaster::State_Flashlight(const stateParms_t& parms) {
	enum {
		FLASHLIGHT_INIT,
		FLASHLIGHT_WAIT,
	};
	switch (parms.stage) {
	case FLASHLIGHT_INIT:
		SetStatus(WP_FLASHLIGHT);
		// Wait for the flashlight anim to play		
		PlayAnim(ANIMCHANNEL_ALL, "flashlight", 0);
		return SRESULT_STAGE(FLASHLIGHT_WAIT);

	case FLASHLIGHT_WAIT:
		if (!AnimDone(ANIMCHANNEL_ALL, 4)) {
			return SRESULT_WAIT;
		}

		if (owner->IsFlashlightOn()) {
			Flashlight(false);
		}
		else {
			Flashlight(true);
		}

		SetState("Idle", 4);
		return SRESULT_DONE;
	}
	return SRESULT_ERROR;
}