
#ifndef CLIENT_DLL
#include <ammotype.h>
#else
#include <../dlls/ammotype.h>
#endif

int GetAmmoRegisterySize(void)
{
	return (int)ammoRegistery.size();
}

// Ammo storage shit
legalAmmoTypes GenerateLegalAmmoIndicies(weaponInfo wiInput)
{
	legalAmmoTypes resultLegalAmmoTypes = legalAmmoTypes();

	for (int i = 0; i < wiInput.size(); i++)
	{
		legalAmmoType resultLegalAmmoType = legalAmmoType();
		for (int y = 0; y < wiInput[i].ammoTypes.size(); y++)
		{
			for (int z = 0; z < ammoRegistery.size(); z++)
			{
				if (!strcmp(ammoRegistery[z], wiInput[i].ammoTypes[y]))
				{
					resultLegalAmmoType.insert(resultLegalAmmoType.begin() + y, z);
					break;
				}
				else
				{
					if (z == ammoRegistery.size() - 1)
						resultLegalAmmoType.insert(resultLegalAmmoType.begin() + y, -1);
				}
			}
		}
		resultLegalAmmoTypes.insert(resultLegalAmmoTypes.begin() + i, resultLegalAmmoType);
	}

	return resultLegalAmmoTypes;
}

int GetAmmoIndex(const char* psz)
{
	int i;

	if (!psz)
		return -1;

	for (i = 0; i < ammoRegistery.size(); i++)
	{
		if (!ammoRegistery[i])
			continue;

		if (stricmp(psz, ammoRegistery[i]) == 0)
			return i;
	}

	return -1;
}

int ValidAmmoIndex(int iAmmoIndex)
{
	if (iAmmoIndex > -1 && iAmmoIndex < GetAmmoRegisterySize())
		return 1;

	return 0;
}