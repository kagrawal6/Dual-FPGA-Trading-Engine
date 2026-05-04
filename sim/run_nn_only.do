# =============================================================================
# Quick one-shot: compile Board B + run only tb_nn_inference.
# Use after touching nn_inference.sv or tb_nn_inference.sv to iterate fast
# without re-running the full regression.
#
# Usage (from sim/):
#   do run_nn_only.do
# =============================================================================

do compile_board_b.do
do _run_lib.do

set tb tb_nn_inference
puts "\n==========================================="
puts " RUN NN-ONLY -- $tb"
puts "==========================================="
set result [run_one_test $tb]

puts "\n==========================================="
puts " NN-ONLY RESULT: $result"
puts "==========================================="
if {$result ne "PASS"} {
    puts " See run_logs/${tb}.log for details."
}
