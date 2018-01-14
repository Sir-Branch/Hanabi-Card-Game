

/* 
 * File:   allegro_start_shutdown.h
 * Author: r2d2
 *
 * Created on February 18, 2016, 9:34 PM
 */

#ifndef ALLEGRO_START_SHUTDOWN_H
#define ALLEGRO_START_SHUTDOWN_H

#ifdef __cplusplus
extern "C" {
#endif

	 #include <allegro5/allegro_audio.h>
    #define AL_STARTUP_ERROR -1
    #define AL_STARTUP_SUCCESS 0

    #define EDA_DISPLAY_ICON                "Common Images Files/hanabi_icon.png"
	#define EDA_DISPLAY_TITLE				"Hanabi Card Game"
    #define BACKGROUND_MUSIC				"Music/track3.wav"

    int allegro_startup(void);
    void allegro_shut_down(void);
	
	ALLEGRO_DISPLAY * create_display(unsigned int width, unsigned int height);
    void stopMusic(ALLEGRO_SAMPLE *music);
    ALLEGRO_SAMPLE * loadPlayMusic(void);

#ifdef __cplusplus
}
#endif
   



#endif /* ALLEGRO_START_SHUTDOWN_H */

