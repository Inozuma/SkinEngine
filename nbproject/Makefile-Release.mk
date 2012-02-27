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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
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
	${OBJECTDIR}/src/Parser/ParserListener.o \
	${OBJECTDIR}/src/Color.o \
	${OBJECTDIR}/src/Parser/Node.o \
	${OBJECTDIR}/src/Filesystem/File.o \
	${OBJECTDIR}/src/ElementList.o \
	${OBJECTDIR}/src/ElementImage.o \
	${OBJECTDIR}/src/ActionFocus.o \
	${OBJECTDIR}/src/ElementButton.o \
	${OBJECTDIR}/src/Screen.o \
	${OBJECTDIR}/src/Parser/Parser.o \
	${OBJECTDIR}/src/ElementInput.o \
	${OBJECTDIR}/src/Action.o \
	${OBJECTDIR}/src/Image.o \
	${OBJECTDIR}/src/Effect.o \
	${OBJECTDIR}/src/ElementVideo.o \
	${OBJECTDIR}/src/Engine.o \
	${OBJECTDIR}/src/Filesystem/Directory.o \
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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.dll: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ElementLabel.o: src/ElementLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementLabel.o src/ElementLabel.cpp

${OBJECTDIR}/src/Vector.o: src/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vector.o src/Vector.cpp

${OBJECTDIR}/src/Parser/ParserListener.o: src/Parser/ParserListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Parser
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser/ParserListener.o src/Parser/ParserListener.cpp

${OBJECTDIR}/src/Color.o: src/Color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Color.o src/Color.cpp

${OBJECTDIR}/src/Parser/Node.o: src/Parser/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Parser
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser/Node.o src/Parser/Node.cpp

${OBJECTDIR}/src/Filesystem/File.o: src/Filesystem/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Filesystem
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Filesystem/File.o src/Filesystem/File.cpp

${OBJECTDIR}/src/ElementList.o: src/ElementList.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementList.o src/ElementList.cpp

${OBJECTDIR}/src/ElementImage.o: src/ElementImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementImage.o src/ElementImage.cpp

${OBJECTDIR}/src/ActionFocus.o: src/ActionFocus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ActionFocus.o src/ActionFocus.cpp

${OBJECTDIR}/src/ElementButton.o: src/ElementButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementButton.o src/ElementButton.cpp

${OBJECTDIR}/src/Screen.o: src/Screen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Screen.o src/Screen.cpp

${OBJECTDIR}/src/Parser/Parser.o: src/Parser/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Parser
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser/Parser.o src/Parser/Parser.cpp

${OBJECTDIR}/src/ElementInput.o: src/ElementInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementInput.o src/ElementInput.cpp

${OBJECTDIR}/src/Action.o: src/Action.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Action.o src/Action.cpp

${OBJECTDIR}/src/Image.o: src/Image.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Image.o src/Image.cpp

${OBJECTDIR}/src/Effect.o: src/Effect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Effect.o src/Effect.cpp

${OBJECTDIR}/src/ElementVideo.o: src/ElementVideo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ElementVideo.o src/ElementVideo.cpp

${OBJECTDIR}/src/Engine.o: src/Engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Engine.o src/Engine.cpp

${OBJECTDIR}/src/Filesystem/Directory.o: src/Filesystem/Directory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Filesystem
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Filesystem/Directory.o src/Filesystem/Directory.cpp

${OBJECTDIR}/src/Box.o: src/Box.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Box.o src/Box.cpp

${OBJECTDIR}/src/ActionCallback.o: src/ActionCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ActionCallback.o src/ActionCallback.cpp

${OBJECTDIR}/src/Element.o: src/Element.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Element.o src/Element.cpp

${OBJECTDIR}/src/Text.o: src/Text.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Text.o src/Text.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSkinEngine.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
