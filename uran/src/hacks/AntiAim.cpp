/*
 * AntiAim.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: nullifiedcat
 */

#include "AntiAim.h"

#include "../common.h"
#include "../sdk.h"

DEFINE_HACK_SINGLETON(AntiAim);

const char* AntiAim::GetName() {
	return "ANTI-AIM";
}

AntiAim::AntiAim() {
	this->v_bEnabled = CreateConVar(CON_PREFIX "aa_enabled", "0", "Enable AntiAim");
	this->v_flPitch = CreateConVar(CON_PREFIX "aa_pitch", "-89.0", "Pitch");
	this->v_flSpinSpeed = CreateConVar(CON_PREFIX "aa_spin", "10.0", "Spin speed");
}

float spin = -180;

bool AntiAim::CreateMove(void*, float, CUserCmd* cmd) {
	if (!this->v_bEnabled->GetBool()) return true;
	if ((cmd->buttons & (IN_ATTACK | IN_USE))) return true;
	if (g_pLocalPlayer->bAttackLastTick) return true;
	spin += v_flSpinSpeed->GetFloat();
	if (spin > 180) spin = -180;
	Vector angl = Vector(v_flPitch->GetFloat(), spin, 0);
	fClampAngle(angl);
	//angl.z = 180;
	cmd->viewangles = angl;
	g_pLocalPlayer->bUseSilentAngles = true;
	return false;
}

void AntiAim::PaintTraverse(void*, unsigned int, bool, bool) {}
