############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project hls_laba_interpolation_man
set_top fir_filter
add_files multirate_filters/src/10.5.2_interpolation_man/fir_filter.h
add_files multirate_filters/src/10.5.2_interpolation_man/manual_interpolate.cpp
add_files multirate_filters/src/10.5.2_interpolation_man/shift_class.h
add_files -tb multirate_filters/src/10.5.2_interpolation_man/IntrplManTester.cpp
open_solution "solution1"
set_part {xc7z020-clg400-1}
create_clock -period 5 -name default
source "./hls_laba_interpolation_man/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
