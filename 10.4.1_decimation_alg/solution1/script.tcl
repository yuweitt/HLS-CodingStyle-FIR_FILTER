############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project firdec2
set_top fir_filter
add_files ../10.4.1_decimation_alg/decimate.hpp
add_files ../10.4.1_decimation_alg/fir_filter.h
add_files ../10.4.1_decimation_alg/fir_filter_decimate.cpp
add_files ../10.4.1_decimation_alg/helper.h
add_files ../10.4.1_decimation_alg/shift_class.h
add_files -tb ../10.4.1_decimation_alg/Tester.cpp 
open_solution "solution1"
set_part {xc7z020-clg400-1}
create_clock -period 5 -name default
source "./firdec2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all -tool xsim
export_design -format ip_catalog
