#include <windows.h>
#include <mmsystem.h>

void sonido_disparo() {
    PlaySound("Voicy_Gun_Shot.wav", NULL, SND_ASYNC);
}

void sonido_pato_caer() {
    PlaySound("Voicy_Duck_Drop.wav", NULL, SND_ASYNC);
}

void sonido_intro() {
    PlaySound("Voicy_Duck_Hunt_Intro.wav", NULL, SND_ASYNC);
}
