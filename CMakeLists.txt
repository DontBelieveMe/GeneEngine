cmake_minimum_required(VERSION 2.6)
project("GeneEngine")

# This is going to be used in every (sub) project, so its ok to put it here
include_directories(Gene/Engine/Public)

add_subdirectory(Gene)
add_subdirectory(Gene.Sandbox)
