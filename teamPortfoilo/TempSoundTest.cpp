#include "Stdafx.h"
#include "TempSoundTest.h"

HRESULT TempSoundTest::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("Peldanos", "Resources/Sounds/Peldanos Hacia la Santidad.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("por", "Resources/Sounds/Por la Via.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Dame", "Resources/Sounds/Dame Tu Tormento.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Luto", "Resources/Sounds/Luto y Estrago.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Mia", "Resources/Sounds/Hermana Mia.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("La", "Resources/Sounds/La Muerte de los Relinchos.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Coplas", "Resources/Sounds/Coplas de Incienso.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Geli", "Resources/Sounds/GelidaExpiracion.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("Lagri", "Resources/Sounds/LagrimasdeGranayOro.mp3");

	return S_OK;
}

void TempSoundTest::update(void)
{
	TEMPSOUNDMANAGER->playSoundWithKey("Peldanos");
}
