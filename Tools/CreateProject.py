import sys
import os

def createCMakeLists(projectName, geneDir):
	cmakeLists = \
	"""cmake_minimum_required(VERSION 3.1)
set(ProjectName """ + projectName + """)\n
project(${ProjectName})\n
set(GeneLibDir """ + geneDir + """)
set(CMAKE_MODULE_PATH ${GeneLibDir}/Setup/CMake)
add_subdirectory(${GeneLibDir} LibraryBuild)
include(GeneBuild)\n
include_directories(${GeneLibDir}/Gene/Engine/Public)
include_directories(${GeneLibDir}/Dependencies/FreeType/include)

# Set your source files here
set(Source
	Source/Main.cc
)\n
gene_add_target(${ProjectName} ${Source})
gene_setup_engine_deps(${ProjectName})\n
add_custom_command(TARGET ${ProjectName} POST_BUILD \n\tCOMMAND ${CMAKE_COMMAND} -E \n\t\tcopy_directory \n\t\t\t\"${CMAKE_CURRENT_SOURCE_DIR}/Data/\" \n\t\t\t\"${CMAKE_CURRENT_BINARY_DIR}/Data/\" \n\tCOMMENT \"Copying assets\"\n)"""

	file = open("CMakeLists.txt", "w")
	file.write(cmakeLists)
	file.close()

def createDirectories():
	os.mkdir("Source")
	os.mkdir("Data")

	mainSourceFile = open("Source/Main.cc", "w")
	mainSourceFile.write("int main(int argc, char** argv)\n{\n}")
	mainSourceFile.close()

	os.makedirs("Platform/Android/res")

def createGitignore():
	gitignore = open(".gitignore", "w")
	gitignore.write("""Build/
Platform/\n
# Qt Creator 
CMakeLists.txt.user\n
# Vim files
[._]*.s[a-w][a-z]
[._]s[a-w][a-z]""")

if len(sys.argv) < 2:
	print ("Please specify a project name!!")
	exit()

projectName = sys.argv[1]
geneDir = sys.argv[2]

createCMakeLists(projectName, geneDir)
createDirectories()
createGitignore()
