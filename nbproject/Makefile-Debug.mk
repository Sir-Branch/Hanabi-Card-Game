#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Deck.o \
	${OBJECTDIR}/Eda_Button.o \
	${OBJECTDIR}/Eda_Menu.o \
	${OBJECTDIR}/Eda_Menu_Game.o \
	${OBJECTDIR}/Eda_Menu_Main.o \
	${OBJECTDIR}/Eda_Menu_Network.o \
	${OBJECTDIR}/Eda_Menu_Settings.o \
	${OBJECTDIR}/Eda_Textbox.o \
	${OBJECTDIR}/Hanabi_Ack_Packet.o \
	${OBJECTDIR}/Hanabi_Board.o \
	${OBJECTDIR}/Hanabi_Card.o \
	${OBJECTDIR}/Hanabi_Deck.o \
	${OBJECTDIR}/Hanabi_Discard_Packet.o \
	${OBJECTDIR}/Hanabi_Draw_Packet.o \
	${OBJECTDIR}/Hanabi_Error_Packet.o \
	${OBJECTDIR}/Hanabi_Game_Over_Packet.o \
	${OBJECTDIR}/Hanabi_IStart_Packet.o \
	${OBJECTDIR}/Hanabi_Match_Over_Packet.o \
	${OBJECTDIR}/Hanabi_Name_Is_Packet.o \
	${OBJECTDIR}/Hanabi_Name_Packet.o \
	${OBJECTDIR}/Hanabi_Play_Again_Packet.o \
	${OBJECTDIR}/Hanabi_Play_Packet.o \
	${OBJECTDIR}/Hanabi_Quit_Packet.o \
	${OBJECTDIR}/Hanabi_Skin.o \
	${OBJECTDIR}/Hanabi_Start_Info_Packet.o \
	${OBJECTDIR}/Hanabi_We_Lost_Packet.o \
	${OBJECTDIR}/Hanabi_We_Won_Packet.o \
	${OBJECTDIR}/Hanabi_You_Have_Packet.o \
	${OBJECTDIR}/Hanabi_You_Start_Packet.o \
	${OBJECTDIR}/Net_connection.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/TFTPClient.o \
	${OBJECTDIR}/TFTPCxn.o \
	${OBJECTDIR}/TFTPServer.o \
	${OBJECTDIR}/TFTP_Ack_Packet.o \
	${OBJECTDIR}/TFTP_Data_Packet.o \
	${OBJECTDIR}/TFTP_Err_Packet.o \
	${OBJECTDIR}/TFTP_Packet.o \
	${OBJECTDIR}/TFTP_Rq_Packet.o \
	${OBJECTDIR}/Token.o \
	${OBJECTDIR}/allegro_start_shutdown.o \
	${OBJECTDIR}/event_dispatcher.o \
	${OBJECTDIR}/event_handler_allegro.o \
	${OBJECTDIR}/event_handler_button_clicks.o \
	${OBJECTDIR}/event_handler_network.o \
	${OBJECTDIR}/event_handler_software.o \
	${OBJECTDIR}/hanabi_game_fsm.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/my_sleep_ms.o \
	${OBJECTDIR}/network_main_test.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5` `pkg-config --libs apr-1` `pkg-config --libs apr-util-1`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanabi-card-game

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanabi-card-game: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanabi-card-game ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Client.o: Client.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Deck.o: Deck.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Deck.o Deck.cpp

${OBJECTDIR}/Eda_Button.o: Eda_Button.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Button.o Eda_Button.cpp

${OBJECTDIR}/Eda_Menu.o: Eda_Menu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Menu.o Eda_Menu.cpp

${OBJECTDIR}/Eda_Menu_Game.o: Eda_Menu_Game.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Menu_Game.o Eda_Menu_Game.cpp

${OBJECTDIR}/Eda_Menu_Main.o: Eda_Menu_Main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Menu_Main.o Eda_Menu_Main.cpp

${OBJECTDIR}/Eda_Menu_Network.o: Eda_Menu_Network.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Menu_Network.o Eda_Menu_Network.cpp

${OBJECTDIR}/Eda_Menu_Settings.o: Eda_Menu_Settings.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Menu_Settings.o Eda_Menu_Settings.cpp

${OBJECTDIR}/Eda_Textbox.o: Eda_Textbox.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eda_Textbox.o Eda_Textbox.cpp

${OBJECTDIR}/Hanabi_Ack_Packet.o: Hanabi_Ack_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Ack_Packet.o Hanabi_Ack_Packet.cpp

${OBJECTDIR}/Hanabi_Board.o: Hanabi_Board.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Board.o Hanabi_Board.cpp

${OBJECTDIR}/Hanabi_Card.o: Hanabi_Card.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Card.o Hanabi_Card.cpp

${OBJECTDIR}/Hanabi_Deck.o: Hanabi_Deck.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Deck.o Hanabi_Deck.cpp

${OBJECTDIR}/Hanabi_Discard_Packet.o: Hanabi_Discard_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Discard_Packet.o Hanabi_Discard_Packet.cpp

${OBJECTDIR}/Hanabi_Draw_Packet.o: Hanabi_Draw_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Draw_Packet.o Hanabi_Draw_Packet.cpp

${OBJECTDIR}/Hanabi_Error_Packet.o: Hanabi_Error_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Error_Packet.o Hanabi_Error_Packet.cpp

${OBJECTDIR}/Hanabi_Game_Over_Packet.o: Hanabi_Game_Over_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Game_Over_Packet.o Hanabi_Game_Over_Packet.cpp

${OBJECTDIR}/Hanabi_IStart_Packet.o: Hanabi_IStart_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_IStart_Packet.o Hanabi_IStart_Packet.cpp

${OBJECTDIR}/Hanabi_Match_Over_Packet.o: Hanabi_Match_Over_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Match_Over_Packet.o Hanabi_Match_Over_Packet.cpp

${OBJECTDIR}/Hanabi_Name_Is_Packet.o: Hanabi_Name_Is_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Name_Is_Packet.o Hanabi_Name_Is_Packet.cpp

${OBJECTDIR}/Hanabi_Name_Packet.o: Hanabi_Name_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Name_Packet.o Hanabi_Name_Packet.cpp

${OBJECTDIR}/Hanabi_Play_Again_Packet.o: Hanabi_Play_Again_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Play_Again_Packet.o Hanabi_Play_Again_Packet.cpp

${OBJECTDIR}/Hanabi_Play_Packet.o: Hanabi_Play_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Play_Packet.o Hanabi_Play_Packet.cpp

${OBJECTDIR}/Hanabi_Quit_Packet.o: Hanabi_Quit_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Quit_Packet.o Hanabi_Quit_Packet.cpp

${OBJECTDIR}/Hanabi_Skin.o: Hanabi_Skin.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Skin.o Hanabi_Skin.cpp

${OBJECTDIR}/Hanabi_Start_Info_Packet.o: Hanabi_Start_Info_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_Start_Info_Packet.o Hanabi_Start_Info_Packet.cpp

${OBJECTDIR}/Hanabi_We_Lost_Packet.o: Hanabi_We_Lost_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_We_Lost_Packet.o Hanabi_We_Lost_Packet.cpp

${OBJECTDIR}/Hanabi_We_Won_Packet.o: Hanabi_We_Won_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_We_Won_Packet.o Hanabi_We_Won_Packet.cpp

${OBJECTDIR}/Hanabi_You_Have_Packet.o: Hanabi_You_Have_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_You_Have_Packet.o Hanabi_You_Have_Packet.cpp

${OBJECTDIR}/Hanabi_You_Start_Packet.o: Hanabi_You_Start_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hanabi_You_Start_Packet.o Hanabi_You_Start_Packet.cpp

${OBJECTDIR}/Net_connection.o: Net_connection.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Net_connection.o Net_connection.cpp

${OBJECTDIR}/Server.o: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/TFTPClient.o: TFTPClient.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTPClient.o TFTPClient.cpp

${OBJECTDIR}/TFTPCxn.o: TFTPCxn.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTPCxn.o TFTPCxn.cpp

${OBJECTDIR}/TFTPServer.o: TFTPServer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTPServer.o TFTPServer.cpp

${OBJECTDIR}/TFTP_Ack_Packet.o: TFTP_Ack_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTP_Ack_Packet.o TFTP_Ack_Packet.cpp

${OBJECTDIR}/TFTP_Data_Packet.o: TFTP_Data_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTP_Data_Packet.o TFTP_Data_Packet.cpp

${OBJECTDIR}/TFTP_Err_Packet.o: TFTP_Err_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTP_Err_Packet.o TFTP_Err_Packet.cpp

${OBJECTDIR}/TFTP_Packet.o: TFTP_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTP_Packet.o TFTP_Packet.cpp

${OBJECTDIR}/TFTP_Rq_Packet.o: TFTP_Rq_Packet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TFTP_Rq_Packet.o TFTP_Rq_Packet.cpp

${OBJECTDIR}/Token.o: Token.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Token.o Token.cpp

${OBJECTDIR}/allegro_start_shutdown.o: allegro_start_shutdown.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/allegro_start_shutdown.o allegro_start_shutdown.c

${OBJECTDIR}/event_dispatcher.o: event_dispatcher.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event_dispatcher.o event_dispatcher.cpp

${OBJECTDIR}/event_handler_allegro.o: event_handler_allegro.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event_handler_allegro.o event_handler_allegro.cpp

${OBJECTDIR}/event_handler_button_clicks.o: event_handler_button_clicks.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event_handler_button_clicks.o event_handler_button_clicks.cpp

${OBJECTDIR}/event_handler_network.o: event_handler_network.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event_handler_network.o event_handler_network.cpp

${OBJECTDIR}/event_handler_software.o: event_handler_software.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/event_handler_software.o event_handler_software.cpp

${OBJECTDIR}/hanabi_game_fsm.o: hanabi_game_fsm.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hanabi_game_fsm.o hanabi_game_fsm.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/my_sleep_ms.o: my_sleep_ms.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/my_sleep_ms.o my_sleep_ms.cpp

${OBJECTDIR}/network_main_test.o: network_main_test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_dialog-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` `pkg-config --cflags apr-1` `pkg-config --cflags apr-util-1`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network_main_test.o network_main_test.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
