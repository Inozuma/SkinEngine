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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ElementLabel.o \
	${OBJECTDIR}/src/Vector.o \
	${OBJECTDIR}/src/Color.o \
	${OBJECTDIR}/src/ElementList.o \
	${OBJECTDIR}/src/ElementImage.o \
	${OBJECTDIR}/src/ActionFocus.o \
	${OBJECTDIR}/src/ElementButton.o \
	${OBJECTDIR}/src/Screen.o \
	${OBJECTDIR}/src/ElementInput.o \
	${OBJECTDIR}/src/Action.o \
	${OBJECTDIR}/src/Image.o \
	${OBJECTDIR}/src/Effect.o \
	${OBJECTDIR}/src/Engine.o \
	${OBJECTDIR}/src/Box.o \
	${OBJECTDIR}/src/ActionCallback.o \
	${OBJECTDIR}/src/Element.o \
	${OBJECTDIR}/src/Text.o


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
LDLIBSOPTIONS=-lSDL -lSDL_gfx -lSDL_image -lSDL_ttf

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ElementLabel.o: nbproject/Makefile-${CND_CONF}.mk src/ElementLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementLabel.o src/ElementLabel.cpp

${OBJECTDIR}/src/Vector.o: nbproject/Makefile-${CND_CONF}.mk src/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vector.o src/Vector.cpp

${OBJECTDIR}/src/Color.o: nbproject/Makefile-${CND_CONF}.mk src/Color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Color.o src/Color.cpp

${OBJECTDIR}/src/ElementList.o: nbproject/Makefile-${CND_CONF}.mk src/ElementList.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementList.o src/ElementList.cpp

${OBJECTDIR}/src/ElementImage.o: nbproject/Makefile-${CND_CONF}.mk src/ElementImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementImage.o src/ElementImage.cpp

${OBJECTDIR}/src/ActionFocus.o: nbproject/Makefile-${CND_CONF}.mk src/ActionFocus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ActionFocus.o src/ActionFocus.cpp

${OBJECTDIR}/src/ElementButton.o: nbproject/Makefile-${CND_CONF}.mk src/ElementButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementButton.o src/ElementButton.cpp

${OBJECTDIR}/src/Screen.o: nbproject/Makefile-${CND_CONF}.mk src/Screen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Screen.o src/Screen.cpp

${OBJECTDIR}/src/ElementInput.o: nbproject/Makefile-${CND_CONF}.mk src/ElementInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementInput.o src/ElementInput.cpp

${OBJECTDIR}/src/Action.o: nbproject/Makefile-${CND_CONF}.mk src/Action.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Action.o src/Action.cpp

${OBJECTDIR}/src/Image.o: nbproject/Makefile-${CND_CONF}.mk src/Image.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Image.o src/Image.cpp

${OBJECTDIR}/src/Effect.o: nbproject/Makefile-${CND_CONF}.mk src/Effect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Effect.o src/Effect.cpp

${OBJECTDIR}/src/Engine.o: nbproject/Makefile-${CND_CONF}.mk src/Engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Engine.o src/Engine.cpp

${OBJECTDIR}/src/Box.o: nbproject/Makefile-${CND_CONF}.mk src/Box.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Box.o src/Box.cpp

${OBJECTDIR}/src/ActionCallback.o: nbproject/Makefile-${CND_CONF}.mk src/ActionCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ActionCallback.o src/ActionCallback.cpp

${OBJECTDIR}/src/Element.o: nbproject/Makefile-${CND_CONF}.mk src/Element.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Element.o src/Element.cpp

${OBJECTDIR}/src/Text.o: nbproject/Makefile-${CND_CONF}.mk src/Text.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Text.o src/Text.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
