############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Man
set_top dec_i1
add_files ../10.4.2_decimation_man/dec2_i2.hpp
add_files ../10.4.2_decimation_man/manual_decimate.cpp
add_files ../10.4.2_decimation_man/manual_decimate.h
add_files ../10.4.2_decimation_man/shift_class.h
add_files -tb ../10.4.2_decimation_man/Tester.cpp 
open_solution "solution1"
set_part {xc7z020-clg400-1}
create_clock -period 5 -name default
#source "./Man/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -tool xsim
export_design -format ip_catalog
