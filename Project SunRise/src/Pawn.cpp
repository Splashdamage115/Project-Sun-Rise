#include "Pawn.h"

void Pawn::applyDamage(int t_damage)
{
	if (m_active)
	{
		m_currentHealth -= t_damage;

		if (m_currentHealth < 0.f)
		{
			dead();
		}
		if (m_currentHealth > m_healthMax)
		{
			m_currentHealth = m_healthMax;
		}
	}
}
