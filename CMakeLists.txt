# CMakeList.txt: proyecto de CMake para AB-U20-CCA, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AB-U20-CCA")

# Agregue un origen al ejecutable de este proyecto.
add_executable (AB-U20-CCA "AB-U20-CCA.cpp" "AB-U20-CCA.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AB-U20-CCA PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
