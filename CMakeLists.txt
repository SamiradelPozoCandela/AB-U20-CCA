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
set(PACIENTE_FILES src/menuPacientes.cpp src/Pacientes.cpp)

set(MEDICO_FILES src/menuMedico.cpp src/Medicos.cpp)

set(CITAS_FILES src/menuCitas.cpp src/Citas.cpp)

set(REPORTE_FILES src/menuReportes.cpp src/Reportes.cpp)

set(BACKUP_FILES src/menuBackup.cpp src/Backup.cpp)

set(COMUNES_FILES src/funciones_comunes.cpp)

add_executable (AB-U20-CCA 
	"src/main.cpp" 
	${PACIENTE_FILES}
	${MEDICO_FILES}
	${CITAS_FILES}
	${REPORTE_FILES}
	${BACKUP_FILES}
	${COMUNES_FILES}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AB-U20-CCA PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
