############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project hls_laba_interpolation_alg
set_top fir_filter
add_files ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/fir_filter.h
add_files ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/fir_filter_interpolate.cpp
add_files ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/helper.h
add_files ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/interpolate.hpp
add_files ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/shift_class.h
add_files -tb ../../../../Documents/pearshakes/multirate_filters/src/10.5.1_interpolation_alg/IntrplAlgTester.cpp
open_solution "solution1"
set_part {xc7z020clg400-1}
create_clock -period 5 -name default
source "./hls_laba_interpolation_alg/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
