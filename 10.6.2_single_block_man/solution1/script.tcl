############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project hls_laba_single_class
set_top dec2_2stage
add_files multirate_filters/src/10.6.2_single_block_man/dec2_2stage.cpp
add_files multirate_filters/src/10.6.2_single_block_man/dec2_2stage.h
add_files multirate_filters/src/10.6.2_single_block_man/dec2_i2.hpp
add_files multirate_filters/src/10.6.2_single_block_man/shift_class.h
add_files -tb multirate_filters/src/10.6.2_single_block_man/SingleBlockManTester.cpp
open_solution "solution1"
set_part {xc7z020clg400-1}
create_clock -period 5 -name default
source "./hls_laba_single_class/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
